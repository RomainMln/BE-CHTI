

#include "../Driver/DriverJeuLaser.h"
#include "../Driver/Affichage_Valise.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void Prepare_Afficheur(char Aff, char Valeur);
extern int DFT_ModuleAuCarre( short int * , char );
extern void CallbackSon(void);
extern void LancerSon(void);

extern short LeSignal[];
int test=0;
int result[4];
int score[4] = {0,0,0,0};
int seuil = 1000000;
short bon = 0;
int random;

void AfficheAll(){
	int aff =0;
	for(int k=1;k<=4;k++){
		aff = score[k-1];
		if(aff >99)
			Prepare_Afficheur(k,99);
		else
			Prepare_Afficheur(k,aff);
			Prepare_Clear_Point_Unite(k);
	}
	Prepare_Set_LED(random);
	Choix_Capteur(random+1);
	
}

short dma_buf[64];
void callback(){
	int mem ; 
	short compt = 0;
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	result[0]=DFT_ModuleAuCarre(dma_buf,17);
	result[1]=DFT_ModuleAuCarre(dma_buf,18);
	result[2]=DFT_ModuleAuCarre(dma_buf,19);
	result[3]=DFT_ModuleAuCarre(dma_buf,20);
	for(int i=0;i<4;i++){
		if(result[i]>seuil && bon==0){
			score[i]++;
			bon = 1;
			//afficheurs(i+1,score[i]);
			LancerSon();
			Prepare_Clear_LED(random);
			srand(rand()%RAND_MAX);
			mem = random;
			while(random == mem )
				random = rand() % 4;
			AfficheAll();
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
	
	srand(rand()%RAND_MAX);
	random = rand() % 4;
	Init_Affichage();
	/*for(int k=1;k<=4;k++){
		Prepare_Afficheur(k,score[k-1]);
		Prepare_Clear_Point_Unite(k);
	}
	Prepare_Set_LED(LED_Cible_1);
	Choix_Capteur(1);
	Mise_A_Jour_Afficheurs_LED();
	*/
	
//============================================================================	
AfficheAll();

while	(1)
	{
		Mise_A_Jour_Afficheurs_LED();
	}
}

