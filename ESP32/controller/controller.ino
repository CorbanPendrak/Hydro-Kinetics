/*
  File: two_way_communication_2.ino
  Author: Corban Pendrak
  Purpose: Provide two way communciation for ESP32 boards
  Date Last Modified: 11/30/2023
*/

#include <esp_now.h>
#include <WiFi.h>
#include "uRTCLib.h"

// Replace with the MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x70, 0xb8, 0xf6, 0x5d, 0x7b, 0xb0};

esp_now_peer_info_t peerInfo;

// Self-gathered data
float temp;
float hum;
long current_time;

// Incoming data
float sender_temperature;
float sender_humidity;
long sender_time;

// Stores whether sending data was successful
String success;

// Must match the receiver structure
typedef struct struct_message {
    float temp;
    float hum;
    long current_time;
} struct_message;

// Create struct_message to hold this board's data to send
struct_message this_readings;

// Create struct_message to hold other board's data
struct_message sender_readings;

// uRTCLib rtc;
uRTCLib rtc(0x68);

/* 
  Input/Output functions
  Determines the outside world connection
*/

// Program input: hardcoded values
void getReadings(){
  
  hum = 8;
  temp = 5;

  if (isnan(hum) || isnan(temp)  ){
    Serial.println("Failed to read from sensor!");
    return;
  }

  current_time = rtc.hour() * 10000 + rtc.minute() * 100 + rtc.second();

}

// Program output: Serial Monitor 
void display_data(){
  Serial.println("INCOMING READINGS");
  Serial.print("Temperature: ");
  Serial.print(sender_readings.temp);
  Serial.println(" ºC");
  Serial.print("Humidity: ");
  Serial.print(sender_readings.hum);
  Serial.println(" %");
  Serial.print("Time: ");
  Serial.print(sender_readings.current_time);
  Serial.println();
}

/*
  Callback functions- what the program does when data is sent or received.
  Determines the reactions of the program
*/

// Callback when data is sent
void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success";
  }
  else{
    success = "Delivery Fail";
  }
}

// Callback when data is received
void data_receive(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&sender_readings, incomingData, sizeof(sender_readings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  sender_temperature = sender_readings.temp;
  sender_humidity = sender_readings.hum;
  sender_time = sender_readings.current_time;
}

/*
  Main functions
  Determines regular action of program
*/
 
// Run once to setup the board
void setup() {
  // Start Serial Monitor and pause to connect
  Serial.begin(115200);
  delay(3000);

  // Setup date and time
  URTCLIB_WIRE.begin();
  
  // Set device as WiFi station
  WiFi.mode(WIFI_STA);
  
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Connect function on data send
  esp_now_register_send_cb(data_sent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;   

  // Add peer    
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  // Connect function on data received
  esp_now_register_recv_cb(data_receive);
}
 
// Main loop
void loop() {
  getReadings();
 
  this_readings.temp = temp;
  this_readings.hum = hum;
  
  Serial.println(this_readings.temp);

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &this_readings, sizeof(this_readings));
   
  
  Serial.print(WiFi.macAddress());
  if (result == ESP_OK) {
    Serial.print(" sent to ");
  }
  else {
    Serial.print(" did not send to ");
  }
  for (int i = 0; i < 6; i++) {
    Serial.print(broadcastAddress[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");

  display_data();
  delay(10000);
}

/*
TODO:
  MAC Address printing function
  Remove placeholding variables outside of structure
  Seperate structure for sending and receiving boards
  Add input for MAC Address
  Loop search for other device
  Enable Graphing
  More documentation
*/