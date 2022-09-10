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
    IDT_WEIRD_API void scramble(charbuffer_t&, std::uint16_t algorithem[]);
}

#endif