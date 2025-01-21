#include <SPI.h>
#include <RH_CC110.h>

// Define SPI pins for CC1101
#define CS_PIN 10   // Chip Select
#define GDO0_PIN 2  // Interrupt pin (GDO0)

// Create an instance of the RH_CC110 driver
RH_CC110 cc110(CS_PIN, GDO0_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing CC1101...");

  // Initialize the CC1101 module
  if (!cc110.init()) {
    Serial.println("CC1101 initialization failed. Check wiring.");
    while (1);
  }
  
  Serial.println("CC1101 initialized successfully!");

  // Set the frequency (e.g., 433 MHz)
  cc110.setFrequency(433.0);

  // Optional: Set output power (default is max power)
  cc110.setTxPower(10);
}

void loop() {
  // Transmit data
  const char* data = "Hello, CC1101!";
  Serial.print("Sending: ");
  Serial.println(data);

  if (cc110.send((uint8_t*)data, strlen(data))) {
    Serial.println("Message sent!");
  } else {
    Serial.println("Message send failed.");
  }

  delay(1000); // Wait 1 second

  // Receive data
  if (cc110.available()) {
    uint8_t buf[RH_CC110_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (cc110.recv(buf, &len)) {
      Serial.print("Received: ");
      Serial.println((char*)buf);
    } else {
      Serial.println("Receive failed.");
    }
  }
}
