#ifndef PERIPHERAL_ST_I2C_H
#define PERIPHERAL_ST_I2C_H

#include <io/types.h>

struct I2C_CONTROLLER {
    VU32 CR1;
    VU32 CR2;
    VU32 OAR1;
    VU32 OAR2;
    VU32 DR;
    VU32 SR1;
    VU32 SR2;
    VU32 CCR;
    VU32 TRISE;
};

#endif
