#include <FirebaseESP8266.h>
#include  <ESP8266WiFi.h>
#define FIREBASE_HOST "streetlight-6f29d-default-rtdb.firebaseio.com"
#define WIFI_SSID "myproject" 
#define WIFI_PASSWORD "myproject123" 
#define FIREBASE_Authorization_key "hsOumHKorK6QjWKir8ZqjPNZ4vaziqwawUKO22aL"
#define PINA D5 
#define PINB D6 
#define PINC D7 
#define PIND D8 

#define LEDA D2
#define LEDB D3
#define LEDC D4


 int ira,irb,irc,ldr,butt;
 int ira1,irb1,irc1;
float voltage;
FirebaseData firebaseData;
FirebaseJson json;

void setup() {

  Serial.begin(115200);
  pinMode(PINA, INPUT);
  pinMode(PINB, INPUT);
  pinMode(PINC, INPUT);
  pinMode(PIND, INPUT_PULLUP);
  
  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDC, OUTPUT);

  
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);

}


void loop() {

  ira=digitalRead(PINA);
  irb=digitalRead(PINB);
  irc=digitalRead(PINC);
  ldr=analogRead(A0);

  voltage = ldr * (5.0 / 1023.0);  
  if(voltage<=2.0)
  {
  if(ira == 0)
  {
    ira1=10;
    digitalWrite(LEDA,HIGH);
  delay(20);
  }
  else
  {
    ira1=20;
     digitalWrite(LEDA,LOW);
  delay(20);
  }

  if(irb == 0)
  {
    irb1=30;
    digitalWrite(LEDB,HIGH);
  delay(20);
  }
  else
  {
    irb1=40;
     digitalWrite(LEDB,LOW);
  delay(20);
  
  }

 if(irc == 0)
  {
    irc1=50;
    digitalWrite(LEDC,HIGH);
  delay(20);
  }
  else
  {
      irc1=60;
     digitalWrite(LEDC,LOW);
  delay(20);
  }
  }
  else
  {
  
     digitalWrite(LEDC,HIGH);
  delay(2000);
  }
 

  Firebase.setFloat(firebaseData, "IR1", ira1);
  Firebase.setFloat(firebaseData, "IR2", irb1);
  Firebase.setFloat(firebaseData, "IR3", irc1);
  Firebase.setFloat(firebaseData, "LDR", voltage);
  delay(200);
}
