#pragma once

#include <structures/view.hpp>
#include <structures/token_types.hpp>
#include <structures/token.hpp>
#include <structures/file_stack.hpp>
#include <utils/char.hpp>

namespace lir::lexer {

	// Consumes an identifier. ([a-zA-Z_][a-zA-Z0-9_]+)
	inline lir::View on_alpha(lir::View& view) {
		constexpr auto ident_reader = [] (auto c) {
			auto ch = *(c + 1);
			return lir::alphanumeric(ch) or ch == '_';
		};

		return view.read_while(ident_reader);
	}



	// Consumes an integer literal. ([0-9]+)
	inline lir::View on_num(lir::View& view) {
		return view.read_while([] (auto c) {
			return lir::digit(*(c + 1));
		});
	}



	// Consumes a string literal. (".+")
	inline lir::View on_string(lir::View& view) {
		++view;

		auto str = view.read_until([] (auto c) {
			return *(c + 1) == '"';
		});

		++view;

		return str;
	}


	// Consumes a comment. (//[^\n]+\n)
	inline void on_comment(lir::View& view) {
		view.skip_until([] (auto c) {
			return *c == '\n';
		});
	}



	template <typename F>
	inline lir::Token on_eof(lir::FileStack& files, F callback) {
		if (files.size() > 1) {
			files.pop();
			return callback(files);
		}

		return {lir::Tokens::Eof};
	}


}
