#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#include <stdlib.h>

#include <U8g2lib.h>
#include <Wire.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

const char *ssid = "Tafel-Counter";
const char *password = "ChangeMe";

String host = "10.3.141.1:3000";

#define ROTARY_ENCODER_A_PIN 13
#define ROTARY_ENCODER_B_PIN 12
#define ROTARY_ENCODER_BUTTON_PIN 14

#define ROTARY_ENCODER_VCC_PIN -1

#define ROTARY_ENCODER_STEPS 4

const int SHORT_PRESS_TIME = 500;
int lastState = HIGH;
int currentState;
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

unsigned long acceletation = 100;
bool circleValues = false;
int minValue = 0;
int maxValue = 9999;

static unsigned long lastTimePressed = 0;

void rotary_onLongButtonClick()
{
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" + host + "/" + rotaryEncoder.readEncoder()); //HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST("");

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

    delay(50);

    getCurrentNumber();

    rotaryEncoder.setEncoderValue(rotaryEncoder.readEncoder() + 1);
  }
}

void rotary_onShortButtonClick()
{
  rotaryEncoder.setEncoderValue(rotaryEncoder.readEncoder() + 1);
}

void rotary_loop()
{
  if (rotaryEncoder.encoderChanged())
  {
    u8g2.setCursor(9, 35);
    u8g2.printf("%04d", rotaryEncoder.readEncoder());
    u8g2.sendBuffer();
    Serial.print("Value: ");
    Serial.println(rotaryEncoder.readEncoder());
  }

  currentState = digitalRead(ROTARY_ENCODER_BUTTON_PIN);

  if (lastState == HIGH && currentState == LOW)       // button is pressed
    pressedTime = millis();
  else if (lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if ( pressDuration <= SHORT_PRESS_TIME && pressDuration != 0) {
      rotary_onShortButtonClick();
    } else {
      rotary_onLongButtonClick();
    }
  }

  lastState = currentState;
}

void setDisplayNormal() {
  u8g2.clear();

  u8g2.drawStr(4, 10, "Nachste:");
  u8g2.drawStr(68, 10, "Aktuell:");
  u8g2.sendBuffer();

  u8g2.setCursor(9, 35);
  u8g2.printf("%04d", rotaryEncoder.readEncoder());
  u8g2.sendBuffer();
}

uint16_t getCurrentNumber() {
  uint16_t currenltyDisplayedNumberServer = 0;
  
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  // configure traged server and url
  http.begin(client, "http://" + host + "/"); //HTTP
  http.addHeader("Content-Type", "application/json");

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header and body
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      const String& payload = http.getString();
      Serial.println("received payload:\n<<");
      Serial.println(payload);
      Serial.println(">>");
      currenltyDisplayedNumberServer = strtol(payload.substring(payload.lastIndexOf(':') + 1, payload.length() - 1).c_str(), NULL, 0);
      Serial.println(currenltyDisplayedNumberServer);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

  u8g2.setCursor(73, 35);
  u8g2.printf("%04d", currenltyDisplayedNumberServer);
  u8g2.sendBuffer();

  return currenltyDisplayedNumberServer;
}

void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder.readEncoder_ISR();
}

void setup()
{
  Serial.begin(115200);

  u8g2.begin();
  u8g2.setFont(u8g2_font_timB10_tf);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    u8g2.clear();
    delay(500);
    u8g2.drawStr(0, 5, ".");
    u8g2.sendBuffer();
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  setDisplayNormal();

  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(minValue, maxValue, circleValues);
  rotaryEncoder.setAcceleration(acceletation);

  getCurrentNumber();
}

void loop()
{
  rotary_loop();
  delay(50);
}
