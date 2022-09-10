#include <weirdutils/string.hxx>
#include <cctype>

namespace weird {
    bool is_suffix(std::string& target_, std::string suffix_) {
        if (target_.length() < suffix_.length())
            return false;
        
        return target_.compare(target_.length() - suffix_.length(), suffix_.length(), suffix_) == 0;
    }

    bool is_prefix(std::string& target_, std::string prefix_) {
        if (target_.length() < prefix_.length())
            return false;

        return target_.compare(0, prefix_.length(), prefix_);
    }

    std::string substring(std::string& target_, std::size_t fromLeft_, std::size_t toRight_) {
        std::string out;

        for (std::size_t i = 0; i < target_.length(); i++) {
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

    stringvec_t split(std::string& target_, std::string& pattern_) {
        stringvec_t    out;
        std::string    current;     

        for (std::string::iterator i = target_.begin(); i != target_.end(); ++i) {
            current += (*i);
            
            if (is_suffix(current, pattern_)) {
                current = substring(current, 0, pattern_.length() - 1);
                out.push_back(current);
                current = "";
            }
        }
        
        return out;
    }

    bool is_float(std::string& target_) {
        std::uint8_t dotCount = 0x00;

        if (is_suffix(target_, "f")) {
            std::string target = substring(target_, 0, target_.length() - 2);

            if (is_prefix(target, "-"))
                target = substring(target_, 1, target_.length() - 1);

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

        return false;
    }

    bool is_integer(std::string& target_) {
        std::string target;

        if (is_suffix(target_, "i") || is_suffix(target_, "d"))
            target = substring(target_, 0, target_.length() - 2);
        else
            target = target_;
        
        if (is_prefix(target, "-"))
            target = substring(target, 1, target.length() - 1);
        
        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isdigit(*i))
                return false;
        }

        return true;
    }

    bool is_hex8(std::string& target_) {
        std::string target;

        if (is_suffix(target_, "x") || is_suffix(target_, "h"))
            target = substring(target_, 0, target.length() - 2);

        else target = target_;

        if (is_prefix(target, "-") || target.length() != 2)
            return false;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    bool is_hex16(std::string& target_) {
        std::string target;

        if (is_suffix(target_, "x") || is_suffix(target_, "h"))
            target = substring(target_, 0, target.length() - 2);

        else target = target_;

        if (is_prefix(target, "-") || target.length() != 4)
            return false;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    bool is_hex32(std::string& target_) {
        std::string target;

        if (is_suffix(target_, "x") || is_suffix(target_, "h"))
            target = substring(target_, 0, target.length() - 2);

        else target = target_;

        if (is_prefix(target_, "-") || target.length() != 8)
            return false;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    bool is_hex64(std::string& target_) {
        std::string target;
        if (is_prefix(target_, "x"))
            target = substring(target_, 0, target.length() - 2);

        else target = target_;

        if (target.length() != 16)
            return false;

        for (std::string::iterator i = target.begin(); i != target.end(); ++i) {
            if (!isxdigit(*i))
                return false;
        }
        return true;
    }

    bool to_boolean(std::string& target_) {
        if ((target_ == "#t")
        or  (target_ == "true")
        or  (target_ == "True")
        or  (target_ == "TRUE"))
            return true;
        
        else if ((target_ == "#f")
             or  (target_ == "false")
             or  (target_ == "False")
             or  (target_ == "FALSE"))
            return false;
        
        return true;

    }

    float to_float(std::string& target_) {
        float out;
        std::stringstream ss;
        ss << target_;
        ss >> out;
        return out;
    }

    int to_integer(std::string& target_) {
        int out;
        std::stringstream ss;
        ss << target_;
        ss >> out;
        return out;
    }

    std::uint8_t to_u8(std::string& target_) {
        std::int16_t out;
        std::stringstream ss;
        ss << target_;
        ss >> out;
        return (std::uint8_t)out;
    }

    std::uint16_t to_u16(std::string& target_) {
        std::uint16_t out;
        std::stringstream ss;
        ss << target_;
        ss >> out;
        return out;
    }

    std::uint32_t to_u32(std::string& target_) {
        std::uint32_t out;
        std::stringstream ss;
        ss << target_;
        ss >> out;
        return out;
    }
    
    std::uint64_t to_u64(std::string& target_) {
        std::uint64_t out;
        std::stringstream ss;
        ss << target_;
        ss >> out;
        return out;
    }




}