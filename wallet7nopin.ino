/**************************
Alt(oids) Bitcoin Wallet
Version 1.0
Buenos Aires, Argentina
May,14, 2022
Roni Bandini @RoniBandini

No guarantees of any kind. 
Use at your own risk.

CC Attribution 4.0 International License
https://creativecommons.org/licenses/by/4.0/

***************************/

#include <SPI.h>
#include <Nokia_LCD.h>
#include <BfButton.h>

#include "privatekey.h"
#include "publickey.h"

// 7 - SCLK // pin 6 -  (DIN) // pin 5 -  (D/C) // pin 4 - (CS) // pin 3 -(RST)
Nokia_LCD lcd(7, 6, 5, 4, 3);

int btnPin=21; 
int DT=20; 
int CLK=19; 

BfButton btn(BfButton::STANDALONE_DIGITAL, btnPin, true, LOW);
 
int counter=0;
int angle=0; 
int aState;
int aLastState;  
int pinSize=5;
int pinIndex=0;
int authenticated=0;
int myPin[10];

// no pin in this free version :(
String comparePin="";
int delayPrivate=5000;

const unsigned char logo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x80, 0x80, 0x80, 0x80, 0x80, 0xf0, 0xf8, 0xf8, 0xf0, 0x80, 0x80, 0xd0, 0xf8, 0xf8, 0xf0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x03, 0x03, 0x83, 
  0x83, 0x83, 0x87, 0x87, 0xcf, 0xff, 0xff, 0xff, 0xfe, 0x7e, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x83, 0x03, 0x03, 0x03, 0x03, 0x83, 0x83, 0x83, 0x87, 0xc7, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 
  0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
  0x03, 0x3f, 0x3f, 0x7f, 0x07, 0x03, 0x07, 0x7f, 0x7f, 0x7f, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 
  0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x10, 0x10, 
  0xb0, 0xe0, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x30, 0xf8, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x10, 0x70, 0xc0, 0x00, 0x00, 0xe0, 0x70, 0xc0, 0x00, 0x00, 0xc0, 0x70, 0x00, 0x20, 
  0x10, 0x10, 0x10, 0xe0, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x80, 0xe0, 
  0xb0, 0x90, 0x90, 0xb0, 0xe0, 0x00, 0x00, 0xf0, 0xf8, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0e, 0x09, 0x09, 0x09, 0x0f, 0x08, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x07, 0x01, 0x00, 0x01, 0x0f, 0x07, 
  0x01, 0x00, 0x00, 0x06, 0x0b, 0x09, 0x08, 0x0f, 0x08, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 
  0x00, 0x00, 0x01, 0x07, 0x0c, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern) {
  
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println("Click");

     
              myPin[pinIndex]=counter;      
              Serial.println("Selected: "+String(counter)); 
              pinIndex++;

      break;
      
    case BfButton::DOUBLE_PRESS:
      Serial.println("Double push");
      break;
      
    case BfButton::LONG_PRESS:
      Serial.println("Long push");

       if (authenticated==1){
        Serial.println("Private key");

        lcd.clear(false);
        lcd.setInverted(true);
        lcd.setCursor(0, 0);
        lcd.print("Private Key");
        lcd.setInverted(false);
        delay(1000);
  
        lcd.clear(false);
        lcd.setCursor(18, 0);
        lcd.draw(privkey,288,false,48);              
        delay(delayPrivate);

        lcd.clear(false);
        lcd.setInverted(true);
        lcd.setCursor(0, 0);
        lcd.print("Public Key");
        lcd.setInverted(false);
        delay(1000);
        lcd.clear(false);
        
       }
        
      break;
  }
}

void setup() {

  delay(2000);
  
  Serial.begin(9600);
  Serial.println("Alt(oids) BTC Wallet Started");
  Serial.println("Roni Bandini, May 2022");

  pinMode(CLK,INPUT_PULLUP);
  pinMode(DT,INPUT_PULLUP);
  aLastState = digitalRead(CLK);
 
  // Button settings
  btn.onPress(pressHandler)
  .onDoublePress(pressHandler) // default timeout
  .onPressFor(pressHandler, 1000); // custom timeout for 1 second
  
  lcd.begin();
  lcd.setContrast(60);
  lcd.clear(true);   
  lcd.clear(false);

  // show bmp logo
  lcd.setCursor(0, 0);
  lcd.draw(logo,498,true,84);           
  delay(2000);
  
  // credits
  lcd.clear(false);
  lcd.setCursor(0, 0);
  lcd.println("The curiously ");  
  lcd.println("cold wallet");
  lcd.println("for your $BTC");
  lcd.println("@RoniBandini");
  lcd.println("5/22 Argentina");
  delay(6000);

  // enter pin
  lcd.clear(false);
  screenHeaders();
  lcd.println("Long press");
  lcd.println("to show PR key");  
  delay(5000);
  lcd.clear(false);

  authenticated=1;
 
}


void authenticate(){

 // Authenticated functions not included
 delay(100);
  
  
}

void screenHeaders(){

      lcd.setCursor(0, 0);
      lcd.println("BTC Alt Wallet");      
      lcd.println("Version v0.1");
      lcd.println("@RoniBandini");

}

void loop() {

  if (authenticated==1){        
    lcd.setCursor(18, 0);
    lcd.draw(pubkey,288,false,48);           
    btn.read();
       
  }

  delay(500); 

}
