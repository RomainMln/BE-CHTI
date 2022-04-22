

#include "DriverJeuLaser.h"
#include <stdio.h>
extern int DFT_ModuleAuCarre( short int * , char );
extern short LeSignal[];
int test=0;
int result[64];
int resultk1, resultk2, resultk3, resultk4, resultk5, resultk6;

short dma_buf[64];
void callback(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(int k=0;k<64;k++){
			result[k]= DFT_ModuleAuCarre(dma_buf,k);
	}
	resultk1=result[17];
	resultk2=result[18];
	resultk3=result[19];
	resultk4=result[20];
	resultk5=result[23];
	resultk6=result[24];
}
	
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();
	
	
	Systick_Period_ff(360000);
	Systick_Prio_IT(2,callback);
	SysTick_On;
	SysTick_Enable_IT;
	
	Init_TimingADC_ActiveADC_ff( ADC1, 72);
	Single_Channel_ADC(ADC1,2);
	Init_Conversion_On_Trig_Timer_ff(ADC1,TIM2_CC2,225);
	Init_ADC1_DMA1(0, dma_buf);

//============================================================================	

	
while	(1)
	{
	}
}

