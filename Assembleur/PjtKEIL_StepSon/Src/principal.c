

#include "DriverJeuLaser.h"

extern void CallbackSon(void);
extern void LancerSon(void);
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

	
PWM_Init_ff(TIM3,3,720);
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
Active_IT_Debordement_Timer(TIM3,2,CallbackSon);
	
	

//============================================================================	
	// backup asm CallbackSon
	/*
	CallbackSon proc
	ldr r0,=LongueurSon ;}
	ldr r1,=Son         ;}
	ldr r2,[r0]         ;}	Build de l'adresse max dans R0
	lsl r2,#1           ;}	R0 = &Son + 2*LongueurSon
	add r2,r1           ;}
	mov r0,r2           ;}
	ldr r2,=Index
	push{r4}				;
	ldr r4,[r2]				;}
	mov r3,r4				;}
	pop{r4}					;}	Construction adresse courante du tableau dans R3, comparaison entre adresse actuelle(R3) et adresse max R0
	lsl r3,#1				;}	R1 = &Son
	add r3,r1				;}  R3 = R1 + 2*Index
	cmp r3,r0				;}  if R3<R0
	beq fin					;}
	ldrsh r0,[r3]		;}
	mov r3,#91			;}
	sdiv r0,r3			;}
	add r0,#360			;}Calcul de SortieSon et incrémentation index
	ldr r1,=SortieSon	;}SortieSon = *R3/91 +360
	strh r0,[r1]		;}Index++
	ldr r0,[r2]			;}
	add r0,#1			;}
	str r0,[r2]			;}
fin
	bx lr
	endp
*/
	
	LancerSon();
while	(1)
	{
	}
}

