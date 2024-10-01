/*
 * Copyright (c) 2013-2023, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CONSOLE_H
#define CONSOLE_H


#define CONSOLE_T_NEXT			(U(0) * REGSZ)
#define CONSOLE_T_FLAGS			(U(1) * REGSZ)
#define CONSOLE_T_PUTC			(U(2) * REGSZ)
#if ENABLE_CONSOLE_GETC
#define CONSOLE_T_GETC			(U(3) * REGSZ)
#define CONSOLE_T_FLUSH			(U(4) * REGSZ)
#define CONSOLE_T_BASE			(U(5) * REGSZ)
#define CONSOLE_T_DRVDATA		(U(6) * REGSZ)
#else
#define CONSOLE_T_FLUSH			(U(3) * REGSZ)
#define CONSOLE_T_BASE			(U(4) * REGSZ)
#define CONSOLE_T_DRVDATA		(U(5) * REGSZ)
#endif

#define CONSOLE_FLAG_BOOT		(U(1) << 0)
#define CONSOLE_FLAG_RUNTIME		(U(1) << 1)
#define CONSOLE_FLAG_CRASH		(U(1) << 2)
/* Bits 3 to 7 reserved for additional scopes in future expansion. */
#define CONSOLE_FLAG_SCOPE_MASK		((U(1) << 8) - 1)
/* Bits 8 to 31 for non-scope use. */
#define CONSOLE_FLAG_TRANSLATE_CRLF	(U(1) << 8)

/* Returned by getc callbacks when receive FIFO is empty. */
#define ERROR_NO_PENDING_CHAR		(-1)
/* Returned by console_xxx() if no registered console implements xxx. */
#define ERROR_NO_VALID_CONSOLE		(-128)

#ifndef __ASSEMBLER__

#include <stdint.h>

typedef struct console {
	struct console *next;
	/*
	 * Only the low 32 bits are used. The type is u_register_t to align the
	 * fields of the struct to 64 bits in AArch64 and 32 bits in AArch32
	 */
	u_register_t flags;
	int (*const putc)(int character, struct console *console);
#if ENABLE_CONSOLE_GETC
	int (*const getc)(struct console *console);
#endif
	void (*const flush)(struct console *console);
	uintptr_t base;
	/* Additional private driver data may follow here. */
} console_t;


#endif
#endif /* CONSOLE_H */
