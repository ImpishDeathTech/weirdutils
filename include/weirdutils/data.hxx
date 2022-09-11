
/*
 * data.hxx
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

#ifndef IDT_WEIRD_UTILS_DATA_HXX
#define IDT_WEIRD_UTILS_DATA_HXX

extern "C" {
#include <weirdutils/configuration.h>
}

#include <cstdint>
#include <vector>
#include <iostream>

namespace weird {
    typedef const char* cstring_t;

    /*
     * data buffer for containing the original size and pointer to
     * the original data
     */
    class IDT_WEIRD_API databuffer_t {
        public:
        void*       data { nullptr };
        std::size_t size { 0 };
    };

    /*
     * Bytecode buffer used to iterate through the bytecode
     * DataBuffer's evil twin! 
     */
    class IDT_WEIRD_API bytebuffer_t {
        public:
        std::uint8_t* data { nullptr };
        std::size_t   size { 0 };
    };
    /* 
     * Char buffer cause why not, it's useful;
     */

    class IDT_WEIRD_API charbuffer_t {
        public:
        cstring_t   data { nullptr };
        std::size_t size { 0 };
    };

    typedef std::vector<databuffer_t> slicevec_t;

    IDT_WEIRD_API void hexshit(databuffer_t& value);
    IDT_WEIRD_API void scramble(charbuffer_t& buffer_, std::vector<std::int8_t> algo_);
}

#endif
