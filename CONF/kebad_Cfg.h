

#ifndef KEBAD_CFG_H_
#define KEBAD_CFG_H_
#define KEY_MARTIX_SIZE 4
#define KEY_ 2
#define KEY_COL 4
#define KEY_ROW 4
static DIO_Pin_type intrerface [KEY_][KEY_MARTIX_SIZE] = {
	{PINC0, PINC1,PINC2,PINC3},
	{PIND4, PIND5,PIND2,PIND3}
	
};
static u8 keys_ret [KEY_ROW][KEY_COL]= {
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'},
};



#endif /* KEBAD_CFG_H_ */