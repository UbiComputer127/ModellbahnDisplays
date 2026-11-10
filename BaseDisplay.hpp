#pragma once
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

class BaseDisplay_Class
{
    public:
    // Constructor
    BaseDisplay_Class(uint8_t MuxAddress, uint8_t I2CAddress, uint8_t Width, uint8_t Height);

    // Inigtialisierung des Displays und löschen des Inhalts
    bool Init();

    Adafruit_SSD1306 Display_;

    protected:

    uint8_t MuxAddress_;

    private:

    static const uint8_t Tca9548Address = 0x70;
    uint8_t I2CAddress_;
    uint8_t Width_;
    uint8_t Height_; 
};

class I2cMultiplexer_Class
{
    public:
    I2cMultiplexer_Class(TwoWire & Wire, int ResetPort);

    void setChannel(uint8_t MuxAddress);

    void I2cMuxReset();

    private:
    static const uint8_t Tca9548Address = 0x70;
    TwoWire & Wire_;
    int ResetPort_;

};

extern  I2cMultiplexer_Class I2cMultiplexer_Object;

