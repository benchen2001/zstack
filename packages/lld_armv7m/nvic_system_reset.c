
void nvic_system_reset(void)
{
    DSB();

    SCB->aircr = (0x5FA << SCB_AIRCR_VEC_OFFSET) |
                 (SCB->aircr & SCB_AIRCR_PRIOGROUP_MASK) |
                 (SCB_AIRCR_SYSTEM_RESET_MASK);

    DSB();

    while(1);
}

