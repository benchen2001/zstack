#ifndef DW_I2C_H
#define DW_I2C_H

#include <types.h>

struct dw_i2c_regs
{
    VU32 CON;
    VU32 TAR;
    VU32 SAR;
    VU32 HS_MADDR;
    VU32 DATA_CMD;

    VU32 SS_SCL_HCNT;
    VU32 SS_SCL_LCNT;
    VU32 FS_SCL_HCNT;
    VU32 FS_SCL_LCNT;
    VU32 HS_SCL_HCNT;
    VU32 HS_SCL_LCNT;

    VU32 INTR_STAT;
    VU32 INTR_MASK;
    VU32 RAW_INTR_STAT;

    VU32 RX_TL;
    VU32 TX_TL;

    VU32 CLR_INTR;
    VU32 CLR_RX_UNDER;
    VU32 CLR_RX_OVER;
    VU32 CLR_TX_OVER;
    VU32 CLR_RD_REQ;
    VU32 CLR_TX_ABRT;
    VU32 CLR_RX_DONE;
    VU32 CLR_ACTIVITY;
    VU32 CLR_STOP_DET;
    VU32 CLR_START_DET;
    VU32 CLR_GEN_CALL;

    VU32 ENABLE;
    VU32 STATUS;

    VU32 TXFLR;
    VU32 RXFLR;

    VU32 SDA_HOLD;
    VU32 TX_ABRT_SOURCE;
    VU32 SLV_DATA_NACK_ONLY;

    VU32 DMA_CR;
    VU32 DMA_TDLR;
    VU32 DMA_RDLR;

    VU32 SDA_SETUP;
    VU32 ACK_GENERAL_CALL;
    VU32 ENABLE_STATUS;
    VU32 FS_SPKLEN;
    VU32 HS_SPKLEN;

    VU32 RESERVED_A8_F4[(0xF4-0xA8)>>2];

    VU32 COMP_PARAM_1;
    VU32 COMP_VERSION;
    VU32 COMP_TYPE;
};

#define IC_COMP_TYPE_VALUE          0x44570140

#define BIT_INTR_RX_UNDER           BIT(0)
#define BIT_INTR_RX_OVER            BIT(1)
#define BIT_INTR_RX_FULL            BIT(2)
#define BIT_INTR_TX_OVER            BIT(3)
#define BIT_INTR_TX_EMPTY           BIT(4)
#define BIT_INTR_TX_ABORT           BIT(6)
#define BIT_INTR_RX_DONE            BIT(7)
#define BIT_INTR_ACTIVITY           BIT(8)
#define BIT_INTR_STOP_DET           BIT(9)
#define BIT_INTR_START_DET          BIT(10)
#define BIT_INTR_GEN_CALL           BIT(11)

#define BIT_MODE_MASTER             BIT(0)
#define BIT_SPEED_STANDARD          ( 1<<1 )
#define BIT_SPEED_FAST              ( 2<<1 )
#define BIT_SPEED_HIGH              ( 3<<1 )
#define BIT_RESTART_ENABLE          BIT(5)
#define BIT_SLAVE_DISABLE           BIT(6)

#define BIT_CMD_WRITE               ( 0 )
#define BIT_CMD_READ                BIT(8)
#define BIT_CMD_STOP                BIT(9)
#define BIT_CMD_RESTART             BIT(10)

#define BIT_STATUS_SLAVE_ACTIVE     BIT(6)
#define BIT_STATUS_MASTER_ACTIVE    BIT(5)
#define BIT_STATUS_RX_FULL          BIT(4)
#define BIT_STATUS_RX_NOT_EMPTY     BIT(3)
#define BIT_STATUS_TX_EMPTY         BIT(2)
#define BIT_STATUS_TX_NOT_FULL      BIT(1)
#define BIT_STATUS_ACTIVE           BIT(0)

#define BIT_STATUS_ENABLE           BIT(0)

#define CONFIG_INTR_DEFAULT         (\
    BIT_INTR_RX_FULL                |\
    BIT_INTR_TX_EMPTY               |\
    BIT_INTR_STOP_DET               |\
    BIT_INTR_TX_ABORT               )

#define CONFIG_MASTER_DEFAULT       (\
    BIT_SLAVE_DISABLE               |\
    BIT_RESTART_ENABLE              |\
    BIT_SPEED_FAST                  |\
    BIT_MODE_MASTER                 )

#define ISR_FLAG_TX                 ( 0 )
#define ISR_FLAG_RX                 ( 1 )
#define ISR_FLAG_ABRT               ( 2 )

#endif

