/*
  De Bruijn Sequence Generator for RF Transmission on Arduino
  Generates all possible sequences of binary values for a specified number of bits.
  This can be used for brute-forcing OOK-based RF systems.
*/

#include <RCSwitch.h>

#define TRANSMIT_PIN 4  // Define the pin to transmit RF signals
#define SEQUENCE_LENGTH 4  // Define the number of bits for the De Bruijn sequence
#define LED_PIN 13  // Built-in LED pin for most Arduino boards


RCSwitch rfSwitch = RCSwitch();  // Initialize RCSwitch

// Function to generate De Bruijn sequence for a given number of bits
void generateDeBruijn(int bits) {
  int sequenceLength = (1 << bits);  // Length of the De Bruijn sequence is 2^bits
  for (int i = 0; i < sequenceLength; i++) {
    // Shift and XOR to generate the next bit in the sequence
    int value = i ^ (i >> 1);
    // Transmit the sequence as binary through RF
    transmitValue(value, bits);
    delay(100);  // Add a delay between transmissions
  }
}

// Function to transmit a binary value using RF
void transmitValue(int value, int bitLength) {
  digitalWrite(LED_PIN, HIGH);  // Turn LED on
  rfSwitch.send(value, bitLength);  // Transmit the binary value as an RF signal
  Serial.print("Transmitting: ");
  Serial.println(value, BIN);  // Print the binary value to the Serial Monitor
  digitalWrite(LED_PIN, LOW);  // Turn LED off
}

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
  Serial.begin(115200);
  rfSwitch.enableTransmit(TRANSMIT_PIN);  // Enable transmission on the defined pin
  Serial.println("Starting De Bruijn Sequence Generation...");
  generateDeBruijn(SEQUENCE_LENGTH);  // Generate the De Bruijn sequence for the specified length
}

void loop() {
  // Loop is left empty since sequence generation is done in setup
}
