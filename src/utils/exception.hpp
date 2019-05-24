#pragma once


#include <string>
#include <stdexcept>


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


namespace lir::except {
	NEW_EXCEPTION_TYPE(LexerNotice,        "Lexical notice!")
	NEW_EXCEPTION_TYPE(LexerWarn,          "Lexical warning!")
	NEW_EXCEPTION_TYPE(LexerError,         "Lexical error!")
	NEW_EXCEPTION_TYPE(PreprocessorNotice, "Preprocessor notice!")
	NEW_EXCEPTION_TYPE(PreprocessorWarn,   "Preprocessor warning!")
	NEW_EXCEPTION_TYPE(PreprocessorError,  "Preprocessor error!")
}


#undef NEW_EXCEPTION_TYPE

