#pragma once

#include "token_types.hpp"
#include "visitor.hpp"

#include <variant>
#include <string>

#include <memory>

namespace lir {

    // Forward declares each expression struct so it can reference itself
    namespace expressions {
        struct Literal;
        struct Unary;
        struct Binary;
        struct Grouping;
    }

    using Expression = std::variant<
                           expressions::Literal,
                           expressions::Unary,
                           expressions::Binary,
                           expressions::Grouping>;

    namespace expressions {

        struct Literal {
            std::string value;
        };

        struct Unary {
            TokenType op;
            std::unique_ptr<Expression> expression;
        };

        struct Binary {
            std::unique_ptr<Expression> left;
            TokenType op;
            std::unique_ptr<Expression> right;
        };

        struct Grouping {
            std::unique_ptr<Expression> expression;
        };

    }

    using AST = std::unique_ptr<Expression>;

}