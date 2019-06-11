#pragma once

#include <structures/structures.hpp>
#include <lexer/lexer.hpp>

namespace lir::parser {

    struct State {
        Token previous;
        Token current;

        FileStack& files;

        AST prefix_node;
        AST infix_node;
    };

    void advance(State& state) {
        state.previous = state.current;

        state.current = lexer::run(state.files);

        lir::println("[L] -> ", state.current);
    }

    void consume(State& state, TokenType type, const char* msg) {
        if (state.current == type) {
            advance(state);
        } else {
            throw lir::except::parser::ParserError(msg);
        }
    }

    enum class Prec: uint8_t {
        None,
        Assignment,  // =
        Or,          // or
        And,         // and
        Equality,    // == !=
        Comparison,  // < > <= >=
        Term,        // + -
        Factor,      // * /
        Unary,       // ! -
        Call,        // . () []
        Primary
    };

    using ParseFn = AST(*)(State& state);

    struct ParseRule {
        ParseFn prefix;
        ParseFn infix;
        Prec    precedence;
    };

}