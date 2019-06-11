#pragma once

#include <structures/structures.hpp>

#include <string>

namespace lir::backend::treewalk {

    // Simple tree walk interpreter, not complete
    class TreeWalk {

    public:

        // Executes literal nodes
        double operator()(lir::expressions::Literal& node) {
            return std::stod(node.value);
        }

        // Executes unary nodes
        double operator()(lir::expressions::Unary& node) {
            auto expr = eval(node.expression);

            switch (node.op) {
                case Tokens::Op_Minus:
                    return -expr;
                    
                default:
                    throw std::runtime_error("UNREACHABLE");
            }
        }

        // Executes binary nodes
        double operator()(lir::expressions::Binary& node) {
            auto left  = eval(node.left);
            auto right = eval(node.right);

            switch (node.op) {
                case Tokens::Op_Plus: 
                    return left + right;
                case Tokens::Op_Minus:
                    return left - right;
                case Tokens::Op_Multiply:
                    return left * right;
                case Tokens::Op_Divide:
                    return left / right;
                
                default:
                    throw std::runtime_error("UNREACHABLE");
            }
        }

        // Executes grouping
        double operator()(lir::expressions::Grouping& node) {
            return eval(node.expression);
        }

        // Recusive function to execute tree using vistor pattern
        double eval(lir::AST& ast) {
            return std::visit(*this, *ast);
        }

    };

}