#include <stdio.h>
#include "../soc/hazard3_apbuart.h"
#include "../soc/hazard3_memorymap.h"

void uart_setup(const int baudrate)
{
	UART1->CSR = 0x1;
	const uint32_t SystemCoreClock = 12000000;
	/* Simple divider. Round up. */
	uint16_t divval = (SystemCoreClock*(16/8) + baudrate/2) / baudrate;
	UART1->DIV = divval;
}

void uart_write(const char *buf, const size_t len)
{
	for (size_t i = 0; i < len; i++) {
		while(UART1->CSR & UART_CSR_BUSY);
		UART1->TX = buf[i];
	}
	while(UART1->CSR & UART_CSR_BUSY);
}

int main(int argc, char *argv[])
{
	uart_setup(115200);
	const char msg[] = "Hello, World!\r\n";
	uart_write(msg, sizeof(msg));

	while(1) {
		__asm volatile("nop");
	}

	return 0;
}
