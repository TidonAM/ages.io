#include <WiFi.h>
#include <WebServer.h>

#include "NewPing.h"

//index html page
#include "index.h"
#include "logs.h"
#include "resident.h"

//servo
#include <ESP32Servo.h>
Servo mainServo;

//tempo rfid
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
MFRC522DriverPinSimple ss_pin(5);
MFRC522DriverSPI driver{ss_pin};
MFRC522 mfrc522{driver};

#define USE_OTHER_WIFI
// #define USE_BOTH_WIFI_AP

#define LOCAL_SSID ""
#define LOCAL_PASS ""

#define AP_SSID "ESP32Website"
#define AP_PASS "espespespesp"

#define PIN_MOTOR 25
#define GATE_OPEN 90
#define GATE_OPEN_VAR 1
#define GATE_CLOSE 0
#define ROTATION_INTERVAL 10
#define MOTOR_STEP 5

#define PIN_LED 2
#define PIN_TEMP 33
// #define PIN_DIST 32
#define PIN_FAN 13

#define DIST_MIN 10
#define DIST_MAX 100
#define PIN_DIST_E 26
#define PIN_DIST_T 27

//distance
NewPing sonar(PIN_DIST_T, PIN_DIST_E, DIST_MAX);

int SensorDistance = 0;
int MotorRotate = -1;
String gateStatus = "0";
int GateStatus = 0;
int MotorAngle = 0;
bool movingToClose = false;
int Temperature = 0;
int FanRPM = 0;
int FanSpeed = 0;
uint32_t SensorUpdate = 0;
uint32_t MotorUpdate = 0;
unsigned long lastServoMoveTime = 0;
bool LED0 = 0;
bool loopClose = false;
bool rfidDone = false;
String rfidUID = "";

char XML[2048];

char buf[32];

IPAddress Actual_IP;

IPAddress PageIP(192, 168, 1, 87);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(PIN_LED, OUTPUT); 
  pinMode(PIN_MOTOR, OUTPUT);
  pinMode(PIN_TEMP, INPUT);
  pinMode(PIN_FAN, OUTPUT);

  LED0 = false;
  int SensorDistance = 0;
  int Temperature = 0;
  int FanRPM = 0;
  digitalWrite(PIN_LED, LED0);
  mainServo.attach(PIN_MOTOR);
  mainServo.write(GATE_CLOSE);
  gateStatus = "0";
  // while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4).
  mfrc522.PCD_Init();  // Init MFRC522 board.
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);	// Show details of PCD - MFRC522 Card Reader details.
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  // disableCore0WDT();
  // disableCore1WDT();

  Serial.println("Starting Wifi Server"); 

  #ifdef USE_OTHER_WIFI
    WiFi.begin(LOCAL_SSID, LOCAL_PASS);
    // if (!WiFi.config(PageIP, gateway, subnet)) {
    //   Serial.println("STA Failed to configure");
    // }
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("IP Address: "); Serial.println(WiFi.localIP());
    Actual_IP = WiFi.localIP();
  #endif

  #ifndef USE_OTHER_WIFI
    WiFi.softAP(AP_SSID, AP_PASS);
    delay(100);
    WiFi.softAPConfig(PageIP, gateway, subnet);
    delay(100);
    Actual_IP = WiFi.softAPIP();
    Serial.print("IP address: "); Serial.println(Actual_IP);
    Serial.print("SSID: "); Serial.println(AP_SSID);
    Serial.print("PASSWORD: "); Serial.println(AP_PASS);
  #endif

  WiFi.setSleep(false);

  printWifiStatus();

  server.on("/", SendWebsite);
  server.on("/logs", SendLogs);
  server.on("/resident", SendRes);

  server.on("/xml", SendXML);
  server.on("/gateposition", ProcessGatePosition);
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - SensorUpdate) >= 50) {
    SensorUpdate = millis();
    if (sonar.ping_cm() != 0) {
      SensorDistance = sonar.ping_cm();
    }
    Temperature = temperatureRead();
  }
  GateClosing();
  rfidRead();

  server.handleClient();
}

unsigned long rfidMillis = 0;
const long interval = 500;

void rfidRead() {
  if (loopClose == false) {
    unsigned long currentMillis = millis();

    if (currentMillis - rfidMillis >= interval) {
      rfidMillis = currentMillis;
      Serial.println("rfid reading:");
      rfidUID = "";
      rfidDone = false;
      if ( !mfrc522.PICC_IsNewCardPresent()) {
        return;
      }
      // Select one of the cards.
      if ( !mfrc522.PICC_ReadCardSerial()) {
        return;
      }
      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        // Serial.print(mfrc522.uid.uidByte[i], HEX);
        rfidUID.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        rfidUID.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      rfidUID.toUpperCase();
      rfidDone = true;

    }

    // Serial.print(F(": Card UID:"));
    // MFRC522Debug::PrintUID(Serial, mfrc522.uid);
    // Serial.println();
  }
}

void GateClosing() {
  if ((millis() - lastServoMoveTime >= ROTATION_INTERVAL)) {
    lastServoMoveTime = millis();
    
    if (loopClose == true) {
      // Step the servo towards GATE_CLOSE
      if (MotorRotate > GATE_CLOSE-1) {
        MotorRotate -= MOTOR_STEP;  // Adjust this step size as needed
        mainServo.write(MotorRotate);
        movingToClose = true;
        Serial.println("Gate closing");
      } else {
        gateStatus = "0";
        loopClose = false;
        movingToClose = false;  // Servo has reached the closed position
        Serial.println("Gate closed");
      }
      
      // If distance is below the minimum, stop and reverse
      if (SensorDistance < DIST_MIN && movingToClose) {
        MotorRotate = GATE_OPEN-1;
        mainServo.write(GATE_OPEN);
        movingToClose = true;
        gateStatus = "1";
        Serial.println("Gate disrupted");
      }
    }

  }
}

void ProcessGatePosition() {
  String positionValue;

  Serial.println(MotorRotate);
  Serial.println(gateStatus);
  Serial.println(mainServo.read());

  if (server.hasArg("position")) {
    positionValue = server.arg("position");  // Get the value of 'position'
    Serial.print("Received position value: ");
    Serial.println(positionValue);
    if (positionValue == "1" && gateStatus == "0") {
      mainServo.write(GATE_OPEN);  // Move servo to 0 when touched
      MotorRotate = GATE_OPEN-1;
      movingToClose = false;
      gateStatus = "1";
      loopClose = false;
      Serial.println("Gate opened");
    } else if (positionValue == "0" && gateStatus == "1") {
        // Close the gate
        loopClose = true;
    } else {
      Serial.println("unknown pos and gate");
      Serial.println(positionValue);
      Serial.println(gateStatus);
    }
  }

  server.send(200, "text/plain", gateStatus); //Send web page

}

void ProcessButton_0() {

  LED0 = !LED0;
  digitalWrite(PIN_LED, LED0);
  Serial.print("Button 0 "); Serial.println(LED0);

  server.send(200, "text/plain", ""); //Send web page

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

void SendXML() {

  Serial.println("sendXML:");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  sprintf(buf, "<SD>%d</SD>\n", SensorDistance);
  strcat(XML, buf);

  sprintf(buf, "<T>%d</T>\n", Temperature);
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

// I think I got this code from the wifi example
