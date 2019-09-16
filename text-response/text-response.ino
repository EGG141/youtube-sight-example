/*
 * YouTube Sight ESP8266 Text Response Example 
 * http://tools.tastethecode.com/youtube-sight
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>

/* Set these to your desired credentials. */
const char *ssid = "WiFIName";  //ENTER YOUR WIFI SETTINGS
const char *password = "WiFiPassword";

//required for non blocking delay implementation
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
bool first_run = true;

//delay interval 60 seconds
const long interval = 60000;

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  HTTPClient http;    //Declare object of class HTTPClient
  currentMillis = millis();

  if (currentMillis - previousMillis >= interval || first_run) {
    first_run = false;
    // save the last time you checked 
    previousMillis = currentMillis;

    //REPLACE THE URL HERE WITH YOUR OWN!
    http.begin("http://tools.tastethecode.com/api/youtube-sight/681cbbcd-41b2-4bd5-92e4-621d052f4daf");
    
    int httpCode = http.GET();            //Send the request
    String payload = http.getString();    //Get the response payload
  
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    
    //print splitted data 
    if (httpCode == 200) {
      Serial.println("views: " + getValue(payload, ',', 0));
      Serial.println("subscribers_gained: " + getValue(payload, ',', 1));
      Serial.println("subscribers_lost: " + getValue(payload, ',', 2));
      Serial.println("subscribers_count: " + getValue(payload, ',', 3));
      Serial.println("estimated_minutes_watched: " + getValue(payload, ',', 4));
      Serial.println("average_view_duration: " + getValue(payload, ',', 5));
    }
    http.end();  //Close connection
  }
  
  //rest of your application code
}

//function to get a specific part of the combined string response
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
