#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define add(a, b, d) (0 << 22 | ((a) & 0x7) << 19 | ((b) & 0x7) << 16 | ((d) & 0x7)),
#define nor(a, b, d) (1 << 22 | ((a) & 0x7) << 19 | ((b) & 0x7) << 16 | ((d) & 0x7)),
#define lw(a, b, v) (2 << 22 | ((a) & 0x7) << 19 | ((b) & 0x7) << 16 | ((v) & 0xffff)),
#define sw(a, b, v) (3 << 22 | ((a) & 0x7) << 19 | ((b) & 0x7) << 16 | ((v) & 0xffff)),
#define beq(a, b, v) (4 << 22 | ((a) & 0x7) << 19 | ((b) & 0x7) << 16 | ((v) & 0xffff)),
#define jalr(a, b) (5 << 22 | ((a) & 0x7) << 19 | ((b) & 0x7) << 16),
#define halt() (6 << 22),
#define nop() (7 << 22),
#define fill(d) (d),

int main() {
	uint16_t pc = 0;
	uint32_t reg[8] = {0};
	uint32_t mem[65536] = {
		#define datapos 15

		lw(0, 1, datapos)
		lw(0, 2, datapos + 1)
		lw(0, 3, datapos + 2)
		lw(0, 6, datapos + 3)
		nor(2, 2, 2)
		beq(0, 0, 3)
		add(3, 3, 3) // loop
		add(6, 6, 6)
		beq(3, 0, 5)
		nor(6, 6, 7) // start
		nor(7, 2, 7)
		beq(7, 0, -6)
		add(1, 3, 1)
		beq(0, 0, -8)
		halt() // done

		fill(0) // datapos
		fill(32766)
		fill(10383)
		fill(1)
	};

	do {
		uint8_t op = (mem[pc] >> 22) & 0x7;
		uint8_t a = (mem[pc] >> 19) & 0x7;
		uint8_t b = (mem[pc] >> 16) & 0x7;
		uint16_t v = mem[pc];
		uint8_t d = mem[pc] & 0x7;

		printf("%d\n", pc);
		switch (op) {
			case 0:
				reg[d] = reg[a] + reg[b];
				pc = pc + 1;
				continue;
			case 1:
				reg[d] = ~(reg[a] | reg[b]);
				pc = pc + 1;
				continue;
			case 2:
				reg[b] = mem[(reg[a] + v) & 0xffff];
				pc = pc + 1;
				continue;
			case 3:
				mem[(reg[a] + v) & 0xffff] = reg[b];
				pc = pc + 1;
				continue;
			case 4:
				if (reg[a] == reg[b]) {
					pc = pc + v + 1;
				} else {
					pc = pc + 1;
				}
				continue;
			case 5:
				reg[b] = pc + 1;
				pc = reg[a];
				continue;
			case 6:
				printf("pc = %d\n", pc);

				for (size_t i = 0; i < 8; ++i) {
					printf("reg %d = %d\n", i, reg[i]);
				}

				for (size_t i = 0; i < 65536; ++i) {
					if (mem[i]) {
						printf("mem %d = %d\n", i, mem[i]);
					}
				}

				return 0;
			case 7:
				pc = pc + 1;
				continue;
		}
	} while (true);
}
