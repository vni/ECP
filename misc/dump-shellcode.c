#include <stdio.h>

unsigned char shellcode[] = {
	0xeb, 0x20,                   /* jmp JMP_1 */
	0xb8, 0x04, 0x00, 0x00, 0x00, /* mov eax, 4 */
	0xbb, 0x01, 0x00, 0x00, 0x00, /* mov ebx, 1 */
	0x8b, 0x0c, 0x24,             /* mov ecx, [esp] */
	0xba, 0x0e, 0x00, 0x00, 0x00, /* mov edx, 14 */
	0xcd, 0x80,                   /* int 0x80 */

	0xb8, 0x01, 0x00, 0x00, 0x00, /* mov eax, 1 */
	0xbb, 0x40, 0x00, 0x00, 0x00, /* mov ebx, 64 */
	0xcd, 0x80,                   /* int 0x80 */

	0xe8, 0xdb, 0xff, 0xff, 0xff, /* call 2 <REAL_START> */
	0x48, 0x65, 0x6c, 0x6c, 0x6f, /* "Hello, World!\n" */
	0x2c, 0x20, 0x57, 0x6f, 0x72,
	0x6c, 0x64, 0x21, 0x0a
};

int main(void) {
	unsigned i = 0;
	for (i = 0; i < sizeof(shellcode); i++)
		printf("%c", shellcode[i]);
	return 0;
}