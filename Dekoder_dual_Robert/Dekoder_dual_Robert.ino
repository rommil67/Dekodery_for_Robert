// MIDI Decoder for Dual Channel Pipe Organ Control
// Handles two MIDI channels controlling overlapping outputs independently
// Channel 1 and Channel 2 have selective activation via input pins
// Author: ChatGPT

#include <MIDI.h>

// MIDI channels
#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_REG 6

// Input pins to enable each channel (active LOW)
const int channel1_enable_pin = 60;  // Input pin to activate Channel 1
const int channel2_enable_pin = 61;  // Input pin to activate Channel 2

// Output pins (shared for both channels with offset for Channel 2)
const int NUM_NOTES = 31; // MIDI notes 36 to 66 inclusive
const int PINS_OFFSET_CH2 = 12; // Channel 2 pins are 12 positions offset

// Output pins array (should be long enough to accommodate both channels)
int outputPins[] = {
  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11,
  A12, A13, A14, A15, 31, 32, 33, 34, 35, 36, 37, 38,
  39, 40, 41, 42, 43, 44, 45, 46, 47, 2, 3, 4, 5, 6,
  7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
  21, 22, 23, 24, 25, 26, 27, 28, 29, 30
};

// Registry control pins (activated via channel 6)
int registryPins[] = {48, 50, 51, 52, 53, 54};

// State tracking arrays for notes
bool noteActiveCh1[128] = {false}; // Keeps track of notes held on Channel 1
bool noteActiveCh2[128] = {false}; // Keeps track of notes held on Channel 2
uint8_t pinHoldCounter[128] = {0}; // Number of active channels holding a pin

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // Set all output pins to OUTPUT mode and LOW state
  for (int i = 0; i < sizeof(outputPins) / sizeof(outputPins[0]); ++i) {
    pinMode(outputPins[i], OUTPUT);
    digitalWrite(outputPins[i], LOW);
  }
  // Set registry pins to OUTPUT mode and LOW state
  for (int i = 0; i < sizeof(registryPins) / sizeof(registryPins[0]); ++i) {
    pinMode(registryPins[i], OUTPUT);
    digitalWrite(registryPins[i], LOW);
  }

  // Set channel enable pins as input with pull-up
  pinMode(channel1_enable_pin, INPUT_PULLUP);
  pinMode(channel2_enable_pin, INPUT_PULLUP);

  // Initialize MIDI and set handlers
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
}

void loop() {
  MIDI.read(); // Continuously read MIDI input
  monitorChannelEnables(); // Check if channel enable inputs have changed
}

// This function checks if channel enable pins have changed state and updates output accordingly
void monitorChannelEnables() {
  static bool prevCh1 = HIGH;
  static bool prevCh2 = HIGH;

  bool ch1 = digitalRead(channel1_enable_pin);
  bool ch2 = digitalRead(channel2_enable_pin);

  if (ch1 != prevCh1) {
    prevCh1 = ch1;
    updateHeldNotes(CHANNEL_1, ch1 == LOW); // Enable/disable notes held by channel 1
  }
  if (ch2 != prevCh2) {
    prevCh2 = ch2;
    updateHeldNotes(CHANNEL_2, ch2 == LOW); // Enable/disable notes held by channel 2
  }
}

// Re-evaluate the state of held notes on the given channel
void updateHeldNotes(byte channel, bool enable) {
  for (byte pitch = 36; pitch <= 66; ++pitch) {
    int pinIdx = getPinIndex(channel, pitch);
    if (pinIdx >= 0 && pinIdx < sizeof(outputPins) / sizeof(outputPins[0])) {
      bool active = (channel == CHANNEL_1) ? noteActiveCh1[pitch] : noteActiveCh2[pitch];
      if (active) {
        if (enable) {
          pinHoldCounter[outputPins[pinIdx]]++;
          digitalWrite(outputPins[pinIdx], HIGH);
        } else {
          if (pinHoldCounter[outputPins[pinIdx]] > 0) pinHoldCounter[outputPins[pinIdx]]--;
          if (pinHoldCounter[outputPins[pinIdx]] == 0) digitalWrite(outputPins[pinIdx], LOW);
        }
      }
    }
  }
}

// Calculate the index of the pin for a given channel and pitch
int getPinIndex(byte channel, byte pitch) {
  int base = pitch - 36;
  if (base < 0 || base >= NUM_NOTES) return -1;
  if (channel == CHANNEL_1) return base;
  if (channel == CHANNEL_2) return base + PINS_OFFSET_CH2;
  return -1;
}

// Handle incoming NOTE ON messages
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  int pinIdx = getPinIndex(channel, pitch);
  if (pinIdx >= 0 && pinIdx < sizeof(outputPins) / sizeof(outputPins[0])) {
    if (channel == CHANNEL_1 && digitalRead(channel1_enable_pin) == LOW) {
      noteActiveCh1[pitch] = true;
      pinHoldCounter[outputPins[pinIdx]]++;
      digitalWrite(outputPins[pinIdx], HIGH);
    }
    else if (channel == CHANNEL_2 && digitalRead(channel2_enable_pin) == LOW) {
      noteActiveCh2[pitch] = true;
      pinHoldCounter[outputPins[pinIdx]]++;
      digitalWrite(outputPins[pinIdx], HIGH);
    }
  }

  // Registry control via channel 6
  if (channel == CHANNEL_REG) {
    int regIdx = pitch - 36;
    if (regIdx >= 0 && regIdx < sizeof(registryPins) / sizeof(registryPins[0])) {
      digitalWrite(registryPins[regIdx], HIGH);
    }
  }
}

// Handle incoming NOTE OFF messages
void handleNoteOff(byte channel, byte pitch, byte velocity) {
  int pinIdx = getPinIndex(channel, pitch);
  if (pinIdx >= 0 && pinIdx < sizeof(outputPins) / sizeof(outputPins[0])) {
    if (channel == CHANNEL_1) {
      noteActiveCh1[pitch] = false;
      if (pinHoldCounter[outputPins[pinIdx]] > 0) pinHoldCounter[outputPins[pinIdx]]--;
      if (pinHoldCounter[outputPins[pinIdx]] == 0) digitalWrite(outputPins[pinIdx], LOW);
    }
    else if (channel == CHANNEL_2) {
      noteActiveCh2[pitch] = false;
      if (pinHoldCounter[outputPins[pinIdx]] > 0) pinHoldCounter[outputPins[pinIdx]]--;
      if (pinHoldCounter[outputPins[pinIdx]] == 0) digitalWrite(outputPins[pinIdx], LOW);
    }
  }

  // Turn off registry pin on NOTE OFF from channel 6
  if (channel == CHANNEL_REG) {
    int regIdx = pitch - 36;
    if (regIdx >= 0 && regIdx < sizeof(registryPins) / sizeof(registryPins[0])) {
      digitalWrite(registryPins[regIdx], LOW);
    }
  }
}

