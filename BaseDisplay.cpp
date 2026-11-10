#include "Arduino.h"
#include "BaseDisplay.hpp"

//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32, 

BaseDisplay_Class::BaseDisplay_Class(uint8_t MuxAddress, uint8_t I2CAddress, uint8_t Width, uint8_t Height)
: MuxAddress_(MuxAddress)
, I2CAddress_(I2CAddress)
, Width_(Width)
, Height_(Height)
, Display_(Width, Height)
{
    
}

bool BaseDisplay_Class::Init()
{
    bool Return = Display_.begin(SSD1306_SWITCHCAPVCC, I2CAddress_);
    if (Return == false)
    {
        Serial.println(F("SSD1306 allocation failed"));
    }
    else
    {
        Display_.clearDisplay();
        Display_.display(); 
    }
}

I2cMultiplexer_Class::I2cMultiplexer_Class(TwoWire & Wire, int ResetPort)
: Wire_(Wire)
, ResetPort_(ResetPort)
{
   
}

// setzen des Multiplexers
 void  I2cMultiplexer_Class::setChannel(uint8_t MuxAddress)
 {
    Wire_.beginTransmission(Tca9548Address);
    Wire_.write(1 << MuxAddress);
    Wire_.endTransmission(); 
    delay(5);      
 }

 // Reset des Multiplexers
 void I2cMultiplexer_Class::I2cMuxReset()
 {
    // Port setzen A3
    pinMode(ResetPort_, OUTPUT);        
    digitalWrite(ResetPort_, LOW);
    delay(500);
    digitalWrite(ResetPort_, HIGH);

    Wire_.begin();
 }
 
 I2cMultiplexer_Class I2cMultiplexer_Object(Wire, A3);

