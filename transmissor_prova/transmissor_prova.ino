//  Guilherme Maioli
//  Gabriel Oliveira Santos
//  Kit 2 - Transmissor

#include <Wire.h>
#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <TimerOne.h>

// transmissor
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define DHTPIN A0
#define LDRPIN A3

#define DHTTYPE DHT11
#define PINO_TRIGGER 4 
#define PINO_ECHO 5

Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO); 

char buffer[50];
RF24 radio(9,10);

int val_ldr;
int val_umd;
int luminosidade;
int cmMsec;

float humidity;
float temperature_celsius;
float temperature_fahrenheit;

char hum_str[10];
char temp_cstr[10];
char temp_fstr[10];

int pino_led = 13;

unsigned char LED_0F[10];

const uint64_t pipe = 0x0020BAF433LL;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3, POSITIVE);

void setup() {
  pinMode(LDRPIN, INPUT);

  Serial.begin(9600);
  radio.begin();
  radio.setChannel(120);
  radio.openWritingPipe(pipe);
}

void loop() {
  long microsec = ultrasonic.timing();  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  val_ldr = analogRead(LDRPIN);
  luminosidade = map(val_ldr,0,1023,0,100);

  humidity = dht.readHumidity();
  temperature_celsius = dht.readTemperature();
  temperature_fahrenheit = dht.readTemperature(true);

  dtostrf(humidity, 3, 2, hum_str);
  dtostrf(temperature_celsius, 3, 2, temp_cstr);
  dtostrf(temperature_fahrenheit, 3, 2, temp_fstr);

  sprintf(buffer,"%s|%s|%s|%d|%d", temp_cstr, temp_fstr, hum_str, luminosidade, cmMsec);

  Serial.write(buffer);
  Serial.write("\n");
  radio.write(buffer, sizeof(buffer));
  delay(500);
}
