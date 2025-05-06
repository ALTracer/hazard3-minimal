	/* Hazard3 baremetal startup assembly. */
	.section .init,"ax",@progbits
	.global _entry
	.align 1
_entry:
	j 	Reset_Handler

	/* Interrupt vector table, 16 entries. */
.macro VEC name:req
.p2align 2
j \name
.p2align 2
.endm

	.section .vector,"ax",@progbits
	.align 1
_vector_base:
	.option norvc;
	/* Single exception vector, also takes IRQs if vectoring is disabled */
	VEC handle_exception
	/* Standard interrupts, if vectoring is enabled */
	VEC .halt
	VEC .halt
	VEC isr_machine_softirq
	VEC .halt
	VEC .halt
	VEC .halt
	VEC isr_machine_timer
	VEC .halt
	VEC .halt
	VEC .halt
	VEC isr_external_irq
	VEC .halt
	VEC .halt
	VEC .halt
	VEC .halt
	.option rvc;
	.section .text.vector_handler,"ax",@progbits
	.weak handle_exception
	.weak isr_machine_softirq
	.weak isr_machine_timer
	.weak isr_external_irq
handle_exception:
1:
	j 1b
isr_machine_softirq:
1:
	j 1b
isr_machine_timer:
1:
	j 1b
isr_external_irq:
1:
	j 1b

	/* The Reset Handler, relies on newlib crt0 */
	.section .text.Reset_Handler,"ax",@progbits
	.global Reset_Handler
	.align 1
Reset_Handler:
.option push
.option norelax
	la gp, __global_pointer$
.option pop
	la sp, _estack

	/* Configure IVT mode and address */
	la t0, _vector_base;
	ori t0, t0, 1;
	csrw mtvec, t0

	/* Enable global interrupt and configure privileged mode */
	li t0, 8
	csrw mstatus, t0

	jal _mystart
	/* If newlib/main ever return, then drop into a busyloop. */
	j .halt

	.global .halt
.halt:
	wfi
	j .halt
