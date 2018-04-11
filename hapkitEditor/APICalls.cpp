



#include "APICalls.h"



#define PRINT_PAYLOAD

String urlencode(String str)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
}

int days_in_month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

int leap_year(int year) {
    if(year%400==0) return 1;

    if(year%4==0 && year%100!=0) return 1;

    return 0;
}

int number_of_days(int year, int day, int month) {
    int result = 0;
    int i;

    for(i=1; i < year; i++) {
        if(leap_year(i))
            result += 366;
        else
            result += 365;
    }

    for(i=1; i < month; i++) {
        result += days_in_month[i];

        if(leap_year(year) && i == 2) result++;
    }

    result += day;
    return result;
}

String makeLessPrettyJSON(String JSONData)
{
  String notPretty = "";
  for(int i = 0; i < JSONData.length(); i++)
  {
    if(JSONData.charAt(i) != '\n' && JSONData.charAt(i) != '\r' &&
      JSONData.charAt(i) != ' ' && JSONData.charAt(i) != '  ' &&
      JSONData.charAt(i) != '[' && JSONData.charAt(i) != ']')
    {
      notPretty += JSONData.charAt(i);
    }
  }

  return notPretty;
}

void PaperSignals::StartUp()
{
  client.setNoDelay(1);
  client.setTimeout(2000);
  myservo.attach(SERVO_PIN);
  MoveServoToPosition(CENTER_POSITION, 10); // Initialize
}

void PaperSignals::MoveServoToPosition(int position, int speed)
{
  
  if(position < currentServoPosition)
  {
    for(int i = currentServoPosition; i > position; i--)
    {
      myservo.write(i);
      delay(speed);
    }
  }
  else if(position > currentServoPosition)
  {
    for(int i = currentServoPosition; i < position; i++)
    {
      myservo.write(i);
      delay(speed);
    }
  }

  currentServoPosition = position;
}

void PaperSignals::DefaultExecution(String JSONData)
{
    Serial.println("Default");
}





bool PaperSignals::throttleWeatherAPI()
{
  if(millis() < lastWeatherCall) lastWeatherCall = 0; // Reset every 49 days

  if(!updatedIntentTimeStamp && millis() - lastWeatherCall < timeBetweenWeatherCalls) return true;
  lastWeatherCall = millis();

  return false;
}




// Performs Geocoding and a dark sky call to
String PaperSignals::GetWeather(String Location)
{
  String latLong = GetLatLong(Location);

  String curTimeHost = "currentmillis.com";
  String curTimeURL = "/time/minutes-since-unix-epoch.php";
  String unixTime = getJsonHTTP(curTimeHost, curTimeURL);

  unsigned long unixTimeLong = atol(unixTime.c_str())*60;
  String finalUnixTime = String(unixTimeLong);

  String weatherHost = "api.darksky.net";
  String weatherURL = "/forecast/" + DarkSkyAPIKey + "/" + latLong + "," + finalUnixTime + "?exclude=minutely,flags,hourly,currently,alerts";

  // Get Weather
  String weatherPayload = getJson(weatherHost, weatherURL);
  Serial.println(weatherPayload);

  return weatherPayload;
}

// This function handles the Google Geocoding API Pretty Print Output
String PaperSignals::GetLatLong(String Location)
{
  Location = urlencode(Location);
  Serial.println("Location: ***************");
  Serial.println(Location);
  Serial.println("location end");
  char*  geoHost = "maps.googleapis.com";
  String geoURL = "/maps/api/geocode/json?address=" + Location + "&key=" + GeoCodingAPiKey;
  Serial.println(geoURL);

  // Get Lat Long
  String LatLongPayload = getJson(geoHost, geoURL);
  Serial.println(LatLongPayload);

  int index = LatLongPayload.indexOf("lat");

  Serial.println(index);
  boolean foundColon = false;
  String latString = "";
  for(int i = index; i < index+20; i++)
  {
    if(LatLongPayload.charAt(i) == ':')
    {
      foundColon = true;
    }
    else if(foundColon)
    {
      if(LatLongPayload.charAt(i) == ',') break;
      latString += LatLongPayload.charAt(i);
    }
  }

  latString.trim();
  Serial.print("Lat String: ");
  Serial.println(latString);

  index = LatLongPayload.indexOf("lng");

  Serial.println(index);
  foundColon = false;
  String lngString = "";
  for(int i = index; i < index+20; i++)
  {
    if(LatLongPayload.charAt(i) == ':')
    {
      foundColon = true;
    }
    else if(foundColon)
    {
      if(LatLongPayload.charAt(i) == '\n'| LatLongPayload.charAt(i) == '\r') break;
      lngString += LatLongPayload.charAt(i);
    }
  }

  lngString.trim();
  Serial.print("Lng String: ");
  Serial.println(lngString);

  return latString + "," + lngString;

}


void PaperSignals::CountdownExecution(String JSONData)
{
  DynamicJsonBuffer countDownBuffer;
  JsonObject& countDownRoot = countDownBuffer.parseObject(JSONData);
  String timeStamp = countDownRoot["timestamp"];

  // GET START DATE
  int startYear = (timeStamp.charAt(0)-'0')*1000 + (timeStamp.charAt(1)-'0')*100 + (timeStamp.charAt(2)-'0')*10 + (timeStamp.charAt(3)-'0');
  int startMonth = (timeStamp.charAt(5)-'0')*10 + (timeStamp.charAt(6)-'0');
  int startDay = (timeStamp.charAt(8)-'0')*10 + (timeStamp.charAt(9)-'0');

  Serial.print("TimeStamp Year: "); Serial.print(startYear); Serial.print("; Month: "); Serial.print(startMonth); Serial.print("; Day: "); Serial.println(startDay);

  // GET CURRENT DATE
  int curYear = 0;
  int curMonth = 0;
  int curDay = 0;
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  for(int i = 0; i < 12; i++)
  {
    int monthIndex = mostRecentDateString.indexOf(months[i]);
    if(monthIndex != -1)
    {
      curMonth = i+1;

      curDay = ((mostRecentDateString.charAt(monthIndex - 3) - '0')*10) + (mostRecentDateString.charAt(monthIndex - 2) - '0');
      curYear = ((mostRecentDateString.charAt(monthIndex + 4) - '0')*1000) + ((mostRecentDateString.charAt(monthIndex + 5) - '0')*100) + ((mostRecentDateString.charAt(monthIndex + 6) - '0')*10) + (mostRecentDateString.charAt(monthIndex + 7) - '0');
    }
  }
  Serial.print("Current Year: "); Serial.print(curYear); Serial.print("; Month: "); Serial.print(curMonth); Serial.print("; Day: "); Serial.println(curDay);

  // GET DESTINATION DATE
  String destTime = countDownRoot["parameters"]["date"];

  int destYear = (destTime.charAt(0)-'0')*1000 + (destTime.charAt(1)-'0')*100 + (destTime.charAt(2)-'0')*10 + (destTime.charAt(3)-'0');
  int destMonth = (destTime.charAt(5)-'0')*10 + (destTime.charAt(6)-'0');
  int destDay = (destTime.charAt(8)-'0')*10 + (destTime.charAt(9)-'0');
  Serial.print("Dest Year: "); Serial.print(destYear); Serial.print("; Month: "); Serial.print(destMonth); Serial.print("; Day: "); Serial.println(destDay);

  int destDays = number_of_days(destYear, destDay, destMonth);
  int curDays = number_of_days(curYear, curDay, curMonth);
  int startDays = number_of_days(startYear, startDay, startMonth);

  int totalDays = destDays - startDays;
  int daysLeft = destDays - curDays;

  Serial.print("Days Left: "); Serial.println(daysLeft);

  if(daysLeft <= 0) // Countdown done
  {
    Serial.println("Countdown Complete");
  }
  else
  {
    double percentComplete = 1.0 - ((double)daysLeft / (double)totalDays);
    Serial.print("Percent Complete: "); Serial.println(percentComplete);
  }
}

void PaperSignals::TestSignalExecution()
{
  while(numTestServoSwings < TEST_NUM_SWINGS)
  {
    MoveServoToPosition(TEST_FIRST_POSITION, 10);
    MoveServoToPosition(TEST_SECOND_POSITION, 10);
    numTestServoSwings++;
  }
}




void PaperSignals::ParseIntentName(String intentName, String JSONData)
{
    if(intentName == "weather")
    {
      
    }
    else if(intentName == "time_wheel-no")
    {
   
    }
    else if(intentName == "time_wheel-yes")
    {
      
    }else if(intentName == TestSignalType){
      
    }
    

    else if(intentName.equalsIgnoreCase(CustomIntentType))
    {
      CustomExecution(JSONData);
    } else
    {
      DefaultExecution(JSONData);
    }
}

String PaperSignals::getSignalByID(String signalID){
    char* host = "https://hapkit-editor.firebaseio.com";
    String url = "/"".json";

    String payload = getJson(host, url);

    DynamicJsonBuffer jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(payload);

    // Test if parsing succeeds.
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return "bad";
    }
    else
    {
      int len = (root["result"]).measureLength();
      char signalInfo[len+1];
      (root["result"]).printTo(signalInfo, len+1);
      String intentName = root["result"]["metadata"]["intentName"];
      String intentTimeStamp = root["result"]["timestamp"];
      
      if(intentTimeStamp != currentIntentTimeStamp)
      {
        updatedIntentTimeStamp = true;
        numTestServoSwings = 0;
      }
      else {
        updatedIntentTimeStamp = false;
      }
      
      currentIntent = intentName;
      currentIntentTimeStamp = intentTimeStamp;

      return signalInfo;
    }
}

String PaperSignals::getJson(String host, String url){

    Serial.print("connecting to ");
    Serial.println(host);

    if (!client.connect(host.c_str(), httpsPort)) {
    

    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(SSID.c_str(), Password.c_str());
      delay(250);
      Serial.print(".");
    }
      Serial.println("connection failed");
      return "bad";
    }

    Serial.print("requesting URL ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: BuildFailureDetectorESP8266\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("request sent");

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if(line.indexOf("Date") != -1)
      {
        mostRecentDateString = line;
      }
      Serial.println(line);
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }

    String payload = client.readString();

    #ifdef PRINT_PAYLOAD
        Serial.println("reply was:");
        Serial.println("==========");
        Serial.println(payload);
        Serial.println("==========");
    #endif
    return payload;
}

String PaperSignals::getJsonHTTP(String host, String url){

    HTTPClient http;
    String payload;

    Serial.print("[HTTP] begin...\n");

    http.begin("http://"+host+url); //HTTP

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            payload = http.getString();
        }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();


    #ifdef PRINT_PAYLOAD
        Serial.println("reply was:");
        Serial.println("==========");
        Serial.println(payload);
        Serial.println("==========");
    #endif
    return payload;
}
void PaperSignals::RunPaperSignals()
{
  String JSONData = getSignalByID(SignalID.c_str());
  ParseIntentName(currentIntent, JSONData);
  Serial.println("RUN WORKED!!!!!!!!!!!!!!!!!!!!!!!!!");
}
