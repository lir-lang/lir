#pragma once


#include <vector>

#include <structures/token.hpp>
#include <structures/iter.hpp>


namespace lir::lexer {
	namespace Type = lir::TokenType;



	#define HANDLE(f) return lir::lexer::f(iter);
	#define TOKEN(t) return {Type::t};
	#define TOKENVAL(t,v) return {Type::t,v};
	#define TOKENMATCH(a,b) return (lir::lexer::match(iter, '=') ? lir::Token{Type::a} : lir::Token{Type::b});




	lir::Token on_char(lir::Iter& iter) {
		++iter;

		const char* chr = iter;

		if (lir::lexer::match(iter, '\''))
			TOKENVAL(Char, chr)

		lir::errorln("Unterminated char literal.");

		return {};
	}


	lir::Token on_string(lir::Iter& iter) {
		++iter;

		auto str = lir::lexer::read_while(iter, [] (auto current) {
			return (current + 1) != '"';
		});

		++iter;

		TOKENVAL(String, str)
	}


	lir::Token on_alpha(lir::Iter& iter) {
		auto ident_reader = [] (auto current) {
			auto c = current + 1;
			return lir::lexer::alpha(c) or lir::lexer::digit(c) or c == '_';
		};

		TOKENVAL(Identifier, lir::lexer::read_while(iter, ident_reader))
	}


	lir::Token on_num(lir::Iter& iter) {
		TOKENVAL(
			Number,
			lir::lexer::read_while(iter, [] (auto current) {
				return lir::lexer::digit(current + 1);
			})
		)
	}







	lir::Token on_plus(lir::Iter& iter) {
		if (lir::lexer::match(iter, '='))
			TOKEN(Op_PlusEq)

		else if (lir::lexer::match(iter, '+'))
			TOKEN(Op_Incr)

		else
			TOKEN(Op_Plus)
	}


	lir::Token on_minus(lir::Iter& iter) {
		if (lir::lexer::match(iter, '='))
			TOKEN(Op_MinusEq)

		else if (lir::lexer::match(iter, '-'))
			TOKEN(Op_Decr)

		else
			TOKEN(Op_Minus)
	}


	lir::Token on_multiply(lir::Iter& iter) {
		TOKENMATCH(Op_MultiplyEq, Op_Multiply)
	}


	lir::Token on_divide(lir::Iter& iter) {
		TOKENMATCH(Op_DivideEq, Op_Divide)
	}


	lir::Token on_mod(lir::Iter& iter) {
		TOKENMATCH(Op_ModEq, Op_Mod)
	}










	lir::Token on_ampersand(lir::Iter& iter) {
		TOKENMATCH(Op_AndEq, Op_And)
	}


	lir::Token on_bar(lir::Iter& iter) {
		TOKENMATCH(Op_OrEq, Op_Or)
	}


	lir::Token on_tilde(lir::Iter& iter) {
		TOKENMATCH(Op_NegEq, Op_Neg)
	}









	lir::Token on_equal(lir::Iter& iter) {
		TOKENMATCH(Cmp_Eq, Assign)
	}


	lir::Token on_less(lir::Iter& iter) {
		if (lir::lexer::match(iter, '=')) {
			TOKEN(Cmp_LessEq)

		} else if (lir::lexer::match(iter, '<')) {
			TOKENMATCH(Op_ShiftLeftEq, Op_ShiftLeft)

		} else {
			TOKEN(Cmp_Less)
		}
	}


	lir::Token on_more(lir::Iter& iter) {
		if (lir::lexer::match(iter, '=')) {
			TOKEN(Cmp_MoreEq)

		} else if (lir::lexer::match(iter, '>')) {
			TOKENMATCH(Op_ShiftRightEq, Op_ShiftRight)

		} else {
			TOKEN(Cmp_More)
		}
	}















	lir::Token on_colon(lir::Iter& iter) {
		if (lir::lexer::match(iter, ':'))
			TOKEN(Namespace)
		else
			TOKEN(Colon)
	}



	lir::Token on_exclaim(lir::Iter& iter) {
		TOKENMATCH(Cmp_NotEq, Exclaim)
	}











	// Handle all callbacks.
	lir::Token lexer_callback(lir::Iter& iter) {
		if (lir::lexer::space(iter))
			return lexer_callback(++iter);


		// skip comments
		else if (iter == '/' and lir::lexer::match(iter, '/')) {
			lir::lexer::skip_while(iter, [] (auto current) {
				return current != '\n';
			});

			return lexer_callback(++iter);
		}


		else if (lir::lexer::alpha(iter)) HANDLE(on_alpha)
		else if (lir::lexer::digit(iter)) HANDLE(on_num)


		else if (iter == '"')  HANDLE(on_string)
		else if (iter == '\'') HANDLE(on_char)


		else if (iter == '(') TOKEN(ParenLeft)
		else if (iter == ')') TOKEN(ParenRight)
		else if (iter == '{') TOKEN(BraceLeft)
		else if (iter == '}') TOKEN(BraceRight)
		else if (iter == '[') TOKEN(BracketLeft)
		else if (iter == ']') TOKEN(BracketRight)


		else if (iter == '+') HANDLE(on_plus)
		else if (iter == '-') HANDLE(on_minus)
		else if (iter == '*') HANDLE(on_multiply)
		else if (iter == '/') HANDLE(on_divide)
		else if (iter == '%') HANDLE(on_mod)

		else if (iter == '&') HANDLE(on_ampersand)
		else if (iter == '|') HANDLE(on_bar)
		else if (iter == '~') HANDLE(on_tilde)


		else if (iter == '=') HANDLE(on_equal)
		else if (iter == '<') HANDLE(on_less)
		else if (iter == '>') HANDLE(on_more)


		else if (iter == ':') HANDLE(on_colon)
		else if (iter == '!') HANDLE(on_exclaim)
		else if (iter == ';') TOKEN(Semicolon)
		else if (iter == '?') TOKEN(Question)
		else if (iter == '.') TOKEN(Dot)
		else if (iter == ',') TOKEN(Comma)



		else if (not iter.remaining())
			return {lir::SpecialTokenType::Eof};

		return lexer_callback(++iter);
	};



	#undef HANDLE
	#undef TOKEN
}
