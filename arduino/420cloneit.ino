/*

 This example connects to an unencrypted Wifi network.
 Then it prints the  MAC address of the Wifi shield,
 the IP address obtained, and other network details.

 Circuit:
 * WiFi shield attached

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFi101.h>
#include <DHT.h>

char ssid[] = "trackpadia";     //  your network SSID (name)
char pass[] = "sk3leton";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
//char server[] = "www.google.com";    // name address for Google (using DNS)

WiFiClient client;

#define DHTPIN 6 // SENSOR PIN
#define DHTTYPE DHT22 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS
DHT dht(DHTPIN, DHTTYPE);

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL

int t = 0;  // TEMPERATURE VAR
int h = 0;  // HUMIDITY VAR
bool heat = false;
bool light = false;
bool humidifier = false;
bool fans = false;


String data;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();

  dht.begin(); 
  delay(10000); // GIVE THE SENSOR SOME TIME TO START

  h = (int) dht.readHumidity(); 
  t = (int) dht.readTemperature(true); 
  heat = false;
  light = false;
  humidifier = false;
  fans = false;
  

  data = "";

}

void loop() {
  // check the humidity sensor only once every 10 seconds:
  currentMillis = millis();
  if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
    previousMillis = currentMillis;
    h = (int) dht.readHumidity();
    t = (int) dht.readTemperature(true);
  }

  // Set control variables
  heat = false;
  light = false;
  humidifier = false;
  fans = false;

  // data = "temp1=" + String(t) + "&hum1=" + String(h);
  data = "temp1=" + String(t) + "&hum1=" + String(h) + "&heat=" + String(heat) + "&light=" + int(light) + "&humidifier=" + int(humidifier) + "&fans=" + int(fans);
  if (client.connect("192.168.2.3",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /add.php HTTP/1.1"); 
    client.println("Host: 192.168.2.3"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
  } 
  Serial.println("Posted Data");
  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
   
  delay(300000); // WAIT Five MINUTES BEFORE SENDING AGAIN

  // delay(20000); // Use for debugging, logs ever 20 seconds
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);

}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

