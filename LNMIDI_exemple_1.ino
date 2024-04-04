// Playtune bytestream for file "test4.mid" created by MIDITONES V2.4 on Thu Apr  4 02:33:37 2024
// command line: ./miditones -v test4 
const unsigned char PROGMEM score [] = {
// Untitled
0x90,51,100, 0x91,45,100, 0x92,41,100, 2,235, 0x80, 0,2, 0x90,50,70, 0,123, 0x80, 0,127, 0x90,58,80, 0,248, 
0x80, 0,2, 0x90,57,89, 0,248, 0x80, 0x81, 0x82, 0,2, 0x90,56,99, 0,248, 0x80, 0,2, 0x90,50,108, 0,248, 
0x80, 0,2, 0x90,43,118, 0x91,38,118, 0x92,63,118, 3,230, 0x82, 0,2, 0x92,65,104, 0,248, 0x82, 0,2, 0x92,62,83, 
0,248, 0x80, 0x81, 0x82, 0,2, 0x90,60,61, 1,242, 0x80, 0,2, 0x90,34,45, 0x91,39,45, 0x92,70,45, 0,248, 
0x82, 0,2, 0x92,69,56, 0,248, 0x82, 0,2, 0x92,68,68, 0,248, 0x82, 0,2, 0x92,74,80, 0,248, 0x80, 0x81, 
0x82, 0,2, 0x90,45,92, 0x91,37,92, 0x92,68,92, 0,248, 0x82, 0,2, 0x92,63,104, 0,248, 0x82, 0,2, 0x92,51,115, 
1,242, 0x80, 0x81, 0x82, 0,2, 0x90,53,100, 0x91,36,100, 0x92,43,100, 0,248, 0x80, 0,2, 0x90,53,100, 0,248, 
0x80, 0,252, 0x90,53,40, 0,248, 0x80, 0,2, 0x90,62,53, 0,248, 0x80, 0,2, 0x90,63,66, 0,248, 0x80, 0x81, 
0x82, 0,2, 0x90,58,80, 0,248, 0x80, 0,2, 0x90,60,93, 0,123, 0x80, 0,2, 0x90,67,100, 0,123, 0x80, 0xF0};


// This 239 byte score contains 35 notes and uses 3 tone generators

#include "MIDIUSB.h"
#include "LutherieNuMIDI.h"

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}

LNMIDI MF;

void setup() {
  Serial.begin(0);
  MF.begin(score, sizeof(score));
  MF.play();
}

void loop() {
  midiEvent rx;
  do {
    rx = MF.read();
    if (rx.header == 0x9) {
      Serial.print("Note on - Note: ");
      Serial.print(rx.note);
      Serial.print(" Velocity: ");
      Serial.println(rx.velocity);
      noteOn(0, rx.note, rx.velocity);
    } else if (rx.header == 0x8) {
      Serial.print("Note off - Note: ");
      Serial.println(rx.note);
      noteOff(0, rx.note, 0);
    }
  } while (MF.playing == true || rx.valid == true);
  MF.restart();
}
