int main(int argc, char *argv[])
{
	unsigned x = 1;
	while(x) {
		x++;
		__asm volatile("nop");
	}

	return x;
}
