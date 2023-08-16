#include <FastLED.h>

#define LED_PIN     14

#define FASTLED_ESP8266_D1_PIN_ORDER

#define NUM_LEDS_OUT 4*11
#define NUM_LEDS_MIDDLE 4*8
#define NUM_LEDS_IN 4*4
#define NUM_LEDS    NUM_LEDS_IN + NUM_LEDS_MIDDLE + NUM_LEDS_OUT
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 150

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


void setup() {
    delay(300); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}


void loop()
{
    // ChangePalettePeriodically();
    SetupBlackAndWhiteStripedPalette();

    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    CRGB led_color_buffer;
    for( int i = 0; i < NUM_LEDS; i++) {
        if (i == 0 | i == NUM_LEDS_IN || i == (NUM_LEDS_IN + NUM_LEDS_MIDDLE)) {
          led_color_buffer = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        } 
        colorIndex += 3;
        memcpy(&leds[i], &led_color_buffer, sizeof(CRGB));
    }
}

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        // if( secondHand == 0*7)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        // if( secondHand == 1*7)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        // if( secondHand == 2*7)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        // if( secondHand == 3*7)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 4*7)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        // if( secondHand == 5*7)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        // if( secondHand == 6*7)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};
