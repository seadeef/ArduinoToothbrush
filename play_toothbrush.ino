#include "tones1.h"
#include "tones2.h"

#define TOOTHBRUSH1 3
#define TOOTHBRUSH2 6

#define BUTTON 12
#define NOTE_SPACE 20

const unsigned char T1_tones[] =  {REST, T1_G2, T1_G2, T1_G2, T1_DS2, T1_AS2, T1_G2, T1_DS2, T1_AS2, T1_G2, T1_D3, T1_D3, T1_D3, T1_DS3, T1_AS2, T1_FS2, T1_DS2, T1_AS2, T1_G2, T1_G3, T1_G2, T1_G2, T1_G3, T1_FS3, T1_F3, T1_E3, T1_DS3, T1_E3, T1_FS2, T1_CS3, T1_C3, T1_B2, T1_AS2, T1_A2, T1_AS2, T1_DS2, T1_FS2, T1_DS2, T1_FS2, T1_AS2, T1_G2, T1_AS2, T1_D3, T1_G3, T1_G2, T1_G2, T1_G3, T1_FS3, T1_F3, T1_E3, T1_DS3, T1_E3, T1_FS2, T1_CS3, T1_C3, T1_B2, T1_AS2, T1_A2, T1_AS2, T1_DS2, T1_FS2, T1_DS2, T1_AS2, T1_G2, T1_DS2, T1_AS2, T1_G2};
const int T1_delays[] =           {9228, 577,   577,   577,   433,    144,    577,   433,    144,    1154,  577,   577,   577,   433,    144,    577,    433,    144,    1154,  577,   433,   144,   577,   433,    144,   144,   144,    577,   288,    577,    433,   144,   144,    144,   577,    288,    577,    433,    144,    577,    433,   144,    1154,   577,   433,   144,   577,   433,    144,   144,   144,    577,   288,    577,    433,   144,   144,    144,   577,    288,    577,    433,    144,    577,    433,   144,    1158};
const int T1_len = sizeof(T1_tones)/sizeof(T1_tones[0]);

const unsigned char T2_tones[] =  {T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_DS2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_DS2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_DS2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_DS2, T2_G2, T2_G2, T2_G2, T2_DS2, T2_G2, T2_DS2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_DS2, T2_DS2, T2_DS2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_CS2, T2_CS2, T2_CS2, T2_CS2, T2_DS2, T2_DS2, T2_DS2, T2_DS2, T2_G2, T2_DS2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_G2, T2_CS2, T2_CS2, T2_CS2, T2_CS2, T2_DS2, T2_DS2, T2_DS2, T2_DS2, T2_G2, T2_DS2, T2_G2, T2_G2};
const int T2_delays[] =           {577,   192,   192,   192,   577,   577,    577,   192,   192,   192,   577,   577,    577,   192,   192,   192,   577,   577,    577,   192,   192,   192,   577,   577,    577,   577,   577,   577,    577,   577,    577,   577,   577,   577,   577,   577,    577,    577,    577,   577,   577,   577,   577,   577,   577,    577,    577,    577,    577,    577,    577,    577,    577,   577,    577,   577,   577,   577,   577,   577,   577,    577,    577,    577,    577,    577,    577,    577,    577,   577,    577,   577};   
const int T2_len = sizeof(T2_tones)/sizeof(T2_tones[0]);

void setup() {
  pinMode(TOOTHBRUSH1, OUTPUT);
  pinMode(TOOTHBRUSH2, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

bool toothbrush_callback(int toothbrush, int loudness, int duration, unsigned long timestamp, bool* called) {
  if (!(*called) && millis() < (timestamp+duration-NOTE_SPACE)) {
    analogWrite(toothbrush, loudness);
    (*called) = true;
    return false;
  } else if (millis() > (timestamp+duration-NOTE_SPACE) && (*called) == true) {
    analogWrite(toothbrush, 0);
    *called = false;
    return false;
  } else if (millis() > (timestamp+duration)) {
    return true;
  } else {
    return false;
  }
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    for (int i=0; i<2; i++) {       //play song twice
      int T1_index = 0;
      int T2_index = 0;
      unsigned long T1_timestamp = millis();
      unsigned long T2_timestamp = millis();
      bool T1_called = false;
      bool T2_called = false;

      while ((T1_index < T1_len) && (T2_index < T2_len)) {
        if (T1_index < (T1_len) && toothbrush_callback(TOOTHBRUSH1, T1_tones[T1_index], T1_delays[T1_index], T1_timestamp, &T1_called)) {
          T1_index += 1;
          T1_timestamp = millis();
        }
  
        if (T2_index < (T2_len) && toothbrush_callback(TOOTHBRUSH2, T2_tones[T2_index], T2_delays[T2_index], T2_timestamp, &T2_called)) {
          T2_index += 1;
          T2_timestamp = millis();
  
        }
      }
    }
  }
}
