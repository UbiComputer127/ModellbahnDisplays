#pragma once
#include "BaseDisplay.hpp"

class TrainDisplay_Class : public BaseDisplay_Class
{
    public:

    enum Position_Enum
    {
        FORWARD,
        BACKWARD
    };

		struct PlatformText_Struct
		{
			  std::string TrainNumber;
			  std::string DepartureTime;
			  std::string Destination1;
			  std::string Destination2;
			  uint8_t TrainNumberX;
			  uint8_t TrainNumberY;
			  uint8_t TimeX;
			  uint8_t TimeY;
			  uint8_t Destination1X;
			  uint8_t Destination1Y;
			  uint8_t Destination2X;
			  uint8_t Destination2Y;
		};

		struct DisplayText_Struct
		{
				struct PlatformText_Struct PlatformLeft;
				struct PlatformText_Struct PlatformRight;
		};

    // Constructor
    TrainDisplay_Class(uint8_t MuxAddress, uint8_t I2CAddress, uint8_t Width, uint8_t Height, Position_Enum Position);

    // Init des Display
    void Init();

    // Anzeige der Zugnummer
    void writeTrainNumberLeft(std::string NumberText);
    void writeTrainNumberRight(std::string NumberText);

    // Anzeige Abfahrtszeit
    void writeDepartureTimeLeft(std::string DestinationText);
    void writeDepartureTimeRight(std::string DestinationText);

    // Anzeige Zielort1
    void writeDestination1Left(std::string DestinationText);
    void writeDestination1Right(std::string DestinationText);
    
     // Anzeige Zielort2
    void writeDestination2Left(std::string DestinationText);
    void writeDestination2Right(std::string DestinationText);

		void UdateDisplay();

    void setDisplayTexte(std::string TrainNumberLeft, std::string TrainNumberRight,
                         std::string DepartureTimeLeft, std::string DepartureTimeRight, 
                         std::string Destination1Left, std::string Destination1Right, 
                         std::string Destination2Left, std::string Destination2Right);
     
    private:

		static const uint8_t LineUpX = 64;
		static const uint8_t LineUpY = 0;
		static const uint8_t LineDownX = 64;
		static const uint8_t LineDownY = 31;
		 
    static const uint16_t RightTrainNumberPosX = LineUpX+2;
    static const uint16_t RightTrainNumberPosY = 0;
    static const uint16_t RightDestination1PosX = LineUpX+2;
    static const uint16_t RightDestination1PosY = 13;
		static const uint16_t RightDestination2PosX = LineUpX+2;
    static const uint16_t RightDestination2PosY = 25;
    static const uint16_t RightDepartureTimePosX = LineUpX+32;
    static const uint16_t RightDepartureTimePosY = 0;

		static const uint16_t LeftTrainNumberPosX = 0;
    static const uint16_t LeftTrainNumberPosY = 0;
    static const uint16_t LeftDestination1PosX = 0;
    static const uint16_t LeftDestination1PosY = 13;
		static const uint16_t LeftDestination2PosX = 0;
    static const uint16_t LeftDestination2PosY = 25;
    static const uint16_t LeftDepartureTimePosX = 34;
    static const uint16_t LeftDepartureTimePosY = 0;

    Position_Enum Position_;
		DisplayText_Struct DisplayText_;
};

extern TrainDisplay_Class Platform1Normal_Object;
extern TrainDisplay_Class Platform2Normal_Object;