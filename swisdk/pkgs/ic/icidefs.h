/*************
 *
 * $Id: icidefs.h,v 1.3 2008/07/30 22:10:02 rfiler Exp $
 *
 * Filename: icidefs
 *
 * Purpose:  Internal constants and data structures for the ic package.
 *
 * Note:     None
 *
 * Copyright: © 2008 Sierra Wireless Inc., all rights reserved
 *
 **************/

/*
 *  Local constants and enumerated types.
 */
#ifndef icidefs_h
#define icidefs_h

#include "dl/dludefs.h"
#include "mm/mmudefs.h"
#include "ic/icudefs.h"
#include "ql/qludefs.h"

/* Logging Interval for the tick task main loop */
#define ICLOGINTERVAL 100  /* Number of loops between logs */

/* Defines for use with dlLog calls */
#define ICLOG_CLASSA   0x0001
#define ICLOG_CLASSB   0x0002
#define ICLOG_CLASSC   0x0004
#define ICLOG_CLASSD   0x0008

/*************
 *
 * Name:     icttcb
 *
 * Purpose:  IC Time Tick Task control block. Contains items required 
 *           by the IC Time Tick task during normal operation
 *             
 * Members:  
 *           icttsem     - Tick Task semaphore 
 *           icttwaiter  - Waiter structure 
 *           icttdluser  - Used by the log task
 *           icttregqhp  - Head of registration queue block
 *
 * 
 * Notes:    None
 *
 **************/
struct icttcb {
    struct swi_ossemaphore icttsem;      /* Tick Task semaphore */
    struct swi_oswaiter    icttwaiter;   /* waiter structure */
    struct dlusercb        icttdluser;   /* for log task */
    struct icttregqblk     icttregqhp;   /* head of registration queue */
};

#include "iciproto.h"

#endif
/*
 * $Log: icidefs.h,v $
 */
