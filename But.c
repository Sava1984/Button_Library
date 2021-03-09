#include "main.h"
#include "But.h"

//uint8_t Button_State = 0;
//uint8_t PressOk=0;
//uint8_t PressOk_LongPress = 0;
//uint32_t Button_Timer=0,Deb_Timer = 0;
//uint32_t Button_Release_Timer;
//uint32_t Deb_Timer_Reset;
//uint32_t Button_Double_Press_Timer = 0;
void Button_Set_State ( BUTTON *But,uint8_t State)
{
	But->But_State = State;
	But->Deb_Timer = 0;
}
uint8_t Button_Get_State (BUTTON *But)
{
	return But->But_State;
}


void But_Poll ( BUTTON *But)
{
	if (!HAL_GPIO_ReadPin(But->BUT_GPIO,But->BUT_Pin))
		{
			
			But->Deb_Timer++;
			if (But->Deb_Timer>50)				// Таймер дребезга. 
			{
				if (!But->PressOk_LongPress)
					{	// Если события долгого нажатия не было, 
					
						if (But->Button_Timer>2000)	// Кнопку держали 2 сек
						{
							But->PressOk_LongPress = 1;//устанавливаем событие долгого нажатия
							Button_Set_State(But,BUT_STATE_LONG_PRESS);
							But->Button_Timer = 0;
							But->PressOk =0;						//Обнуляем событие быстрого нажатия
						}
						else
						{											//запускаем  nfqvth
							But->PressOk = 1;				//устанавливаем событие быстрого нажатия
							But->Button_Timer++;
						}
					}	
			}
			But->Deb_Timer_Reset = 0;
		}
		else 												//отпустили кнопку
		{
			if (But->PressOk)							
			{
				if (But->Deb_Timer_Reset>50)
					{
						if (But->Button_Timer<2000)
							{
								Button_Set_State(But,BUT_STATE_PRESSED);
							}
						But->PressOk = 0;	
					}
			}
			But->PressOk_LongPress = 0;
			But->Deb_Timer_Reset++;
			But->Button_Timer = 0;
			But->Deb_Timer = 0;
		}
}
