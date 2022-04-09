//เรียกใช้ LiquidCrystal เป็น library สำหรับ การทำงานของหน้าจอ LCD ในการต่อแบบขนาน
#include <LiquidCrystal.h> 

// ประการตัวแปร และ define ค่าต่างๆเพื่อนำไปใช้คำนวนหาตำแหน่งในการ display graphic ในหน้าจอ LCD
#define lenght 16.0   
double percent=100.0;
unsigned char b;
unsigned int peace;

// ทำการสร้างทำแหน่งของ graphic ทั้งหมด และใช้คำสั่ง createChar ภายใน void setup เพื่อสร้างจุดดำบนหน้าจอ LCD ตามตำแหน่งที่กำหนดนี้
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

// ทำการเชื่อ หน้าจอ LCD กับ ARDUINO โดย ARDUINO จะส่งข้อมูลไปติดต่อกับหน้าจอ LCD ผ่าน pin เหล่านี้ 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()   {
  delay(100);
  lcd.createChar(0, p1);
  lcd.createChar(1, p2);
  lcd.createChar(2, p3);
  lcd.createChar(3, p4);
  lcd.createChar(4, p5);
 
  lcd.begin(16, 2);
  lcd.print(" voltage reader");
  delay(2000); 
}
 
void loop()
{
// รับค่าจาก Potentiometer มาเก็บไว้ในตัวแปร value แล้วนำมา convert ให้เป็น 0-5 แล้วนำไปเก็บไว้ในตัวแปร percent ให้หน่วยเป็น V
  unsigned int value = analogRead(0);
  percent = (value/1024.0*100.0)*0.05;
  
// ทำการ display ค่าในตัวแปร percent ในหน้าจอ LCD 
  lcd.setCursor(0, 1);
  lcd.print("voltage(V)");
  lcd.print(":");
  lcd.print(percent);        
  lcd.setCursor(0,0);

// ทำการ คำนวนหา % ของ graphic และแสดงผลออกมากหน้าจอ LCD
  double a=lenght/100*(percent/0.05);
  if (a>=1) {
    for (int i=1;i<a;i++) {
      lcd.write(4);
      b=i;
    }
    a=a-b;
  }
 
  peace=a*5;
  switch (peace) {
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
  
 //ล้าง graphic ที่แสดงบนหน้าจอ LCD
  for (int i =0;i<(lenght-b);i++) {
    lcd.print(" ");
  }
  ;
}
 
