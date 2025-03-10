// https://uhpowerup.com/ //
//AI genrated code modified by 2E0UMR//
// use at your own risk //

#include <Arduino.h>
#include "BluetoothSerial.h"

#define ATR 25
#define AFR 34
#define PTT 4

BluetoothSerial BTSerial;  // Bluetooth KISS Interface
bool useBluetooth = false;

// KISS protocol special characters
#define FEND 0xC0  // Frame End
#define FESC 0xDB  // Frame Escape
#define TFEND 0xDC // Transposed FEND
#define TFESC 0xDD // Transposed FESC

void setup() {
    Serial.begin(115200);  // USB Serial KISS
    BTSerial.begin("ESP32_KISS_TNC"); // Bluetooth KISS (change"ESP32_KISS_TNC" to rename bluetooth)
    pinMode(PTT, OUTPUT);
    digitalWrite(PTT, LOW);

    Serial.println("ESP32 KISS TNC Ready");
}

// Function to send KISS packets over serial/Bluetooth
void sendKISSPacket(uint8_t *data, size_t len) {
    Serial.write(FEND);
    BTSerial.write(FEND);
    
    for (size_t i = 0; i < len; i++) {
        if (data[i] == FEND) {
            Serial.write(FESC);
            Serial.write(TFEND);
            BTSerial.write(FESC);
            BTSerial.write(TFEND);
        } else if (data[i] == FESC) {
            Serial.write(FESC);
            Serial.write(TFESC);
            BTSerial.write(FESC);
            BTSerial.write(TFESC);
        } else {
            Serial.write(data[i]);
            BTSerial.write(data[i]);
        }
    }
    Serial.write(FEND);
    BTSerial.write(FEND);
}

// Function to generate AFSK tones (simplified example)
void transmitAFSK(uint8_t *packet, size_t len) {
    digitalWrite(PTT, HIGH);
    delay(50); // Small delay for radio keying

    for (size_t i = 0; i < len; i++) {
        // Generate 1200 Hz or 2200 Hz based on packet bits
        tone(ATR, (packet[i] & 1) ? 2200 : 1200, 10);
        delay(10);
    }

    delay(50); // Hold PTT briefly
    digitalWrite(PTT, LOW);
}

// Function to decode received AFSK audio (simplified)
void receiveAFSK() {
    int sample = analogRead(AFR);
    if (sample > 2000) {  // Threshold for detecting signal
        uint8_t receivedPacket[] = { 0x82, 0xA6, 0x40, 0x61, 0xE0, 0x03, 0xF0, 'H', 'e', 'l', 'l', 'o' };
        sendKISSPacket(receivedPacket, sizeof(receivedPacket));
    }
}

void loop() {
    // Check USB Serial for KISS frames
    if (Serial.available()) {
        uint8_t kissFrame[256];
        size_t len = Serial.readBytes(kissFrame, sizeof(kissFrame));
        transmitAFSK(kissFrame, len);
    }

    // Check Bluetooth Serial for KISS frames
    if (BTSerial.available()) {
        uint8_t kissFrame[256];
        size_t len = BTSerial.readBytes(kissFrame, sizeof(kissFrame));
        transmitAFSK(kissFrame, len);
    }

    receiveAFSK(); // Process incoming audio
}
