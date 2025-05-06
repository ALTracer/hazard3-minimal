#include <stdint.h>
__attribute__((interrupt))
void handle_exception(void)
{
	volatile static uint32_t mcause1 = 0;
	__asm volatile ( "csrr %0," "mcause" : "=r" (mcause1) );

	while(1);
}
