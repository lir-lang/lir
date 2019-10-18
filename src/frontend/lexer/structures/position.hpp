#pragma once

#include <iostream>
#include <cstdint>

namespace lir {
	// Stores a position and filename.
	struct Position {
		uint32_t line = 1, column = 1;
		std::string filename;


		Position() = default;

		Position(uint32_t l, uint32_t c, const std::string& f)
			: line(l), column(c), filename(f) {}



		void incr_line(uint32_t n = 1) {
			column = 1;
			line += n;
		}


		void incr_column(uint16_t n = 1) {
			column += n;
		}
	};



	std::ostream& operator<<(std::ostream& os, const lir::Position& pos) {
		const auto& [line, column, file] = pos;
		return (os << "[ " << tinge::style::bold << line << ": " << column << tinge::reset << " ]" << " in '" << tinge::bg::black << file << tinge::bg::reset << '\'');
	}
}



