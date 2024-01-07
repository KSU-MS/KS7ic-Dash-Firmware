

#include "IC_Dash.h"



IC_Dash::IC_Dash()
{
    Serial.begin(9600);
    Serial.println("Yippie");

    pinMode(LOWV_EN, OUTPUT);
    pinMode(GEAR_EN, OUTPUT);

    pinMode(BCD_A, OUTPUT);
    pinMode(BCD_B, OUTPUT);
    pinMode(BCD_C, OUTPUT);
    pinMode(BCD_D, OUTPUT);

    digitalWrite(LOWV_EN, HIGH);
    delayMicroseconds(500);
}

IC_Dash::~IC_Dash()
{
    Serial.println("Bye Bye..");
}


void IC_Dash::initDashLEDs()
{
    FastLED.addLeds<WS2812, TACH_DPIN, GRB>(this->tachLEDs, TACH_LEDS);
    FastLED.addLeds<WS2812, INDI_DPIN, GRB>(this->indiLEDs, INDI_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.setBrightness(10);

    // fill_gradient(this->tachLEDs, TACH_LEDS - 1, CHSV(0, 255, 255), 0, CHSV(70, 255, 255), SHORTEST_HUES);
}


void IC_Dash::handleTachometer(uint16_t rpm)
{
    CRGB* leds = this->tachLEDs;

    int height = map(rpm, 0, MAX_RPM, 0, TACH_LEDS + 1);

    fill_gradient(leds, TACH_LEDS - 1, CHSV(0, 255, 255), 0, CHSV(70, 255, 255), SHORTEST_HUES);

    for (int i = 0; i < TACH_LEDS; i++) 
    {
        if (i >= height)
        {
            leds[i] = CRGB::Black;
        }
    }

    FastLED.show();
}

void IC_Dash::handleGear(uint8_t num)
{
    digitalWrite(GEAR_EN, LOW);
    delayMicroseconds(100);
    
    switch (num)
    {
    case 0:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 1:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 2:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 3:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, LOW);
        break;
    case 4:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 5:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 6:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 7:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, HIGH);
        digitalWrite(BCD_C, HIGH);
        digitalWrite(BCD_D, LOW);
        break;
    case 8:
        digitalWrite(BCD_A, LOW);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, HIGH);
        break;
    case 9:
        digitalWrite(BCD_A, HIGH);
        digitalWrite(BCD_B, LOW);
        digitalWrite(BCD_C, LOW);
        digitalWrite(BCD_D, HIGH);
        break;
    default:
        break;
    }

    delayMicroseconds(100);
    digitalWrite(GEAR_EN, HIGH);
    delayMicroseconds(100);
}



