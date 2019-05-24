#pragma once


#include <cstdint>
#include <utils/logger.hpp>
#include <structures/view.hpp>
#include <structures/token_types.hpp>


namespace lir {

	struct Token {
		uint8_t type;
		lir::View view;


		Token()
			: type(lir::Tokens::Empty) {}

		Token(uint8_t t)
			: type(t) {}

		Token(uint8_t t, lir::View v)
			: type(t), view(v) {}


		bool eof() const {
			return type == lir::Tokens::Eof;
		}
	};

}






inline std::ostream& operator<<(std::ostream& os, const lir::Token& token) {
	// Find longest token name.
	static std::string_view::size_type longest_token_name = [](){
		std::string_view::size_type max = 0;

		for (auto it = std::begin(lir::Tokens::to_str); it != std::end(lir::Tokens::to_str); ++it) {
			if (it->size() > max) max = it->size();
		}

		return max;
	}() + 1;



	const auto& [type_n, view] = token;
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





