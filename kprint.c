#include "error.h"
#include "kprint.h"

#define VGA_COLOR_TEXT_START 0xB8000
#define VGA_COLOR_TEXT_END 0xBFFFF
#define VGA_COLOR_MAX_RANGE (VGA_COLOR_TEXT_END - VGA_COLOR_TEXT_START)
#define MAX_COLUMNS 80
#define MAX_ROWS 25

#define xy_to_laddr(x, y) ((x) + ((y) * MAX_COLUMNS))

/*
 * Per cell size is 2Bytes in VGA color text mode.
 *	1st Byte to store ASCII value to print
 *	2nd Byte to store related Attributes as follows:
 *
 *		Bits 0 - 2: Foreground color
 *			Bit 0: Red
 *			Bit 1: Green
 *			Bit 2: Blue
 *		Bit 3: Foreground Intensity
 *			Bits 4 - 6: Background color
 *			Bit 4: Red
 *			Bit 5: Green
 *			Bit 6: Blue
 *		Bit 7: Blinking or background intensity
 */
#define CELL_SIZE 2

/* Holds the postion of the cursor. */
unsigned int g_vga_x, g_vga_y;

/* Pointer to VGA memory. */
unsigned short *g_vga_mem = (unsigned short*) VGA_COLOR_TEXT_START;

/* Prints a unsigned character at x, y codinate. */
int kput_xy(unsigned char chr, unsigned char x, unsigned char y)
{
	unsigned short cur;

	if (x > MAX_COLUMNS && y > MAX_ROWS)
		return -EINVAL;
	/*
	 * We need to convert x, y codinates to linear address
	 * as VGA memory is mapped in that way in computer memory.
	 */
	cur = xy_to_laddr(x, y);

	g_vga_mem[cur] = SET_CHR_ATTR(chr, VGA_ATTR_BL);
}

/*
 * Prints a unsigned character at current cursor position and
 * increments the cursor.
 */
int kput(unsigned char chr)
{
	int tmp_x = g_vga_x, tmp_y = g_vga_y, cur;

	switch (chr) {
		case '\n':
			/* Incase of new line move cursor to next row. */
			if ((tmp_y+1) >= MAX_ROWS)
				goto out_of_range;

			g_vga_y++;
			break;
		case '\r':
			/*
			 * Incase of carriage return move to start of
			 * current line.
			 */
			g_vga_x = 0;
			break;
		default:
			if ((tmp_x+1) >= MAX_COLUMNS) {
				tmp_y++;
				tmp_x = 0;
			} else {
				tmp_x++;
			}
			cur = xy_to_laddr(tmp_x, tmp_y);
			if(cur > VGA_COLOR_MAX_RANGE)
				goto out_of_range;

			g_vga_mem[cur] =
				(SET_CHR_ATTR(chr, VGA_ATTR_BL));

			g_vga_x = tmp_x;
			g_vga_y = tmp_y;
	};

	return 0;

out_of_range:
	return -ERANGE;
}

/* Print passed null terminated string. */
int kprint(char *str)
{
	int count, rc;

	if (!str)
		return -EINVAL;

	for (count = 0; *str != '\0'; str++, count++) {
		rc = kput(*str);
		if (rc < 0)
			return rc;
	}

	return count;
}

/* Clear screen */

void kclear(void)
{
	int i = 0;
	while(i < (MAX_COLUMNS * MAX_ROWS))
		g_vga_mem[i++] = 0x0;
}
