#pragma once

#include <variant>

namespace lir {

    template<typename... Base>
    struct Visitor : Base... {
        using Base::operator()...;
    };

    template<typename... T>
    Visitor(T...) -> Visitor<T...>;

}