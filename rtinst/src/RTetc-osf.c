/*
 * Copyright (c) 1996-2000 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * This license is for research uses.  For such uses, there is no
 * charge. We define "research use" to mean you may freely use it
 * inside your organization for whatever purposes you see fit. But you
 * may not re-distribute Paradyn or parts of Paradyn, in any form
 * source or binary (including derivatives), electronic or otherwise,
 * to any other organization or entity without our permission.
 * 
 * (for other uses, please contact us at paradyn@cs.wisc.edu)
 * 
 * All warranties, including without limitation, any warranty of
 * merchantability or fitness for a particular purpose, are hereby
 * excluded.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * Even if advised of the possibility of such damages, under no
 * circumstances shall we (or any other person or entity with
 * proprietary rights in the software licensed hereunder) be liable
 * to you or any third party for direct, indirect, or consequential
 * damages of any character regardless of type of action, including,
 * without limitation, loss of profits, loss of use, loss of good
 * will, or computer failure or malfunction.  You agree to indemnify
 * us (and any other person or entity with proprietary rights in the
 * software licensed hereunder) for any and all liability it may
 * incur to third parties resulting from your use of Paradyn.
 */

/************************************************************************
 * $Id: RTetc-osf.c,v 1.1 2000/06/14 22:28:46 paradyn Exp $
 * RTosf.c: mutatee-side library function specific to OSF
************************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <sys/procfs.h>
#include <assert.h>
#include <fcntl.h>

#include "rtinst/h/rtinst.h"
#include "rtinst/h/trace.h"

static const double NANO_PER_USEC   = 1.0e3;
static const long int MILLION       = 1000000;

/* The alpha does not have a divide instruction */
/* Division is emulated in software */

int divide(int a,int b)
{
  return (a/b);
}

static unsigned long long div1000(unsigned long long in) {
   /* Divides by 1000 without an integer division instruction or library call,
    * both of which are slow.
    * We do only shifts, adds, and subtracts.
    *
    * We divide by 1000 in this way:
    * multiply by 1/1000, or multiply by (1/1000)*2^30 then right-shift by 30.
    * So what is 1/1000 * 2^30?
    * It is 1,073,742.   (actually this is rounded)
    * So we can multiply by 1,073,742 and then right-shift by 30 (neat, eh?)
    *
    * Now for multiplying by 1,073,742...
    * 1,073,742 = (1,048,576 + 16384 + 8192 + 512 + 64 + 8 + 4 + 2)
    * or, slightly optimized:
    * = (1,048,576 + 16384 + 8192 + 512 + 64 + 16 - 2)
    * for a total of 8 shifts and 6 add/subs, or 14 operations.
    */

   unsigned long long temp = in << 20; /* multiply by 1,048,576 */
   /* beware of overflow; left shift by 20 is quite a lot.
      If you know that the input fits in 32 bits (4 billion) then
      no problem.  But if it's much bigger then start worrying...
   */

   temp += in << 14; /* 16384 */
   temp += in << 13; /* 8192  */
   temp += in << 9;  /* 512   */
   temp += in << 6;  /* 64    */
   temp += in << 4;  /* 16    */
   temp -= in >> 2;  /* 2     */

   return (temp >> 30); /* divide by 2^30 */
}

static unsigned long long divMillion(unsigned long long in) {
   /* Divides by 1,000,000 without an integer division instruction or library
    * call, both of which are slow.
    * We do only shifts, adds, and subtracts.
    *
    * We divide by 1,000,000 in this way:
    * multiply by 1/1,000,000, or multiply by (1/1,000,000)*2^30 and then
    * right-shift by 30.  So what is 1/1,000,000 * 2^30?
    * It is 1,074.   (actually this is rounded)
    * So we can multiply by 1,074 and then right-shift by 30 (neat, eh?)
    *
    * Now for multiplying by 1,074
    * 1,074 = (1024 + 32 + 16 + 2)
    * for a total of 4 shifts and 4 add/subs, or 8 operations.
    *
    * Note: compare with div1000 -- it's cheaper to divide by a million than
    *       by a thousand (!)
    */

   unsigned long long temp = in << 10; /* multiply by 1024 */
   /* beware of overflow...if the input arg uses more than 52 bits
      than start worrying about whether (in << 10) plus the smaller additions
      we're gonna do next will fit in 64...
   */

   temp += in << 5; /* 32 */
   temp += in << 4; /* 16 */
   temp += in << 1; /* 2  */

   return (temp >> 30); /* divide by 2^30 */
}

static unsigned long long mulMillion(unsigned long long in) {
   unsigned long long result = in;

   /* multiply by 125 by multiplying by 128 and subtracting 3x */
   result = (result << 7) - result - result - result;

   /* multiply by 125 again, for a total of 15625x */
   result = (result << 7) - result - result - result;

   /* multiply by 64, for a total of 1,000,000x */
   result <<= 6;

   /* cost was: 3 shifts and 6 subtracts
    * cost of calling mul1000(mul1000()) would be: 6 shifts and 4 subtracts
    *
    * Another algorithm is to multiply by 2^6 and then 5^6.
    * The former is super-cheap (one shift); the latter is more expensive.
    * 5^6 = 15625 = 16384 - 512 - 256 + 8 + 1
    * so multiplying by 5^6 means 4 shift operations and 4 add/sub ops
    * so multiplying by 1000000 means 5 shift operations and 4 add/sub ops.
    * That may or may not be cheaper than what we're doing
    * (3 shifts; 6 subtracts); I'm not sure.  --ari
    */

   return result;
}

static int ctr_procFd = -1;

void DYNINSTos_init(int calledByFork, int calledByAttach)
{
  char fname[128];
  sprintf(fname, "/proc/%i", getpid());
  if ((ctr_procFd = open(fname, O_RDONLY)) == -1) {
    perror("DYNINSTinitCPUtime - open()");
    abort();
  }
}

/*static int MaxRollbackReport = 0; /* don't report any rollbacks!*/
static int MaxRollbackReport = 1; /* only report 1st rollback */
/*static int MaxRollbackReport = INT_MAX; /* report all rollbacks */

/************************************************************************
 * time64 DYNINSTgetCPUtime(void)
 *
 * return value is in usec units.
 ************************************************************************/

/* return (user+sys) CPU time in microseconds (us) */
time64
DYNINSTgetCPUtime(void)
{
  static time64 cpuPrevious=0;
  static int cpuRollbackOccurred=0;
  time64 now, tmp_cpuPrevious=cpuPrevious;

  prpsinfo_t procinfo;
  
  if (ioctl(ctr_procFd, PIOCPSINFO, &procinfo) == -1) {
      perror("DYNINSTgetCPUtime - PIOCPSINFO");
      abort();
  }

  /* Put secs and nsecs into usecs */
  now = mulMillion(procinfo.pr_time.tv_sec) +
        div1000(procinfo.pr_time.tv_nsec);

  if (now < tmp_cpuPrevious) {
    if (cpuRollbackOccurred < MaxRollbackReport) {
      rtUIMsg traceData;
      sprintf(traceData.msgString, "CPU time rollback %lld with current time:"
                          " %lld usecs, using previous value %lld usecs.",
                          tmp_cpuPrevious-now,now,tmp_cpuPrevious);
      traceData.errorNum = 112;
      traceData.msgType = rtWarning;
      DYNINSTgenerateTraceRecord(0, TR_ERROR, sizeof(traceData), &traceData, 1,
                                             1, 1);
    }
    cpuRollbackOccurred++;
    now = cpuPrevious;
  }
  else  cpuPrevious = now;
  
  return now;
}

/************************************************************************
 * time64 DYNINSTgetWalltime(void)
 *
 * get the total walltime used by the monitored process.
 * return value is in usec units.
 ************************************************************************/

time64
DYNINSTgetWalltime(void) {
  static time64 wallPrevious=0;
  static int wallRollbackOccurred=0;
  time64 now, tmp_wallPrevious=wallPrevious;

  struct timeval tv;
  if (gettimeofday(&tv,NULL) == -1) {
      perror("gettimeofday");
      assert(0);
      abort();
  }

  /* now = mulMillion(tv.tv_sec) + tv.tv_usec; */
  now = (time64)tv.tv_sec*(time64)1000000 + (time64)tv.tv_usec;

  if (now < tmp_wallPrevious) {
    if (wallRollbackOccurred < MaxRollbackReport) {
      rtUIMsg traceData;
      sprintf(traceData.msgString, "Wall time rollback %lld with current time:"
                          " %lld usecs, using previous value %lld usecs.",
                          tmp_wallPrevious-now,now,tmp_wallPrevious);
      traceData.errorNum = 112;
      traceData.msgType = rtWarning;
      DYNINSTgenerateTraceRecord(0, TR_ERROR, sizeof(traceData), &traceData, 1,
                                             1, 1);
    }
    wallRollbackOccurred++;
    now = wallPrevious;
  }
  else  wallPrevious = now;

  
  return(now);
}

