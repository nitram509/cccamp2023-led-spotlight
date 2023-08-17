// ## Requirements:
// -  FastLED by Daniel Garcia, v3.5.0
//
// ## Target:
// - LOLIN(WeMos) D1 mini Lite
//   (You might need to install the board first https://github.com/esp8266/Arduino)

#include <FastLED.h>

#define LED_PIN 14

#define FASTLED_ESP8266_D1_PIN_ORDER

#define NUM_LEDS_OUT 4 * 11
#define NUM_LEDS_MIDDLE 4 * 8
#define NUM_LEDS_IN 4 * 4
#define NUM_RINGS 3
#define NUM_LEDS NUM_LEDS_IN + NUM_LEDS_MIDDLE + NUM_LEDS_OUT
#define BRIGHTNESS 255
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 3

CRGBPalette16 currentPalette;
TBlendType currentBlending;


CRGB leds[NUM_LEDS];
CRGB grey50;
CRGB grey40;
CRGB grey30;
CRGB grey20;
CRGB grey10;
CRGB rainbow;


void setup()
{
    delay(300); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    grey50 = CRGB::White;
    grey50.fadeToBlackBy(128);

    grey40 = CRGB::White;
    grey40.fadeToBlackBy(128+25);

    grey30 = CRGB::White;
    grey30.fadeToBlackBy(128+25+25);

    grey20 = CRGB::White;
    grey20.fadeToBlackBy(200);

    grey10 = CRGB::White;
    grey10.fadeToBlackBy(228);

    currentPalette = RainbowStripeColors_p;

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
  
    rainbow = ColorFromPalette(currentPalette, ringIndex, BRIGHTNESS, currentBlending);
    if (ringIndex % NUM_RINGS == 0) {
      // color = CRGB::White
      fill_solid(&leds[0], NUM_LEDS_IN, CRGB::Black);
      fill_solid(&leds[NUM_LEDS_IN], NUM_LEDS_MIDDLE, CRGB::Black);
      // fill_solid(&leds[NUM_LEDS_IN+NUM_LEDS_MIDDLE], NUM_LEDS_OUT, grey20);
      // color: Rainbow     
      fill_solid(&leds[NUM_LEDS_IN+NUM_LEDS_MIDDLE], NUM_LEDS_OUT, rainbow);

    }
    else if (ringIndex % NUM_RINGS == 1) {
      // color = CRGB::White
      fill_solid(&leds[0], NUM_LEDS_IN, CRGB::Black);
      // fill_solid(&leds[NUM_LEDS_IN], NUM_LEDS_MIDDLE, grey40);
      // color: Rainbow 
      fill_solid(&leds[NUM_LEDS_IN], NUM_LEDS_MIDDLE, rainbow);
      fill_solid(&leds[NUM_LEDS_IN+NUM_LEDS_MIDDLE], NUM_LEDS_OUT, CRGB::Black);
    }
    else if (ringIndex % NUM_RINGS == 2) {
      // color = CRGB::White
      // fill_solid(&leds[0], NUM_LEDS_IN, CRGB::White);
      // color: Rainbow 
      fill_solid(&leds[0], NUM_LEDS_IN, rainbow);
      fill_solid(&leds[NUM_LEDS_IN], NUM_LEDS_MIDDLE, CRGB::Black);
      fill_solid(&leds[NUM_LEDS_IN+NUM_LEDS_MIDDLE], NUM_LEDS_OUT, CRGB::Black);
    }
}