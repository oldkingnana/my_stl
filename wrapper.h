#ifndef WRAPPER_H
#define WRAPPER_H
#pragma once
#include "string"
#include "config.h"
#include "printable.h"

namespace original
{
    template <typename TYPE>
    class wrapper : public printable{
    public:
        virtual TYPE& getVal() = 0;
        virtual const TYPE& getVal() const = 0;
        virtual void setVal(TYPE data) = 0;
        virtual wrapper* getPPrev() const = 0;
        virtual wrapper* getPNext() const = 0;
        ~wrapper() override = default;
        _GLIBCXX_NODISCARD std::string toString(bool enter) override;
    };

}
    template<typename TYPE>
    auto original::wrapper<TYPE>::toString(const bool enter) -> std::string
    {
        std::stringstream ss;
        ss << this->getVal();
        if (enter)
        {
            ss << "\n";
        }
        return ss.str();
    }
#endif //WRAPPER_H
