
#include "TrainDisplay.hpp"

TrainDisplay_Class::TrainDisplay_Class(uint8_t MuxAddress, uint8_t I2CAddress, uint8_t Width, uint8_t Height, Position_Enum Position)
: BaseDisplay_Class(MuxAddress, I2CAddress, Width, Height)
, Position_(Position)
{
    DisplayText_ = {{"Re123", "12:30", "Chemnitz", "   ", 
                    LeftTrainNumberPosX, LeftTrainNumberPosY,
                    LeftDepartureTimePosX, LeftDepartureTimePosY,
                    LeftDestination1PosX, LeftDestination1PosY,
                    LeftDestination2PosX, LeftDestination2PosY},
                    {"Re99", "12:40", "Plauen", "   ", 
                    RightTrainNumberPosX, RightTrainNumberPosY,
                    RightDepartureTimePosX, RightDepartureTimePosY,
                    RightDestination1PosX, RightDestination1PosY,
                    RightDestination2PosX, RightDestination2PosY}};       
}

 void TrainDisplay_Class::Init()
 {
    I2cMultiplexer_Object.setChannel(MuxAddress_); 
    BaseDisplay_Class::Init();
  
      if (Position_ == BACKWARD)
      {
          Display_.setRotation(2);
          Display_.ssd1306_command(0x80);
      } 
 }

void TrainDisplay_Class::UdateDisplay()
{
    // set I2C Multiplexer
    I2cMultiplexer_Object.setChannel(MuxAddress_); 
    // komplett löschen
    Display_.clearDisplay();

    // Linie in der Mitte zeichnen
    Display_.drawLine(LineUpX, LineUpY, LineDownX, LineDownY, SSD1306_WHITE); 
    // Textgrösse
    Display_.setTextSize(1);
    Display_.setTextColor(SSD1306_WHITE);

    // Zug Nummer Links
    Display_.setCursor(DisplayText_.PlatformLeft.TrainNumberX,DisplayText_.PlatformLeft.TrainNumberY);
    Display_.println(DisplayText_.PlatformLeft.TrainNumber.c_str());
    // Abfahrtszeit links
    Display_.setCursor(DisplayText_.PlatformLeft.TimeX, DisplayText_.PlatformLeft.TimeY);
    Display_.println(DisplayText_.PlatformLeft.DepartureTime.c_str());
    // Zielort 1 links
    Display_.setCursor(DisplayText_.PlatformLeft.Destination1X, DisplayText_.PlatformLeft.Destination1Y);
    Display_.println(DisplayText_.PlatformLeft.Destination1.c_str());
    // Zielort 2 links
    Display_.setCursor(DisplayText_.PlatformLeft.Destination2X, DisplayText_.PlatformLeft.Destination2Y);
    Display_.println(DisplayText_.PlatformLeft.Destination2.c_str());

    // Zug Nummer rechts
    Display_.setCursor(DisplayText_.PlatformRight.TrainNumberX,DisplayText_.PlatformRight.TrainNumberY);
    Display_.println(DisplayText_.PlatformRight.TrainNumber.c_str());
    // Abfahrtszeit links
    Display_.setCursor(DisplayText_.PlatformRight.TimeX, DisplayText_.PlatformRight.TimeY);
    Display_.println(DisplayText_.PlatformRight.DepartureTime.c_str());
    // Zielort 1 links
    Display_.setCursor(DisplayText_.PlatformRight.Destination1X, DisplayText_.PlatformRight.Destination1Y);
    Display_.println(DisplayText_.PlatformRight.Destination1.c_str());
    // Zielort 2 links
    Display_.setCursor(DisplayText_.PlatformRight.Destination2X, DisplayText_.PlatformRight.Destination2Y);
    Display_.println(DisplayText_.PlatformRight.Destination2.c_str());

    // Anzeigen 
    Display_.display();
}

void TrainDisplay_Class::setDisplayTexte(std::string TrainNumberLeft, std::string TrainNumberRight,
                                         std::string DepartureTimeLeft, std::string DepartureTimeRight, 
                                         std::string Destination1Left, std::string Destination1Right, 
                                         std::string Destination2Left, std::string Destination2Right)
{
    writeTrainNumberLeft(TrainNumberLeft);
    writeTrainNumberRight(TrainNumberRight);
    writeDepartureTimeLeft(DepartureTimeLeft);
    writeDepartureTimeRight(DepartureTimeRight);
    writeDestination1Left(Destination1Left);
    writeDestination1Right(Destination1Right);
    writeDestination2Left(Destination2Left);
    writeDestination2Right(Destination2Right);
    UdateDisplay();
}

 void TrainDisplay_Class::writeTrainNumberLeft(std::string TrainNumber)
 {
      DisplayText_.PlatformLeft.TrainNumber = TrainNumber;   
 }

 void TrainDisplay_Class::writeTrainNumberRight(std::string TrainNumber)
 {
      DisplayText_.PlatformRight.TrainNumber = TrainNumber;   
 }

// Anzeige Abfahrtszeit
void TrainDisplay_Class::writeDepartureTimeLeft(std::string Time)
{
    DisplayText_.PlatformLeft.DepartureTime = Time;
}

void TrainDisplay_Class::writeDepartureTimeRight(std::string Time)
{
    DisplayText_.PlatformRight.DepartureTime = Time;
}

// Anzeige Zielort1
void TrainDisplay_Class::writeDestination1Left(std::string DestinationText)
{
    DisplayText_.PlatformLeft.Destination1 = DestinationText;
}

void TrainDisplay_Class::writeDestination1Right(std::string DestinationText)
{
    DisplayText_.PlatformRight.Destination1 = DestinationText;
}
    
// Anzeige Zielort2
void TrainDisplay_Class::writeDestination2Left(std::string DestinationText)
{
     DisplayText_.PlatformLeft.Destination2 = DestinationText;
}

void TrainDisplay_Class::writeDestination2Right(std::string DestinationText)
{
     DisplayText_.PlatformRight.Destination2 = DestinationText;
}

 // Objekte
 TrainDisplay_Class Platform1Normal_Object(0, 0x3C, 128, 32, TrainDisplay_Class::FORWARD);
 TrainDisplay_Class Platform2Normal_Object(1, 0x3C, 128, 32, TrainDisplay_Class::FORWARD);
 