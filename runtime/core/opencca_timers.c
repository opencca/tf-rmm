/* Opencca: Based on timers.c but without cnthctl_el2 EL2_CNTVMASK support */

#include <arch_helpers.h>
#include <rec.h>
#include <smc-rmi.h>
#include <timers.h>

/*
 * Check that timer output is asserted:
 * Timer enabled: CNTx_CTL_ENABLE = 1
 * Timer condition is met: CNTx_CTL_ISTATUS = 1
 * Timer interrupt is not masked: CNTx_CTL_IMASK = 0
 */
#define TIMER_ASSERTED(reg)                                                    \
    (((reg) & (CNTx_CTL_ENABLE | CNTx_CTL_ISTATUS | CNTx_CTL_IMASK)) ==        \
     (CNTx_CTL_ENABLE | CNTx_CTL_ISTATUS))


bool
opencca_check_pending_timers(struct rec* rec, int simd_trap)
{
#define ABS(x) ((x) < 0 ? -(x) : (x))
    unsigned long cntv_ctl = read_cntv_ctl_el02();
    unsigned long cntp_ctl = read_cntp_ctl_el02();

    /* Save the old state */
    unsigned long cntv_ctl_old = rec->sysregs.cntv_ctl_el0;
    unsigned long cntp_ctl_old = rec->sysregs.cntp_ctl_el0;

    /* Virt Timer */
    if (TIMER_ASSERTED(cntv_ctl) || simd_trap) {
        // Mask
        rec->sysregs.cntv_ctl_el0 |= CNTx_CTL_IMASK;
    } else {
        // Unmask
        rec->sysregs.cntv_ctl_el0 &= ~CNTx_CTL_IMASK;
    }


    /* Phy Timer */
    if (TIMER_ASSERTED(cntp_ctl) || simd_trap) {
        // Mask
        rec->sysregs.cntp_ctl_el0 |= CNTx_CTL_IMASK;
    } else {
        // Unmask
        rec->sysregs.cntp_ctl_el0 &= ~CNTx_CTL_IMASK;
    }

    write_cntv_ctl_el02(rec->sysregs.cntv_ctl_el0);
    write_cntp_ctl_el02(rec->sysregs.cntp_ctl_el0);
    isb();

    /*
     * We don't want to run the Realm just to immediately exit due a
     * physical interrupt caused by one of the timer interrupts not having
     * been retired from the CPU interface yet. Check that the interrupts
     * are retired before entering the Realm.
     */
    while (true) {
        unsigned long hppir = read_icc_hppir1_el1();
        unsigned int intid = (unsigned int)EXTRACT(ICC_HPPIR1_EL1_INTID, hppir);

        if (!((((rec->sysregs.cntv_ctl_el0 & CNTx_CTL_IMASK) != 0UL) &&
               (intid == EL1_VIRT_TIMER_PPI)) ||
              (((rec->sysregs.cntp_ctl_el0 & CNTx_CTL_IMASK) != 0UL) &&
               (intid == EL1_PHYS_TIMER_PPI)))) {
            break;
        }
    }

    /*
     * Check if the timers changed their output status based on
     * the previously saved timer state at the last Realm exit.
     */
    return (TIMER_ASSERTED(cntv_ctl) != TIMER_ASSERTED(cntv_ctl_old)) ||
           (TIMER_ASSERTED(cntp_ctl) != TIMER_ASSERTED(cntp_ctl_old));


    return 0;
}
