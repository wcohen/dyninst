/*
 * Copyright (c) 1996-2011 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/* Test application (Mutatee) */

/* $Id: test1_16F_mutatee.c,v 1.1 2008/10/30 19:17:56 legendre Exp $ */

#include <stdlib.h>
#include "mutatee_util.h"

// **********************************************************************
// The following structure (struct block_) is made to correspond with the
// Fortran common block (globals) defined in test1_common.h.  Be sure all
// changes to this structure are reflected in the other.
// **********************************************************************
struct block_ {
  int test1_16_globalVariable16_1, test1_16_globalVariable16_2_, test1_16_globalVariable16_3_, test1_16_globalVariable16_4_, test1_16_globalVariable16_5_,
    test1_16_globalVariable16_6_, test1_16_globalVariable16_7_, test1_16_globalVariable16_8_, test1_16_globalVariable16_9_, test1_16_globalVariable16_10_;
  int passedTest_;
};

#if !defined(XLF)
#define test1_16_func1 test1_16_func1_
#define test1_16f_init_globals test1_16f_init_globals_
#define test1_16f_globals test1_16f_globals_
#endif

extern struct block_ test1_16f_globals;

extern void test1_16f_init_globals ();
extern void test1_16_func1 ();

int mutateeFortran = 1;

#ifdef F77
int mutateeF77 = 1;
#else
int mutateeF77 = 0;
#endif

int test1_16F_mutatee() {
  test1_16f_globals.passedTest_ = FALSE;

  if (setupFortranOutput()) {
    logerror("Error redirecting Fortran component output to log file\n");
  }

  test1_16f_init_globals();

  test1_16_func1();

  if (cleanupFortranOutput()) {
    logerror("Error restoring output to stdout\n");
  }

  /* Combine fortran passedTest with C passedTest */
  if (test1_16f_globals.passedTest_) {
    test_passes(testname);
    return 0;
  } else {
    return -1;
  }
}
