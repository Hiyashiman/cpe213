#include <LiquidCrystal_I2C_Hangul.h>
#include <WiFi.h>
#include "ThingsBoard.h"

//lcd2004 
int lcdColumns = 20;
int lcdRows = 4;

double percent=100.0;
#define lenght 14.0
unsigned char b;
unsigned int peace;
int sensorValue = 0;
double value = 0.0;
double a = 0.0;
LiquidCrystal_I2C_Hangul lcd(0x27, lcdColumns, lcdRows);

// custom charaters
byte p1[8] = {
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10,
  0x10};
 
byte p2[8] = {
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18,
  0x18};
 
byte p3[8] = {
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C,
  0x1C};
 
byte p4[8] = {
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x1E};
 
byte p5[8] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F};

const char* ssid     = "Hiyashiman";
const char* password = "11111111";
const char* token ="T2NJXDGFgA94PSm4Sl2k";
const char*  broker =  "thingsboard.cloud";
WiFiClient espClient;
ThingsBoard tb(espClient);

void setup() {
  pinMode(32, INPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin("Wokwi-GUEST", "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);
  lcd.begin(lcdColumns, lcdRows);

  lcd.setCursor (3, 1);  
  lcd.print("Voltage reader");
  delay(1500);
  lcd.clear();

  lcd.setCursor (2, 1); 
  lcd.print("Connecting");
  for(int i = 13 ;i < 18 ; i++ ){
    delay(1000);
    lcd.setCursor (i, 1); 
    lcd.print(".");
  }
  lcd.clear();
  delay(1500);

}

void loop() {

  if (!tb.connected()) {
    Serial.print("Connecting to: ");
    Serial.print(broker);
    Serial.print(" with token ");
    Serial.println(token);

    if (!tb.connect(broker, token)) {
      Serial.println("Failed to connect");
      lcd.setCursor (1, 1); 
      lcd.print("Failed to connect!"); 
      delay(1000);
      return;
    }

  }

  value = analogRead(32);
  value = ((value / 4095.0)*100.0)*0.05;
  percent = value / 0.05;
  Serial.println(value);
  Serial.println("Sending data...");
  tb.sendTelemetryFloat("voltage(V) :", value);
  Serial.println(value);
  delay(1000);

  lcd.setCursor (3,0); 
  lcd.print("Voltage reader"); 
  lcd.setCursor (0,1); 
  lcd.print("voltage:"); 
  lcd.setCursor (9,1); 
  lcd.print(value); 
  lcd.setCursor (14,1); 
  lcd.print("(V)"); 
  lcd.setCursor (0,2); 
  lcd.print("graph:");
  g(percent);
  lcd.setCursor (6,3); 
  lcd.print("MIN        MAX"); 
  delay(1000);

  

}

void g(double percent){
 lcd.setCursor(6,2);

  a = lenght / 100 * percent;
  if (a >= 1) {
    for (int i=1;i<a;i++) {
      lcd.write(4);
      b = i;
    }
    a = a - b;
  }

  peace=a*5;
  switch (peace) {
   case 1:
    lcd.write(0);
   break;
   case 2:
    lcd.write(1);
   break;
   case 3:
    lcd.write(2);
   break;
   case 4:
    lcd.write(3);
   break;
 
  }
 
for (int i = 0;i < (lenght-b) ;i++) {
  lcd.print(" ");
}
}
