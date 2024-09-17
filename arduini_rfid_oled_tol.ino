
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

// Define the pins for RFID
#define SS_PIN 10
#define RST_PIN 9

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Create LCD instance
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C bisa berbeda, tergantung modul LCD Anda

// Create Servo instance
Servo myServo;

// Known RFID UID
byte authorizedUID4[8] = {0x05, 0x8E, 0x09, 0x2C, 0x51, 0xD1, 0x00};
String text = "Silahkan Scan Kartu Anda!";

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  
  // Initialize the MFRC522
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize the Servo
  myServo.attach(8); // Ganti dengan pin yang digunakan untuk servo
  myServo.write(0); // Servo pada posisi awal (0 derajat)
  
  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Silahkan Scan");
  lcd.setCursor(0,1);
  lcd.print("Kartu Anda!");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    
    return;
  }
  Serial.print("UID tag : ");
  printUID(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  
  if  (isAuthorized4(mfrc522.uid.uidByte)) {
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Akses Diterima");
    lcd.setCursor(0,1);
    lcd.print("Hai Shaskia");
    myServo.write(90); // Buka pintu (90 derajat)
    delay(5000); // Tunda 3 detik
    myServo.write(0); 
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Akses");
    lcd.setCursor(0,1);
    lcd.print("DiTolak");
    delay(5000); // Tunda 2 detik untuk menunjukkan pesan  
  }

  lcd.clear();
  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print("Silahkan Scan");
  lcd.setCursor(0,1);
  lcd.print("Kartu Anda!");
  
  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}

bool isAuthorized4(byte *uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != authorizedUID4[i]) {
      return false;
    }
  }
  return true;
}

void printUID(byte *uid, byte length) {
  for (byte i = 0; i < length; i++) {
    if (uid[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(uid[i], HEX);
    if (i < length - 1) {
      Serial.print(" ");
    }
  }
}