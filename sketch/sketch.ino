#include <Arduino.h>

#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>
#include <NewPing.h>
#include <NewPing.h>
#include "index.h"
#include "logs.h"
#include "resident.h"
#include "vehicle.h"
#include <SoftwareSerial.h>
SoftwareSerial RFID(5,4);

#define LOCAL_SSID "paconnect"
#define LOCAL_PASS "f3hrazik"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <rdm6300.h>
#include <esp_now.h>

#define RDM6300_RX_PIN 18 // read the SoftwareSerial doc above! may need to change this pin to 10...
// SoftwareSerial RFID(18,4);

#define LOCAL_SSID "secretong_nakatago"
#define LOCAL_PASS "W0rd_per0_m4yr00ng_n0"

#define PIN_MOTOR_RPM 32
#define PIN_MOTOR_BRK 33
#define PIN_MOTOR_DIR 25

#define PIN_DIST_T 14
#define PIN_DIST_E 27
#define DIST_MAX 100

Rdm6300 rdm6300;

// NewPing sonar(PIN_DIST_T, PIN_DIST_E, DIST_MAX);

// Motor shenanigans
bool isClosing = false;
bool isReversing = false;
unsigned long motorStartTime = 0; // Variable to store the start time
const unsigned long motorDuration = 750; // 3 seconds (3000 milliseconds)
bool motorRunning = false; // Flag to check if the motor is running
bool motorOpening = false; // Track motor state (opening/closing)
// Motor shenanigans
bool isClosing = false;
bool isReversing = false;
unsigned long motorStartTime = 0; // Variable to store the start time
const unsigned long motorDuration = 750; // 3 seconds (3000 milliseconds)
bool motorRunning = false; // Flag to check if the motor is running
bool motorOpening = false; // Track motor state (opening/closing)
String gateStatus = "0";
// Overall Sensor Website Update
// Overall Sensor Website Update
uint32_t SensorUpdate = 0;
bool rfidDone = false;
String rfidUID = "";
const unsigned long interval = 50;  // Reading interval in milliseconds
const unsigned long readTimeout = 100;  // Timeout for a complete read
char c;
char XML[2048];
char buf[32];
uint8_t broadcastAddress[] = {0xCC, 0xDB, 0xA7, 0x15, 0xC4, 0xD8};

IPAddress Actual_IP;

IPAddress PageIP(192, 168, 1, 87);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

WebServer server(80);

unsigned long rfidMillis = 0;

// Function to handle the request to take a picture
void handleTakePicture() {
  Serial.println("Take picture request received"); // Debugging line
  const char *message = "take_picture"; 
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)message, strlen(message));

  if (result == ESP_OK) {
    server.send(200, "text/plain", "Signal sent to ESP32-CAM.");
  } else {
    server.send(500, "text/plain", "Error sending signal.");
  }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t send_status) {
  Serial.print("Send Status: ");
  Serial.println(send_status);

  if (send_status == ESP_OK) {
    Serial.println("Delivery Success");
  } else {
    Serial.println("Delivery Fail");
    Serial.print("MAC Address: ");
    for (int i = 0; i < 6; i++) {
      Serial.print(mac_addr[i], HEX);
      if (i < 5) Serial.print(":");
    }
    Serial.println();
  }
}

void setupESPNow() {
    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    } else {
        Serial.println("ESP-NOW initialized successfully");
    }

    // Prepare peer info
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  // Use the current channel
    peerInfo.encrypt = false; // No encryption

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
    } else {
        Serial.println("Peer added successfully");
    }

    // Register ESP-NOW send callback
    esp_now_register_send_cb(OnDataSent);
}


void SendWebsite() {
  Serial.println("sending web page");
  //TRY ADJUSTING 200MS
  server.send(200, "text/html", PAGE_MAIN);
}

void SendLogs() {
  Serial.println("sending web page");
  //TRY ADJUSTING 200MS
  server.send(200, "text/html", PAGE_LOGS);
}

void SendRes() {
  Serial.println("sending resident");
  server.send(200, "text/html", PAGE_RES);
}

void SendVeh() {
  Serial.println("sending resident");
  server.send(200, "text/html", PAGE_VEH);
}

int readUltrasonicSensor() {
    // Send a 10us pulse to trigger the sensor
    digitalWrite(PIN_DIST_T, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_DIST_T, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_DIST_T, LOW);

    // Measure the time it takes for the echo to return
    long duration = pulseIn(PIN_DIST_E, HIGH, DIST_MAX * 58); // timeout in microseconds
    if (duration == 0) {
        return -1; // Return -1 if no valid distance reading
    }

    // Calculate distance in cm
    int distance = duration / 58;
    return distance;
}

void SendXML() {

  // Serial.println("sendXML:");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  sprintf(buf, "<SD>%d</SD>\n", readUltrasonicSensor());
  sprintf(buf, "<SD>%d</SD>\n", readUltrasonicSensor());
  strcat(XML, buf);

  if (rfidDone) {
  // Ensure the RFID UID is not empty
    Serial.print("rfid:");
    Serial.println(rfidUID);
    if (rfidUID.length() > 0) {
      sprintf(buf, "<RFID>%s</RFID>\n", rfidUID.c_str());  // Use %s for strings and c_str() to convert String to C-style string
      strcat(XML, buf);  // Append RFID data to XML
    } else {
      sprintf(buf, "<RFID/>\n");  // Empty RFID tag if UID is empty
      strcat(XML, buf);
    }
    rfidDone = false;  // Reset flag for the next scan
    rfidUID = ""; 
  } else {
    sprintf(buf, "<RFID/>\n");  // Empty RFID tag if rfidDone is false
    strcat(XML, buf);
  }

  //if open, value must me closed
  if (gateStatus == "0") {
    strcat(XML, "<GPOS>0</GPOS>\n");
  } else if (gateStatus == "1") {
    strcat(XML, "<GPOS>1</GPOS>\n");
  } else {
    strcat(XML, "<GPOS>2</GPOS>\n");
  }

  strcat(XML, "</Data>\n");

  // delay(50);

  server.send(200, "text/xml", XML);

}

void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}

void stopMotor(boolean state) {
    if (state) {
        Serial.println("stopMotor()");
        digitalWrite(PIN_MOTOR_BRK, HIGH); // Activate brake
    } else {
        Serial.println("stopMotor()");
        digitalWrite(PIN_MOTOR_BRK, LOW);  // Release brake
    }
}

void runMotor(String state) {
    stopMotor(true);  // Activate brake before starting

    // Start the motor based on the given state (open or close)
    if (state == "close") {
        // Serial2.write(0);
        Serial.println("0 sent");
        digitalWrite(PIN_MOTOR_DIR, LOW);   // Send close signal to Arduino
        motorStartTime = millis();  // Set the start time for closing
        gateStatus = "0";
    } else if (state == "open") {
        // Serial2.write(1);
        Serial.println("1 sent");
        digitalWrite(PIN_MOTOR_DIR, HIGH);   // Send open signal to Arduino
        motorStartTime = millis();  // Set the start time for opening
        gateStatus = "1";
    }

    stopMotor(false);  // Release brake and start the motor
    analogWrite(PIN_MOTOR_RPM, 10); // Set motor speed
    motorRunning = true;  // Set motorRunning to true since it's now running
}

void ProcessGatePosition() {
  String positionValue;

  Serial.print("Current Gate Status: ");
  Serial.println(gateStatus);

  if (server.hasArg("position")) {
    positionValue = server.arg("position");  // Get the value of 'position'
    Serial.print("Received position value from server: ");
    Serial.println(positionValue);
    if (positionValue == "1" && gateStatus == "0") {
      runMotor("open");
      Serial.println("Gate opened");
    } else if (positionValue == "0" && gateStatus == "1") {
        // Close the gate
        runMotor("close");
    } else {
      Serial.println("unknown pos and gate");
      Serial.println(positionValue);
      Serial.println(gateStatus);
    }
  }

  server.send(200, "text/plain", gateStatus); //Send web page

}

void rfidRead() {
	if (rdm6300.get_new_tag_id()) {
    rfidUID = String(rdm6300.get_tag_id(), HEX);
    // Serial.println(rdm6300.get_tag_id(), HEX);
    Serial.println("RFID Detected");
    rfidDone = true;
  }
	/* get_tag_id returns the tag_id as long as it is near, 0 otherwise. */
	delay(10);
}

// void rfidRead() {
//   unsigned long startMillis = millis();
  
//   while (RFID.available() > 0) {
//     // Add a small delay to give the buffer time to fill if needed
//     delay(5);
//     char c = RFID.read();
//     rfidUID += c;

//     // Check for timeout to break out of the while loop if it takes too long
//     if (millis() - startMillis > readTimeout) {
//       Serial.println("RFID read timed out");
//       rfidUID = "";  // Clear buffer due to timeout
//       return;
//     }
//   }

//   // If we have a full RFID UID, mark it as done
//   if (rfidUID.length() >= 10) {
//     rfidDone = true;
//   }
// }




void setup() {
    Serial.begin(115200);
    rdm6300.begin(RDM6300_RX_PIN);

    pinMode(PIN_DIST_T, OUTPUT);
    pinMode(PIN_DIST_E, INPUT);
    pinMode(PIN_MOTOR_DIR, OUTPUT);
    pinMode(PIN_MOTOR_BRK, OUTPUT);
    pinMode(27, OUTPUT);

    digitalWrite(PIN_MOTOR_BRK, LOW); // Disengage brake (active low)
    digitalWrite(PIN_MOTOR_DIR, LOW); 
    analogWrite(PIN_MOTOR_RPM, 0);
    gateStatus = "0";

    WiFi.begin(LOCAL_SSID, LOCAL_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("IP Address: "); Serial.println(WiFi.localIP());
    Actual_IP = WiFi.localIP();

    WiFi.setSleep(false);

    setupESPNow();

    printWifiStatus();

    server.on("/", SendWebsite);
    server.on("/logs.html", SendLogs);
    server.on("/resident.html", SendRes);
    server.on("/vehicle.html", SendVeh);

    server.on("/xml", SendXML);
    server.on("/gateposition", ProcessGatePosition);
    server.on("/takePicture", handleTakePicture);
    server.begin();

    // Add WiFi and WebServer setup if needed
    // WiFi.begin(LOCAL_SSID, LOCAL_PASS);
    // ... other WiFi or server setup code
}

void loop() {
    if (motorRunning && (millis() - motorStartTime >= motorDuration)) {
        stopMotor(true);
        motorRunning = false;
        analogWrite(PIN_MOTOR_RPM, 0);
        Serial.println("Motor Stopping");
        motorOpening = !motorOpening;
    } 
    // if (!motorRunning) {
    //   if (motorOpening) {
    //       runMotor("open");  // Start the motor in the open direction
    //       Serial.println("Motor Opening");
    //   } else {
    //       runMotor("close"); // Start the motor in the close direction
    //       Serial.println("Motor Closing");
    //   }
    //   Serial.println(millis());
    // }
    if ((millis() - SensorUpdate) >= 100) {
      SensorUpdate = millis();
      rfidRead();
      server.handleClient();
    }
    // analogWrite(PIN_MOTOR_RPM, 50);
    // digitalWrite(PIN_MOTOR_BRK, HIGH);
    // Serial.println("HIGH");
    // delay(1000);
    // digitalWrite(PIN_MOTOR_BRK, LOW);
    // Serial.println("LOW");
    // delay(1000);
}








