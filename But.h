#include "main.h"

#define BUT_STATE_NOT_PRESSED		0
#define	BUT_STATE_PRESSED				1
#define	BUT_STATE_LONG_PRESS		2
#define BUT_SATET_DOUBLE_PRESS	3

typedef struct 
{
	GPIO_TypeDef* BUT_GPIO;
	uint16_t BUT_Pin;
	uint8_t But_State;
	uint32_t Deb_Timer;
	uint8_t PressOk_LongPress;
	uint32_t Button_Timer;
	uint32_t Deb_Timer_Reset;
	uint8_t PressOk;
} BUTTON;

void Button_Set_State ( BUTTON *But,uint8_t State);
uint8_t Button_Get_State (BUTTON *But);
void But_Poll ( BUTTON *But);
