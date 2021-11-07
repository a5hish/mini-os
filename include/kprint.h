#ifndef __KPRINT_H
#define __KPRINT_H

#define SET_CHR_ATTR(chr, attr) ((chr) | (attr << 8))

/* Color attributes */
#define VGA_ATTR_BL 0x0F

int kput(unsigned char chr);
int kput_xy(unsigned char chr, unsigned char x, unsigned char y);
int kprint(char *str);
void kclear(void);

#endif
