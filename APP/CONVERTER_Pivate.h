


#ifndef CONVERTER_PIVATE_H_
#define CONVERTER_PIVATE_H_

static u8 strings [3][4]=
{
	"DES" , "BIN" , "HEX"
};
static chose_type from = DES ;
static chose_type TO = DES ;
static u32 num = 0 ;
static u8 binary_pos = 0 ;
static char bin_str[9] ={"        "};
static u8 hex_str[3] ={"  "};
static u8 hex_pos = 0 ;
static u8 key = 0 ;
static u8 flag = 0  ;
static u8 moves = 0 ;
static void Chose_Convert();
static u8 Convert_B_D(u8 * data );
//static void Convert_get_B (u8 key , u8 *str , u8 pos);
//static void Convert_get_D (u8 key , u32 *num );
void Get_B();
void Get_H();
void Get_D ();
void Set_H();
void Set_B();
void Set_D();
void Reset_Valls();




#endif /* CONVERTER_PIVATE_H_ */