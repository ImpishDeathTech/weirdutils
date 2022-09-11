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
