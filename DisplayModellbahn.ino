
#include "TrainDisplay.hpp"
#include "TimeTable.hpp"

void setup()
{
    Serial.begin(9600);
    // Wait for display
    I2cMultiplexer_Object.I2cMuxReset();

		Platform1Normal_Object.Init();
		Platform2Normal_Object.Init();
		
		TimeTable_Object.Init();
}

void loop()
{
		TimeTable_Object.process();
		if (TimeTable_Object.ifChangeTable())
		{
				std::string Time;
				std::string TrainNumber;
				std::string Destination;
				std::string Platform;
				if (TimeTable_Object.selectTrainRow(TimeTable_Object.getCurrentIndex(),
				                   									Time,
													 									TrainNumber,
													 									Destination,
													 									Platform))
				{
						Serial.println("new Platform");
						int NumPlatform = atoi(Platform.c_str());
						Serial.print(Time.c_str());
						Serial.print(" ");
						Serial.print(TrainNumber.c_str());
						Serial.print(" ");
						Serial.print(Destination.c_str());
						Serial.print(" ");
						Serial.println(NumPlatform);
						switch (NumPlatform)
						{
								case 1:
									Platform1Normal_Object.writeDepartureTimeLeft(Time);
									Platform1Normal_Object.writeDestination1Left(Destination);
									Platform1Normal_Object.writeTrainNumberLeft(TrainNumber);
									Platform1Normal_Object.UdateDisplay();
								break;
								case 2:
									Platform1Normal_Object.writeDepartureTimeRight(Time);
									Platform1Normal_Object.writeDestination1Right(Destination);
									Platform1Normal_Object.writeTrainNumberRight(TrainNumber);
									Platform1Normal_Object.UdateDisplay();
								break;
								case 3:
									Platform2Normal_Object.writeDepartureTimeLeft(Time);
									Platform2Normal_Object.writeDestination1Left(Destination);
									Platform2Normal_Object.writeTrainNumberLeft(TrainNumber);
									Platform2Normal_Object.UdateDisplay();
								break;
								case 4:
									Platform2Normal_Object.writeDepartureTimeRight(Time);
									Platform2Normal_Object.writeDestination1Right(Destination);
									Platform2Normal_Object.writeTrainNumberRight(TrainNumber);
									Platform2Normal_Object.UdateDisplay();
								break;
								case 5:
								break;
						}

				}
		}

		
}

