
#pragma once

#include <string>
#include <sstream>

namespace StringHelper {
    const char FORMAT_SYMBOL = '$';

    inline std::string ToString(int x) { return std::to_string(x); };
    inline std::string ToString(unsigned int x) { return std::to_string(x); };
    inline std::string ToString(long x) { return std::to_string(x); };
    inline std::string ToString(unsigned long x) { return std::to_string(x); };
    inline std::string ToString(long long x) { return std::to_string(x); };
    inline std::string ToString(unsigned long long x) { return std::to_string(x); };
    inline std::string ToString(float x) { return std::to_string(x); };
    inline std::string ToString(double x) { return std::to_string(x); };
    inline std::string ToString(long double x) { return std::to_string(x); };
    inline std::string ToString(const std::string& x) { return x; };
    inline std::string ToString(const char* x) { return std::string(x); };

    template<typename T>
    inline std::string ToString(const T& t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    };

    template<typename T, typename... Targs>
    inline std::string Format(const std::string& fstr, const T& value, const Targs& ... args)
    {
        std::size_t pos = fstr.find_first_of(FORMAT_SYMBOL);

        if (pos == std::string::npos)
            return fstr;

        return fstr.substr(0, pos) + ToString(value) + Format(fstr.substr(pos + 1), args...);
    };

    inline std::string Format(const std::string& fstr) { return fstr; };
};