/*
Copyright 2017 Google LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include <Time.h>
#include "Credentials.h"

#define SERVO_PIN 14

// Servo Positions and Intent specific Numbers

#define CENTER_POSITION 90

// Crypto Currency
#define CURRENCY_UP 180
#define CURRENCY_DOWN 0
#define CURRENCY_NO_CHANGE 90



// Test Signal
#define TEST_FIRST_POSITION 10
#define TEST_SECOND_POSITION 170
#define TEST_NUM_SWINGS 5

class PaperSignals
{
public:
  PaperSignals() {};
  ~PaperSignals() {};

  void StartUp();
  String getJson(String host, String url);
  String getJsonHTTP(String host, String url);
  void ParseIntentName(String intentName, String JSONData);
  String getSignalByID(String signalID);
  void RunPaperSignals();

  // Intent Types
  
  String UmbrellaType = "Umbrella";
  String TimerType = "Timer";
  

  String CountdownType = "Countdown";
  String TestSignalType = "TestSignal";

  String CustomIntentType = "move";

  String currentIntent = "";
  String currentIntentTimeStamp = "";
  bool updatedIntentTimeStamp = true;

  unsigned long lastWeatherCall = 0;
  unsigned long timeBetweenWeatherCalls = 120000;
  bool throttleWeatherAPI();


  

public:

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  const int httpsPort = 443;

  // Signal Functions
  void DefaultExecution(String JSONData);
  void CountdownExecution(String JSONData);
  
  void UmbrellaExecution(String JSONData);

  void TestSignalExecution();
  void StockExecution(String JSONData);
  void CustomExecution(String JSONData);
  String GetWeather(String JSONData);
  String GetLatLong(String JSONData);


  void MoveServoToPosition(int position, int speed);

  double initialBitcoin;
  double initialEthereum;

  int lastTimerTime = 0;

  unsigned long breakTimeLength = 60000; // 1 Minute Default
  unsigned long breakTimeInterval = 900000; // 15 Minute Default
  unsigned long lastBreakTime = 0;

  unsigned long rocketStartedTime = 0;
  boolean rocketLaunched = false;

  int numTestServoSwings = 0;

  String mostRecentDateString = "";
  String NextRocketLaunchTime = "";

  Servo myservo;
  int currentServoPosition = 0;
};

