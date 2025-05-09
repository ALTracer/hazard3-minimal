#include <stdint.h>

	static void print_exception_cause(uint32_t cause);
volatile static const char * desc = 0;

__attribute__((interrupt))
void handle_exception_c(void)
{
	/* Fetch exception cause */
	volatile static uint32_t mcause1 = 0;
	__asm volatile ( "csrr %0," "mcause" : "=r" (mcause1) );
	if ((mcause1 & 0x80000000U) == 0U)
		print_exception_cause(mcause1);
	/* Some processors provide more info via mtval & mtinst. */
	if (desc == 0U)
		return;

	while(1)
		__asm volatile("nop");
}

#include <string.h>
#include <unistd.h>

struct exception_desc {
	uint8_t number;
	char * desc;
};
static const struct exception_desc descs[16] = {
	{0, "Instruction address misaligned"},
	{1, "Instruction-fetch bus-fault"},
	{2, "Illegal instruction"},
	{3, "Breakpoint"},
	{4, "Load from misaligned address"},
	{5, "Load-access bus-fault"},
	{6, "Store/AMO to misaligned address"},
	{7, "Store/AMO bus-fault"},
	{8, "Ecall from U-mode"},
	{9, ""}, //Ecall from S-mode
	{10, ""},
	{11, "Ecall from M-mode"},
	{12, ""}, //Instruction-fetch page error
	{13, ""}, //Load-access page error
	{14, ""},
	{15, ""}, //Store/AMO page error
};

static void print_exception_cause(const uint32_t cause)
{
	if (cause >= 16)
		return;
	desc = descs[cause].desc;
//	write(2, desc, strlen(desc));
}
