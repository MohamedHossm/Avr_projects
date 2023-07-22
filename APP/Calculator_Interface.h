

#ifndef CALCULATOR_INTERFACE_H_
#define CALCULATOR_INTERFACE_H_
typedef struct {
	u8 N_1_S ;
	u8 N_2_S ;
	u8 OP ;
	s64 num_1 ;
	s64 num_2 ;
	s64 res;
}calculater_Frame_type;

void Calculator_Init(void);
void Calculator_Rannable(void);
s32 Sum(s32 data1 , s32 data2 );
s32 MuL(s32 data1 , s32 data2 );
s32 Div(s32 data1 , s32 data2 );
s32 Sub(s32 data1 , s32 data2 );
void reset_Cal();
void print_Calcaulator(void);
u8 handel_fun(u8 data_in);
#endif /* CALCULATOR_INTERFACE_H_ */