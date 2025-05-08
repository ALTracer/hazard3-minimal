/*
 * Prints helloworld via semihosting. However, as the naive approach of
 * stdio printf()/puts()/fwrite() references kilobytes of library code for buffered IO,
 * instead let Newlib populate FD table through init_semihosting()/open() to be correct to
 * RISC-V and ARM semihosting specs (see https://github.com/riscv-non-isa/riscv-semihosting
 * and https://github.com/ARM-software/abi-aa/blob/main/semihosting/semihosting.rst )
 * then do direct/unbuffered write() calls.
 */

#include <fcntl.h> //open
#include <unistd.h> //close, STDOUT_FILENO
#include <errno.h>

extern void init_semihosting(void);

int do_hello(void)
{
	const char msg[] = "Hello, World!\r\n";
//	printf(msg); //boring
	const int fd = STDERR_FILENO;
	const int res = write(fd, msg, sizeof(msg));
	if (res < 0) {
		return errno;
	}
	close(fd);
	return 0;
}

int main(int argc, char *argv[])
{
	init_semihosting(); /* Newlib wants this in constructors to populate fdtable */
	do_hello();

	while(1) {
		__asm volatile("nop");
	}

	return 0;
}
