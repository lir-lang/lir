#pragma once

#include <cstdint>
#include <utils/logger.hpp>
#include <structures/view.hpp>
#include <structures/token_types.hpp>

namespace lir {

	struct Token {
		lir::View str;
		uint8_t type;


		Token()
			: type(lir::Tokens::Empty) {}

		Token(uint8_t t)
			: type(t) {}

		Token(uint8_t t, const lir::View& s)
			: str(s), type(t) {}



		operator std::string_view() const {
			return str;
		}

		operator std::string() const {
			return str;
		}





		bool eof() const {
			return type == lir::Tokens::Eof;
		}
	};

}



// Easily compare a token and token_type.
inline bool operator==(const lir::Token& lhs, lir::TokenType rhs) {
	return lhs.type == rhs;
}

inline bool operator!=(const lir::Token& lhs, lir::TokenType rhs) {
	return not(lhs == rhs);
}


// Compare a string and content of token.
inline bool operator==(const lir::Token& lhs, const char* rhs) {
	return lhs.str == rhs;
}

inline bool operator!=(const lir::Token& lhs, const char* rhs) {
	return not(lhs == rhs);
}




// Just for output.
inline std::ostream& operator<<(std::ostream& os, const lir::Token& token) {
	// Find longest token name.
	static std::string_view::size_type longest_token_name = [](){
		std::string_view::size_type max = 0;

		for (auto it = std::begin(lir::Tokens::to_str); it != std::end(lir::Tokens::to_str); ++it) {
			if (it->size() > max) max = it->size();
		}

		return max;
	}() + 1;



	const auto& [view, type_n] = token;
	auto type = lir::Tokens::to_str[type_n];

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
	<< view
	<< lir::colour::bg::normal
	<< lir::colour::fg::black
	<< "]"
	<< lir::colour::bg::normal;

	return os;
}





