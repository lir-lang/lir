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
            Literal(const std::string& val)
                : value(val) {}

            std::string value;
        };

        struct Unary {
            Unary(TokenType o, std::unique_ptr<Expression>& expr)
                : op(o), expression(std::move(expr)) {}

            TokenType op;
            std::unique_ptr<Expression> expression;
        };

        struct Binary {
            Binary(std::unique_ptr<Expression>& l, TokenType o, std::unique_ptr<Expression>& r)
                : left(std::move(l)), op(o), right(std::move(r)) {}

            std::unique_ptr<Expression> left;
            TokenType op;
            std::unique_ptr<Expression> right;
        };

        struct Grouping {
            Grouping(std::unique_ptr<Expression>& expr)
                : expression(std::move(expr)) {}
            
            std::unique_ptr<Expression> expression;
        };

    }

    using AST = std::unique_ptr<Expression>;

}