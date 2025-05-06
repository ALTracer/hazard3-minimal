#include <stdint.h>
__attribute__((interrupt))
void handle_exception(void)
{
	volatile static uint32_t mcause1 = 0;
	volatile static uint32_t mtval1 = 0;
	__asm volatile ( "csrr %0," "mcause" : "=r" (mcause1) );
	__asm volatile ( "csrr %0," "mtval" : "=r" (mtval1) );

	while(1);
}
