#ifdef __GDT_H
#define __GDT_H

#include <stdint.h>
#include <bitopts.h>

/*
 * Intel x86 GDT structure
 * -------------------------
 * 1st Double word :
 * Bits		Function	Description
 * 0-15		Limit 0:15	First 16 bits in the segment limiter.
 * 16-31	Base 0:15	First 16 bits in the base address.
 *
 * 2nd Double word:
 * Bits		Function	Description
 * 0-7		Base 16:23	Bits 16-23 in the base address.
 * 8-12		Type		Segment type and attributes.
 * 13-14			Privilege Level	0 = Highest privilege (OS),
 *				3 = Lowest privilege (User applications).
 * 15		Present flag	Set to 1 if segment is present.
 * 16-19	Limit 16:19	Bits 16-19 in the segment limiter.
 * 20-22	Attributes	Different attributes, depending on the
 *				segment type.
 * 23		Granularity	Used together with the limiter, to determine
 *				the size of the segment.
 * 24-31	Base 24:31	The last 24-31 bits in the base address.
 * */

#define X86_GDT_BYTE_SIZE 8

/* *************
 * ACCESS TYPE *
 * *************
 */

/*
 * Ac: Accessed bit.
 * Best left clear (0), the CPU will set it when the segment
 * is accessed.
 */
#define SET_SEG_AC(x)		((x) << 0)

/*
 * RW: Readable bit/Writable bit.
 *	For code segments: Readable bit. If clear (0), read access for this
 *	segment is not allowed. If set (1) read access is allowed.
 *	Write access is never allowed for code segments.
 *
 *	For data segments: Writeable bit. If clear (0), write access for this
 *	segment is not allowed. If set (1) write access is allowed.
 *	Read access is always allowed for data segments.
 */
#define SET_SEG_RW(x)		((x) << 1)

/*
 *  DC: Direction bit/Conforming bit.
 *	For data selectors: Direction bit. If clear (0) the segment grows up.
 *	If set (1) the segment grows down, ie. the Offset has to be greater
 *	than the Limit.
 *
 *	For code selectors: Conforming bit.
 *       If clear (0) code in this segment can only be executed from the ring
 *	set in Privl. If set (1) code in this segment can be executed from an
 *	equal or lower privilege level. For example, code in ring 3 can
 *	far-jump to conforming code in a ring 2 segment.
 *
 *	The Privl field represent the highest privilege level that is allowed
 *	to execute the segment. For example, code in ring 0 cannot far-jump to
 *	a conforming code segment where Privl is 2, while code in ring 2 and 3
 *	can.
 *	Note that the privilege level remains the same, ie. a far-jump from
 *	ring 3 to a segment with a Privl of 2 remains in ring 3 after the jump.
 */
#define SET_SEG_DC(x)		((x) << 2)

/*
 * Ex: Executable bit. If clear (0) the descriptor defines a data segment.
 * If set (1) it defines a code segment which can be executed from.
 */
#define SET_SEG_EXEC(x)		((x) << 3)

/* S: Descriptor type bit. If clear (0) the descriptor defines a system
 * segment (eg. a Task State Segment). If set (1) it defines a code or
 * data segment.
 */
#define SET_SEG_TYPE(x)		((x) << 4)

/*
 * Privl: Descriptor privilege level field. Contains the CPU Privilege level of
 * the segment. 0 = highest privilege (kernel), 3 = lowest privilege (user
 * applications).
 */
#define SET_SEG_PRIV(x)		(((x) & 0x3) << 5)

/*
 * Pr: Present bit. Allows an entry to refer to a valid segment. Must be set (1)
 * for any valid segment.
 */
#define SET_SEG_PRES(x)		((x) << 7)


/* *******
 * FLAGS *
 * *******
 */

/* First nibble of this byte should contain the higher limit value */
#define SET_SEG_LIMITH(lh)	((lh) & 0xC)

/*
 * Long-mode code flag. If set (1), the descriptor defines a 64-bit code
 * segment. When set, Sz should always be clear. For any other type of
 * segment (other code types or any data segment), it should be clear (0).
 */
#define SET_SEG_LM_FLAG(x)	((x) << 5)

/*
 * Size flag. If clear (0), the descriptor defines a 16-bit protected mode
 * segment. If set (1) it defines a 32-bit protected mode segment. A GDT can
 * have both 16-bit and 32-bit selectors at once.
 */
#define SET_SEG_SZ_FLAG(x)	((x) << 6)

/*
 * Gr: Granularity flag, indicates the size the Limit value is scaled by. If
 * clear (0), the Limit is in 1 Byte blocks (byte granularity). If set (1),
 * the Limit is in 4 KiB blocks (page granularity).
 */
#define SET_SEG_GR_FLAGS(x)	((x) << 7)

/* ******************************************
 * GENMASK FOR GDT when store in two dwords *
 * ******************************************
 */

/* 1st Double Word */
#define GDT_LIMIT_LOW_MASK	GENMASK(0, 15)
#define GDT_BASE_LOW_MASK	GENMASK(16, 31)
/* end Double Word */
#define GDT_BASE_MID_MASK	GENMASK(0, 7)
#define GDT_TYPE_MASK		GENMASK(8, 12)
#define GDT_PRIVILEGE_MASK	GENMASK(13, 14)
#define GDT_LIMIT_HIGH_MASK	GENMASK(16, 19)
#define GDT_ATTRIBUTE_MASK	GENMASK(20, 22)
#define GDT_BASE_HIGH_MASK	GENMASK(24, 31)

#define SET_SEG_SIZE(x)		((x) << 22)
#define SET_SEG_GR(x)		((x) << 23)

#endif
