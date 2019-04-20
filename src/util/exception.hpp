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
	NEW_EXCEPTION_TYPE(Notice, "Lexical notice!")
	NEW_EXCEPTION_TYPE(Warn,   "Lexical warning!")
	NEW_EXCEPTION_TYPE(Error,  "Lexical error!")
}


#undef NEW_EXCEPTION_TYPE

