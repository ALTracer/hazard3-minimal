#include <errno.h>

int _kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	_kill(status, -1);
	while (1) {}
}

/* Drop newlib cruft */
void exit(int code)
{
	_exit(code);
}

/* Redefine newlib crt0 */
#include <stdlib.h>
extern unsigned _sbss, _ebss;
extern int main(int argc, char * argv[]);
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

void _mystart(void)
{
	volatile unsigned *dest = &_sbss;
	while (likely(dest < &_ebss)) {
		*dest++ = 0;
	}
	int argc = 1;
	char * argv[] = {"hazard3-blink", NULL};
	int ret = main(argc, argv);
	exit(ret);
}
