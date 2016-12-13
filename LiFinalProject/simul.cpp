//
//  simul.cpp
//  LiFinalProject
//
//  Created by Roshan Thapaliya on 12/12/16.
//  Copyright © 2016 Roshan Thapaliya. All rights reserved.
//

#include "simul.hpp"
#include "lcgrand.hpp"

#include<iostream>
#include <cmath>

//main function

int main(int argc, const char * argv[]) {
    
    initialize();           // Intialization of the System
    
    std::cout<<"                 * Single-server queueing system with fixed run *\n";
    
    std::cout<<"                 _________________________________________________"<<std::endl;
    
    std::cout<<"\n First In First Out"<<std::endl;
    
    choice = 1;
    
    std::cout<<"\nMean Inter arrival Time: "<<Mean_interArrival_Time;
    
    std::cout<<"\nMean Service Time: "<<Mean_service_Time<< std::endl;
    
    std::cout<<"The End of Simulation Time: "<<End_Time<<std::endl<<std::endl;
    
    
    while(true)
    {
        
        Timing();  // Timing Routine To Determine The Next Event
        
        if(Clock>End_Time)
            break;
        
        switch (int(Type_Next_Event))
        {
                
            case 1:
                Arrival();
                break;
                
            case 2:
                Completition();
                break;
        }
    }
    
    // Print Summary Statistics.
    
    std::cout<<"\nTotal Flow Time: "<<Total_Flow_Time;
    
    std::cout<<"\nTotal Waiting Time in Queue: "<<Waiting_Time;
    
    std::cout<<"\nAverage Waiting Time in Queue: "<<Waiting_Time / Num_Completed_Customers;
    
    std::cout<<"\nAverage Flow Time: "<<Total_Flow_Time / Num_Completed_Customers;
    
    std::cout<<"\nNumber of Completed Customers: "<<Num_Completed_Customers;
    
    std::cout<<"\nAverage Number of Customers In System / Unit Time: "<<Num_Completed_Customers / Clock<<std::endl<<std::endl;
    
    return 0;
    
}

//Intialization Function

void initialize()
{
    
    Number_of_Events = 2;      // Arrival , Completion
    
    Mean_interArrival_Time=3.0;
    
    Mean_service_Time=5.0;
    
    End_Time=100.0;
    
    Clock = 0.0;
    
    Server_Status = IDLE;
    
    Number_in_Queue = 0;
    
    Num_Completed_Customers = 0;
    
    Total_Flow_Time = 0.0;
    
    Waiting_Time = 0.0;
    
    Next_Arrival_Time = Clock + expon(Mean_interArrival_Time);//Arriving
    
    Next_Service_Time = expon(Mean_service_Time);
    
    Next_Completion_Time = 1.0e+10;    // Completing  Guarantening that the first event is arriving
    
    Progres_Arrival_Time=0.0;
    
    Progres_Completion_Time = 0.0;
}
//////////////////////////////////////////////////////////////////////////////
// Timing Routine Function

void Timing()
{
    Type_Next_Event = 0;
    
    
    
    //(TODO: thapaliya)Next_Completion_Time needs to be determined from the array
    
    if(Next_Arrival_Time < Next_Completion_Time)
    {
        
        Type_Next_Event = 1;
        
        Clock=Next_Arrival_Time;
        
    }
    
    else
    {
        Type_Next_Event = 2;
        
        Clock = Next_Completion_Time;
        
    }
    
    if (Type_Next_Event == 0)
    {
        std::cout<<"\nEvent List Empty at Time: "<<Clock;
        
        exit(1);
    }
    
}

////////////////////////////////////////////////////////////////////////////
// Arriving Customer function

void Arrival()
{
    
    // (TODO:thapaliya) Server status for each server needs to be busy then add in queue
    if (Server_Status == BUSY)
    {
        ++Number_in_Queue;
        
        if (Number_in_Queue > Queu_Limit)
        {
            std::cout<<"\nOverflow of the array time_arrival at";
            
            std::cout<<"time: "<<Clock;
            
            exit(2);
        }
        
        Time_Arrival[Number_in_Queue] = Clock;
        
        Service_Time[Number_in_Queue] = Next_Service_Time;
        
    }
    
    else
    {
        Server_Status = BUSY;
        
        Next_Completion_Time = Clock + Next_Service_Time;
        
        // (TODO:thapaliya) Add to array of completion time
        
        Progres_Arrival_Time = Next_Arrival_Time;
        
        Progres_Completion_Time = Next_Completion_Time;
        
    }
    
    Next_Arrival_Time = Clock + expon(Mean_interArrival_Time);
    
    Next_Service_Time = expon(Mean_service_Time);
    
    
}
/////////////////////////////////////////////////////////////////////////////
// Completion Customer Function

void Completition()
{
    
    double Delay;
    
    ++Num_Completed_Customers;
    
    Total_Flow_Time+= ( Progres_Completion_Time - Progres_Arrival_Time );
    
    
    if (Number_in_Queue == 0)
    {
        Server_Status= IDLE;
        
        Next_Completion_Time = 1.0e+10;      // High Value
    }
    
    else
    {
        
        if(choice==2)
            Search_Min(Time_Arrival,Service_Time);    // Minimum Processing Time
        
        Delay= Clock - Time_Arrival[1];
        
        Waiting_Time+= Delay;
        
        Next_Completion_Time = Clock + Service_Time[1];
        
        Progres_Arrival_Time = Time_Arrival[1];
        
        Progres_Completion_Time = Next_Completion_Time;
        
        --Number_in_Queue;
        
        for (int i=1;i<=Number_in_Queue;i++)
        {
            Time_Arrival[i] = Time_Arrival[i + 1];
            
            Service_Time[i] = Service_Time[i + 1];
        }
        
    }
}

/////////////////////////////////////////////////////////////////////////
//Sort Function
void Search_Min(double A_time[],double S_time[])
{
    int Min=1;
    
    double temp;
    
    for(int i=1;i<Number_in_Queue;i++)
        if(S_time[Min]>S_time[i+1])
            Min=i+1;
    
    temp=S_time[1];
    S_time[1]=S_time[Min];
    S_time[Min]=temp;
    
    temp=A_time[1];
    A_time[1]=A_time[Min];
    A_time[Min]=temp;
    
}

///////////////////////////////////////////////////////////////////////////
// Generate The Random Number

float expon(float mean)
{
    return (-mean * log(lcgrand(1)));
}
