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
#if !defined(ROSE_CONVERSIONS_H)
#define ROSE_CONVERSIONS_H

class SgAsmExpression;
class SgAsmValueExpression;
class SgAsmByteValueExpression;
class SgAsmWordValueExpression;
class SgAsmDoubleWordValueExpression;
class SgAsmQuadWordValueExpression;
class SgAsmSingleFloatValueExpression;
class SgAsmDoubleFloatValueExpression;
class SgAsmVectorValueExpression;
class SgAsmBinaryExpression;
class SgAsmBinaryAdd;
class SgAsmBinarySubtract;
class SgAsmBinaryMultiply;
class SgAsmBinaryDivide;
class SgAsmBinaryMod;
class SgAsmBinaryAddPreupdate;
class SgAsmBinarySubtractPreupdate;
class SgAsmBinaryAddPostupdate;
class SgAsmBinarySubtractPostupdate;
class SgAsmBinaryLsl;
class SgAsmBinaryLsr;
class SgAsmBinaryAsr;
class SgAsmBinaryRor;
class SgAsmUnaryExpression;
class SgAsmUnaryPlus;
class SgAsmUnaryMinus;
class SgAsmUnaryRrx;
class SgAsmMemoryReferenceExpression;
class SgAsmRegisterReferenceExpression;
class SgAsmx86RegisterReferenceExpression;
class SgAsmPowerpcRegisterReferenceExpression;
class SgAsmInstruction;
class SgAsmOperandList;
class SgAsmType;
class SgAsmTypeByte;
class SgAsmTypeWord;
class SgAsmTypeDoubleWord;
class SgAsmTypeQuadWord;
class SgAsmTypeDoubleQuadWord;
class SgAsmType80bitFloat;
class SgAsmType128bitFloat;
class SgAsmTypeSingleFloat;
class SgAsmTypeDoubleFloat;
class SgAsmTypeVector;
class SgAsmx86Instruction;
class SgAsmPowerpcInstruction;

class SageInterface {
 public:
    static uint64_t getAsmSignedConstant(SgAsmValueExpression *);
};

SgAsmExpression* isSgAsmExpression( SgNode *s);
const SgAsmExpression* isSgAsmExpression( const SgNode * s );
SgAsmValueExpression* isSgAsmValueExpression( SgNode *);
const SgAsmValueExpression* isSgAsmValueExpression( const SgNode * s );
SgAsmByteValueExpression* isSgAsmByteValueExpression( SgNode *);
const SgAsmByteValueExpression* isSgAsmByteValueExpression( const SgNode * s );
SgAsmWordValueExpression* isSgAsmWordValueExpression( SgNode *);
const SgAsmWordValueExpression* isSgAsmWordValueExpression( const SgNode * s );
SgAsmDoubleWordValueExpression* isSgAsmDoubleWordValueExpression( SgNode *);
const SgAsmDoubleWordValueExpression* isSgAsmDoubleWordValueExpression( const SgNode * s );
SgAsmQuadWordValueExpression* isSgAsmQuadWordValueExpression( SgNode *);
const SgAsmQuadWordValueExpression* isSgAsmQuadWordValueExpression( const SgNode * s );
SgAsmSingleFloatValueExpression* isSgAsmSingleFloatValueExpression( SgNode *);
const SgAsmSingleFloatValueExpression* isSgAsmSingleFloatValueExpression( const SgNode * s );
SgAsmDoubleFloatValueExpression* isSgAsmDoubleFloatValueExpression( SgNode *);
const SgAsmDoubleFloatValueExpression* isSgAsmDoubleFloatValueExpression( const SgNode * s );
SgAsmVectorValueExpression* isSgAsmVectorValueExpression( SgNode *);
const SgAsmVectorValueExpression* isSgAsmVectorValueExpression( const SgNode * s );
SgAsmBinaryExpression* isSgAsmBinaryExpression( SgNode *);
const SgAsmBinaryExpression* isSgAsmBinaryExpression( const SgNode * s );
SgAsmBinaryAdd* isSgAsmBinaryAdd( SgNode *);
const SgAsmBinaryAdd* isSgAsmBinaryAdd( const SgNode * s );
SgAsmBinarySubtract* isSgAsmBinarySubtract( SgNode *);
const SgAsmBinarySubtract* isSgAsmBinarySubtract( const SgNode * s );
SgAsmBinaryMultiply* isSgAsmBinaryMultiply( SgNode *);
const SgAsmBinaryMultiply* isSgAsmBinaryMultiply( const SgNode * s );
SgAsmBinaryDivide* isSgAsmBinaryDivide( SgNode *);
const SgAsmBinaryDivide* isSgAsmBinaryDivide( const SgNode * s );
SgAsmBinaryMod* isSgAsmBinaryMod( SgNode *);
const SgAsmBinaryMod* isSgAsmBinaryMod( const SgNode * s );
SgAsmBinaryAddPreupdate* isSgAsmBinaryAddPreupdate( SgNode *);
const SgAsmBinaryAddPreupdate* isSgAsmBinaryAddPreupdate( const SgNode * s );
SgAsmBinarySubtractPreupdate* isSgAsmBinarySubtractPreupdate( SgNode *);
const SgAsmBinarySubtractPreupdate* isSgAsmBinarySubtractPreupdate( const SgNode * s );
SgAsmBinaryAddPostupdate* isSgAsmBinaryAddPostupdate( SgNode *);
const SgAsmBinaryAddPostupdate* isSgAsmBinaryAddPostupdate( const SgNode * s );
SgAsmBinarySubtractPostupdate* isSgAsmBinarySubtractPostupdate( SgNode *);
const SgAsmBinarySubtractPostupdate* isSgAsmBinarySubtractPostupdate( const SgNode * s );
SgAsmBinaryLsl* isSgAsmBinaryLsl( SgNode *);
const SgAsmBinaryLsl* isSgAsmBinaryLsl( const SgNode * s );
SgAsmBinaryLsr* isSgAsmBinaryLsr( SgNode *);
const SgAsmBinaryLsr* isSgAsmBinaryLsr( const SgNode * s );
SgAsmBinaryAsr* isSgAsmBinaryAsr( SgNode *);
const SgAsmBinaryAsr* isSgAsmBinaryAsr( const SgNode * s );
SgAsmBinaryRor* isSgAsmBinaryRor( SgNode *);
const SgAsmBinaryRor* isSgAsmBinaryRor( const SgNode * s );
SgAsmUnaryExpression* isSgAsmUnaryExpression( SgNode *);
const SgAsmUnaryExpression* isSgAsmUnaryExpression( const SgNode * s );
SgAsmUnaryPlus* isSgAsmUnaryPlus( SgNode *);
const SgAsmUnaryPlus* isSgAsmUnaryPlus( const SgNode * s );
SgAsmUnaryMinus* isSgAsmUnaryMinus( SgNode *);
const SgAsmUnaryMinus* isSgAsmUnaryMinus( const SgNode * s );
SgAsmUnaryRrx* isSgAsmUnaryRrx( SgNode *);
const SgAsmUnaryRrx* isSgAsmUnaryRrx( const SgNode * s );
SgAsmMemoryReferenceExpression* isSgAsmMemoryReferenceExpression( SgNode *);
const SgAsmMemoryReferenceExpression* isSgAsmMemoryReferenceExpression( const SgNode * s );
SgAsmRegisterReferenceExpression* isSgAsmRegisterReferenceExpression( SgNode *);
const SgAsmRegisterReferenceExpression* isSgAsmRegisterReferenceExpression( const SgNode * s );
SgAsmx86RegisterReferenceExpression* isSgAsmx86RegisterReferenceExpression( SgNode *);
const SgAsmx86RegisterReferenceExpression* isSgAsmx86RegisterReferenceExpression( const SgNode * s );
SgAsmPowerpcRegisterReferenceExpression* isSgAsmPowerpcRegisterReferenceExpression( SgNode *);
const SgAsmPowerpcRegisterReferenceExpression* isSgAsmPowerpcRegisterReferenceExpression( const SgNode * s );
SgAsmInstruction* isSgAsmInstruction( SgNode *);
const SgAsmInstruction* isSgAsmInstruction( const SgNode * s );
SgAsmOperandList* isSgAsmOperandList( SgNode *);
const SgAsmOperandList* isSgAsmOperandList( const SgNode * s );
SgAsmType* isSgAsmType( SgNode *);
const SgAsmType* isSgAsmType( const SgNode * s );
SgAsmTypeByte* isSgAsmTypeByte( SgNode *);
const SgAsmTypeByte* isSgAsmTypeByte( const SgNode * s );
SgAsmTypeWord* isSgAsmTypeWord( SgNode *);
const SgAsmTypeWord* isSgAsmTypeWord( const SgNode * s );
SgAsmTypeDoubleWord* isSgAsmTypeDoubleWord( SgNode *);
const SgAsmTypeDoubleWord* isSgAsmTypeDoubleWord( const SgNode * s );
SgAsmTypeQuadWord* isSgAsmTypeQuadWord( SgNode *);
const SgAsmTypeQuadWord* isSgAsmTypeQuadWord( const SgNode * s );
SgAsmTypeDoubleQuadWord* isSgAsmTypeDoubleQuadWord( SgNode *);
const SgAsmTypeDoubleQuadWord* isSgAsmTypeDoubleQuadWord( const SgNode * s );
SgAsmType80bitFloat* isSgAsmType80bitFloat( SgNode *);
const SgAsmType80bitFloat* isSgAsmType80bitFloat( const SgNode * s );
SgAsmType128bitFloat* isSgAsmType128bitFloat( SgNode *);
const SgAsmType128bitFloat* isSgAsmType128bitFloat( const SgNode * s );
SgAsmTypeSingleFloat* isSgAsmTypeSingleFloat( SgNode *);
const SgAsmTypeSingleFloat* isSgAsmTypeSingleFloat( const SgNode * s );
SgAsmTypeDoubleFloat* isSgAsmTypeDoubleFloat( SgNode *);
const SgAsmTypeDoubleFloat* isSgAsmTypeDoubleFloat( const SgNode * s );
SgAsmTypeVector* isSgAsmTypeVector( SgNode *);
const SgAsmTypeVector* isSgAsmTypeVector( const SgNode * s );
SgAsmx86Instruction* isSgAsmx86Instruction( SgNode *);
const SgAsmx86Instruction* isSgAsmx86Instruction( const SgNode * s );
SgAsmPowerpcInstruction* isSgAsmPowerpcInstruction( SgNode *);
const SgAsmPowerpcInstruction* isSgAsmPowerpcInstruction( const SgNode * s );
#endif
