/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL7lQMl89Q"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "MuQHgY0EqIsPYjqcXRwrsj7uVHea6ptr"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define RelayPin1 5  //D1
#define RelayPin2 4  //D2
#define RelayPin3 14 //D5
#define RelayPin4 12 //D6

#define SwitchPin1 10  //SD3
#define SwitchPin2 0   //D3 
#define SwitchPin3 13  //D7
#define SwitchPin4 3   //RX

#define wifiLed   16   //D0

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4

int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 1; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 1; //Define integer to remember the toggle state for relay 4

int wifiFlag = 0;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TP-LINK_2C0722_plus";
char pass[] = "india.1999";

BlynkTimer timer;

void relayOnOff(int relay){

    switch(relay){
      case 1: 
             if(toggleState_1 == 1){
              digitalWrite(RelayPin1, LOW); // turn on relay 1
              toggleState_1 = 0;
              Serial.println("Device1 ON");
              }
             else{
              digitalWrite(RelayPin1, HIGH); // turn off relay 1
              toggleState_1 = 1;
              Serial.println("Device1 OFF");
              }
             delay(100);
      break;
      case 2: 
             if(toggleState_2 == 1){
              digitalWrite(RelayPin2, LOW); // turn on relay 2
              toggleState_2 = 0;
              Serial.println("Device2 ON");
              }
             else{
              digitalWrite(RelayPin2, HIGH); // turn off relay 2
              toggleState_2 = 1;
              Serial.println("Device2 OFF");
              }
             delay(100);
      break;
      case 3: 
             if(toggleState_3 == 1){
              digitalWrite(RelayPin3, LOW); // turn on relay 3
              toggleState_3 = 0;
              Serial.println("Device3 ON");
              }
             else{
              digitalWrite(RelayPin3, HIGH); // turn off relay 3
              toggleState_3 = 1;
              Serial.println("Device3 OFF");
              }
             delay(100);
      break;
      case 4: 
             if(toggleState_4 == 1){
              digitalWrite(RelayPin4, LOW); // turn on relay 4
              toggleState_4 = 0;
              Serial.println("Device4 ON");
              }
             else{
              digitalWrite(RelayPin4, HIGH); // turn off relay 4
              toggleState_4 = 1;
              Serial.println("Device4 OFF");
              }
             delay(100);
      break;
      default : break;      
      }
  
}

void with_internet(){
    //Manual Switch Control
    if (digitalRead(SwitchPin1) == LOW){
      delay(200);
      relayOnOff(1); 
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);   // Update Button Widget  
      delay(200);
      relayOnOff(1); 
      Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
    }
    else if (digitalRead(SwitchPin2) == LOW){
      delay(200);
      relayOnOff(2);      
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);   // Update Button Widget
      delay(200);
      relayOnOff(2); 
      Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
    }
    else if (digitalRead(SwitchPin3) == LOW){
      delay(200);
      relayOnOff(3);
      Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);   // Update Button Widget
      delay(200);
      relayOnOff(3); 
      Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
    }
    else if (digitalRead(SwitchPin4) == LOW){
      delay(200);
      relayOnOff(4);
      Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);   // Update Button Widget
      delay(200);
      relayOnOff(4); 
      Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
    }
}
void without_internet(){
    //Manual Switch Control
    if (digitalRead(SwitchPin1) == LOW){
      delay(200);
      relayOnOff(1);
      delay(200);
      relayOnOff(1);      
    }
    else if (digitalRead(SwitchPin2) == LOW){
      delay(200);
      relayOnOff(2);
      delay(200);
      relayOnOff(2);
    }
    else if (digitalRead(SwitchPin3) == LOW){
      delay(200);
      relayOnOff(3);
      delay(200);
      relayOnOff(3);
    }
    else if (digitalRead(SwitchPin4) == LOW){
      delay(200);
      relayOnOff(4);
      delay(200);
      relayOnOff(4);
    }
}

BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
  Blynk.syncVirtual(VPIN_BUTTON_3);
  Blynk.syncVirtual(VPIN_BUTTON_4);
}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  if (toggleState_1==0)                          // Do this if it was an On command from the Button widget in the App
    {
      Blynk.virtualWrite(VPIN_BUTTON_1, LOW);   // Change the app button state and keep it ON while you remove the finger - for visual feedback
      digitalWrite(RelayPin1, LOW);          // Turn the relay On
      delay (500);                            // Wait for 0.5 sec
      digitalWrite(RelayPin1, HIGH);  // Turn the relay Off
      Blynk.virtualWrite(VPIN_BUTTON_1, HIGH);  //Change the app button state to OFF
     }
    else                                      // Else do this if it was an Off command from the Button widget in the App
    {
      digitalWrite(RelayPin1, HIGH);           // Turn/ Keep the relay Off
    }
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  if (toggleState_2==0)                          // Do this if it was an On command from the Button widget in the App
    {
      Blynk.virtualWrite(VPIN_BUTTON_2, LOW);   // Change the app button state and keep it ON while you remove the finger - for visual feedback
      digitalWrite(RelayPin2, LOW);          // Turn the relay On
      delay (500);                            // Wait for 0.5 sec
      digitalWrite(RelayPin2, HIGH);  // Turn the relay Off
      Blynk.virtualWrite(VPIN_BUTTON_2, HIGH);  //Change the app button state to OFF
     }
    else                                      // Else do this if it was an Off command from the Button widget in the App
    {
      digitalWrite(RelayPin2, HIGH);           // Turn/ Keep the relay Off
    }
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  if (toggleState_3==0)                          // Do this if it was an On command from the Button widget in the App
    {
      Blynk.virtualWrite(VPIN_BUTTON_3, LOW);   // Change the app button state and keep it ON while you remove the finger - for visual feedback
      digitalWrite(RelayPin3, LOW);          // Turn the relay On
      delay (500);                            // Wait for 0.5 sec
      digitalWrite(RelayPin3, HIGH);  // Turn the relay Off
      Blynk.virtualWrite(VPIN_BUTTON_3, HIGH);  //Change the app button state to OFF
     }
    else                                      // Else do this if it was an Off command from the Button widget in the App
    {
      digitalWrite(RelayPin3, HIGH);           // Turn/ Keep the relay Off
    }
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  if (toggleState_4==0)                          // Do this if it was an On command from the Button widget in the App
    {
      Blynk.virtualWrite(VPIN_BUTTON_4, LOW);   // Change the app button state and keep it ON while you remove the finger - for visual feedback
      digitalWrite(RelayPin4, LOW);          // Turn the relay On
      delay (500);                            // Wait for 0.5 sec
      digitalWrite(RelayPin4, HIGH);  // Turn the relay Off
      Blynk.virtualWrite(VPIN_BUTTON_4, HIGH);  //Change the app button state to OFF
     }
    else                                      // Else do this if it was an Off command from the Button widget in the App
    {
      digitalWrite(RelayPin4, HIGH);           // Turn/ Keep the relay Off
    }
}


void checkBlynkStatus() { // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    wifiFlag = 1;
    digitalWrite(wifiLed, HIGH); //Turn off WiFi LED
  }
  if (isconnected == true) {
    wifiFlag = 0;
    digitalWrite(wifiLed, LOW); //Turn on WiFi LED
  }
}
void setup()
{
  Serial.begin(9600);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(RelayPin4, toggleState_4);

  WiFi.begin(ssid, pass);
  timer.setInterval(1000L, checkBlynkStatus); // check if Blynk server is connected every 3 seconds
  Blynk.begin(auth,ssid,pass);
}

void loop()
{  
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi Not Connected");
  }
  else
  {
    Serial.println("WiFi Connected");
    Blynk.run();
  }

  timer.run(); // Initiates SimpleTimer
  if (wifiFlag == 0)
    with_internet();
  else
    without_internet();
}
