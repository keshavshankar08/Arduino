#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <NewPing.h>

LiquidCrystal_I2C lcd(0x27,16,2);
NewPing sonar (10,11);

//setup buttons
const char cleanButton = 5;
const char dirtyButton = 6;

//setup LED's
const int greenLED = 4;
const int redLED = 3;

bool clean = true;
bool dirty = false;
bool washerStatus = clean;

void setup() {
  lcd.init();
  lcd.noBacklight();
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(cleanButton, INPUT_PULLUP);
  pinMode(dirtyButton, INPUT_PULLUP);
}

void loop() {
  bool currentStateClean = digitalRead(cleanButton);
  if(currentStateClean == false){
    washerStatus = clean;
    lcd.backlight();
    lcd.clear();
    lcd.print("Dishes Clean!");
    delay(3000);
    lcd.noBacklight();
    while(digitalRead(cleanButton) == false){
      //do nothing
    }
  }
  bool currentStateDirty = digitalRead(dirtyButton);
  if(currentStateDirty == false){
    washerStatus = dirty;
    lcd.backlight();
    lcd.clear();
    lcd.print("Dishes Dirty!");
    delay(3000);
    lcd.noBacklight();
    while(digitalRead(dirtyButton) == false){
      //do nothing
    }
  }
  if(sonar.ping_cm() <= 5){
    lcd.backlight();
    status(washerStatus);
    delay(3000);
    lcd.noBacklight();
  }
}

void status(bool washerStatus){
  if(washerStatus == clean){
    lcd.clear();
    lcd.print("Dishes Clean!");
  }
  else{
    lcd.clear();
    lcd.print("Dishes Dirty!");
  } 
}
