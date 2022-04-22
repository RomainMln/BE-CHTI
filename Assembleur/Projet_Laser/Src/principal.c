

#include "DriverJeuLaser.h"
#include <stdio.h>
extern int DFT_ModuleAuCarre( short int * , char );
extern void CallbackSon(void);
extern void LancerSon(void);

extern short LeSignal[];
int test=0;
int result[4];
int score[4] = {0,0,0,0};
int seuil = 5000000;
short bon = 0;

short dma_buf[64];
void callback(){
	short compt = 0;
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	result[0]=DFT_ModuleAuCarre(dma_buf,17)>>1;
	result[1]=DFT_ModuleAuCarre(dma_buf,18)>>1;
	result[2]=DFT_ModuleAuCarre(dma_buf,19)>>1;
	result[3]=DFT_ModuleAuCarre(dma_buf,20)>>1;
	for(int i=0;i<4;i++){
		if(result[i]>seuil && bon==0){
			score[i]++;
			bon = 1;
			LancerSon();
		}
		else if (result[i]<seuil ){
			compt++;
			if(compt==4){
				bon = 0;
			}
		}
	}
}
	
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
  CLOCK_Configure();
	
	
	Systick_Period_ff(72000*5);
	Systick_Prio_IT(2,callback);
	SysTick_On;
	SysTick_Enable_IT;
	
	Init_TimingADC_ActiveADC_ff( ADC1, 72);
	Single_Channel_ADC(ADC1,2);
	Init_Conversion_On_Trig_Timer_ff(ADC1,TIM2_CC2,225);
	Init_ADC1_DMA1(0, dma_buf);
	
	PWM_Init_ff(TIM3,3,720);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	Timer_1234_Init_ff( TIM4,11000);
	Active_IT_Debordement_Timer(TIM4,2,CallbackSon);

//============================================================================	


while	(1)
	{
	}
}

