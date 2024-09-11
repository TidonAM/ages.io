#include <WiFi.h>
#include <WebServer.h>
#include "index.h"

// #define USE_OTHER_WIFI

#define LOCAL_SSID "...."
#define LOCAL_PASS "...."

#define AP_SSID "ESP32Website"
#define AP_PASS "espespespesp"

#define PIN_MOTOR 4
#define PIN_LED 2
#define PIN_TEMP 14
#define PIN_DIST 15
#define PIN_FAN 13

int SensorDistance = 0;
int MotorRotate = 0;
int Temperature = 0;
int FanRPM = 0;
int FanSpeed = 0;
uint32_t SensorUpdate = 0;
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
  digitalWrite(PIN_MOTOR, MotorRotate);

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
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - SensorUpdate) >= 50) {
    SensorUpdate = millis();
    SensorDistance = digitalRead(PIN_DIST);
    Temperature = digitalRead(PIN_TEMP);
    // Serial.print("SD");
    // Serial.println(SensorDistance);
    // Serial.print("T");
    // Serial.println(Temperature);
  }

  server.handleClient();
}

// void UpdateSlider() {

//   // many I hate strings, but wifi lib uses them...
//   String t_state = server.arg("VALUE");

//   // conver the string sent from the web page to an int
//   FanSpeed = t_state.toInt();
//   Serial.print("UpdateSlider"); Serial.println(FanSpeed);
//   // now set the PWM duty cycle
//   ledcWrite(0, FanSpeed);

//   FanRPM = map(FanSpeed, 0, 255, 0, 2400);
//   strcpy(buf, "");
//   sprintf(buf, "%d", FanRPM);
//   sprintf(buf, buf);

//   // now send it back
//   server.send(200, "text/plain", buf); //Send web page

// }

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
  // send Volts0
  // sprintf(buf, "<V0>%d.%d</V0>\n", (int) (VoltsA0), abs((int) (VoltsA0 * 10)  - ((int) (VoltsA0) * 10)));
  // strcat(XML, buf);

  // send bits1
  // sprintf(buf, "<B1>%d</B1>\n", BitsA1);
  // strcat(XML, buf);
  
  // send Volts1
  // sprintf(buf, "<V1>%d.%d</V1>\n", (int) (VoltsA1), abs((int) (VoltsA1 * 10)  - ((int) (VoltsA1) * 10)));
  // strcat(XML, buf);

  // if (LED0) {
  //   strcat(XML, "<LED>1</LED>\n");
  // }
  // else {
  //   strcat(XML, "<LED>0</LED>\n");
  // }

  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  // Serial.println(XML);

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
