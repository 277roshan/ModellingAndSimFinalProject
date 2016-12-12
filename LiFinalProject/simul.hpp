//
//  simul.hpp
//  LiFinalProject
//
//  Created by Roshan Thapaliya on 12/12/16.
//  Copyright © 2016 Roshan Thapaliya. All rights reserved.
//

#ifndef simul_hpp
#define simul_hpp

#include <stdio.h>




/////////////////////////////////////////////////////////////////////////
const int Queu_Limit=100;
const int BUSY=1;
const int IDLE=0;

int
choice,
Num_Completed_Customers,    //Number of Completed Customers
Number_of_Events,           //Number of Events 1.Arriving 2.Completion
Number_in_Queue,            //Number of Customers In Queue
Server_Status;              //Server Status ( Idle , Busy )

double
End_Time,
Type_Next_Event,
Mean_interArrival_Time,
Mean_service_Time,
Clock,
Time_Arrival[Queu_Limit + 1],
Service_Time[Queu_Limit + 1],
Next_Arrival_Time,
Next_Completion_Time,
Next_Service_Time,
Total_Flow_Time,
Progres_Arrival_Time,
Progres_Completion_Time,
Waiting_Time;


//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Prototype of the System Function

void  initialize();
void  Timing();
void  Arrival();
void  Completition();
float expon(float mean);
void  Search_Min(double[],double[]);

////////////////////////////////////////////////////////////////////////////////////






#endif /* simul_hpp */
