#pragma once
#include "BaseDisplay.hpp"


class TimeTable_Class : public BaseDisplay_Class
{
    public:
    // Constructor
    TimeTable_Class(uint8_t MuxAddress, uint8_t I2CAddress, uint8_t Width, uint8_t Height);

    void updateTimeTable(int & Index);

    void process();

    // Init des Display
    void Init();

    bool selectTrainRow(int Index, std::string & Time, std::string & TrainNumber, std::string & Destination, std::string & Platform);

    bool ifChangeTable();

    int getCurrentIndex();

    static const std::string TimeTableTexts_[];
    static const int MaxIndex = 20;
    static const int Lines = 4;

    private:

    int Index;
    int LastIndex;
    unsigned long Time;
    static const unsigned long TimeDiff = 1000;

};

extern TimeTable_Class TimeTable_Object;