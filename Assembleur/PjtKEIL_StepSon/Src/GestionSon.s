	PRESERVE8
	THUMB   
		
	export CallbackSon
	extern Son
	export LancerSon
	extern LongueurSon
	include ./Driver/DriverJeuLaser.inc
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		

	
; ===============================================================================================
	
SortieSon dcw 0
	export SortieSon

Index dcd 5512
	export Index
		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici	



LancerSon 
	ldr r1,=Index
	mov r0,#0
	str r0,[r1]
	bx lr

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
	add r0,#360	
	ldr r1,=SortieSon	;}SortieSon = *R3/91 +360
	strh r0,[r1]
	push {lr}
	bl PWM_Set_Value_TIM3_Ch3
	pop {lr}
	ldr r2,=Index	
	ldr r0,[r2]	
	add r0,#1			;}
	str r0,[r2]			;}
	bx lr
fin
	mov r0, #0
	ldr r1,=SortieSon	;}SortieSon = *R3/91 +360
	strh r0,[r1]
	push {lr}
	bl PWM_Set_Value_TIM3_Ch3
	pop {lr}
	bx lr
	endp

		
		
	END	