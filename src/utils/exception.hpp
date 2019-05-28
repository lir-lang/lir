#pragma once


#include <string>
#include <stdexcept>


#include <utils/logger.hpp>


#define NEW_EXCEPTION_TYPE(name, default_msg) \
	class name: public std::runtime_error { \
		private: \
			std::string msg; \
		public: \
			name(const std::string& msg_): \
				std::runtime_error(msg_), \
				msg(msg_) \
			{ \
			} \
			\
			name(): \
				std::runtime_error(default_msg), \
				msg(default_msg) \
			{ \
			} \
			\
			std::string get_msg() const { return msg; } \
	};


#define NEW_THROWER(name, type)                              \
	template <typename... Ts> void name(Ts&&... args) {      \
		throw type(((std::string{args}) + ...)); \
	}


#define NEW_CATCHER(name, type, str, func) \
	void name(const type& arg)  { func(str, arg.get_msg());  }




namespace lir::except {

	namespace lexer {
		NEW_EXCEPTION_TYPE(LexerNotice,  "lexer notice!")
		NEW_EXCEPTION_TYPE(LexerWarn,    "lexer warning!")
		NEW_EXCEPTION_TYPE(LexerSuccess, "lexer success!")
		NEW_EXCEPTION_TYPE(LexerError,   "lexer error!")

		NEW_CATCHER(catch_notice,  LexerNotice,  "lexer notice: ",  lir::noticeln_em)
		NEW_CATCHER(catch_warn,    LexerWarn,    "lexer warning: ", lir::warnln_em)
		NEW_CATCHER(catch_success, LexerSuccess, "lexer success: ", lir::successln_em)
		NEW_CATCHER(catch_error,   LexerError,   "lexer error: ",   lir::errorln_em)

		NEW_THROWER(throw_notice,  LexerNotice)
		NEW_THROWER(throw_warn,    LexerWarn)
		NEW_THROWER(throw_success, LexerSuccess)
		NEW_THROWER(throw_error,   LexerError)
	}

	namespace preprocessor {
		NEW_EXCEPTION_TYPE(PreprocessorNotice,  "preprocessor notice!")
		NEW_EXCEPTION_TYPE(PreprocessorWarn,    "preprocessor warning!")
		NEW_EXCEPTION_TYPE(PreprocessorSuccess, "preprocessor success!")
		NEW_EXCEPTION_TYPE(PreprocessorError,   "preprocessor error!")

		NEW_CATCHER(catch_notice,  PreprocessorNotice,  "preprocessor notice: ",  lir::noticeln_em)
		NEW_CATCHER(catch_warn,    PreprocessorWarn,    "preprocessor warning: ", lir::warnln_em)
		NEW_CATCHER(catch_success, PreprocessorSuccess, "preprocessor success: ", lir::successln_em)
		NEW_CATCHER(catch_error,   PreprocessorError,   "preprocessor error: ",   lir::errorln_em)

		NEW_THROWER(throw_notice,  PreprocessorNotice)
		NEW_THROWER(throw_warn,    PreprocessorWarn)
		NEW_THROWER(throw_success, PreprocessorSuccess)
		NEW_THROWER(throw_error,   PreprocessorError)
	}

	namespace parser {
		NEW_EXCEPTION_TYPE(ParserNotice,  "parser notice!")
		NEW_EXCEPTION_TYPE(ParserWarn,    "parser warning!")
		NEW_EXCEPTION_TYPE(ParserSuccess, "parser success!")
		NEW_EXCEPTION_TYPE(ParserError,   "parser error!")

		NEW_CATCHER(catch_notice,  ParserNotice,  "parser notice: ",  lir::noticeln_em)
		NEW_CATCHER(catch_warn,    ParserWarn,    "parser warning: ", lir::warnln_em)
		NEW_CATCHER(catch_success, ParserSuccess, "parser success: ", lir::successln_em)
		NEW_CATCHER(catch_error,   ParserError,   "parser error: ",   lir::errorln_em)

		NEW_THROWER(throw_notice,  ParserNotice)
		NEW_THROWER(throw_warn,    ParserWarn)
		NEW_THROWER(throw_success, ParserSuccess)
		NEW_THROWER(throw_error,   ParserError)
	}

}



#undef NEW_EXCEPTION_TYPE
#undef NEW_THROWER
#undef NEW_CATCHER
