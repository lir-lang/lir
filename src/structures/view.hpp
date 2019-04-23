#pragma once


#include <cstdint>
#include <string_view>
#include <string>
#include <variant>
#include <iostream>


namespace lir {

	struct View {
		const char* ptr;
		const char* end;


		View() = default;

		// View()
		// 	: ptr(nullptr), end(nullptr) {}

		View(const std::string& str)
			: ptr(str.c_str()), end(ptr + str.size()) {}

		View(const char* s)
			: ptr(s), end(ptr + 1) {}

		View(const char* s, const char* p)
			: ptr(s), end(p) {}



		bool remaining() {
			return ptr != end;
		}
	};
}



std::ostream& operator<<(std::ostream& os, const lir::View& v) {
	os << std::string_view{v.ptr, static_cast<std::string_view::size_type>(v.end - v.ptr)};
	return os;
}
