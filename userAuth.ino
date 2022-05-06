#include <LiquidCrystal_I2C.h>
#include <RFID.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9

LiquidCrystal_I2C lcd(0x27,16,2);
RFID rfid(SS_PIN, RST_PIN);

String rfidCard;
#define numIds(arg) ((unsigned int) (sizeof(arg) / sizeof(arg[0])))

void setup() {
  Serial.begin(9600);
  //lcd setup
  lcd.init();
  lcd.backlight();
  lcd.print("Scanning...");
  //RFID setup
  Serial.println("Scanning...");
  SPI.begin();
  rfid.init();
  delay(50);
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + String(rfid.serNum[1]) + String(rfid.serNum[2]) + String(rfid.serNum[3]);
      checkAccess(rfidCard);
      }
    rfid.halt();
    }
}

void checkAccess(String card){
  String authorizedUsersIds[] = {"20911211825"};
  String authorizedUsers[] = {"Test ID"};
  boolean checkValidity = false;
  for(int i = 0; i < numIds(authorizedUsersIds); i++){
    if(rfidCard == authorizedUsersIds[i]){
      lcd.clear();
      lcd.print("Welcome " + authorizedUsers[i] + "!");
      checkValidity = true;
      break;
    }
  }
  if(checkValidity == false){
    lcd.clear();
    lcd.print("Invalid Id!");
    delay(1000);
    lcd.clear();
    lcd.print("Scanning...");
  }
}
