#pragma once


#include <cstdint>


namespace lir {
	struct Position {
		uint32_t line = 1;
		uint16_t column = 1;


		void incr_line(uint32_t n = 1) {
			column = 1;
			line += n;
		}


		void incr_column(uint16_t n = 1) {
			column += n;
		}
	};
}
