#include <WiFi.h>
#include <WebServer.h>

#include "NewPing.h"

//index html page
#include "index.h"
#include "logs.h"
#include "resident.h"
#include "vehicle.h"

#define LOCAL_SSID "paconnect"
#define LOCAL_PASS "f3hrazik"

#define PIN_MOTOR_RPM 37
#define PIN_MOTOR_BRK 34
#define PIN_MOTOR_DIR 32
#define PIN_ARD_RX 5
#define PIN_ARD_TX 12

#define PIN_DIST_T 26
#define PIN_DIST_E 27
#define DIST_MAX 100

NewPing sonar(PIN_DIST_T, PIN_DIST_E, DIST_MAX);

//Motor shenanigans
bool isClosing = false;
bool isReversing = false;
unsigned long motorStartTime = 0; // Variable to store the start time
const unsigned long motorDuration = 3000; // 3 seconds (3000 milliseconds)
bool motorRunning = false; // Flag to check if the motor is running

//Overall Sensor Website Update
uint32_t SensorUpdate = 0;

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, PIN_ARD_RX, PIN_ARD_TX);
    pinMode(PIN_MOTOR_BRK, OUTPUT);
    pinMode(PIN_MOTOR_DIR, OUTPUT);
    
}

void loop() {
    runMotor('close');
    delay(3000);
    runMotor('open');
    if (motorRunning && (millis() - motorStartTime >= motorDuration)) {
        stopMotor(true);
        motorRunning = false;
        analogWrite(PIN_MOTOR_RPM, 0);
    }
}

void runMotor(string State) {
    stopMotor(true);
    if (state == 'close') {
        Serial2.println(0);
        motorOpening = false;
    } else if (state == 'open'){
        Serial2.println(1);
        motorOpening = true;
    }
    stopMotor(false);
    analogWrite(PIN_MOTOR_RPM, 50);
}

void stopMotor(boolean state){
    if (state == true) {
        digitalWrite(PIN_MOTOR_BRK, HIGH);
    } else {
        digitalWrite(PIN_MOTOR_BRK, LOW);
    }
}

int readUltrasonicSensor() {
    if (sonar.ping_cm() != 0) {
        return distance;
    }
}