/* Memory map */
#define AHB_BASE 	0x40000000
#define TIMER1_BASE	(AHB_BASE + 0x0000)
#define UART1_BASE	(AHB_BASE + 0x4000)

#define TIMER1	((TIMER_Type *) TIMER1_BASE)
#define UART1	((UART_Type *) UART1_BASE)
