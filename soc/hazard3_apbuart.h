#include <stdint.h>

typedef struct {
	volatile uint32_t CSR;
	volatile uint32_t DIV;
	volatile uint32_t FSTAT;
	volatile uint32_t TX;
	volatile uint32_t RX;
} UART_Type;

#define UART_CSR_EN 	(1U << 0U)
#define UART_CSR_BUSY	(1U << 1U)
#define UART_CSR_TXIE	(1U << 2U)
#define UART_CSR_RXIE	(1U << 3U)
#define UART_CSR_CTSEN	(1U << 4U)
#define UART_CSR_LOOPBACK	(1U << 5U)
