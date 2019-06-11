#pragma once

#include <parser/common.hpp>

namespace lir::parser {

    AST expression (State& state);
    AST literal    (State& state);
    AST unary      (State& state);
    AST binary     (State& state);
    AST grouping   (State& state);

    constexpr ParseRule rules[] = {
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

    AST parse_precedence(State& state, Prec precedence) {
        advance(state);

        ParseFn prefix_rule = rules[state.previous.type].prefix;
        if (prefix_rule == nullptr) {
            // Throw error
            return nullptr;
        }

        prefix_rule(state);

        while (precedence <= rules[state.current.type].precedence) {
            advance(state);
            ParseFn infix_rule = rules[state.previous.type].infix;
            if (infix_rule == nullptr) {
                // Throw error
                return nullptr;
            }
            infix_rule(state);
        }
    }

    AST expression(State& state) {
        parse_precedence(state, Prec::Assignment);
    }

    AST literal(State& state) {
        state.prefix = std::move(std::make_unique<Expression>(expressions::Literal(state.current.str)));
    }

    AST unary(State& state) {
        TokenType op = state.previous.type;

        parse_precedence(state, Prec::Unary);
    }

    AST binary(State& state) {
        TokenType op = state.previous.type;
        parse_precedence(state, static_cast<Prec>(static_cast<uint8_t>(rules[op].precedence) + 1));

    }
    
    AST grouping(State& state) {
        expression(state);
    }

    decltype(auto) run(lir::FileStack& files) {
        State state = { .previous = {},
                        .current  = {}, 
                        .files    = files,
                        .prefix   = nullptr,
                        .infix    = nullptr };
        
        advance(state);
        AST ast = std::move(expression(state));
        consume(state, Tokens::Eof, "Expected EOF");

        return std::move(ast);
    }

}
