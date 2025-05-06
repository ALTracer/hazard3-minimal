#include <stdint.h>

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t MTIME;
	volatile uint32_t MTIMEH;
	volatile uint32_t MTIMECMP;
	volatile uint32_t MTIMECMPH;
} TIMER_Type;

#define TIMER_CTRL_EN	(1U << 0U)
