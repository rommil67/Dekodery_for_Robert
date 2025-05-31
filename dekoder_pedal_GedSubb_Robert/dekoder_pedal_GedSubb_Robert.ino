#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

const byte CHANNEL1 = 1;
const byte CHANNEL2 = 2;

const int NOTE_MIN = 36;
const int NOTE_MAX = 66;
const int NUM_NOTES = NOTE_MAX - NOTE_MIN + 1;

const int INPUT_CH1 = 48;  // LOW = kanał aktywny
const int INPUT_CH2 = 49;

// Mapa nut -> piny
int noteToPinCh1[NUM_NOTES];  // kanał 1: 36–66 -> 14–44
int noteToPinCh2[NUM_NOTES];  // kanał 2: 36–66 -> 2–32

int pinUsage[50] = {0};  // ile razy pin jest aktywowany

bool noteActiveCh1[NUM_NOTES] = {false};  // czy nuta jest aktywna logicznie
bool noteActiveCh2[NUM_NOTES] = {false};

bool prevStateCh1 = true;  // ostatni stan logiczny pinów
bool prevStateCh2 = true;

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);

  pinMode(INPUT_CH1, INPUT_PULLUP);
  pinMode(INPUT_CH2, INPUT_PULLUP);

  for (int i = 0; i < NUM_NOTES; i++) {
    noteToPinCh1[i] = 14 + i;
    noteToPinCh2[i] = 2 + i;

    pinMode(noteToPinCh1[i], OUTPUT);
    digitalWrite(noteToPinCh1[i], LOW);

    pinMode(noteToPinCh2[i], OUTPUT);
    digitalWrite(noteToPinCh2[i], LOW);
  }
}

void loop() {
  MIDI.read();
  updateChannelState();
}

void handleNoteOn(byte channel, byte note, byte velocity) {
  if (note < NOTE_MIN || note > NOTE_MAX) return;
  int index = note - NOTE_MIN;

  if (channel == CHANNEL1) {
    noteActiveCh1[index] = true;
    if (digitalRead(INPUT_CH1) == LOW) {
      int pin = noteToPinCh1[index];
      pinUsage[pin]++;
      digitalWrite(pin, HIGH);
    }
  }

  if (channel == CHANNEL2) {
    noteActiveCh2[index] = true;
    if (digitalRead(INPUT_CH2) == LOW) {
      int pin = noteToPinCh2[index];
      pinUsage[pin]++;
      digitalWrite(pin, HIGH);
    }
  }
}

void handleNoteOff(byte channel, byte note, byte velocity) {
  if (note < NOTE_MIN || note > NOTE_MAX) return;
  int index = note - NOTE_MIN;

  if (channel == CHANNEL1) {
    noteActiveCh1[index] = false;
    int pin = noteToPinCh1[index];
    if (pinUsage[pin] > 0) {
      pinUsage[pin]--;
      if (pinUsage[pin] == 0) digitalWrite(pin, LOW);
    }
  }

  if (channel == CHANNEL2) {
    noteActiveCh2[index] = false;
    int pin = noteToPinCh2[index];
    if (pinUsage[pin] > 0) {
      pinUsage[pin]--;
      if (pinUsage[pin] == 0) digitalWrite(pin, LOW);
    }
  }
}

void updateChannelState() {
  bool currentStateCh1 = digitalRead(INPUT_CH1);
  bool currentStateCh2 = digitalRead(INPUT_CH2);

  // KANAŁ 1 – stan się zmienił
  if (currentStateCh1 != prevStateCh1) {
    prevStateCh1 = currentStateCh1;

    for (int i = 0; i < NUM_NOTES; i++) {
      int pin = noteToPinCh1[i];

      if (currentStateCh1 == HIGH) {
        // Dezaktywacja kanału 1
        if (pinUsage[pin] > 0) {
          pinUsage[pin] = 0;
          digitalWrite(pin, LOW);
        }
      } else {
        // Aktywacja kanału 1 — jeśli nuta aktywna, to ją włącz
        if (noteActiveCh1[i]) {
          pinUsage[pin]++;
          digitalWrite(pin, HIGH);
        }
      }
    }
  }

  // KANAŁ 2 – stan się zmienił
  if (currentStateCh2 != prevStateCh2) {
    prevStateCh2 = currentStateCh2;

    for (int i = 0; i < NUM_NOTES; i++) {
      int pin = noteToPinCh2[i];

      if (currentStateCh2 == HIGH) {
        // Dezaktywacja kanału 2
        if (pinUsage[pin] > 0) {
          pinUsage[pin] = 0;
          digitalWrite(pin, LOW);
        }
      } else {
        // Aktywacja kanału 2 — jeśli nuta aktywna, to ją włącz
        if (noteActiveCh2[i]) {
          pinUsage[pin]++;
          digitalWrite(pin, HIGH);
        }
      }
    }
  }
}

