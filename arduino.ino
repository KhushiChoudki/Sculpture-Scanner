#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9  // Reset pin for Reader 1
#define SS_PIN_1 10  // SDA pin for Reader 1
#define RST_PIN_2 7  // Reset pin for Reader 2
#define SS_PIN_2 8   // SDA pin for Reader 2

MFRC522 mfrc522_1(SS_PIN_1, RST_PIN_1); // Instance for Reader 1
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN_2); // Instance for Reader 2

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522_1.PCD_Init();
  mfrc522_2.PCD_Init();
}

void loop() {
  sendCardData(mfrc522_1, "Reader 1");
  sendCardData(mfrc522_2, "Reader 2");
}

void sendCardData(MFRC522 &reader, const char *readerName) {
  if (!reader.PICC_IsNewCardPresent() || !reader.PICC_ReadCardSerial())
    return;

  // Send reader ID and card UID over Serial
  Serial.print(readerName);
  Serial.print(": ");
  for (byte i = 0; i < reader.uid.size; i++) {
    Serial.print(reader.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(reader.uid.uidByte[i], HEX);
  }
  Serial.println();

  reader.PICC_HaltA();
}
