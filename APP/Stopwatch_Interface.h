/*
 * Stopwatch.h
 *
 * Created: 4/1/2023 9:40:30 PM
 *  Author: Amm
 */ 


#ifndef STOPWATCH_H_
#define STOPWATCH_H_
#define START_BOS 10 
#define MODE_t 3
typedef enum{
	MODE_1 , 
	MODE_2 ,
	MODE_3 

}stopWatch_Mode_Type ; 
void StopWatch_Init() ;
void StopWatch_Rannable() ;
void StopWatch_Rannable_Seg();


#endif /* STOPWATCH_H_ */