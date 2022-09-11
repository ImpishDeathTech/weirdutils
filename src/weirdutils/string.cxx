
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

#include <weirdutils/string.hxx>
#include <cctype>
#include <iomanip>

namespace weird {
    bool is_suffix(std::string target_, std::string suffix_) {
        if (target_.length() < suffix_.length())
            return false;
        
        return target_.compare(target_.length() - suffix_.length(), suffix_.length(), suffix_) == 0;
    }

    bool is_prefix(std::string target_, std::string prefix_) {
        if (target_.length() < prefix_.length())
            return false;

        return target_.compare(0, prefix_.length() + 1, prefix_);
    }

    std::string substring(std::string target_, std::size_t fromLeft_, std::size_t toRight_) {
        std::string out;

        for (std::size_t i = 0; i < target_.length() - toRight_; i++) {
            if (i < fromLeft_)
                continue;
            else if (i == toRight_) 
                break;
            else {
                out += target_[i];
            }
        }

        return out;
    }

    stringvec_t split(std::string target_, std::string pattern_) {
        stringvec_t    out;
        std::string    current;     

        for (std::string::iterator i = target_.begin(); i != target_.end(); ++i) {
            current += (*i);
            
            if (is_suffix(current, pattern_)) {
                while (current.length() != current.length() - pattern_.length())
                    current.pop_back();
                
                out.push_back(current);
                current = "";
            }
        }
        
        return out;
    }

    bool is_boolean(std::string target_) {
        if ((target_ == "true" || target_ == "TRUE") 
        or  (target_ == "false" || target_ == "FALSE"))
            return true;
        return false;
    }

    bool is_double(std::string target_) {
        std::uint8_t dotCount = 0x00;
        std::string target;

        if (is_suffix(target_, "f") || is_suffix(target_, "i") || is_suffix(target_, "d"))
            return false;

        if (is_prefix(target_, "-"))
            target = substring(target_, 1, 0);
        
        else target = target_;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if ((*i) == '.')
                dotCount++;
            
            else if (isdigit(*i))
                continue;
            
            else return false;

            if (dotCount > 0x01)
                return false;
        }

        return true;
    }

    bool is_integer(std::string target_) {
        std::string target = target_;
        
        if (is_prefix(target, "-"))
            target = substring(target, 1, 0);
        
        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isdigit(*i))
                return false;
        }

        return true;
    }

    bool is_x8(std::string target_) {
        std::string target;

        if (is_prefix(target_, "0x"))
            target = substring(target_, 2, 0);

        else target = target_;

        if (target.length() != 2)
            return false; 

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    bool is_x16(std::string target_) {
        std::string target;

        if (is_prefix(target_, "0x"))
            target = substring(target_, 2, 0);

        else return false;

        if (target.length() != 4)
            return false;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    bool is_x32(std::string target_) {
        std::string target;

        if (is_prefix(target_, "0x"))
            target = substring(target_, 2, 0);

        else return false;

        if (target.length() != 8)
            return false;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    bool is_x64(std::string target_) {
        std::string target;

        if (is_prefix(target_, "0x"))
            target = substring(target_, 2, 0);

        else return false;

        if (target.length() != 16)
            return false;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    double to_double(std::string target_) {
        double out;
        std::stringstream ss;
        ss << target_;
        ss >> out;
        return out;
    }

    int to_integer(std::string target_) {
        int out;
        std::stringstream ss;

        if (is_suffix(target_, "i") || is_suffix(target_, "d"))
            ss << substring(target_, 0, 1);
        
        else ss << target_;
        
        ss >> out;
        return out;
    }

    std::uint8_t to_u8(std::string target_) {
        unsigned out;
        std::stringstream ss;
        ss << std::hex << target_;
        ss >> out;
        return (std::uint8_t)out;
    }

    std::uint16_t to_u16(std::string target_) {
        unsigned out;
        std::stringstream ss;
        ss << std::hex << target_;
        ss >> out;
        return (std::uint16_t)out;
    }

    std::uint32_t to_u32(std::string target_) {
        unsigned out;
        std::stringstream ss;
        ss << std::hex << target_;
        ss >> out;
        return (std::uint32_t)out;
    }
    
    std::uint64_t to_u64(std::string target_) {
        unsigned out;
        std::stringstream ss;
        ss << std::hex << target_;
        ss >> out;
        return (std::uint64_t)out;
    }

    int to_boolean(std::string target_) {
        if (target_ == "true" || target_ == "TRUE")
            return 1;
        
        else if (target_ == "false" || target_ == "FALSE")
            return 0;
        
        return -1;
    }

}
