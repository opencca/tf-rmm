#include <arch.h>
#include <arch_features.h>
#include <arch_helpers.h>
#include <debug.h>
#include <esr.h>
#include <rec.h>
#include <smc-rmi.h>
#include <sysreg_traps.h>

static inline unsigned long
read_sysreg_by_esr(unsigned long esr_val, struct rec* rec)
{
    unsigned long val = 0;
    switch (esr_val) {
        case ESR_EL2_SYSREG_SCTLR_EL1:
            val = read_sctlr_el12();
            VERBOSE("sysreg: read SCTLR_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_TTBR0_EL1:
            val = read_ttbr0_el12();
            VERBOSE("read TTBR0_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_TTBR1_EL1:
            val = read_ttbr1_el12();
            VERBOSE("read TTBR1_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_TCR_EL1:
            val = read_tcr_el12();
            VERBOSE("read TCR_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_MAIR_EL1:
            val = read_mair_el12();
            VERBOSE("read MAIR_EL12 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_AMAIR_EL1:
            val = read_amair_el12();
            VERBOSE("read AMAIR_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_CONTEXTIDR_EL1:
            val = read_contextidr_el12();
            VERBOSE("read CONTEXTIDR_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_AFSR0_EL1:
            val = read_afsr0_el12();
            VERBOSE("read AFSR0_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_AFSR1_EL1:
            val = read_afsr1_el12();
            VERBOSE("read AFSR1_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_ESR_EL1:
            val = read_esr_el12();
            VERBOSE("read ESR_EL1 -> %lx\n", val);
            break;
        case ESR_EL2_SYSREG_FAR_EL1:
            val = read_far_el12();
            VERBOSE("read FAR_EL1 -> %lx\n", val);
            break;
        default:
            ERROR("read: unknown sysreg (ESR=0x%lx)\n", esr_val);
            break;
    }

    return val;
}

static inline void
write_sysreg_by_esr(unsigned long esr_val, unsigned long val, struct rec* rec)
{
    switch (esr_val) {
        case ESR_EL2_SYSREG_SCTLR_EL1:
            VERBOSE("write SCTLR_EL1 <- %lx\n", val);
            write_sctlr_el12(val);
            break;
        case ESR_EL2_SYSREG_TTBR0_EL1:
            VERBOSE("write TTBR0_EL1 <- %lx\n", val);
            write_ttbr0_el12(val);
            break;
        case ESR_EL2_SYSREG_TTBR1_EL1:
            VERBOSE("write TTBR1_EL1 <- %lx\n", val);
            write_ttbr1_el12(val);
            break;
        case ESR_EL2_SYSREG_TCR_EL1:
            VERBOSE("write TCR_EL1 <- %lx\n", val);
            write_tcr_el12(val);
            break;
        case ESR_EL2_SYSREG_MAIR_EL1:
            VERBOSE("write MAIR_EL1 <- %lx\n", val);
            write_mair_el12(val);
            break;
        case ESR_EL2_SYSREG_AMAIR_EL1:
            VERBOSE("write AMAIR_EL1 <- %lx\n", val);
            write_amair_el12(val);
            break;
        case ESR_EL2_SYSREG_CONTEXTIDR_EL1:
            VERBOSE("write CONTEXTIDR_EL1 <- %lx\n", val);
            write_contextidr_el12(val);
            break;
        case ESR_EL2_SYSREG_AFSR0_EL1:
            VERBOSE("write AFSR0_EL1 <- %lx\n", val);
            write_afsr0_el12(val);
            break;
        case ESR_EL2_SYSREG_AFSR1_EL1:
            VERBOSE("write AFSR1_EL1 <- %lx\n", val);
            write_afsr1_el12(val);
            break;
        case ESR_EL2_SYSREG_ESR_EL1:
            VERBOSE("write ESR_EL1 <- %lx\n", val);
            write_esr_el12(val);
            break;
        case ESR_EL2_SYSREG_FAR_EL1:
            VERBOSE("write FAR_EL1 <- %lx\n", val);
            write_far_el12(val);
            break;
        default:
            ERROR("write: unknown sysreg (ESR=0x%lx, val=%lx)\n", esr_val, val);
            break;
    }
}

static inline bool
has_cache_enabled(struct rec* rec)
{
    unsigned long cache_bits = SCTLR_ELx_M_BIT | SCTLR_ELx_C_BIT;
    unsigned long reg = read_sctlr_el12();

    return (reg & cache_bits) == cache_bits;
}

void
opencca_stage2_flush_realm(struct rec* rec)
{
    flush_dcache_all();
}

static void
toggle_cache(struct rec* rec, bool was_enabled)
{
    bool now_enabled = has_cache_enabled(rec);
    unsigned long hcr;

    /* Here we do the same quirks as KVM does to deal with lack of FWB: */

    /*
     * If switching the MMU+caches on, need to invalidate the caches.
     * If switching it off, need to clean the caches.
     * Clean + invalidate does the trick always.
     */
    if (now_enabled != was_enabled) {
        opencca_stage2_flush_realm(rec);
    }

    /* Caches are now on, stop trapping VM ops */
    if (now_enabled) {
        VERBOSE("Caches are on now. Disable TVM trapping\n");
        hcr = read_hcr_el2();
        hcr &= ~HCR_TVM;
        write_hcr_el2(hcr);
        rec->common_sysregs.hcr_el2 &= ~HCR_TVM;
        isb();
    }
}

bool
opencca_handle_esr_tvm_sysreg_trap(struct rec* rec,
                struct rmi_rec_exit* rec_exit,
                unsigned long esr)
{
    unsigned long sysreg = esr & ESR_EL2_SYSREG_MASK;
    unsigned int rt = (unsigned int)ESR_EL2_SYSREG_ISS_RT(esr);
    bool was_cache_enabled = has_cache_enabled(rec);
    
    if (ESR_EL2_SYSREG_IS_WRITE(esr)) {
        write_sysreg_by_esr(sysreg, rec->regs[rt], rec);
    } else {
        rec->regs[rt] = read_sysreg_by_esr(sysreg, rec);
    }
    toggle_cache(rec, was_cache_enabled);
    return true;
}
