// ## Requirements:
// -  FastLED by Daniel Garcia, v3.5.0
//
// ## Target:
// - LOLIN(WeMos) D1 mini Lite

#include <FastLED.h>

#define LED_PIN 14

#define FASTLED_ESP8266_D1_PIN_ORDER

#define NUM_LEDS_OUT 4 * 11
#define NUM_LEDS_MIDDLE 4 * 8
#define NUM_LEDS_IN 4 * 4
#define NUM_RINGS 3
#define NUM_LEDS NUM_LEDS_IN + NUM_LEDS_MIDDLE + NUM_LEDS_OUT
#define BRIGHTNESS 64
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 3

void setup()
{
    delay(300); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
    static uint8_t ringIndex = 0;
    ringIndex = ringIndex + 1;

    FillLedColorSequence(ringIndex);

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLedColorSequence(uint8_t ringIndex)
{
    CRGB color;
    if (ringIndex % NUM_RINGS == 0) {
      // color = CRGB::White
      fill_solid(&leds[0], NUM_LEDS_IN, CRGB::Black);
      fill_solid(&leds[NUM_LEDS_IN], NUM_LEDS_MIDDLE, CRGB::Black);
      fill_solid(&leds[NUM_LEDS_IN+NUM_LEDS_MIDDLE], NUM_LEDS_OUT, CRGB::White);
    }
    else if (ringIndex % NUM_RINGS == 1) {
      // color = CRGB::White
      fill_solid(&leds[0], NUM_LEDS_IN, CRGB::Black);
      fill_solid(&leds[NUM_LEDS_IN], NUM_LEDS_MIDDLE, CRGB::White);
      fill_solid(&leds[NUM_LEDS_IN+NUM_LEDS_MIDDLE], NUM_LEDS_OUT, CRGB::Black);
    }
    else if (ringIndex % NUM_RINGS == 2) {
      // color = CRGB::White
      fill_solid(&leds[0], NUM_LEDS_IN, CRGB::White);
      fill_solid(&leds[NUM_LEDS_IN], NUM_LEDS_MIDDLE, CRGB::Black);
      fill_solid(&leds[NUM_LEDS_IN+NUM_LEDS_MIDDLE], NUM_LEDS_OUT, CRGB::Black);
    }
}