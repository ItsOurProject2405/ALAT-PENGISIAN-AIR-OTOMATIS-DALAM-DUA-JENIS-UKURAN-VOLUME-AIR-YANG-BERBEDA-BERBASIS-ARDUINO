#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const int pinSensor = 2;
const int pinBuz = 4;
const int pinPump = 5;
const int pinTombolMerah = 7;
const int pinTombolHijau = 6;
int tombolMerah,tombolHijau;
int urut;
float pulseMil = 2.9; //100miliLiter = 62.5pulse, 1ml = 1.6pulse
int kecil = 200;//mL
int besar = 400;//mL
int airKeluar;
volatile int pulseCount;
int pilihan;
void setup(){
Serial.begin(9600);
lcd.init();
lcd.backlight();
pinMode(pinSensor, INPUT);
pinMode(pinTombolMerah,INPUT_PULLUP);
pinMode(pinTombolHijau,INPUT_PULLUP);
pinMode(pinBuz,OUTPUT);
pinMode(pinPump,OUTPUT);
digitalWrite(pinSensor, HIGH);
digitalWrite(pinBuz,HIGH);
digitalWrite(pinPump,HIGH);
delay(2000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Air : ");
lcd.print("0 mL");
lcd.setCursor(0,1);
lcd.print("Total : ");
lcd.print("0 mL");
}
void loop(){
tombolMerah = digitalRead(pinTombolMerah);
tombolHijau = digitalRead(pinTombolHijau);
{
beep();
digitalWrite(pinPump,LOW);
pulseCount = 0;
attachInterrupt(0, pulseCounter, FALLING);
urut = 1;
pilihan = kecil;
}else if (inputString.indexOf("besar") != -1){
beep();
digitalWrite(pinPump,LOW);
pulseCount = 0;
attachInterrupt(0, pulseCounter, FALLING);
urut = 2;
pilihan = besar;
}
switch(urut){
case 0 :
if(tombolMerah == LOW){
delay(100);
beep();
digitalWrite(pinPump,LOW);
pulseCount = 0;
attachInterrupt(0, pulseCounter, FALLING);
urut = 1;
pilihan = kecil;
}
if(tombolHijau == LOW){
delay(100);
beep();
digitalWrite(pinPump,LOW);
pulseCount = 0;
attachInterrupt(0, pulseCounter, FALLING);
urut = 2;
pilihan = besar;
}
break;
case 1:
airKeluar = pulseCount*pulseMil;
lcd.setCursor(0,0);
lcd.print("Air : ");
lcd.print(pilihan);
lcd.print(" mL ");
lcd.setCursor(0,1);
lcd.print("Total : ");
lcd.print(airKeluar);
lcd.print(" mL ");
if(airKeluar >= kecil){
digitalWrite(pinPump,HIGH);
detachInterrupt(pinSensor);
beeps();
urut = 3;
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Air : ");
lcd.print(pilihan);
lcd.print(" mL ");
lcd.setCursor(0,1);
lcd.print("Total : ");
lcd.print(airKeluar);
lcd.print(" mL ");
delay(2000);
}
break;
case 2:
airKeluar = pulseCount*pulseMil;
lcd.setCursor(0,0);
lcd.print("Air : ");
lcd.print(pilihan);
lcd.print(" mL ");
lcd.setCursor(0,1);
lcd.print("Total : ");
lcd.print(airKeluar);
lcd.print(" mL ");
if(airKeluar >= besar){
digitalWrite(pinPump,HIGH);
detachInterrupt(pinSensor);
beeps();
urut = 3;
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Air : ");
lcd.print(pilihan);
lcd.print(" mL ");
lcd.setCursor(0,1);
lcd.print("Total : ");
lcd.print(airKeluar);
lcd.print(" mL ");
delay(2000);
}
break;
case 3:
pulseCount = 0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Air : ");
lcd.print("0 mL ");
lcd.setCursor(0,1);
lcd.print("Total : ");
lcd.print("0 mL ");
airKeluar = 0;
urut = 0;
break;
}
}
void pulseCounter(){
pulseCount++;
}
void beep(){
digitalWrite(pinBuz,LOW);
delay(100);
digitalWrite(pinBuz,HIGH);
delay(100);
}
void beeps(){
for(int i = 0; i <= 3; i++){
digitalWrite(pinBuz,!digitalRead(pinBuz));
delay(100);
}
}
