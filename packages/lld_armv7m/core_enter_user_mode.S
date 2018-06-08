/*
 * Thread-Mode: from reset exception, use MSP by default, change to PSP
 * Handle-Mode: from other exception, use MSP
 *
 * Thread-Mode consist of Privilege-Mode and Unpriviledge-Mode.
 *
 * CONTROL[0] : MSP or PSP
 * CONTROL[1] : Privilege or not
 *
 * After enter unprivilege mode, user can't access SCS area.
 */
    .global core_enter_user_mode
core_enter_user_mode:
    mrs r0, control
    orr r0, r0, #3
    msr control, r0
    bx lr

