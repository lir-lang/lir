#pragma once

#include <string_view>

#define TOKEN_TYPES        \
	TOKEN(Empty)           \
	TOKEN(Eof)             \
	TOKEN(Char)            \
	TOKEN(String)          \
	TOKEN(Identifier)      \
	TOKEN(Number)          \
	TOKEN(ParenLeft)       \
	TOKEN(ParenRight)      \
	TOKEN(BraceLeft)       \
	TOKEN(BraceRight)      \
	TOKEN(BracketLeft)     \
	TOKEN(BracketRight)    \
	TOKEN(Op_Incr)         \
	TOKEN(Op_Decr)         \
	TOKEN(Op_Plus)         \
	TOKEN(Op_Minus)        \
	TOKEN(Op_Divide)       \
	TOKEN(Op_Multiply)     \
	TOKEN(Op_Mod)          \
	TOKEN(Op_ShiftLeft)    \
	TOKEN(Op_ShiftRight)   \
	TOKEN(Op_And)          \
	TOKEN(Op_Or)           \
	TOKEN(Op_Neg)          \
	TOKEN(Op_PlusEq)       \
	TOKEN(Op_MinusEq)      \
	TOKEN(Op_DivideEq)     \
	TOKEN(Op_MultiplyEq)   \
	TOKEN(Op_ModEq)        \
	TOKEN(Op_ShiftLeftEq)  \
	TOKEN(Op_ShiftRightEq) \
	TOKEN(Op_AndEq)        \
	TOKEN(Op_OrEq)         \
	TOKEN(Op_NegEq)        \
	TOKEN(Cmp_Less)        \
	TOKEN(Cmp_More)        \
	TOKEN(Cmp_Eq)          \
	TOKEN(Cmp_LessEq)      \
	TOKEN(Cmp_MoreEq)      \
	TOKEN(Cmp_NotEq)       \
	TOKEN(Assign)          \
	TOKEN(Exclaim)         \
	TOKEN(Question)        \
	TOKEN(Comma)           \
	TOKEN(Dot)             \
	TOKEN(Colon)           \
	TOKEN(Namespace)       \
	TOKEN(Semicolon)

namespace lir {
	using TokenType = uint8_t;

	namespace Tokens {
		#define TOKEN(x) x,
		enum: lir::TokenType {TOKEN_TYPES};
		#undef TOKEN

		#define TOKEN(x) "x",
		constexpr std::string_view to_str[] = {TOKEN_TYPES};
		#undef TOKEN
	}
}

#undef TOKEN_TYPES

