#pragma once

#include <structures/structures.hpp>

#include <string>
#include <variant>

namespace lir::backend::treewalk {

    using TreeWalkValue = std::variant<double, bool>;

    // Simple tree walk interpreter, not complete
    class TreeWalk {
    public:

        // Executes literal nodes
        TreeWalkValue operator()(const lir::expressions::Literal& node) {
            return { std::stod(node.value) };
        }

        // Executes unary nodes
        TreeWalkValue operator()(const lir::expressions::Unary& node) {
            auto expr = eval(node.expression);

            switch (node.op) {
                case Tokens::Op_Minus:
                    return { -std::get<double>(expr) };
                    
                default:
                    throw std::runtime_error("UNREACHABLE");
            }
        }

        // Executes binary nodes
        TreeWalkValue operator()(const lir::expressions::Binary& node) {
            auto left  = eval(node.left);
            auto right = eval(node.right);

            switch (node.op) {
                // Numerical operations
                case Tokens::Op_Plus: 
                    return { std::get<double>(left) + std::get<double>(right) };
                case Tokens::Op_Minus:
                    return { std::get<double>(left) - std::get<double>(right) };
                case Tokens::Op_Multiply:
                    return { std::get<double>(left) * std::get<double>(right) };
                case Tokens::Op_Divide:
                    return { std::get<double>(left) / std::get<double>(right) };

                // Boolean operations
                case Tokens::Cmp_Less:
                    return { std::get<double>(left) < std::get<double>(right) };
                case Tokens::Cmp_More:
                    return { std::get<double>(left) > std::get<double>(right) };
                case Tokens::Cmp_Eq:
                    return { std::get<double>(left) == std::get<double>(right) };
                case Tokens::Cmp_LessEq:
                    return { std::get<double>(left) <= std::get<double>(right) };
                case Tokens::Cmp_MoreEq:
                    return { std::get<double>(left) >= std::get<double>(right) };
                case Tokens::Cmp_NotEq: 
                    return { std::get<double>(left) != std::get<double>(right) };
                
                default:
                    throw std::runtime_error("UNREACHABLE");
            }
        }

        // Executes grouping
        TreeWalkValue operator()(const lir::expressions::Grouping& node) {
            return eval(node.expression);
        }

        // Recusive function to execute tree using vistor pattern
        TreeWalkValue eval(const lir::AST& ast) {
            return std::visit(*this, *ast);
        }

    };

    decltype(auto) interpret(const lir::AST& ast) {
        TreeWalk interpreter;
        return interpreter.eval(std::forward<decltype(ast)>(ast));
    }

}

// In its own namespace since gcc is super weird about templates
inline std::ostream& operator<<(std::ostream& os, const lir::backend::treewalk::TreeWalkValue& value) {
    if(auto d = std::get_if<double>(&value)) {
        os << *d;
    } else if(auto b = std::get_if<bool>(&value)) {
        if(*b)
            os << "true";
        else
            os << "false";
    } else {
        throw std::runtime_error("UNREACHABLE");
    }
    return os;
}