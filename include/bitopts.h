#ifndef __BITOPTS_H
#define __BITOPTS_H

#define BITS_PER_BYTE 8
#define BITS_PER_LONG  (sizeof(unsigned long) * BITS_PER_BYTE)

#define BIT(n) (1UL << (n))
#define GENMASK(l, h) (~(0UL) << (l) & \
			((~0UL) >> (BITS_PER_LONG - l - h)))
#endif
