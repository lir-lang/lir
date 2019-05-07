#pragma once


#include <cstdint>
#include <string_view>
#include <string>
#include <variant>
#include <iostream>


namespace lir {


	#define likely(x)      __builtin_expect(!!(x), 1)
	#define unlikely(x)    __builtin_expect(!!(x), 0)


	struct View {
		const char* ptr;
		const char* end;


		View()
			: ptr(nullptr), end(nullptr) {}

		View(const std::string& str)
			: ptr(str.c_str()), end(ptr + str.size()) {}

		View(const char* s)
			: ptr(s), end(ptr + 1) {}

		View(const char* s, const char* p)
			: ptr(s), end(p) {}



		__attribute__((pure)) const char* get() const {
			return ptr;
		}



		__attribute__((pure)) char operator*() const {
			return *ptr;
		}





		View& operator++() {
			++ptr;
			return *this;
		}


		View& operator--() {
			--ptr;
			return *this;
		}





		template <typename T>
		__attribute__((pure)) const char* operator+(const T& x) const {
			return ptr + x;
		}


		template <typename T>
		__attribute__((pure)) const char* operator-(const T& x) const {
			return ptr - x;
		}





		__attribute__((pure)) bool remaining() const {
			return likely(ptr != end);
		}
	};


	#undef likely
	#undef unlikely
}





std::ostream& operator<<(std::ostream& os, const lir::View& v) {
	auto diff = static_cast<std::string_view::size_type>(v.end - v.ptr);

	std::string_view view{v.ptr, diff};

	return (os << view);
}
