#ifndef OPENCCA_DEBUG_H
#define OPENCCA_DEBUG_H

#ifndef __ASSEMBLER__
#include <debug.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

__unused static void
opencca_debug_dump_guest_state()
{
    uint64_t value;
    #define PRINT_MACRO INFO

    PRINT_MACRO("----- BEGIN: guest state -----\n");

    asm volatile("mrs %0, SP_EL0" : "=r"(value));
    PRINT_MACRO("sp_el0:\t\t\t0x%016lx\n", value);

    asm volatile("mrs %0, SP_EL1" : "=r"(value));
    PRINT_MACRO("sp_el1:\t\t\t0x%016lx\n", value);

    asm volatile("mrs %0, ELR_EL1" : "=r"(value));
    PRINT_MACRO("elr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, SPSR_EL1" : "=r"(value));
    PRINT_MACRO("spsr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, PMCR_EL0" : "=r"(value));
    PRINT_MACRO("pmcr_el0:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TPIDRRO_EL0" : "=r"(value));
    PRINT_MACRO("tpidrro_el0:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TPIDR_EL0" : "=r"(value));
    PRINT_MACRO("tpidr_el0:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CSSELR_EL1" : "=r"(value));
    PRINT_MACRO("csselr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, SCTLR_EL1" : "=r"(value));
    PRINT_MACRO("sctlr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, ACTLR_EL1" : "=r"(value));
    PRINT_MACRO("actlr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CPACR_EL1" : "=r"(value));
    PRINT_MACRO("cpacr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TTBR0_EL1" : "=r"(value));
    PRINT_MACRO("ttbr0_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TTBR1_EL1" : "=r"(value));
    PRINT_MACRO("ttbr1_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TCR_EL1" : "=r"(value));
    PRINT_MACRO("tcr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, ESR_EL1" : "=r"(value));
    PRINT_MACRO("esr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, AFSR0_EL1" : "=r"(value));
    PRINT_MACRO("afsr0_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, AFSR1_EL1" : "=r"(value));
    PRINT_MACRO("afsr1_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, FAR_EL1" : "=r"(value));
    PRINT_MACRO("far_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, MAIR_EL1" : "=r"(value));
    PRINT_MACRO("mair_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, VBAR_EL1" : "=r"(value));
    PRINT_MACRO("vbar_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CONTEXTIDR_EL1" : "=r"(value));
    PRINT_MACRO("contextidr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TPIDR_EL1" : "=r"(value));
    PRINT_MACRO("tpidr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, AMAIR_EL1" : "=r"(value));
    PRINT_MACRO("amair_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CNTKCTL_EL1" : "=r"(value));
    PRINT_MACRO("cntkctl_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, PAR_EL1" : "=r"(value));
    PRINT_MACRO("par_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, MDSCR_EL1" : "=r"(value));
    PRINT_MACRO("mdscr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, MDCCINT_EL1" : "=r"(value));
    PRINT_MACRO("mdccint_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, DISR_EL1" : "=r"(value));
    PRINT_MACRO("disr_el1:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CNTHCTL_EL2" : "=r"(value));
    PRINT_MACRO("cnthctl_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CNTVOFF_EL2" : "=r"(value));
    PRINT_MACRO("cntvoff_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CNTP_CTL_EL0" : "=r"(value));
    PRINT_MACRO("cntp_ctl_el0:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CNTP_CVAL_EL0" : "=r"(value));
    PRINT_MACRO("cntp_cval_el0:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CNTV_CTL_EL0" : "=r"(value));
    PRINT_MACRO("cntv_ctl_el0:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CNTV_CVAL_EL0" : "=r"(value));
    PRINT_MACRO("cntv_cval_el0:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, VMPIDR_EL2" : "=r"(value));
    PRINT_MACRO("vmpidr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, HCR_EL2" : "=r"(value));
    PRINT_MACRO("hcr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, CPTR_EL2" : "=r"(value));
    PRINT_MACRO("cptr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, VTTBR_EL2" : "=r"(value));
    PRINT_MACRO("vttbr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, VTCR_EL2" : "=r"(value));
    PRINT_MACRO("vtcr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, MDCR_EL2" : "=r"(value));
    PRINT_MACRO("mdcr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, ICC_SRE_EL2" : "=r"(value));
    PRINT_MACRO("icc_sre_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, ESR_EL2" : "=r"(value));
    PRINT_MACRO("esr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, HPFAR_EL2" : "=r"(value));
    PRINT_MACRO("hpfar_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, FAR_EL2" : "=r"(value));
    PRINT_MACRO("far_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, VSESR_EL2" : "=r"(value));
    PRINT_MACRO("vsesr_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, VBAR_EL2" : "=r"(value));
    PRINT_MACRO("vbar_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, SCTLR_EL2" : "=r"(value));
    PRINT_MACRO("sctlr_el2:\t\t0x%016lx\n", value);
    asm volatile("mrs %0, TTBR0_EL2" : "=r"(value));
    PRINT_MACRO("ttbr0_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TTBR1_EL2" : "=r"(value));
    PRINT_MACRO("ttbr1_el2:\t\t0x%016lx\n", value);

    asm volatile("mrs %0, TCR_EL2" : "=r"(value));
    PRINT_MACRO("tcr_el2:\t\t0x%016lx\n", value);
    
    asm volatile("mrs %0, MAIR_EL2" : "=r"(value));
    PRINT_MACRO("mair_el2:\t\t0x%016lx\n", value);

    PRINT_MACRO("----- END: guest state -----\n");
}

#endif /* not __ASSEMBLER__ */
#endif
