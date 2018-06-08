#include "dw_i2c.h"

static int dw_i2c_init (uint32_t base)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	if (IC_COMP_TYPE_VALUE != i2c->COMP_TYPE) {
		return -1;
	}

	return 0;
}

static void dw_i2c_uninit (uint32_t base)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	i2c->ENABLE = 0;
	while (i2c->ENABLE_STATUS != 0);
}

static int dw_i2c_init_transaction (
	uint32_t base,
	uint16_t slave_addr
	)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	i2c->ENABLE = 0;
	while ((i2c->ENABLE_STATUS & BIT_STATUS_ENABLE));

	i2c->CON = CONFIG_MASTER_DEFAULT;
	i2c->RX_TL = 0;
	i2c->TX_TL = 1;

	/* errdat: enforce disable interrupts (due to HW issues) */
	i2c->INTR_MASK = 0;

	i2c->TAR = slave_addr;

	i2c->ENABLE = 1;
	while ( !(i2c->ENABLE_STATUS & BIT_STATUS_ENABLE) );

	return 0;
}

static int dw_i2c_poll_write (
	uint32_t base, 
	const uint8_t *buffer, 
	uint32_t length
	)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	uint32_t cmd = BIT_CMD_WRITE;

	for (int i=0; i<length; i++) {
		if (i == length-1) {
			cmd |= BIT_CMD_STOP;
		}
		
		i2c->DATA_CMD = buffer[i] | cmd;
		while ( !(i2c->STATUS & BIT_STATUS_TX_NOT_FULL) );
	}

	return 0;
}

static int dw_i2c_poll_read (uint32_t base, uint8_t *buffer, int length)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	uint32_t cmd = BIT_CMD_READ;

	for (int i=0; i<length; i++) {
		if (i == length-1) {
			cmd |= BIT_CMD_STOP;
		}

		i2c->DATA_CMD = 0 | cmd;
		while ( !(i2c->STATUS & BIT_STATUS_RX_NOT_EMPTY) );

		buffer[i] = (uint8_t)(i2c->DATA_CMD & 0xFF);
	}

	return 0;
}

static void dw_i2c_irq_enable (uint32_t base)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	i2c->INTR_MASK = CONFIG_INTR_DEFAULT;
}

static void dw_i2c_irq_disable (uint32_t base)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	i2c->INTR_STAT;
	i2c->INTR_MASK = 0;
}

static void dw_i2c_isr_send_byte (
	uint32_t base,
	uint8_t data,
	uint8_t read,
	uint8_t restart,
	uint8_t stop
	)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	uint32_t cmd = 0;

	cmd = cmd | (read ? BIT_CMD_READ : 0);
	cmd = cmd | (restart ? BIT_CMD_RESTART : 0);
	cmd = cmd | (stop ? BIT_CMD_STOP : 0);

	i2c->DATA_CMD = cmd | data;
}

#ifdef DW_I2C_USE_FIFO
static uint32_t dw_i2c_isr_send_multibytes (
	uint32_t base,
	uint8_t *data,
	uint32_t data_len,
	uint8_t read,
	uint8_t restart,
	uint8_t stop
	)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	uint8_t cmd;
	uint32_t empty_entries;
	uint32_t min;
	
	empty_entries = i2c->TX_TL - i2c->TXFLR;

	min = (empty_entries < data_len) ? empty_entries : data_len;

	for (int i=0; i<min; i++) {
		cmd = read ? BIT_CMD_READ : 0;
		if (restart && (0 == i)) {
			cmd = cmd | BIT_CMD_RESTART;
		}
		if (stop && (min == data_len) && (min-1 == i)) {
			cmd = cmd | BIT_CMD_STOP;
		}

		i2c->DATA_CMD = data[i] | cmd;
	}

	i2c->TX_TL = min;

	return min;
}
#endif

void dw_i2c_isr (uint32_t base)
{
	i2c_dw_apb200a_regs_t *i2c = (i2c_dw_apb200a_regs_t *)base;

	if (i2c->INTR_STAT & BIT_INTR_RX_FULL) {
		for (int i = 0; i < i2c->TXFLR; i++) {
            uint32_t data = i2c->DATA_CMD;
		}
	}

	if (i2c->INTR_STAT & BIT_INTR_TX_EMPTY) {
        // send data
	}

	if (i2c->INTR_STAT & BIT_INTR_TX_ABORT) {
		i2c->CLR_TX_ABRT;
	}

	if (i2c->INTR_STAT & BIT_INTR_STOP_DET) {
		i2c->CLR_STOP_DET;
	}
}
