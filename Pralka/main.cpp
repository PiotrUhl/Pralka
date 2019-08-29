#include "Programowanie.h"

int main(int argc, char** argv) {
	
	unsigned int memSize = 8;
	if (argc >= 2) {
		 memSize = strtol(argv[1], nullptr, 10);
		 if (memSize <= 0 || memSize > 256)
			 memSize = 8;
	}
	Programowanie cmd(memSize);
	return cmd.cmd(); //uruchamia interpreter poleceñ
}