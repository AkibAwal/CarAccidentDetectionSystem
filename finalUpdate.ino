#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include<BlynkSimpleEsp8266.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
const int buzzerPin = D3; 
int led = D7;
int led_flag = 0;
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLElVq14hD"
#define BLYNK_TEMPLATE_NAME "Car Accident and Probable Crash Alert System"
#define BLYNK_AUTH_TOKEN "My Token"
#define VIRTUAL_PIN_SWITCH_1 V2
#define VIRTUAL_PIN_SWITCH_2 V3
#define VIRTUAL_PIN_SWITCH_3 V7
int beep = 0; 
#define RX_PIN D7
#define TX_PIN D8

const int trigPin = D6; 
SoftwareSerial gpsSerial(RX_PIN, TX_PIN);
TinyGPSPlus gps;

const int echoPin = D5; 
const char* ssid = "Mod"; 
const char* password = "password_nai";  
char server[] = "mail.smtp2go.com"; 
WiFiClient espClient;
int buzz = 0;
int email = 0;
int flag = 0;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {

  Serial.begin(115200);
    gpsSerial.begin(115200);


  if(!accel.begin()) {
    Serial.println("Failed to initialize ADXL345");
    while(1);
  }

  accel.setRange(ADXL345_RANGE_16_G);

  pinMode(buzzerPin, OUTPUT);
   
   pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

 WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
       delay(500);
       Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi Connected.");

 Blynk.begin(BLYNK_AUTH_TOKEN,ssid,password);

}


void loop() {
  
  sensors_event_t event;
  accel.getEvent(&event);

 Blynk.run();
 
  Blynk.virtualWrite(V4,event.acceleration.x);

    Blynk.virtualWrite(V5,event.acceleration.y);

      Blynk.virtualWrite(V6,event.acceleration.z);


   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  Blynk.virtualWrite(V0,distance);
           beep = 0;

   if(abs(abs(event.acceleration.x) - 6.2) >= 1.5 || abs(abs(event.acceleration.y) - 1.92) >= 1.5 || abs(abs(event.acceleration.z)-31.97) > 2.30) {
    
            if(email>=1)flag = 1;

    beep = 1; 

  }

if(buzz <= 0)beep=0;


  if(beep) {

  
    tone(buzzerPin,1000);

    delay(2000); 

         noTone(buzzerPin);
         if(led_flag){

              digitalWrite(led,HIGH);
              delay(2000);
              digitalWrite(led,LOW);

         }

     beep = 0; 
          


  }

else {
          
        
  if (distance < 10 && buzz>=1) {

    beep = map(distance, 0, 10, 100, 1000);
    //Serial.println(beep);

  }
  else {

    beep = 0;

  }



if (beep > 0) {

    tone(buzzerPin, 1000);

    delay(500);

    noTone(buzzerPin);


  if(distance <= 10  && led_flag>=1){
   digitalWrite(led,HIGH);
   delay(500);
   digitalWrite(led,LOW);

  }



  }


}
if(flag==1){
  

  if(gpsSerial.available()>0){

    if(gps.encode(gpsSerial.read())){

     

     byte ret  = sendEmail(gps.location.lat(),gps.location.lng());


    }
    
  }


 

}

delay(100);

}


byte sendEmail(double lat,double lng) {
  if (espClient.connect(server, 2525) == 1)  {
       Serial.println(F("connected"));
  } else {
       Serial.println(F("connection failed"));
       return 0;
  }
  if (!emailResp())
    return 0;
 
  Serial.println(F("Sending EHLO"));

   String s = "http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";

         s+=lat;

         s+="+";

         s+=lng;  

  espClient.println("EHLO www.example.com");
  if (!emailResp())
       return 0;
 
  Serial.println(F("Sending auth login"));
  espClient.println("AUTH LOGIN");
  if (!emailResp())
       return 0;
  
  Serial.println(F("Sending User"));
 
 
  espClient.println("Y3k5dXM="); 
  if (!emailResp())
       return 0;
 
  Serial.println(F("Sending Password"));
 
  espClient.println("MTkyMTE0MTQyNQ=="); 

  if (!emailResp())
       return 0;
 
  Serial.println(F("Sending From"));
 
  espClient.println(F("MAIL From: albqkx@gmail.com")); 
  if (!emailResp())
       return 0;
 
  Serial.println(F("Sending To"));
  espClient.println(F("RCPT To: nomanshiblisunny@gmail.com")); 
  if (!emailResp())
       return 0;
 
  Serial.println(F("Sending DATA"));
  espClient.println(F("DATA"));
  if (!emailResp())
       return 0;
  Serial.println(F("Sending email"));
 
  espClient.println(F("To: nomanshiblisunny@gmail.com")); 

  espClient.println(F("From: albqkx@gmail.com")); 
  espClient.println(F("Subject: ACCIDENT OCCURED\r\n")); 
  espClient.println(F("ACCIDENT OCCURED WITH LOCATION:\n"));
  espClient.println(s);
  espClient.println(F("CLICK THE ABOVE LINK TO SHOW IN GOOGLE MAP\nPLEASE CONTACT THE EMERGENCY SERVICES"));
  //
  espClient.println(F("."));
  if (!emailResp())
       return 0;
  //
  Serial.println(F("Sending QUIT"));
  espClient.println(F("QUIT"));
  if (!emailResp())
       return 0;
  //
  espClient.stop();
  Serial.println(F("disconnected"));
  return 1;
}




// Callback function for switch state change
BLYNK_WRITE(VIRTUAL_PIN_SWITCH_1) {
   buzz = param.asInt();
}

BLYNK_WRITE(VIRTUAL_PIN_SWITCH_2) {
   email = param.asInt();
}



 
byte emailResp() {
  byte responseCode;
  byte readByte;
  int loopCount = 0;
 
  while (!espClient.available()) {
       delay(1);
       loopCount++;
 
       if (loopCount > 20000)
       {
       espClient.stop();
       Serial.println(F("\r\nTimeout"));
       return 0;
       }
  }
 
  responseCode = espClient.peek();
  while (espClient.available()) {
       readByte = espClient.read();
       Serial.write(readByte);
  }
 
  if (responseCode >= '4') {
  
       return 0;
  }
  return 1;
}



