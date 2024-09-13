#include <WiFi.h>
#include <WebServer.h>

//index html page
#include "index.h"

//Temperature
#include <OneWire.h>
#include <DallasTemperature.h>

//servo
#include <ESP32Servo.h>
Servo mainServo;

// #define USE_OTHER_WIFI

#define LOCAL_SSID "..."
#define LOCAL_PASS "..."

#define AP_SSID "ESP32Website"
#define AP_PASS "espespespesp"

#define PIN_MOTOR 25
#define PIN_LED 2
#define PIN_TEMP 33
#define PIN_DIST 32
#define PIN_FAN 13

OneWire oneWire(PIN_TEMP);
DallasTemperature sensors(&oneWire);

int SensorDistance = 0;
int MotorRotate = 0;
int Temperature = 0;
int FanRPM = 0;
int FanSpeed = 0;
uint32_t SensorUpdate = 0;
uint32_t MotorUpdate = 0;
bool LED0 = 0;

char XML[2048];

char buf[32];

IPAddress Actual_IP;

IPAddress PageIP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(PIN_LED, OUTPUT); 
  pinMode(PIN_MOTOR, OUTPUT);
  pinMode(PIN_DIST, INPUT);
  pinMode(PIN_TEMP, INPUT);
  pinMode(PIN_FAN, OUTPUT);

  LED0 = false;
  int SensorDistance = 0;
  int MotorRotate = 0;
  int Temperature = 0;
  int FanRPM = 0;
  digitalWrite(PIN_LED, LED0);
  // digitalWrite(PIN_MOTOR, MotorRotate);
  mainServo.attach(PIN_MOTOR);
  mainServo.write(180);
  delay(1000);

  sensors.begin();

  //FAN RPM
  // ledcSetup(0, 10000, 8);
  // ledcAttachPin(PIN_FAN, 0);
  // ledcWrite(0, FanSpeed);

  // disableCore0WDT();
  // disableCore1WDT();

  Serial.println("Starting Wifi Server"); 

  #ifdef USE_OTHER_WIFI
    WiFi.begin(LOCAL_SSID, LOCAL_PASS);
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

  printWifiStatus();

  server.on("/", SendWebsite);
  server.on("/xml", SendXML);
  server.on("/gateposition", ProcessGatePosition);
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - SensorUpdate) >= 50) {
    SensorUpdate = millis();
    SensorDistance = analogRead(PIN_DIST);
    sensors.requestTemperatures();
    // Temperature = analogRead(PIN_TEMP);
    Temperature = sensors.getTempCByIndex(0);
    MotorRotate = mainServo.read() + 2;
    // Serial.println(MotorRotate);
    // Serial.print("SD");
    // Serial.println(SensorDistance);
    // Serial.print("T");
    // Serial.println(Temperature);
  }

    // mainServo.write(0);
    // Serial.println(mainServo.read());
    // delay(2000);
    // mainServo.write(180);
    // Serial.println(mainServo.read());
    // delay(2000);

  server.handleClient();
}

void ProcessGatePosition() {

  String gateStatus;

  if (MotorRotate == 1) {
    mainServo.write(180);
    delay(1000);
    Serial.print("Gate Closed");
    gateStatus = "0";
  } else if (MotorRotate == 180) {
    mainServo.write(0);
    delay(1000);
    Serial.print("Gate Opened");
    gateStatus = "1";
  } else {
    Serial.print("Gate is Rotating");
    gateStatus = "2";
  }

  server.send(200, "text/plain", gateStatus); //Send web page

}

void ProcessButton_0() {

  LED0 = !LED0;
  digitalWrite(PIN_LED, LED0);
  Serial.print("Button 0 "); Serial.println(LED0);

  server.send(200, "text/plain", ""); //Send web page

  // option 2 -- keep page live AND send a status
  // if you want to send feed back immediataly
  // note you must have reading code in the java script
  /*
    if (LED0) {
    server.send(200, "text/plain", "1"); //Send web page
    }
    else {
    server.send(200, "text/plain", "0"); //Send web page
    }
  */

}

void SendWebsite() {

  Serial.println("sending web page");
  //TRY ADJUSTING 200MS
  server.send(200, "text/html", PAGE_MAIN);

}

void SendXML() {

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  sprintf(buf, "<SD>%d</SD>\n", SensorDistance);
  strcat(XML, buf);

  sprintf(buf, "<T>%d</T>\n", Temperature);
  strcat(XML, buf);

  if (MotorRotate == 1) {
    strcat(XML, "<GPOS>0</GPOS>\n");
  } else if (MotorRotate == 180) {
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
