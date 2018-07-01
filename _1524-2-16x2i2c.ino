// sistem comanda LM1036 - sketch sris de Nicu FLORICA (niq_ro)
// ver.0 - sketch initial, 25.02.2017
// ver.0a - adaugat afisaj LCD1602 pe i2c de Mihai BRINDUSOIU
// ver.1 - adaugat memorare date in EEPROM


#include <EEPROM.h> - de studiat http://tronixstuff.com/2011/03/16/tutorial-your-arduinos-inbuilt-eeprom/

#include <Wire.h>
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(0); // Adress, columns, rows. use 16,2 for a 16x2 LCD, etc.

#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// definim pini cu control PWN care au frecventa maxima de 32kHz
#define pinvol 3  //volum
#define pinbal 9  // balans
#define pinbas 10 //bas
#define pinint 11  //inalte

// defini butoane
#define pinmen 4  //meniu
#define pinmin 5  //minuus
#define pinpls 6  //plus

/*
int volum=15;
int balans=127;   // balans la jumate
int bas=127;
int inalte=127;
*/

int volum, balans, bas, inalte;

int nivel = 0; // 0 - functionare normala
                // > 0 modificare valori
              


void setup()
{

volum = EEPROM.read(101);
balans = EEPROM.read(102);
bas = EEPROM.read(103);
inalte = EEPROM.read(104);

if ((volum < 0) || (volum > 222)) volum = 0;
if ((balans < 0) || (balans > 222)) volum = 127;
if ((bas < 0) || (bas > 222)) bas = 111;
if ((inalte < 0) || (inalte > 222)) inalte = 127;

pinMode(pinvol, OUTPUT);
pinMode(pinbal, OUTPUT);
pinMode(pinbas, OUTPUT);
pinMode(pinint, OUTPUT);

setPwmFrequency(pinvol, 1);  // frecventa pwm 32kHz
setPwmFrequency(pinbal, 1);  // frecventa pwm 32kHz
setPwmFrequency(pinbas, 1);  // frecventa pwm 32kHz
setPwmFrequency(pinint, 1);  // frecventa pwm 32kHz  

analogWrite(pinvol, volum);
analogWrite(pinbal, balans);
analogWrite(pinbas, bas);
analogWrite(pinint, inalte);

pinMode(pinmen, INPUT);
pinMode(pinmin, INPUT);
pinMode(pinpls, INPUT);

digitalWrite(pinmen, HIGH);
digitalWrite(pinmin, HIGH);
digitalWrite(pinpls, HIGH);

//  lcd.begin(16,2); 
  lcd.begin();
  lcd.setBacklight (HIGH);

  lcd.clear();
    
Serial.begin(9600);
//lcd.setCursor(0,0);
lcd.print("----------------");
//Serial.println("------------");
lcd.setCursor(0,1);
lcd.print("Comanda TDA1524 ");
//Serial.println("Sistem comanda LM1036 ");
delay(2000); lcd.clear();
lcd.setCursor(0,0);
  lcd.print("VOL BAL BAS TRE ");
  lcd.setCursor(1,1);
 if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
  lcd.setCursor(5,1);
   if(balans/6 <10)
 lcd.print("0");
  lcd.print(balans/6);
  lcd.setCursor(9,1);
   if(bas/6 <10)
 lcd.print("0");
  lcd.print(bas/6);
  lcd.setCursor(13,1);
   if(inalte/6 <10)
 lcd.print("0");
  lcd.print(inalte/6);
} // sfarsit parte setare


void setPwmFrequency(int pin, int divisor) { // http://playground.arduino.cc/Code/PwmFrequency
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}   // terminare subrutina de frecventa



void loop()
{
 
if (nivel == 0)
{
//REGLAJ VOLUM 
if (digitalRead(pinmin) == LOW)
{
  volum = volum - 6;
   lcd.setCursor(0,0);
 // lcd.print("                ");
 // lcd.setCursor(0,1);
 // lcd.print("  Scade volumul ");
 lcd.setCursor(0,0);
  lcd.print("  VOLUM         ");
  lcd.setCursor(4,1);
 if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
  Serial.println("Scade volumul");
  delay(250);
  lcd.clear();



  
  //lcd.setCursor(0,0);
  //lcd.print("   Functionare  ");
 // lcd.setCursor(0,1);
 // lcd.print("     normala    ");
 lcd.setCursor(0,0);
  lcd.print("  VOLUM         ");
  lcd.setCursor(4,1);
  if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("VOL BAL BAS TRE ");
  lcd.setCursor(1,1);
 if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
  lcd.setCursor(5,1);
   if(balans/6 <10)
 lcd.print("0");
  lcd.print(balans/6);
  lcd.setCursor(9,1);
   if(bas/6 <10)
 lcd.print("0");
  lcd.print(bas/6);
  lcd.setCursor(13,1);
   if(inalte/6 <10)
 lcd.print("0");
  lcd.print(inalte/6);
}
if (digitalRead(pinpls) == LOW)
{
  volum = volum + 6;
 //  lcd.setCursor(0,0);
 // lcd.print("                ");
 // lcd.setCursor(0,1);
 // lcd.print(" Creste volumul ");
 lcd.setCursor(0,0);
  lcd.print("  VOLUM         ");
  lcd.setCursor(4,1);
 if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
 Serial.println("Creste volumul");
  delay(250);
  lcd.clear();
 // lcd.setCursor(0,0);
 // lcd.print("----------------");
  //lcd.setCursor(0,1);
  //lcd.print("COMANDA TDA1524 ");
  lcd.setCursor(0,0);
  lcd.print("  VOLUM         ");
  lcd.setCursor(4,1);
  if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);

   delay(500);
  lcd.setCursor(0,0);
  lcd.print("VOL BAL BAS TRE ");
  lcd.setCursor(1,1);
 if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
  lcd.setCursor(5,1);
   if(balans/6 <10)
 lcd.print("0");
  lcd.print(balans/6);
  lcd.setCursor(9,1);
   if(bas/6 <10)
 lcd.print("0");
  lcd.print(bas/6);
  lcd.setCursor(13,1);
   if(inalte/6 <10)
 lcd.print("0");
  lcd.print(inalte/6);
}

if (volum > 222) volum = 222;
if (volum <0) volum = 0;
analogWrite(pinvol, volum);
EEPROM.write(101, volum);

  //END REGLAJ VOLUM
 // */

 
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Reglaj volum  ");
  Serial.println("Reglaj volum");
  delay(250);
}
}  // sfarsit nivel 0

if (nivel == 1)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Reglaj balans ");
  //Serial.println("Reglaj balans");
  delay(250);
}

if (digitalRead(pinmin) == LOW)
{
  volum = volum - 6;
  //lcd.setCursor(0,0);
 // lcd.print(volum/6);
  lcd.setCursor(0,1);
 // lcd.print("  Scade volumul ");

  if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
  
  Serial.println("Scade volumul");
  delay(250);
}//
if (digitalRead(pinpls) == LOW)
{
  volum = volum + 6;
  //lcd.setCursor(0,0);
 // lcd.print(volum/6);
  lcd.setCursor(0,1);
  //lcd.print(" Creste volumul ");
  if(volum/6 <10)
 
   // lcd.print("0"+volum/6);
 // else
 lcd.print("0");
  lcd.print(volum/6);
  
  Serial.println("Creste volumul");
  delay(250);
}

if (volum > 222) volum = 222;
if (volum <0) volum = 0;
analogWrite(pinvol, volum);
}  // sfarsit nivel 1


if (nivel == 2)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Reglaj bas   ");
  
 // Serial.println("Reglaj bas");
  delay(250);
}

if (digitalRead(pinmin) == LOW)
{
  balans = balans - 6;
 // lcd.setCursor(0,1);
   lcd.setCursor(0,1);
 // lcd.print("  Scade volumul ");

  if(balans/6 <10)
 lcd.print("0");
  lcd.print(balans/6);
 // lcd.print("  Balans stanga ");
 // Serial.println("Balans spre stanga");
  delay(250);
}
if (digitalRead(pinpls) == LOW)
{
  balans = balans + 6;
  lcd.setCursor(0,1);
   if(balans/6 <10)
 lcd.print("0");
  lcd.print(balans/6);
 // lcd.print(" Balans dreapta ");
 // Serial.println("Balans spre dreapta");
  delay(250);
}

if (balans > 222) balans = 222;
if (balans <0) balans = 0;
analogWrite(pinbal, balans);
}  // sfarsit nivel 2

if (nivel == 3)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = nivel + 1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Reglaj inalte ");
 // Serial.println("Reglaj inalte");
  delay(250);
}

if (digitalRead(pinmin) == LOW)
{
  bas = bas - 6;
  lcd.setCursor(0,1);
   if(bas/6 <10)
 lcd.print("0");
  lcd.print(bas/6);
 // lcd.print("  Scade basul   ");
 // Serial.println("Scade basul");
  delay(250);
}
if (digitalRead(pinpls) == LOW)
{
  bas = bas + 6;
  lcd.setCursor(0,1);
   if(bas/6 <10)
 lcd.print("0");
  lcd.print(bas/6);
 // lcd.print("  Creste basul  ");
 // Serial.println("Creste basul");
  delay(250);
}

if (bas > 222) bas = 222;
if (bas <0) bas = 0;
analogWrite(pinbas, bas);
}  // sfarsit nivel 3
 

if (nivel == 4)
{
if (digitalRead(pinmen) == LOW)
{
  nivel = 0;
  lcd.clear();
 lcd.setCursor(0,0);
  lcd.print("  VOLUM         ");
  lcd.setCursor(4,1);
  if(volum/6 <10)
   lcd.print("0");
  lcd.print(volum/6);
  Serial.println("Functionare normala");
  EEPROM.write(101, volum);
  EEPROM.write(102, balans);
  EEPROM.write(103, bas);
  EEPROM.write(104, inalte);
  delay(5250);
  lcd.setCursor(0,0);
  lcd.print("VOL BAL BAS TRE ");
  lcd.setCursor(1,1);
 if(volum/6 <10)
 lcd.print("0");
  lcd.print(volum/6);
  lcd.setCursor(5,1);
   if(balans/6 <10)
 lcd.print("0");
  lcd.print(balans/6);
  lcd.setCursor(9,1);
   if(bas/6 <10)
 lcd.print("0");
  lcd.print(bas/6);
  lcd.setCursor(13,1);
   if(inalte/6 <10)
 lcd.print("0");
  lcd.print(inalte/6);
///*  

}

if (digitalRead(pinmin) == LOW)
{
  inalte = inalte - 6;
  lcd.setCursor(0,1);
  if(inalte/6 <10)
 lcd.print("0");
  lcd.print(inalte/6);
 // lcd.print(" Scad inaltele  ");
 // Serial.println("Scad inaltele");
  delay(250);
}
if (digitalRead(pinpls) == LOW)
{
  inalte = inalte + 6;
  lcd.setCursor(0,1);
   if(inalte/6 <10)
 lcd.print("0");
  lcd.print(inalte/6);
 // lcd.print(" Cresc inaltele ");
  //Serial.println("Cresc inaltele");
  delay(250);
}

if (inalte > 222) inalte = 222;
if (inalte <0) inalte = 0;
analogWrite(pinint, inalte);
}  // sfarsit nivel 3
 

}  // sfarsit program principoal
