#pragma once

#include <structures/ast.hpp>
#include <lexer/lexer.hpp>
#include <utils/utils.hpp>

namespace lir::parser {

	// Parser state passed throughout the parser internally
	struct State {
		Token previous;
		Token current;

		FileStack& files;

		lir::AST prefix_node;
		lir::AST infix_node;

		bool debug_mode;
	};

	// Gets next token
	void advance(State& state) {
		state.previous = state.current;

		state.current = lexer::run(state.files);

		if(state.debug_mode)
			lir::println("[L] -> ", state.current);
	}

	// Consumes next token, if incorrect token, throws error
	void consume(State& state, TokenType type, const char* msg) {
		if (state.current == type) {
			advance(state);
		} else {
			lir::except::parser::throw_error({}, msg);
		}
	}

	// Parsing precedence
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

	// Parse function
	using ParseFn = lir::AST(*)(State& state);

	// Parse rule for each token
	struct ParseRule {
		ParseFn prefix;
		ParseFn infix;
		Prec    precedence;
	};

}