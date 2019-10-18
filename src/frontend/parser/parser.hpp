#pragma once

#include <frontend/parser/utils/common.hpp>
#include <frontend/parser/structures/ast.hpp>
#include <frontend/parser/structures/visitor.hpp>

// namespace lir::parser {

// 	// Recursive parse functions forward declared
// 	lir::AST expression (State& state);
// 	lir::AST literal    (State& state);
// 	lir::AST unary      (State& state);
// 	lir::AST binary     (State& state);
// 	lir::AST grouping   (State& state);

// 	// Rule table for each token
// 	constexpr ParseRule rules[] = {
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Empty
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Eof
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Char
// 		{ literal,  nullptr, Prec::None       }, // Tokens::String
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Identifier
// 		{ literal,  nullptr, Prec::None       }, // Tokens::Number
// 		{ grouping, nullptr, Prec::Call       }, // Tokens::ParenLeft
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::ParenRight
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::BraceLeft
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::BraceRight
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::BracketLeft
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::BracketRight
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_Incr
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_Decr
// 		{ nullptr,  binary,  Prec::Term       }, // Tokens::Op_Plus
// 		{ unary,    binary,  Prec::Term,      }, // Tokens::Op_Minus
// 		{ nullptr,  binary,  Prec::Factor     }, // Tokens::Op_Divide
// 		{ nullptr,  binary,  Prec::Factor     }, // Tokens::Op_Multiply
// 		{ nullptr,  binary,  Prec::None       }, // Tokens::Op_Mod
// 		{ nullptr,  binary,  Prec::None       }, // Tokens::Op_ShiftLeft
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_ShiftRight
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_And
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_Or
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_Neg
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_PlusEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_MinusEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_DivideEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_MultiplyEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_ModEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_ShiftLeftEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_ShiftRightEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_AndEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_OrEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Op_NegEq
// 		{ nullptr,  binary,  Prec::Comparison }, // Tokens::Cmp_Less
// 		{ nullptr,  binary,  Prec::Comparison }, // Tokens::Cmp_More
// 		{ nullptr,  binary,  Prec::Comparison }, // Tokens::Cmp_Eq
// 		{ nullptr,  binary,  Prec::Comparison }, // Tokens::Cmp_LessEq
// 		{ nullptr,  binary,  Prec::Comparison }, // Tokens::Cmp_MoreEq
// 		{ nullptr,  binary,  Prec::Comparison }, // Tokens::Cmp_NotEq
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Assign
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Exclaim
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Question
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Comma
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Dot
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Colon
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Namespace
// 		{ nullptr,  nullptr, Prec::None       }, // Tokens::Semicolon
// 	};

// 	// Parses each expression in the correct precedence order
// 	lir::AST parse_precedence(State& state, Prec precedence) {
// 		advance(state);

// 		ParseFn prefix_rule = rules[state.previous.type].prefix;
// 		if (prefix_rule == nullptr) {
// 			throw except::parser::ParserError("Expected prefix expression");
// 			return nullptr;
// 		}

// 		state.prefix_node = prefix_rule(state);

// 		while (precedence <= rules[state.current.type].precedence) {
// 			advance(state);
// 			ParseFn infix_rule = rules[state.previous.type].infix;
// 			if (infix_rule == nullptr) {
// 				throw except::parser::ParserError("Expected infix expression");
// 				return nullptr;
// 			}
// 			state.prefix_node = infix_rule(state);
// 		}

// 		return std::move(state.prefix_node);
// 	}

// 	lir::AST expression(State& state) {
// 		return parse_precedence(state, Prec::Assignment);
// 	}

// 	lir::AST literal(State& state) {
// 		return std::make_unique<Expression>(expressions::Literal(state.previous));
// 	}

// 	lir::AST unary(State& state) {
// 		TokenType op = state.previous.type;

// 		AST expr = parse_precedence(state, Prec::Unary);

// 		return std::make_unique<Expression>(expressions::Unary(op, expr));
// 	}

// 	lir::AST binary(State& state) {
// 		AST left = std::move(state.prefix_node);
// 		TokenType op = state.previous.type;
// 		AST right = parse_precedence(state, static_cast<Prec>(static_cast<uint8_t>(rules[op].precedence) + 1));
// 		return std::make_unique<Expression>(expressions::Binary(left, op, right));
// 	}

// 	lir::AST grouping(State& state) {
// 		AST expr = expression(state);
// 		consume(state, Tokens::ParenRight, "Expected right parenthesis");
// 		return std::make_unique<Expression>(expressions::Grouping(expr));
// 	}

// 	// Parses files and returns AST
// 	lir::AST run(std::string_view filename) {
// 		lir::State state{files};

// 		advance(state);
// 		AST ast = expression(state);
// 		consume(state, Tokens::Eof, "Expected EOF");

// 		return ast;
// 	}

// }
