

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif


#define PIN_START 2
#define PIN_SW1 3
#define PIN_SW2 4
#define PIN_SW3 5
#define PIN_SW4 6
#define PIN_SW5 7
#define PIN_SW6 8
#define PIN_SW7 9
#define PIN_WS2812 10
#define PIN_LED 13


#define SEGMENTS_COUNT 54
#define LED_COUNT 197
#define BRIGHTNESS 250  // Set BRIGHTNESS to about 1/5 (max = 255)


int seg_start[SEGMENTS_COUNT] = {
  0, 4, 8, 12,
  15, 19, 23,
  26, 30, 34,
  37, 40, 44,
  47, 50, 54,
  57, 60, 64,
  67, 70, 74,
  77, 81, 85, 89,
  92, 96, 100, 104,
  107, 111, 115, 119,
  122, 126, 130, 134,
  137, 141, 145, 149,
  152, 156, 160, 164,
  167, 171, 175, 179,
  182, 186, 190, 194
};


Adafruit_NeoPixel strip(LED_COUNT, PIN_WS2812, NEO_RGB + NEO_KHZ800);

char buf[SEGMENTS_COUNT + 1];

int sw_state = 0;  // здесь собираем статус элементов управления

void setup() {

  pinMode(PIN_START, INPUT);
  pinMode(PIN_SW1, INPUT);
  pinMode(PIN_SW2, INPUT);
  pinMode(PIN_SW3, INPUT);
  pinMode(PIN_SW4, INPUT);
  pinMode(PIN_SW5, INPUT);
  pinMode(PIN_SW6, INPUT);
  pinMode(PIN_SW7, INPUT);
  pinMode(PIN_WS2812, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(9600);
  Serial.setTimeout(500);

  strip.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.setBrightness(BRIGHTNESS);

  for (int j = 0; j < (SEGMENTS_COUNT + 1); j++) {
    for (int i = 0; i < SEGMENTS_COUNT; i++) {
      if (i == j) {
        set_segment(i, true);
      } else {
        set_segment(i, false);
      }
    }
    strip.show();
    delay(5);
  }
}

void loop() {

  digitalWrite(PIN_LED, digitalRead(PIN_START));

  sw_state = (digitalRead(PIN_START)) | (digitalRead(PIN_SW1) << 1) | (digitalRead(PIN_SW2) << 2) | (digitalRead(PIN_SW3) << 3) | (digitalRead(PIN_SW4) << 4) | (digitalRead(PIN_SW5) << 5) | (digitalRead(PIN_SW6) << 6) | (digitalRead(PIN_SW7) << 7);
  Serial.write(sw_state);

  if (Serial.available() > 0) {

    if (Serial.readBytesUntil('\n', buf, SEGMENTS_COUNT) == SEGMENTS_COUNT) {
      for (int i = 0; i < SEGMENTS_COUNT; i++) {
        set_segment(i, (bool)buf[i]);
      }
    } else {
      Serial.flush();
    };
  }
  strip.show();
  delay(50);
}


void set_segment(int seg_num, bool state) {
  int col;
  if (state) {
    col = 255;
  } else {
    col = 0;
  };

//  strip.setPixelColor(seg_num, strip.Color(0, col, 0, 255));      // Set color

  
  strip.setPixelColor(seg_start[seg_num], strip.Color(0, col, 0, 255));      // Set color
  strip.setPixelColor(seg_start[seg_num] + 1, strip.Color(0, col, 0, 255));  // Set color
  strip.setPixelColor(seg_start[seg_num] + 2, strip.Color(0, col, 0, 255));  // Set color
  
}