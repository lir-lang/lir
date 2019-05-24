#pragma once


#include <cstdint>
#include <string_view>
#include <string>
#include <iostream>
#include <utility>

#include <file/file.hpp>

namespace lir {

	struct View {
		const char* ptr;
		const char* end;


		View()
			: ptr(nullptr), end(nullptr) {}

		View(const std::string& str)
			: ptr(str.c_str()), end(ptr + str.size()) {}

		View(const lir::File& file)
			: ptr(file.ptr), end(ptr + file.size()) {}

		View(const char* s)
			: ptr(s), end(ptr + 1) {}

		View(const char* s, const char* e)
			: ptr(s), end(e) {}



		std::string str() const {
			auto diff = static_cast<std::string::size_type>(end - ptr);

			return std::string{ptr, diff};
		}



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
		__attribute__((pure)) const char* operator+(T x) const {
			return ptr + x;
		}


		template <typename T>
		__attribute__((pure)) const char* operator-(T x) const {
			return ptr - x;
		}





		__attribute__((pure)) bool remaining() const {
			return ptr < end;
		}






		// Check next char, if matched, increment view and return true else false.
		bool match(char expect) noexcept {
			if (*(ptr + 1) != expect)
				return false;

			++ptr;
			return true;
		}



		// Skip characters until predicate fails.
		template <typename P, typename... Ts>
		void skip_while(P pred, Ts&&... args) {
			// Switch function body depending on whether arguments are provided.
			if constexpr(sizeof...(Ts) > 0) {
				while (pred(*this, std::forward<Ts>(args)...) and remaining())
					++ptr;

			} else {
				while (pred(*this) and remaining())
					++ptr;
			}
		}



		// Consume characters while predicate is satisfied.
		template <typename P, typename... Ts>
		inline lir::View read_while(P pred, Ts&&... args) {
			auto begin = get();

			// Switch function body depending on whether arguments are provided.
			if constexpr(sizeof...(Ts) > 0) {
				while (pred(*this, std::forward<Ts>(args)...) and remaining())
					++ptr;

			} else {
				while (pred(*this) and remaining())
					++ptr;
			}

			return {begin, ptr + 1};
		}

	};

}





inline std::ostream& operator<<(std::ostream& os, const lir::View& v) {
	auto diff = static_cast<std::string_view::size_type>(v.end - v.ptr);

	return (os << std::string_view{v.ptr, diff});
}
