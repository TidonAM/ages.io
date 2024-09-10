#include <WiFi.h>
#include <WebServer.h>
#include "SuperMon.h"

// #define USE_INTRANET

#define LOCAL_SSID "car"
#define LOCAL_PASS "111"

#define AP_SSID "ESP32Website"
#define AP_PASS "espesp"

#define PIN_MOTOR 26
#define PIN_LED 2

// variables to store sensor data

int SensorDistance = 0;
int MotorRotate = 0;
uint32_t SensorUpdate = 0;
bool LED = 0;

char XML[2048];

char buf[32];

IPAddress Actual_IP;

IPAddress PageIP (192, 168, 1, 1);
IPAddress gateway (192, 168, 1, 1);
IPAddress subnet (255, 255, 255, 0);
IPAddress ip;

WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_MOTOR, OUTPUT); 

  LED = false;
  digitalWrite(PIN_LED, LED0);

  disableCore1WDT();

  Serial.println("Starting Wifi Server"); 

  #ifdef USE_INTRANET
    WiFi.begin(LOCAL_SSID, LOCAL_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("IP Address: "); Serial.println(WiFi.localIP());
    Actual_IP = WiFi.localIP();
  #endif

    printWifiStatus();

  // these calls will handle data coming back from your web page
  // this one is a page request, upon ESP getting / string the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
  // just parts of the web page
  server.on("/xml", SendXML);

  // upon ESP getting /UPDATE_SLIDER string, ESP will execute the UpdateSlider function
  // same notion for the following .on calls
  // add as many as you need to process incoming strings from your web page
  // as you can imagine you will need to code some javascript in your web page to send such strings
  // this process will be documented in the SuperMon.h web page code
  server.on("/UPDATE_SLIDER", UpdateSlider);
  server.on("/BUTTON_0", ProcessButton_0);
  // server.on("/BUTTON_1", ProcessButton_1);

  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - SensorUpdate) >= 50) {
    //Serial.println("Reading Sensors");
    SensorUpdate = millis();
    SensorDistance = analogRead(PIN_A0);

  }

  // no matter what you must call this handleClient repeatidly--otherwise the web page
  // will not get instructions to do something
  server.handleClient();
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

// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code

// same notion for processing button_1

void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  sprintf(buf, "<SD>%d</SD>\n", SensorDistance);
  strcat(XML, buf);
  // send Volts0
  sprintf(buf, "<V0>%d.%d</V0>\n", (int) (VoltsA0), abs((int) (VoltsA0 * 10)  - ((int) (VoltsA0) * 10)));
  strcat(XML, buf);

  // send bits1
  // sprintf(buf, "<B1>%d</B1>\n", BitsA1);
  // strcat(XML, buf);
  
  // send Volts1
  // sprintf(buf, "<V1>%d.%d</V1>\n", (int) (VoltsA1), abs((int) (VoltsA1 * 10)  - ((int) (VoltsA1) * 10)));
  // strcat(XML, buf);

  // show led0 status
  if (LED0) {
    strcat(XML, "<LED>1</LED>\n");
  }
  else {
    strcat(XML, "<LED>0</LED>\n");
  }

  if (SomeOutput) {
    strcat(XML, "<SWITCH>1</SWITCH>\n");
  }
  else {
    strcat(XML, "<SWITCH>0</SWITCH>\n");
  }

  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  Serial.println(XML);

  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
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
