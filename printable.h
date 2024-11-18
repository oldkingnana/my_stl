#ifndef PRINTABLE_H
#define PRINTABLE_H
#pragma once
#include "config.h"
#include "sstream"

namespace original {
    class printable {
        mutable std::string cachedString;
    public:
        virtual ~printable() = 0;

        _GLIBCXX_NODISCARD virtual std::string toString(bool enter) const;
        _GLIBCXX_NODISCARD const char* toCString(bool enter) const;

        template<typename TYPE>
        static std::string formatString(const TYPE& t);
        template<typename TYPE>
        static const char* formatCString(const TYPE& t);
        template<typename TYPE>
        static std::string formatEnum(const TYPE& t);

        friend std::ostream& operator<<(std::ostream& os, const printable& p);
    };

    std::ostream& operator<<(std::ostream& os, const printable& p);
}

    inline original::printable::~printable() = default;

    inline std::string original::printable::toString(const bool enter) const
    {
        std::stringstream ss;
        ss << typeid(this).name() << "(#" << this << ")";
        if (enter) ss << "\n";
        return ss.str();
    }

    _GLIBCXX_NODISCARD inline auto original::printable::toCString(const bool enter) const -> const char*
    {
        this->cachedString = this->toString(enter);
        return this->cachedString.c_str();
    }

    template<typename TYPE>
    auto original::printable::formatString(const TYPE& t) -> std::string
    {
        if constexpr (std::is_enum_v<TYPE>) {
            return formatEnum(t);
        } else {
            std::stringstream ss;
            ss << t;
            return ss.str();
        }
    }

    template <typename TYPE>
    auto original::printable::formatCString(const TYPE& t) -> const char*
    {
        thread_local std::string cached_result;
        cached_result = formatString<TYPE>(t);
        return cached_result.c_str();
    }

    template <typename TYPE>
    auto original::printable::formatEnum(const TYPE& t) -> std::string
    {
        std::string enumName = typeid(t).name();
        const int enumValue = static_cast<std::underlying_type_t<TYPE>>(t);
        return enumName + "(" + std::to_string(enumValue) + ")";
    }

template<>
    inline auto original::printable::formatString<std::string>(const std::string& t) -> std::string
    {
        return "\"" + t + "\"";
    }

    template<>
    inline auto original::printable::formatString<char>(const char& t) -> std::string
    {
        return "'" + std::string(1, t) + "'";
    }

    template<>
    inline auto original::printable::formatString<bool>(const bool& t) -> std::string
    {
        return t != 0 ? "true" : "false";
    }

    template<>
    inline auto original::printable::formatString<std::nullptr_t>(const std::nullptr_t&) -> std::string
    {
        return "nullptr";
    }

    inline std::ostream& original::operator<<(std::ostream& os, const printable& p){
        os << p.toString(false);
        return os;
    }

#endif // PRINTABLE_H