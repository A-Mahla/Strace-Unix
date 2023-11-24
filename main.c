#include <stdio.h>
#include <signal.h>

int main() {
//	int	buf[10];
//	for (int i = 0; i < 100000; i++) {
//		buf[i] = 9;
//	}
//	raise(SIGINT);
	raise(SIGHUP);
//	raise(SIGILL);
//	sleep(3);
//    unsigned char illegal_instruction[] = {0xFF, 0xFF, 0xFF, 0xFF}; // Invalid opcode
//    void (*func)() = (void (*)())illegal_instruction;
//    func();
}
