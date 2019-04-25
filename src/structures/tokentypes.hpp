#pragma once


#include <string_view>


namespace lir::TokenType {
	enum: uint8_t {
		Empty,
		Eof,

		Char,
		String,
		Identifier,
		Number,

		ParenLeft,
		ParenRight,

		BraceLeft,
		BraceRight,

		BracketLeft,
		BracketRight,

		Op_Incr,
		Op_Decr,

		Op_Plus,
		Op_Minus,
		Op_Divide,
		Op_Multiply,
		Op_Mod,
		Op_ShiftLeft,
		Op_ShiftRight,
		Op_And,
		Op_Or,
		Op_Neg,

		Op_PlusEq,
		Op_MinusEq,
		Op_DivideEq,
		Op_MultiplyEq,
		Op_ModEq,
		Op_ShiftLeftEq,
		Op_ShiftRightEq,
		Op_AndEq,
		Op_OrEq,
		Op_NegEq,

		Cmp_Less,
		Cmp_More,
		Cmp_Eq,

		Cmp_LessEq,
		Cmp_MoreEq,
		Cmp_NotEq,

		Assign,

		Exclaim,
		Question,
		Comma,
		Dot,
		Colon,
		Namespace,
		Semicolon
	};


	constexpr std::string_view to_str[] = {
		"Empty",
		"Eof",

		"Char",
		"String",
		"Identifier",
		"Number",

		"ParenLeft",
		"ParenRight",

		"BraceLeft",
		"BraceRight",

		"BracketLeft",
		"BracketRight",

		"Op_Incr",
		"Op_Decr",

		"Op_Plus",
		"Op_Minus",
		"Op_Divide",
		"Op_Multiply",
		"Op_Mod",
		"Op_ShiftLeft",
		"Op_ShiftRight",
		"Op_And",
		"Op_Or",
		"Op_Neg",

		"Op_PlusEq",
		"Op_MinusEq",
		"Op_DivideEq",
		"Op_MultiplyEq",
		"Op_ModEq",
		"Op_ShiftLeftEq",
		"Op_ShiftRightEq",
		"Op_AndEq",
		"Op_OrEq",
		"Op_NegEq",

		"Cmp_Less",
		"Cmp_More",
		"Cmp_Eq",

		"Cmp_LessEq",
		"Cmp_MoreEq",
		"Cmp_NotEq",

		"Assign",

		"Exclaim",
		"Question",
		"Comma",
		"Dot",
		"Colon",
		"Namespace",
		"Semicolon"
	};
}
