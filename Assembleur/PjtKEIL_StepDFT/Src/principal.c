

#include "DriverJeuLaser.h"
#include <stdio.h>
extern int DFT_ModuleAuCarre( short int * , char );
extern short LeSignal[];
int test;
int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

	test = DFT_ModuleAuCarre(LeSignal,7);
	printf("%d\n",test);
	

//============================================================================	
	
	
while	(1)
	{
	}
}

