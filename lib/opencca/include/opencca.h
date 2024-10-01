#ifndef OPENCCA_H
#define OPENCCA_H

#if ENABLE_OPENCCA

#ifndef __ASSEMBLER__
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <debug.h>

#ifdef OPENCCA_DEBUG
#define OPENCCA_TRACE(fmt, ...) \
	do { \
		VERBOSE("[opencca/rmm] " fmt, ##__VA_ARGS__); \
	} while (0)
#else /* OPENCCA_TRACE */
#define OPENCCA_TRACE(fmt, ...) \
	do { \
	} while (0)	
#endif

#endif /* not __ASSEMBLER__ */
#include <utils_def.h>

#define OPENCCA_SYSREG_DUMMY afsr0_el2
#ifndef __ASSEMBLER__


static inline uint64_t read_dummy_sysreg()
{
	volatile uint64_t v=0;
	__asm__ volatile ("mrs %0, afsr0_el2" : "=r" (v));	
	return 0;
}

static inline void write_dummy_sysreg(uint64_t v)
{									\
	__asm__ volatile ("msr afsr0_el2, %0" : : "r" (v));
}

#define FN_RETURN_BOOL(name, val) \
static inline bool name(void) \
{ \
	OPENCCA_TRACE("%s=%d\n", #name, val); \
    read_dummy_sysreg(); \
    return val; \
}

static inline void xpaci(uint64_t v)
{
    (void)v; 
	asm volatile("nop");
}


/* Spoof FEAT_RNG for opencca */
FN_RETURN_BOOL(is_feat_rng_present, true)


/* FEAT_RNG not implemented on Arm v8.2 */
static inline bool arch_collect_entropy(uint64_t *random)
{
	static uint64_t val;
	*random = val++;
	return true;
}

FN_RETURN_BOOL(is_armv8_4_ttst_present, false)
FN_RETURN_BOOL(is_feat_sme_present, false)
FN_RETURN_BOOL(is_feat_vmid16_present, false)
FN_RETURN_BOOL(is_feat_lpa2_4k_present, false)
FN_RETURN_BOOL(is_feat_lpa2_4k_2_present, false)
FN_RETURN_BOOL(is_feat_hpmn0_present, false)



#ifdef __cplusplus
/*
 * Disable write-strings warnings when building C++ code (used for unit
 * testing) as ISO C++ forbits converting a string constant to char*,
 * which is actually done by DEFINE_SYSREG_{READ, WRITE}_FUNC macros.
 */

#ifdef __clang__
	#pragma clang diagnostic ignored "-Wwrite-strings"
#else
	#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif /* __clang__ */
#endif /* __cplusplus__ */

/**********************************************************************
 * Macros which create inline functions to read or write CPU system
 * registers
 *********************************************************************/
#define OPENCCA_DEFINE_SYSREG_READ_FUNC_(_name, _reg_name)		\
static inline uint64_t read_ ## _name(void)			\
{								\
	OPENCCA_TRACE("read_%s\n", #_name);				\
	return read_dummy_sysreg();			\
}

#define OPENCCA_DEFINE_SYSREG_WRITE_FUNC_(_name, _reg_name)		\
static inline void write_ ## _name(uint64_t v)		\
{								\
	OPENCCA_TRACE("write_%s\n", #_name );		\
	write_dummy_sysreg(v);				\
}

/* Define read function for system register */
#define OPENCCA_DEFINE_SYSREG_READ_FUNC(_name)			\
	OPENCCA_DEFINE_SYSREG_READ_FUNC_(_name, _name)

/* Define read & write function for system register */
#define OPENCCA_DEFINE_SYSREG_RW_FUNCS(_name)			\
	OPENCCA_DEFINE_SYSREG_READ_FUNC_(_name, _name)		\
	OPENCCA_DEFINE_SYSREG_WRITE_FUNC_(_name, _name)

/* Define read & write function for renamed system register */
#define OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(_name, _reg_name)	\
	OPENCCA_DEFINE_SYSREG_READ_FUNC_(_name, _reg_name)	\
	OPENCCA_DEFINE_SYSREG_WRITE_FUNC_(_name, _reg_name)

/* Define read function for renamed system register */
#define OPENCCA_DEFINE_RENAME_SYSREG_READ_FUNC(_name, _reg_name)	\
	OPENCCA_DEFINE_SYSREG_READ_FUNC_(_name, _reg_name)

/* Define write function for renamed system register */
#define OPENCCA_DEFINE_RENAME_SYSREG_WRITE_FUNC(_name, _reg_name)	\
	OPENCCA_DEFINE_SYSREG_WRITE_FUNC_(_name, _reg_name)



/* Armv8.3 Pointer Authentication Registers */
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apiakeyhi_el1, APIAKeyHi_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apiakeylo_el1, APIAKeyLo_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apibkeyhi_el1, APIBKeyHi_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apibkeylo_el1, APIBKeyLo_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apdakeyhi_el1, APDAKeyHi_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apdakeylo_el1, APDAKeyLo_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apdbkeyhi_el1, APDBKeyHi_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apdbkeylo_el1, APDBKeyLo_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apgakeyhi_el1, APGAKeyHi_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(apgakeylo_el1, APGAKeyLo_EL1)

/* Armv8.5 MTE Registers */
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(tfsre0_el1, TFSRE0_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(tfsr_el1, TFSR_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(rgsr_el1, RGSR_EL1)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(gcr_el1, GCR_EL1)

/* Armv8.5 Random Number Register */
OPENCCA_DEFINE_SYSREG_READ_FUNC_(rndr, RNDR)


OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(cntpoff_el2, CNTPOFF_EL2)
OPENCCA_DEFINE_RENAME_SYSREG_RW_FUNCS(cntvoff_el2, cntvoff_el2)


struct rmi_rec_exit;
struct rec;
bool opencca_handle_esr_tvm_sysreg_trap(struct rec* rec,
                struct rmi_rec_exit* rec_exit,
                unsigned long esr);

void opencca_stage2_flush_realm(struct rec* rec);
bool opencca_check_pending_timers(struct rec* rec, int simd_trap);


#endif /* not __ASSEMBLER__ */

#define DIT 	OPENCCA_SYSREG_DUMMY
#define DIT_BIT 0
#define sb nop
#define RNDR OPENCCA_SYSREG_DUMMY

#endif
#endif /* DEBUG_H */
