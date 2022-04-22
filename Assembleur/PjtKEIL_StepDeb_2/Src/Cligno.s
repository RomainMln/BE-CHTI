	PRESERVE8
	THUMB   
	include ./Driver/DriverJeuLaser.inc	
	export callback
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		

	
; ===============================================================================================
	
FlagCligno dcd 0
	export FlagCligno



		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici	

callback proc
	ldr r1,=FlagCligno
	mov r0,#1
	ldr r3,[r1]
	cmp r3,#0
	bne allumer
	str r0,[r1]
	push {lr}
	bl GPIOB_Clear
	pop {pc}
allumer
	mov r2,#0
	str r2,[r1]
	push {lr}
	bl GPIOB_Set
	pop {pc}
	endp





		
		
	END	