/* The system call implemented in this file:
 *   m_type:	SYS_FORK
 *
 * The parameters for this system call are:
 *    m1_i1:	PR_PROC_NR	(child's process table slot)	
 *    m1_i2:	PR_PPROC_NR	(parent, process that forked)	
 *    m1_i3:	PR_PID	 	(child pid received from PM)
 */

#include "../system.h"
#include <signal.h>
#if (CHIP == INTEL)
#include "../protect.h"
#endif

#if USE_FORK

/*===========================================================================*
 *				do_fork					     *
 *===========================================================================*/
PUBLIC int do_fork(m_ptr)
register message *m_ptr;	/* pointer to request message */
{
/* Handle sys_fork().  PR_PPROC_NR has forked.  The child is PR_PROC_NR. */

#if (CHIP == INTEL)
  reg_t old_ldt_sel;
#endif
  register struct proc *rpc;
  struct proc *rpp;

  rpp = proc_addr(m_ptr->PR_PPROC_NR);
  rpc = proc_addr(m_ptr->PR_PROC_NR);
  if (! isemptyp(rpc)) return(EINVAL);

  /* Copy parent 'proc' struct to child. */
#if (CHIP == INTEL)
  old_ldt_sel = rpc->p_ldt_sel;	/* stop this being obliterated by copy */
#endif

  *rpc = *rpp;					/* copy 'proc' struct */

#if (CHIP == INTEL)
  rpc->p_ldt_sel = old_ldt_sel;
#endif
  rpc->p_nr = m_ptr->PR_PROC_NR;	/* this was obliterated by copy */
  rpc->p_ntf_q = NULL;			/* remove pending notifications */

  /* Only one in group should have SIGNALED, child doesn't inherit tracing. */
  rpc->p_rts_flags |= NO_MAP;		/* inhibit process from running */
  rpc->p_rts_flags &= ~(SIGNALED | SIG_PENDING | P_STOP);
  sigemptyset(&rpc->p_pending);

  rpc->p_reg.retreg = 0;	/* child sees pid = 0 to know it is child */
  rpc->p_user_time = 0;		/* set all the accounting times to 0 */
  rpc->p_sys_time = 0;

  return(OK);
}

#endif /* USE_FORK */
