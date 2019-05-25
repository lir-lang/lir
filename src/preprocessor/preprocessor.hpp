#pragma once

#include <string>
#include <utils/logger.hpp>
#include <structures/view.hpp>
#include <structures/file_stack.hpp>
#include <lexer/common.hpp>

namespace lir {

	inline lir::Token preprocessor_callback(lir::View& view) {
		namespace Type = lir::Tokens;

		char current = *view;

		if (lir::common_whitespace(current)) {
			++view;
			return preprocessor_callback(view);
		}


		// - Dont ignore whitespace, path names can have spaces etc...

		else if (lir::alpha(current)) return {Type::Identifier, lir::lexer::on_alpha(view)};
		else if (lir::digit(current)) return {Type::Number, lir::lexer::on_num(view)};

		else if (current == '(') return {Type::ParenLeft};
		else if (current == ')') return {Type::ParenRight};

		else if (current == ',') return {Type::Comma};
		else if (current == '"') return {Type::String, lir::lexer::on_string(view)};

		// Handle EOF...
		else if (not view.remaining())
			return {Type::Eof};

		lir::errorln("Unexpected character ", current, " in preprocessor directive.");

		++view;
		return preprocessor_callback(view);
	}




	inline bool match_token(lir::Token& tok, lir::View& view, lir::TokenType type) noexcept {
		tok = preprocessor_callback(view);

		if (tok.type != type)
			return false;

		++view;
		return true;
	}



	constexpr auto directive_reader = [] (auto c) {
		return *c == '\n';
	};


	void preprocessor(lir::FileStack& files) {
		++files.view(); // skip '#'
		auto directive = files.view().read_until(directive_reader);


		lir::Token arg, directive_type;


		match_token(directive_type, directive, lir::Tokens::Identifier);


		if (not match_token(arg, directive, lir::Tokens::String)) {
			static std::string error_msg = std::string{"Unexpected token '"} + std::string{lir::Tokens::to_str[arg.type]} + "', expected 'String'.";
			throw lir::except::PreprocessorError(error_msg);
		}


		// lir::warnln(directive_type.view, " -> ", arg.view);

		++files.view(); // skip terminating char, '\n'


		// read file.
		files.newfile(arg.view.str());
	}
}
















