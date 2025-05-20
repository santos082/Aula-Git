#include <Arduino.h>
#define pinA 35
#define pinB 34
#define pinC 32
#define pinD 13
#define pinE 33
#define pinF 12
#define pinK 25
#define pinX 26
#define pinY 27

void setup()
{
  Serial.begin(9600);
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
  pinMode(pinD, INPUT);
  pinMode(pinE, INPUT);
  pinMode(pinF, INPUT);
  pinMode(pinK, INPUT);
}

void loop()
{
  Serial.printf("A: %d\n\r", digitalRead(pinA));
  Serial.printf("B: %d\n\r", digitalRead(pinB));
  Serial.printf("C: %d\n\r", digitalRead(pinC));
  Serial.printf("D: %d\n\r", digitalRead(pinD));
  Serial.printf("E: %d\n\r", digitalRead(pinE));
  Serial.printf("F: %d\n\r", digitalRead(pinF));
  Serial.printf("K: %d\n\r", digitalRead(pinK));
  Serial.printf("X: %d\n\r", analogRead(pinX));
  Serial.printf("Y: %d\n\r", analogRead(pinY));
  Serial.println("===========================");
  delay(1000);
}