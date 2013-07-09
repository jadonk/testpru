/*
 * prucomm.h - structure definitions for communication
 *
 */
#ifndef PRUCOMM_H
#define PRUCOMM_H

#include "pru_defs.h"

struct pwm_config {
	u32 hi_cycles;
	u32 hi_err;
	u32 lo_cycles;
	u32 lo_err;
};

/* maximum */
#define MAX_PWMS	16

/* mask of the possibly enabled PWMs (due to h/w) */
/* 14, 15 are not routed out for PRU1 */
#define PWM_EN_MASK	( \
	BIT( 0)|BIT( 1)|BIT( 2)|BIT( 3)|BIT( 4)|BIT( 5)|BIT( 6)|BIT( 7)| \
	BIT( 8)|BIT( 9)|BIT(10)|BIT(11)|BIT(12)|BIT(13) \
	)

#define MIN_PWM_PULSE	PRU_us(4)

struct pwm_multi_config {
	u32 enmask;	/* enable mask */
	u32 offmsk;	/* state when pwm is off */
	u32 hilo[MAX_PWMS][2];
};

#define PWM_CMD_MAGIC	0xf00fbaaf
#define PWM_REPLY_MAGIC	0xbaaff00f

#define PWM_CMD_CONFIG	0	/* full configuration in one go */
#define PWM_CMD_ENABLE	1	/* enable a pwm */
#define PWM_CMD_DISABLE	2	/* disable a pwm */
#define PWM_CMD_MODIFY	3	/* modify a pwm */
#define PWM_CMD_SET	4	/* set a pwm output explicitly */
#define PWM_CMD_CLR	5	/* clr a pwm output explicitly */ 

struct pwm_cmd {
	u32 magic;
	u8 cmd;
	u8 pwm_nr;	/* in case it is required */
	u8 pad[2];
	union {
		struct pwm_multi_config cfg;
		u32 hilo[2];
	} u;
};

/* the command is at the start of shared DPRAM */
#define PWM_CMD		((struct pwm_cmd *)((void *)DPRAM_SHARED))

#endif
