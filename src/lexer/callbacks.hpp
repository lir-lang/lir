#pragma once


#include <vector>

#include <structures/token.hpp>
#include <structures/view.hpp>


namespace lir::lexer {
	namespace Type = lir::TokenType;



	#define HANDLE(f) return lir::lexer::f(view);
	#define TOKEN(t) return {Type::t};
	#define TOKENVAL(t,v) return {Type::t,v};
	#define TOKENMATCH(a,b) return (lir::lexer::match(view, '=') ? lir::Token{Type::a} : lir::Token{Type::b});




	lir::Token on_char(lir::View& view) {
		++view.ptr;

		auto chr = view.ptr;

		if (lir::lexer::match(view, '\''))
			TOKENVAL(Char, chr)

		lir::errorln("Unterminated char literal.");

		return {};
	}


	lir::Token on_string(lir::View& view) {
		++view.ptr;

		auto str = lir::lexer::read_while(view, [] (auto c) {
			return (*c) != '"';
		});

		++view.ptr;

		TOKENVAL(String, str)
	}


	lir::Token on_alpha(lir::View& view) {
		auto ident_reader = [] (auto c) {
			return lir::lexer::alpha(*c) or lir::lexer::digit(*c) or *c == '_';
		};

		TOKENVAL(Identifier, lir::lexer::read_while(view, ident_reader))
	}


	lir::Token on_num(lir::View& view) {
		TOKENVAL(
			Number,
			lir::lexer::read_while(view, [] (auto c) {
				return lir::lexer::digit(*c);
			})
		)
	}







	lir::Token on_plus(lir::View& view) {
		if (lir::lexer::match(view, '='))
			TOKEN(Op_PlusEq)

		else if (lir::lexer::match(view, '+'))
			TOKEN(Op_Incr)

		else
			TOKEN(Op_Plus)
	}


	lir::Token on_minus(lir::View& view) {
		if (lir::lexer::match(view, '='))
			TOKEN(Op_MinusEq)

		else if (lir::lexer::match(view, '-'))
			TOKEN(Op_Decr)

		else
			TOKEN(Op_Minus)
	}


	lir::Token on_multiply(lir::View& view) {
		TOKENMATCH(Op_MultiplyEq, Op_Multiply)
	}


	lir::Token on_divide(lir::View& view) {
		TOKENMATCH(Op_DivideEq, Op_Divide)
	}


	lir::Token on_mod(lir::View& view) {
		TOKENMATCH(Op_ModEq, Op_Mod)
	}










	lir::Token on_ampersand(lir::View& view) {
		TOKENMATCH(Op_AndEq, Op_And)
	}


	lir::Token on_bar(lir::View& view) {
		TOKENMATCH(Op_OrEq, Op_Or)
	}


	lir::Token on_tilde(lir::View& view) {
		TOKENMATCH(Op_NegEq, Op_Neg)
	}









	lir::Token on_equal(lir::View& view) {
		TOKENMATCH(Cmp_Eq, Assign)
	}


	lir::Token on_less(lir::View& view) {
		if (lir::lexer::match(view, '=')) {
			TOKEN(Cmp_LessEq)

		} else if (lir::lexer::match(view, '<')) {
			TOKENMATCH(Op_ShiftLeftEq, Op_ShiftLeft)

		} else {
			TOKEN(Cmp_Less)
		}
	}


	lir::Token on_more(lir::View& view) {
		if (lir::lexer::match(view, '=')) {
			TOKEN(Cmp_MoreEq)

		} else if (lir::lexer::match(view, '>')) {
			TOKENMATCH(Op_ShiftRightEq, Op_ShiftRight)

		} else {
			TOKEN(Cmp_More)
		}
	}















	lir::Token on_colon(lir::View& view) {
		if (lir::lexer::match(view, ':'))
			TOKEN(Namespace)
		else
			TOKEN(Colon)
	}



	lir::Token on_exclaim(lir::View& view) {
		TOKENMATCH(Cmp_NotEq, Exclaim)
	}











	// Handle all callbacks.
	lir::Token lexer_callback(lir::View& view) {

		char current = *view.ptr;

		if (lir::lexer::space(current)) {
			++view.ptr;
			return lexer_callback(view);
		}




		else if (lir::lexer::alpha(current)) HANDLE(on_alpha)

		else if (current == '(') TOKEN(ParenLeft)
		else if (current == ')') TOKEN(ParenRight)


		else if (current == ';') TOKEN(Semicolon)
		else if (current == ',') TOKEN(Comma)
		else if (current == ':') HANDLE(on_colon)

		// skip comments
		else if (current == '/' and lir::lexer::match(view, '/')) {
			lir::lexer::skip_while(view, [] (auto c) {
				return *(c - 1) != '\n';
			});


			++view.ptr;
			return lexer_callback(view);
		}

		else if (lir::lexer::digit(current)) HANDLE(on_num)

		else if (current == '{') TOKEN(BraceLeft)
		else if (current == '}') TOKEN(BraceRight)

		else if (current == '=') HANDLE(on_equal)

		else if (current == '"')  HANDLE(on_string)

		else if (current == '?') TOKEN(Question)
		else if (current == '[') TOKEN(BracketLeft)
		else if (current == '+') HANDLE(on_plus)
		else if (current == ']') TOKEN(BracketRight)

		else if (current == '<') HANDLE(on_less)

		else if (current == '*') HANDLE(on_multiply)

		else if (current == '\'') HANDLE(on_char)


		else if (current == '-') HANDLE(on_minus)
		else if (current == '/') HANDLE(on_divide)
		else if (current == '%') HANDLE(on_mod)

		else if (current == '&') HANDLE(on_ampersand)
		else if (current == '|') HANDLE(on_bar)
		else if (current == '~') HANDLE(on_tilde)


		else if (current == '>') HANDLE(on_more)


		else if (current == '!') HANDLE(on_exclaim)
		else if (current == '.') TOKEN(Dot)



		else if (not view.remaining())
			return {lir::SpecialTokenType::Eof};

		++view.ptr;
		return lexer_callback(view);
	};



	#undef HANDLE
	#undef TOKEN
}
