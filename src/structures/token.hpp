#pragma once


#include <cstdint>
#include <structures/view.hpp>
#include <util/logger.hpp>


namespace lir {

	namespace SpecialTokenType {
		enum: uint8_t {
			Empty = 250,
			Eof
		};
	}

	namespace TokenType {
		enum: uint8_t {
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

	struct Token {
		uint8_t type;
		lir::View val;


		Token(): type(lir::SpecialTokenType::Empty) {}
		Token(uint8_t t): type(t) {}
		Token(uint8_t t, const lir::View& v)
			: type(t), val(v)
		{

		}
	};


	bool remaining(const Token& tok) {
		return tok.type != lir::SpecialTokenType::Eof;
	}
}






inline std::ostream& operator<<(std::ostream& os, const lir::Token& token) {
	if (not lir::remaining(token)) return os;


	static std::string_view::size_type longest_token_name = [](){
		std::string_view::size_type max = 0;

		for (auto it = std::begin(lir::TokenType::to_str); it != std::end(lir::TokenType::to_str); ++it) {
			if (it->size() > max) max = it->size();
		}

		return max;
	}() + 1;



	const auto& [type_n, val] = token;
	auto type = lir::TokenType::to_str[type_n];

	std::string str(longest_token_name - type.size(), '.');


	os << lir::style::bold
	<< lir::colour::fg::bright::yellow
	<< type
	<< lir::style::reset
	<< lir::colour::fg::black
	<< str
	<< "["
	<< lir::colour::bg::black
	<< lir::colour::fg::normal
	<< val
	<< lir::colour::bg::normal
	<< lir::colour::fg::black
	<< "]"
	<< lir::colour::bg::normal;

	return os;
}



inline std::ostream& operator<<(std::ostream& os, const std::vector<lir::Token>& tokens) {
	for (auto& t: tokens) {
		if (not lir::remaining(t)) break;
		os << lir::colour::fg::black << "└ " << t << '\n';
	}

	return os;
}


