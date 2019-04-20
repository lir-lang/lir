#pragma once


#include <string>


namespace lir {

	// Utility functions
	namespace details {
		// unsafe, can be called like: repeat(5, 'n') or repeat('n', 5)
		inline std::string repeat(char c, unsigned n) {
			return std::string(n, c);
		}
	}



	// std::string constructor does not allow repeating a string so
	// this function implements it.
	inline std::string repeat(const std::string& c, unsigned n) {
		if (!n) return ""; // Check for 0.

		std::string out = c;

		for (n--; n > 0; n--) out += c;

		return out;
	}


	inline std::string spaces(unsigned n) {
		return lir::details::repeat(' ', n);
	}


	inline std::string tabs(unsigned n) {
		return lir::details::repeat('\t', n);
	}


	inline std::string lines(unsigned n) {
		return lir::details::repeat('\n', n);
	}

}
