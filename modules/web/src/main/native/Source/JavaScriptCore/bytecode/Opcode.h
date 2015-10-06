/*
 * Copyright (C) 2008, 2009, 2013, 2014 Apple Inc. All rights reserved.
 * Copyright (C) 2008 Cameron Zwarich <cwzwarich@uwaterloo.ca>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef Opcode_h
#define Opcode_h

#include "LLIntOpcode.h"

#include <algorithm>
#include <string.h>

#include <wtf/Assertions.h>

namespace JSC {

#define FOR_EACH_CORE_OPCODE_ID_WITH_EXTENSION(macro, extension__) \
    macro(op_enter, 1) \
    macro(op_create_activation, 2) \
    macro(op_touch_entry, 1) \
    macro(op_init_lazy_reg, 2) \
    macro(op_create_arguments, 2) \
    macro(op_create_this, 4) \
    macro(op_get_callee, 3) \
    macro(op_to_this, 3) \
    \
    macro(op_new_object, 4) \
    macro(op_new_array, 5) \
    macro(op_new_array_with_size, 4) \
    macro(op_new_array_buffer, 5) \
    macro(op_new_regexp, 3) \
    macro(op_mov, 3) \
    macro(op_captured_mov, 4) \
    \
    macro(op_not, 3) \
    macro(op_eq, 4) \
    macro(op_eq_null, 3) \
    macro(op_neq, 4) \
    macro(op_neq_null, 3) \
    macro(op_stricteq, 4) \
    macro(op_nstricteq, 4) \
    macro(op_less, 4) \
    macro(op_lesseq, 4) \
    macro(op_greater, 4) \
    macro(op_greatereq, 4) \
    \
    macro(op_inc, 2) \
    macro(op_dec, 2) \
    macro(op_to_number, 3) \
    macro(op_negate, 3) \
    macro(op_add, 5) \
    macro(op_mul, 5) \
    macro(op_div, 5) \
    macro(op_mod, 4) \
    macro(op_sub, 5) \
    \
    macro(op_lshift, 4) \
    macro(op_rshift, 4) \
    macro(op_urshift, 4) \
    macro(op_unsigned, 3) \
    macro(op_bitand, 5) \
    macro(op_bitxor, 5) \
    macro(op_bitor, 5) \
    \
    macro(op_check_has_instance, 5) \
    macro(op_instanceof, 4) \
    macro(op_typeof, 3) \
    macro(op_is_undefined, 3) \
    macro(op_is_boolean, 3) \
    macro(op_is_number, 3) \
    macro(op_is_string, 3) \
    macro(op_is_object, 3) \
    macro(op_is_function, 3) \
    macro(op_in, 4) \
    \
    macro(op_init_global_const_nop, 5) \
    macro(op_init_global_const, 5) \
    macro(op_get_by_id, 9) /* has value profiling */ \
    macro(op_get_by_id_out_of_line, 9) /* has value profiling */ \
    macro(op_get_array_length, 9) /* has value profiling */ \
    macro(op_get_arguments_length, 4) \
    macro(op_put_by_id, 9) \
    macro(op_put_by_id_out_of_line, 9) \
    macro(op_put_by_id_transition_direct, 9) \
    macro(op_put_by_id_transition_direct_out_of_line, 9) \
    macro(op_put_by_id_transition_normal, 9) \
    macro(op_put_by_id_transition_normal_out_of_line, 9) \
    macro(op_del_by_id, 4) \
    macro(op_get_by_val, 6) /* has value profiling */ \
    macro(op_get_argument_by_val, 6) /* must be the same size as op_get_by_val */ \
    macro(op_get_by_pname, 7) \
    macro(op_put_by_val, 5) \
    macro(op_put_by_val_direct, 5) \
    macro(op_del_by_val, 4) \
    macro(op_put_by_index, 4) \
    macro(op_put_getter_setter, 5) \
    \
    macro(op_jmp, 2) \
    macro(op_jtrue, 3) \
    macro(op_jfalse, 3) \
    macro(op_jeq_null, 3) \
    macro(op_jneq_null, 3) \
    macro(op_jneq_ptr, 4) \
    macro(op_jless, 4) \
    macro(op_jlesseq, 4) \
    macro(op_jgreater, 4) \
    macro(op_jgreatereq, 4) \
    macro(op_jnless, 4) \
    macro(op_jnlesseq, 4) \
    macro(op_jngreater, 4) \
    macro(op_jngreatereq, 4) \
    \
    macro(op_loop_hint, 1) \
    \
    macro(op_switch_imm, 4) \
    macro(op_switch_char, 4) \
    macro(op_switch_string, 4) \
    \
    macro(op_new_func, 4) \
    macro(op_new_captured_func, 4) \
    macro(op_new_func_exp, 3) \
    macro(op_call, 8) /* has value profiling */ \
    macro(op_call_eval, 8) /* has value profiling */ \
    macro(op_call_varargs, 8) /* has value profiling */ \
    macro(op_tear_off_activation, 2) \
    macro(op_tear_off_arguments, 3) \
    macro(op_ret, 2) \
    macro(op_ret_object_or_this, 3) \
    \
    macro(op_construct, 8) \
    macro(op_strcat, 4) \
    macro(op_to_primitive, 3) \
    \
    macro(op_get_pnames, 6) \
    macro(op_next_pname, 7) \
    \
    macro(op_resolve_scope, 6) \
    macro(op_get_from_scope, 8) /* has value profiling */ \
    macro(op_put_to_scope, 7) \
    \
    macro(op_push_with_scope, 2) \
    macro(op_pop_scope, 1) \
    macro(op_push_name_scope, 4) \
    \
    macro(op_catch, 2) \
    macro(op_throw, 2) \
    macro(op_throw_static_error, 3) \
    \
    macro(op_debug, 3) \
    macro(op_profile_will_call, 2) \
    macro(op_profile_did_call, 2) \
    \
    extension__ \
    \
    macro(op_end, 2) // end must be the last opcode in the list

#define FOR_EACH_CORE_OPCODE_ID(macro) \
    FOR_EACH_CORE_OPCODE_ID_WITH_EXTENSION(macro, /* No extension */ )

#define FOR_EACH_OPCODE_ID(macro) \
    FOR_EACH_CORE_OPCODE_ID_WITH_EXTENSION( \
        macro, \
        FOR_EACH_LLINT_OPCODE_EXTENSION(macro) \
    )


#define OPCODE_ID_ENUM(opcode, length) opcode,
    typedef enum { FOR_EACH_OPCODE_ID(OPCODE_ID_ENUM) } OpcodeID;
#undef OPCODE_ID_ENUM

const int maxOpcodeLength = 9;
const int numOpcodeIDs = op_end + 1;

#define OPCODE_ID_LENGTHS(id, length) const int id##_length = length;
    FOR_EACH_OPCODE_ID(OPCODE_ID_LENGTHS);
#undef OPCODE_ID_LENGTHS

#define OPCODE_LENGTH(opcode) opcode##_length

#define OPCODE_ID_LENGTH_MAP(opcode, length) length,
    const int opcodeLengths[numOpcodeIDs] = { FOR_EACH_OPCODE_ID(OPCODE_ID_LENGTH_MAP) };
#undef OPCODE_ID_LENGTH_MAP

#define VERIFY_OPCODE_ID(id, size) COMPILE_ASSERT(id <= op_end, ASSERT_THAT_JS_OPCODE_IDS_ARE_VALID);
    FOR_EACH_OPCODE_ID(VERIFY_OPCODE_ID);
#undef VERIFY_OPCODE_ID

#if ENABLE(COMPUTED_GOTO_OPCODES)
typedef void* Opcode;
#else
typedef OpcodeID Opcode;
#endif

#define PADDING_STRING "                                "
#define PADDING_STRING_LENGTH static_cast<unsigned>(strlen(PADDING_STRING))

extern const char* const opcodeNames[];

inline const char* padOpcodeName(OpcodeID op, unsigned width)
{
    unsigned pad = width - strlen(opcodeNames[op]);
    pad = std::min(pad, PADDING_STRING_LENGTH);
    return PADDING_STRING + PADDING_STRING_LENGTH - pad;
}

#undef PADDING_STRING_LENGTH
#undef PADDING_STRING

#if ENABLE(OPCODE_STATS)

struct OpcodeStats {
    OpcodeStats();
    ~OpcodeStats();
    static long long opcodeCounts[numOpcodeIDs];
    static long long opcodePairCounts[numOpcodeIDs][numOpcodeIDs];
    static int lastOpcode;
    
    static void recordInstruction(int opcode);
    static void resetLastInstruction();
};

#endif

inline size_t opcodeLength(OpcodeID opcode)
{
    switch (opcode) {
#define OPCODE_ID_LENGTHS(id, length) case id: return OPCODE_LENGTH(id);
         FOR_EACH_OPCODE_ID(OPCODE_ID_LENGTHS)
#undef OPCODE_ID_LENGTHS
    }
    RELEASE_ASSERT_NOT_REACHED();
    return 0;
}

} // namespace JSC

#endif // Opcode_h