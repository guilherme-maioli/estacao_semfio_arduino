//  Guilherme Maioli
//  Gabriel Oliveira Santos
//  Kit 2 - Receptor

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <LiquidCrystal_I2C.h>
#include <string.h>

#define LCDPIN4 A4
#define LCDPIN5 A5

#define VW_MAX_MESSAGE_LEN 50

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

RF24 radio(9,10);
const uint64_t pipe = 0x0020BAF433LL;
 
void setup()   {
//  Timer1.initialize(1500); // set a timer of length 1500
//  Timer1.attachInterrupt(timerIsr); // attach the service routine here

  radio.begin();
  radio.setChannel(120);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  
  lcd.begin (16,2);
  lcd.clear();
  
  lcd.setBacklight(HIGH);
  
  lcd.setCursor(0,0);
  lcd.print("SISTEMAS");
  lcd.setCursor(0,1);
  lcd.print("EMBARCADOS");
  delay(2000);
    
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Gabriel Oliveira");
  lcd.setCursor(0,1);
  lcd.print("dos Santos");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Guilherme");
  lcd.setCursor(0,1);
  lcd.print("Maioli");
  delay(2000);
}
 
void loop() {
  char *temp_c, *temp_f, *hum, *lum, *dis;
  char message[VW_MAX_MESSAGE_LEN];
  
  if (radio.available()) {
     radio.read(message, sizeof(message));
     
     temp_c = strtok(message,"|");
     temp_f = strtok(NULL,"|");
     hum = strtok(NULL,"|");
     lum = strtok(NULL,"|");
     dis = strtok(NULL,"\0");

     lcd.clear();
  
     lcd.setCursor(0,0);
     lcd.print("TEMPERATURA:");
     lcd.setCursor(0,1);
     lcd.print(temp_c);
     lcd.print(" C");
     
     delay(1000);
    
     lcd.clear();
      
     lcd.setCursor(0,0);
     lcd.print("TEMPERATURA:");
     lcd.setCursor(0,1);
     lcd.print(temp_f);
     lcd.print(" F");
     delay(2000);
    
     lcd.clear();
      
     lcd.setCursor(0,0);
     lcd.print("UMIDADE AR:");
     lcd.setCursor(0,1);
     lcd.print(hum);
     lcd.print(" %");
     delay(2000);
    
     lcd.clear();
      
     lcd.setCursor(0,0);
     lcd.print("LUMINOSIDADE:");
     lcd.setCursor(0,1);
     lcd.print(lum);
     delay(2000);
    
     lcd.clear();
      
     lcd.setCursor(0,0);
     lcd.print("DISTANCIA:");
     lcd.setCursor(0,1);
     lcd.print(dis);
     lcd.print(" cm");
     delay(2000);
  }
}
