#pragma once

#include <utils/logger.hpp>
#include <structures/token_types.hpp>
#include <structures/token.hpp>
#include <structures/view.hpp>
#include <preprocessor/preprocessor.hpp>

namespace lir::lexer {
	namespace Type = lir::Tokens;


	// Consume a character literal. ('.')
	inline lir::Token on_char(lir::FileStack& files) {
		++files.view();

		auto chr = files.view().get();

		if (files.view().match('\''))
			return {Type::Char, chr};

		lir::except::lexer::throw_error(files.pos(), "unterminated character literal");

		return {};
	}



	// (+= | ++ | +)
	inline lir::Token on_plus(lir::View& view) {
		if (view.match('='))
			return {Type::Op_PlusEq};

		else if (view.match('+'))
			return {Type::Op_Incr};

		else
			return {Type::Op_Plus};
	}


	// (-= | -- | -)
	inline lir::Token on_minus(lir::View& view) {
		if (view.match('='))
			return {Type::Op_MinusEq};

		else if (view.match('-'))
			return {Type::Op_Decr};

		else
			return {Type::Op_Minus};
	}




	// (*= | *)
	inline lir::Token on_multiply(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Op_MultiplyEq}
			: lir::Token{Type::Op_Multiply});
	}

	// (/= | /)
	inline lir::Token on_divide(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Op_DivideEq}
			: lir::Token{Type::Op_Divide});
	}

	// (%= | %)
	inline lir::Token on_mod(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Op_ModEq}
			: lir::Token{Type::Op_Mod});
	}






	// ( &= | & )
	inline lir::Token on_ampersand(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Op_AndEq}
			: lir::Token{Type::Op_And});
	}

	// ( \|= | \|)
	inline lir::Token on_bar(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Op_OrEq}
			: lir::Token{Type::Op_Or});
	}

	// ( ~= | ~ )
	inline lir::Token on_tilde(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Op_NegEq}
			: lir::Token{Type::Op_Neg});
	}

	// ( == | = )
	inline lir::Token on_equal(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Cmp_Eq}
			: lir::Token{Type::Assign});
	}





	// ( <= | << | < )
	inline lir::Token on_less(lir::View& view) {
		if (view.match('=')) {
			return {Type::Cmp_LessEq};

		} else if (view.match('<')) {
			return (view.match('=')
				? lir::Token{Type::Op_ShiftLeftEq}
				: lir::Token{Type::Op_ShiftLeft});

		} else {
			return {Type::Cmp_Less};
		}
	}



	// ( >= | >> | > )
	inline lir::Token on_more(lir::View& view) {
		if (view.match('=')) {
			return {Type::Cmp_MoreEq};

		} else if (view.match('>')) {
			return (view.match('=')
				? lir::Token{Type::Op_ShiftRightEq}
				: lir::Token{Type::Op_ShiftRight});

		} else {
			return {Type::Cmp_More};
		}
	}



	// ( :: | : )
	inline lir::Token on_colon(lir::View& view) {
		return (view.match(':')
			? lir::Token{Type::Namespace}
			: lir::Token{Type::Colon});
	}


	// ( != | ! )
	inline lir::Token on_exclaim(lir::View& view) {
		return (view.match('=')
			? lir::Token{Type::Cmp_NotEq}
			: lir::Token{Type::Exclaim});
	}





	// Handle all callbacks.
	lir::Token run(lir::FileStack& files) {
		namespace err = lir::except::lexer;


		auto& view   = files.view();
		auto& pos    = files.pos();
		char current = *view;

		lir::Token ret;


		// Special.
		if (lir::in_group<'\t', ' '>(current)) {
			// Skip whitespace...
			++view;
			pos.incr_column();
			return run(files);
		}

		else if (current == '\n') {
			++view;
			pos.incr_line();
			return run(files);
		}

		else if (current == '/' and view.match('/')) {
			// Skip comments...
			lir::lexer::on_comment(files);
			return run(files);
		}

		else if (current == '#') {
			// Handle preprocessor directives...
			lir::preprocessor::run(files);
			return run(files);
		}

		else if (not view.remaining())
			// Handle EOF...
			return lir::lexer::on_eof(files, run);




		// Identifier & Number.
		else if (lir::alpha(current)) ret = {Type::Identifier, lir::lexer::on_alpha(files)};
		else if (lir::digit(current)) ret = {Type::Number, lir::lexer::on_num(files)};


		// String & Char.
		else if (current == '"')  ret = {Type::String, lir::lexer::on_string(files)};
		else if (current == '\'') ret = on_char(files);


		// Grouping.
		else if (current == '(') ret = {Type::ParenLeft};
		else if (current == ')') ret = {Type::ParenRight};
		else if (current == '{') ret = {Type::BraceLeft};
		else if (current == '}') ret = {Type::BraceRight};
		else if (current == '[') ret = {Type::BracketLeft};
		else if (current == ']') ret = {Type::BracketRight};


		// Comparison operators.
		else if (current == '>') ret = on_more(view);
		else if (current == '<') ret = on_less(view);
		else if (current == '!') ret = on_exclaim(view);
		else if (current == '=') ret = on_equal(view);


		// Numerical operators.
		else if (current == '+') ret = on_plus(view);
		else if (current == '-') ret = on_minus(view);
		else if (current == '*') ret = on_multiply(view);
		else if (current == '/') ret = on_divide(view);
		else if (current == '%') ret = on_mod(view);


		// Logical operators.
		else if (current == '&') ret = on_ampersand(view);
		else if (current == '|') ret = on_bar(view);
		else if (current == '~') ret = on_tilde(view);


		// Seperators
		else if (current == ':') ret = on_colon(view);
		else if (current == ';') ret = {Type::Semicolon};
		else if (current == '?') ret = {Type::Question};
		else if (current == ',') ret = {Type::Comma};
		else if (current == '.') ret = {Type::Dot};


		else {
			err::throw_error(pos, "unexpected character '", current, "'.");
			++view;
			return run(files);
		}


		pos.incr_column(ret.str.size());

		++view;
		return ret;
	};
}
