#pragma once


#include <cstdint>
#include <util/logger.hpp>
#include <structures/view.hpp>
#include <structures/tokentypes.hpp>


namespace lir {

	#define likely(x)      __builtin_expect(!!(x), 1)
	#define unlikely(x)    __builtin_expect(!!(x), 0)


	struct Token {
		uint8_t type;
		lir::View val;


		Token()
			: type(lir::TokenType::Empty) {}

		Token(uint8_t t)
			: type(t) {}

		Token(uint8_t t, const lir::View& v)
			: type(t), val(v) {}


		bool eof() const {
			return unlikely(type == lir::TokenType::Eof);
		}
	};


	#undef likely
	#undef unlikely
}






inline std::ostream& operator<<(std::ostream& os, const lir::Token& token) {
	// Find longest token name.
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





