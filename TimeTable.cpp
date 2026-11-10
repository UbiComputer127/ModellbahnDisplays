#include "TimeTable.hpp"

const std::string TimeTable_Class::TimeTableTexts_[] = 
{"16:21 C14 Thalheim  1",
 "16:30 C11 Chemnitz  2",
 "16:30 RB30 Zwickau  3",
 "16:30 RB35 Dresden  4",
 "16:31 RE6 Leipzig   5",
 "16:35 C14 Mittweida 1",
 "16:36 RB80 Cranzahl 2",
 "16:51 C13 Aue(Sa)   3",
 "16:54 RE3 Hof(Hbf)  4",
 "16:55 C15 Hainichen 5",
 "17:00 C7 Altchemn.  1",
 "17:04 RE3 Dresden   2",
 "17:05 RB30 Zwickau  3",
 "17:06 C8 Technopark 4",
 "17:07 C3 Burgstaedt 5",
 "17:10 RE6 Leipzig   1",
 "17:24 RE3 Glauchau  2",
 "17:50 RB40 Berlin   3",
 "18:00 C8 Technopark 4",
 "18:05 C3 Burgstaedt 5"};

TimeTable_Class::TimeTable_Class(uint8_t MuxAddress, uint8_t I2CAddress, uint8_t Width, uint8_t Height)
: BaseDisplay_Class(MuxAddress, I2CAddress, Width, Height)
, Index(0)
, LastIndex(0)
{
            
}

 void TimeTable_Class::Init()
 {
     // set I2C Multiplexer
      I2cMultiplexer_Object.setChannel(MuxAddress_); 

      BaseDisplay_Class::Init(); 

      // komplett löschen
      Display_.clearDisplay();

      // Textgrösse
      Display_.setTextSize(1);
      Display_.setTextColor(SSD1306_WHITE);

      // Tabellenheader zeichnen
      Display_.setCursor(0, 0);
      Display_.println("       Abfahrt  ");
      Display_.setCursor(0, 16);
      Display_.println("Zeit  Zug Ziel  Gleis");

      Display_.setCursor(0, 26);
      Display_.println(TimeTableTexts_[0].c_str());
      Display_.setCursor(0, 36);
      Display_.println(TimeTableTexts_[1].c_str());
      Display_.setCursor(0, 46);
      Display_.println(TimeTableTexts_[2].c_str());
      Display_.setCursor(0, 56);
      Display_.println(TimeTableTexts_[3].c_str());

       // Anzeigen 
      Display_.display(); 

      Time = millis() + TimeDiff;  
 }

void TimeTable_Class::updateTimeTable(int & Index)
{
     int MyIndex = Index;

     // set I2C Multiplexer
      I2cMultiplexer_Object.setChannel(MuxAddress_); 
      // komplett löschen
      Display_.clearDisplay();

      // Textgrösse
      Display_.setTextSize(1);
      Display_.setTextColor(SSD1306_WHITE);

      // Tabellenheader zeichnen
      Display_.setCursor(0, 0);
      Display_.println("       Abfahrt  ");
      Display_.setCursor(0, 16);
      Display_.println("Zeit  Zug Ziel  Gleis");

      Display_.setCursor(0, 26);
      Display_.println(TimeTableTexts_[MyIndex].c_str());
      MyIndex++; MyIndex %= MaxIndex;
      Display_.setCursor(0, 36);
      Display_.println(TimeTableTexts_[MyIndex].c_str());
      MyIndex++; MyIndex %= MaxIndex;
      Display_.setCursor(0, 46);
      Display_.println(TimeTableTexts_[MyIndex].c_str());
      MyIndex++; MyIndex %= MaxIndex;
      Display_.setCursor(0, 56);
      Display_.println(TimeTableTexts_[MyIndex].c_str());
      MyIndex++; MyIndex %= MaxIndex;

      Index++;
      Index %= MaxIndex;

       // Anzeigen 
      Display_.display();      
}

void TimeTable_Class::process()
{
     if (millis() >= Time)
     {
          Time = millis() + TimeDiff;
          updateTimeTable(Index);
     }
}

bool TimeTable_Class::selectTrainRow(int Index, std::string & Time, std::string & TrainNumber, std::string & Destination, std::string & Platform)
{
     bool Return = false; 
     if (Index < MaxIndex)
     {
          Return = true;
          std::string TempString = TimeTableTexts_[Index];
          int Pos = TempString.find_first_of(" ");
          Time = TempString.substr(0, Pos);
          TempString.erase(0, Pos+1);
          // Serial.println(TempString.c_str());
          Pos = TempString.find_first_of(" ");
          TrainNumber = TempString.substr(0, Pos);
          TempString.erase(0, Pos+1);
          Pos = TempString.find_first_of(" ");
          Destination = TempString.substr(0, Pos);
          TempString.erase(0, Pos+1);
          Platform = TempString;
     }
     return Return;
}

bool TimeTable_Class::ifChangeTable()
{
     bool Return = false;
     if (Index != LastIndex)
     {
          LastIndex = Index;
          Return = true;
     }
     return Return;
}

int TimeTable_Class::getCurrentIndex()
{
     return Index;
}


TimeTable_Class TimeTable_Object(2, 0x3C, 128, 64);
