#pragma once


#include <cstdint>
#include <string_view>
#include <variant>
#include <iostream>


namespace lir {

	template <typename T>
	struct View {
		const T* ptr;
		uint8_t length;


		View(): ptr(nullptr), length(0) {}
		View(const T* s): ptr(s), length(1) {}
		View(const T* s, uint8_t p): ptr(s), length(p) {}
	};


	using StrView = View<char>;
}



template <typename T>
std::ostream& operator<<(std::ostream& os, const lir::View<T>& v) {
	os << std::string_view{v.ptr, v.length};

	return os;
}
