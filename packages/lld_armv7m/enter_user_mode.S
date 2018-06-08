	.global enter_user_mode

enter_user_mode:
	mrs r0, control
	orr r0, #3
	msr control, r0
	bx lr

