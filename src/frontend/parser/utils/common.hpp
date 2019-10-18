#pragma once

#include <frontend/parser/structures/ast.hpp>
#include <frontend/lexer/lexer.hpp>

// namespace lir::parser {

// 	// Parser state passed throughout the parser internally
// 	struct State {
// 		State(FileStack& fs)
// 			: files(fs) {}

// 		Token previous;
// 		Token current;

// 		FileStack& files;

// 		lir::AST prefix_node = nullptr;
// 		lir::AST infix_node  = nullptr;

// 		bool debug_mode = false;
// 	};

// 	// Gets next token
// 	void advance(State& state) {
// 		state.previous = state.current;

// 		state.current = lexer::run(state.files);

// 		if(state.debug_mode)
// 			tinge::println("[L] -> ", state.current);
// 	}

// 	// Consumes next token, if incorrect token, throws error
// 	void consume(State& state, TokenType type, const char* msg) {
// 		if (state.current == type) {
// 			advance(state);
// 		} else {
// 			lir::except::parser::throw_error({}, msg);
// 		}
// 	}

// 	// Parsing precedence
// 	enum class Prec: uint8_t {
// 		None,
// 		Assignment,  // =
// 		Or,          // or
// 		And,         // and
// 		Equality,    // == !=
// 		Comparison,  // < > <= >=
// 		Term,        // + -
// 		Factor,      // * /
// 		Unary,       // ! -
// 		Call,        // . () []
// 		Primary
// 	};

// 	// Parse function
// 	using ParseFn = lir::AST(*)(State& state);

// 	// Parse rule for each token
// 	struct ParseRule {
// 		ParseFn prefix;
// 		ParseFn infix;
// 		Prec    precedence;
// 	};

// }
