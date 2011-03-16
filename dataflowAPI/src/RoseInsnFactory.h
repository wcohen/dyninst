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
#pragma once

#if !defined(_ROSE_INSN_FACTORY_H_)
#define _ROSE_INSN_FACTORY_H_

#include "entryIDs.h"
#include "external/rose/rose-compat.h"
#include "external/rose/powerpcInstructionEnum.h"
#include "Visitor.h"
#include "dyn_detail/boost/shared_ptr.hpp"
#include <vector>

#if defined(_MSC_VER)
#include "external/stdint-win.h"
#elif defined(os_solaris)
#include <inttypes.h>
#else
#include <stdint.h>
#endif

class SgAsmInstruction;
class SgAsmx86Instruction;
class SgAsmExpression;
class SgAsmPowerpcInstruction;
class SgAsmOperandList;
class SgAsmx86RegisterReferenceExpression;
class SgAsmPowerpcRegisterReferenceExpression;

namespace Dyninst
{
namespace InstructionAPI {
  class RegisterAST;
  class Dereference;
  class Immediate;
  class BinaryFunction;
  class Expression;
  class Operand;
  class Instruction;
}

namespace DataflowAPI {
  class RoseInsnFactory {
  protected:
    typedef dyn_detail::boost::shared_ptr<InstructionAPI::Expression> ExpressionPtr;
    typedef dyn_detail::boost::shared_ptr<InstructionAPI::Instruction> InstructionPtr;
  public:
    DATAFLOW_EXPORT RoseInsnFactory(void) {};
    DATAFLOW_EXPORT virtual ~RoseInsnFactory(void) {};
    DATAFLOW_EXPORT virtual SgAsmInstruction *convert(const InstructionPtr &insn, uint64_t addr);

  protected:
    virtual SgAsmInstruction *createInsn() = 0;
    virtual void setOpcode(SgAsmInstruction *insn, entryID opcode, prefixEntryID prefix, std::string mnem) = 0;
    virtual void setSizes(SgAsmInstruction *insn) = 0; 
    virtual bool handleSpecialCases(entryID opcode, SgAsmInstruction *rinsn, SgAsmOperandList *roperands) = 0;
    virtual void massageOperands(const InstructionPtr &insn, std::vector<InstructionAPI::Operand> &operands) = 0;

    virtual SgAsmExpression *convertOperand(const ExpressionPtr expression, uint64_t addr);

    friend class ExpressionConversionVisitor;

    virtual Architecture arch() { return Arch_none; };
  };

class RoseInsnX86Factory : public RoseInsnFactory {
  public:
    DATAFLOW_EXPORT RoseInsnX86Factory() {};
    DATAFLOW_EXPORT virtual ~RoseInsnX86Factory() {};
    
  private:
    virtual SgAsmInstruction *createInsn();
    virtual void setOpcode(SgAsmInstruction *insn, entryID opcode, prefixEntryID prefix, std::string mnem);
    virtual void setSizes(SgAsmInstruction *insn);
    virtual bool handleSpecialCases(entryID opcode, SgAsmInstruction *rinsn, SgAsmOperandList *roperands);
    virtual void massageOperands(const InstructionPtr &insn, std::vector<InstructionAPI::Operand> &operands);

    X86InstructionKind convertKind(entryID opcode, prefixEntryID prefix);

    virtual Architecture arch() { return Arch_x86; };
  };

  class RoseInsnPPCFactory : public RoseInsnFactory {
  public:
    DATAFLOW_EXPORT RoseInsnPPCFactory(void) {};
    DATAFLOW_EXPORT virtual ~RoseInsnPPCFactory(void) {};

  private:
    virtual SgAsmInstruction *createInsn();
    virtual void setOpcode(SgAsmInstruction *insn, entryID opcode, prefixEntryID prefix, std::string mnem);
    virtual void setSizes(SgAsmInstruction *insn);
    virtual bool handleSpecialCases(entryID opcode, SgAsmInstruction *rinsn, SgAsmOperandList *roperands);
    virtual void massageOperands(const InstructionPtr &insn, std::vector<InstructionAPI::Operand> &operands);

    PowerpcInstructionKind convertKind(entryID opcode, std::string mnem);
    PowerpcInstructionKind makeRoseBranchOpcode(entryID iapi_opcode, bool isAbsolute, bool isLink);

    virtual Architecture arch() { return Arch_ppc32; };
    PowerpcInstructionKind kind;
  };
};
};

#endif
