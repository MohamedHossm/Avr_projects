

#ifndef CONVERTER_INTERFACE_H_
#define CONVERTER_INTERFACE_H_
void Get_B(void);
static u8 Convert_H_D(u8 * data );

void Get_H(void);
typedef enum {
	DES,
	BIN,
	HEX
}chose_type;

void CONVEER_Init (void);
void CONVEER_Rannable (void);

#endif /* CONVERTER_INTERFACE_H_ */