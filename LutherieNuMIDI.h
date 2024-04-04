struct midiEvent {
  unsigned char header = 0;
  unsigned char channel = 0;
  unsigned char note = 0;
  unsigned char velocity = 0;
  bool valid = true;
};

struct LNMIDI {
  public:
    int index = -1;
    unsigned int size;
    const unsigned char *score;
    bool playing = false;
    unsigned char voices[16] = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255 };
    
    void begin(const unsigned char *_score, unsigned int _size) {
      score = _score;
      size = _size;
      index = -1;
      playing = false;
    }
    
    void play() { index = 0; playing = true; }
    void restart() { index = 0; }
    
    midiEvent read() {
      midiEvent ev;
      if (index == -1) {
        ev.header = 0;
        ev.valid = false;
        playing = false;
        return ev;
      }
      
      unsigned char cur = pgm_read_byte_near(score + index);
      if (cur & 0x80) {
        if ((cur & 0xF0) == 0x80) {
          ev.header = 0x8;
          ev.note = voices[cur & 0x0F];
          ev.velocity = 64;
          voices[cur & 0x0F] = 255;
        } else if ((cur & 0xF0) == 0x90) {
          voices[cur & 0x0F] = pgm_read_byte_near(score + index + 1);
          ev.header = 0x9;
          ev.note = voices[cur & 0x0F];
          ev.velocity = pgm_read_byte_near(score + index + 2);
          index += 2;
        } else if (cur == 0xF0) {
          ev.header = 0;
          ev.valid = false;
          playing = false;
          index = -1;
          return ev;
        } else {
        }
      } else {
        int number = pgm_read_byte_near(score + index + 1) | pgm_read_byte_near(score + index) << 8;
        // Serial.print("Wait... -> ");
        // Serial.println(number);
        delay(number);
        index += 1;
      }
      
      index += 1;
      // if (index >= size) index = 0;
      
      return ev;
    }
};

