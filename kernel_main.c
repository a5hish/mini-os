#define VGAMEM 0xB8000

char * vga_buf = (char*)VGAMEM;

void main(void)
{
	vga_buf[0] = 'A';
	vga_buf[1] = 0x0f;

	return;
}
