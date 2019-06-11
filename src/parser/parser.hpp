#pragma once

#include <parser/common.hpp>

namespace lir::parser {

    AST& expression(State& state);
    AST& literal(State& state);
    AST& unary(State& state);
    AST& binary(State& state);
    AST& grouping(State& state);

    constexpr ParseRule parse_rules[] = {
        { nullptr,  nullptr, Prec::None   }, // Tokens::Empty
        { nullptr,  nullptr, Prec::None   }, // Tokens::Eof
        { nullptr,  nullptr, Prec::None   }, // Tokens::Char
        { literal,  nullptr, Prec::None   }, // Tokens::String
        { nullptr,  nullptr, Prec::None   }, // Tokens::Identifier
        { literal,  nullptr, Prec::None   }, // Tokens::Number
        { grouping, nullptr, Prec::Call   }, // Tokens::ParenLeft
        { nullptr,  nullptr, Prec::None   }, // Tokens::ParenRight
        { nullptr,  nullptr, Prec::None   }, // Tokens::BraceLeft
        { nullptr,  nullptr, Prec::None   }, // Tokens::BraceRight
        { nullptr,  nullptr, Prec::None   }, // Tokens::BracketLeft
        { nullptr,  nullptr, Prec::None   }, // Tokens::BracketRight
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_Incr
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_Decr
        { nullptr,  binary,  Prec::Term   }, // Tokens::Op_Plus
        { unary,    binary,  Prec::Term,  }, // Tokens::Op_Minus
        { nullptr,  binary,  Prec::Factor }, // Tokens::Op_Divide
        { nullptr,  binary,  Prec::Factor }, // Tokens::Op_Multiply
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_Mod
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_ShiftLeft
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_ShiftRight
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_And
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_Or
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_Neg
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_PlusEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_MinusEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_DivideEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_MultiplyEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_ModEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_ShiftLeftEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_ShiftRightEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_AndEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_OrEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Op_NegEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Cmp_Less
        { nullptr,  nullptr, Prec::None   }, // Tokens::Cmp_More
        { nullptr,  nullptr, Prec::None   }, // Tokens::Cmp_Eq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Cmp_LessEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Cmp_MoreEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Cmp_NotEq
        { nullptr,  nullptr, Prec::None   }, // Tokens::Assign
        { nullptr,  nullptr, Prec::None   }, // Tokens::Exclaim
        { nullptr,  nullptr, Prec::None   }, // Tokens::Question
        { nullptr,  nullptr, Prec::None   }, // Tokens::Comma
        { nullptr,  nullptr, Prec::None   }, // Tokens::Dot
        { nullptr,  nullptr, Prec::None   }, // Tokens::Colon
        { nullptr,  nullptr, Prec::None   }, // Tokens::Namespace
        { nullptr,  nullptr, Prec::None   }, // Tokens::Semicolon
    };



    AST& expression(State& state) {

    }

    AST& literal(State& state) {

    }

    AST& unary(State& state) {

    }

    AST& binary(State& state) {

    }
    
    AST& grouping(State& state) {

    }

    AST& run(lir::FileStack& files) {
        State state = { .previous = {},
                        .current  = {}, 
                        .files    = files };
        
        advance(state);
        AST ast = std::move(expression(state));
        consume(state, Tokens::Eof, "Expected EOF");

        return ast;
    }

}
