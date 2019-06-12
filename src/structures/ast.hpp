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

        // Constant values in code such as strings and numbers
        struct Literal {
            Literal(const std::string& val)
                : value(val) {}

            std::string value;
        };

        // Unary operators such as - 
        struct Unary {
            Unary(TokenType o, std::unique_ptr<Expression>& expr)
                : op(o), expression(std::move(expr)) {}

            TokenType op;
            std::unique_ptr<Expression> expression;
        };

        // Binary operators such as +, - , *, /
        struct Binary {
            Binary(std::unique_ptr<Expression>& l, TokenType o, std::unique_ptr<Expression>& r)
                : left(std::move(l)), op(o), right(std::move(r)) {}

            std::unique_ptr<Expression> left;
            TokenType op;
            std::unique_ptr<Expression> right;
        };

        // Parenthesis
        struct Grouping {
            Grouping(std::unique_ptr<Expression>& expr)
                : expression(std::move(expr)) {}
            
            std::unique_ptr<Expression> expression;
        };

    }

    // Will contain all types of AST nodes, right only only expessions exist
    using AST = std::unique_ptr<Expression>;

    // Simple struct used for printing the AST
    struct ASTPrinter {

        std::ostream& os = std::cout;

        void reset() {
            os << lir::style::reset
               << lir::colour::bg::normal
		       << lir::colour::fg::black;
        }

        void operator()(const lir::expressions::Literal& node) {
            os << lir::colour::bg::black
		       << lir::colour::fg::normal
               << node.value
               << lir::colour::bg::normal
               << lir::colour::fg::black;
        }

        void operator()(const lir::expressions::Unary& node) {
            os << "(" 
               << lir::style::bold
		       << lir::colour::fg::bright::yellow
               << std::string(lir::Tokens::to_str[node.op])
               << lir::style::reset
		       << lir::colour::fg::black
               << " ";

            print(node.expression);

            os << ")";
        }

        void operator()(const lir::expressions::Binary& node) {
            os << "(" 
               << lir::style::bold
		       << lir::colour::fg::bright::yellow
               << std::string(lir::Tokens::to_str[node.op])
               << lir::style::reset
		       << lir::colour::fg::black
               << " ";

            print(node.left);

            os << " ";

            print(node.right);

            os << ")";
        }

        void operator()(const lir::expressions::Grouping& node) {
            os << "(" 
               << lir::style::bold
		       << lir::colour::fg::bright::yellow
               << "group"
               << lir::style::reset
		       << lir::colour::fg::black
               << " ";

            print(node.expression);

            os << ")";
        }

        void print(const lir::AST& ast) {
            reset();
            return std::visit(*this, *ast);
        }
        
    };

}

// Printing the AST using ASTPrinter
inline std::ostream& operator<<(std::ostream& os, const lir::AST& ast) {
    lir::ASTPrinter p = { .os = os };
    p.print(ast);
    return os;
}