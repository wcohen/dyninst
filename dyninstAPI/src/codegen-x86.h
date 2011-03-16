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

#include <stdio.h>
#include <common/h/Vector.h>
#include <set>
#include <map>
#include <vector>
#include "dyn_regs.h"
#include "entryIDs.h"

#if !defined(i386_unknown_solaris2_5) \
 && !defined(i386_unknown_nt4_0) \
 && !defined(i386_unknown_linux2_0) \
 && !defined(x86_64_unknown_linux2_4) \
 && !(defined(os_freebsd) \
      && (defined(arch_x86) || defined(arch_x86_64))) \
 && !(defined(os_vxworks) && defined(arch_x86))
 
#error "invalid architecture-os inclusion"
#endif

#include "common/h/ia32_locations.h"

#ifndef _CODEGEN_X86_H
#define _CODEGEN_X86_H

// Code generation

typedef unsigned char codeBuf_t;
typedef unsigned codeBufIndex_t;

class codeGen;
class AddressSpace;

class insnCodeGen {
 public:

  // More code generation
  static void generatePush64(codeGen &gen, Address val);

  // Code generation
  static void generateBranch(codeGen &gen, Address from, Address to);
  static void generateBranch(codeGen &gen, int disp);
  static void generateBranch64(codeGen &gen, Address to);
  static void generateBranch32(codeGen &gen, Address to);
  static void generateCall(codeGen &gen, Address from, Address to);

  // Function relocation...
  static void generateInterFunctionBranch(codeGen &gen, Address from, Address to) { generateBranch(gen, from, to); }
  
  // We may want to generate an efficient set 'o nops
  static void generateNOOP(codeGen &gen, unsigned size = 1);
  
  static void generateIllegal(codeGen &gen);
  static void generateTrap(codeGen &gen);

  static void generate(codeGen &gen, instruction & insn);

  // And generate an equivalent stream somewhere else...
  // fallthroughOverride and targetOverride are used for
  // making the behavior of jumps change. It won't work for 
  // jumptables; that should be cleared up sometime.
  static bool generate(codeGen &gen,
                instruction & insn,
                AddressSpace *addrSpace,
                Address origAddr,
                Address newAddr,
                patchTarget *fallthroughOverride = NULL,
                patchTarget *targetOverride = NULL);

  static bool generateMem(codeGen &gen,
                   instruction & insn,
                   Address origAddr,
                   Address newAddr,
                   Register newLoadReg,
                   Register newStoreReg);
};

#endif
