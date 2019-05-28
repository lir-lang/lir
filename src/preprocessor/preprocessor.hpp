#pragma once

#include <string>
#include <utils/logger.hpp>
#include <structures/view.hpp>
#include <structures/file_stack.hpp>
#include <lexer/common.hpp>

namespace lir::preprocessor {

	inline lir::Token preprocessor_callback(lir::View& view) {
		namespace Type = lir::Tokens;
		namespace err = lir::except::lexer;


		lir::Token ret;
		char current = *view;



		if (lir::common_whitespace(current)) {
			++view;
			return preprocessor_callback(view);
		}


		// - Dont ignore whitespace, path names can have spaces etc...

		else if (lir::alpha(current)) ret = {Type::Identifier, lir::lexer::on_alpha(view)};
		// else if (lir::digit(current)) ret = {Type::Number, lir::lexer::on_num(view)};

		// else if (current == '(') ret = {Type::ParenLeft};
		// else if (current == ')') ret = {Type::ParenRight};

		// else if (current == ',') ret = {Type::Comma};
		else if (current == '"') ret = {Type::String, lir::lexer::on_string(view)};


		// Handle EOF...
		else if (not view.remaining()) ret = {Type::Eof};

		else {
			err::throw_error("unexpected character '", current, "' in preprocessor directive.");
			++view;
			return preprocessor_callback(view);
		}

		++view;
		return ret;
	}


	void run(lir::FileStack& files) {
		namespace err = lir::except::preprocessor;

		++files.view(); // skip '#'

		auto directive = files.view().read_until([] (auto c) {
			return *c == '\n';
		});


		lir::Token type = preprocessor_callback(directive);
		if (type != lir::Tokens::Identifier)
			err::throw_error("unexpected token '", lir::Tokens::to_str[type.type], "', expecting 'Identifier'.");


		lir::Token arg = preprocessor_callback(directive);
		if (arg != lir::Tokens::String)
			err::throw_error("unexpected token '", lir::Tokens::to_str[type.type], "', expecting 'String'.");


		files.newfile(arg.view.str());
	}
}


