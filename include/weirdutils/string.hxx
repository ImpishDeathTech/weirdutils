
/*
 * string.cxx
 *
 * BSD 3-Clause License
 * 
 * Copyright (c) 2022, Christopher Stephen Rafuse
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef IDT_WEIRD_UTILS_STRING_HXX
#define IDT_WEIRD_UTILS_STRING_HXX

extern "C" {
#include <weirdutils/configuration.h>
}

#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <sstream>

namespace weird {
    typedef std::vector<std::string> stringvec_t;
    
    IDT_WEIRD_API bool        is_prefix(std::string target_, std::string prefix_);
    IDT_WEIRD_API bool        is_suffix(std::string target_, std::string suffix_);
    IDT_WEIRD_API std::string substring(std::string target_, std::size_t fromLeft_, std::size_t toRight);
    IDT_WEIRD_API stringvec_t split(std::string target_, std::string pattern_);
    
    IDT_WEIRD_API bool is_double(std::string target_);
    IDT_WEIRD_API bool is_integer(std::string target_);
    IDT_WEIRD_API bool is_boolean(std::string target_);
    IDT_WEIRD_API bool is_x8(std::string target_);
    IDT_WEIRD_API bool is_x16(std::string target_);
    IDT_WEIRD_API bool is_x32(std::string target_);
    IDT_WEIRD_API bool is_x64(std::string target_);

    IDT_WEIRD_API int           to_integer(std::string target_);
    IDT_WEIRD_API double        to_double(std::string target_);
    IDT_WEIRD_API int           to_boolean(std::string target_);
    IDT_WEIRD_API std::uint8_t  to_u8(std::string target_);
    IDT_WEIRD_API std::uint16_t to_u16(std::string target_);
    IDT_WEIRD_API std::uint32_t to_u32(std::string target_);
    IDT_WEIRD_API std::uint64_t to_u64(std::string target_);
}

#endif
