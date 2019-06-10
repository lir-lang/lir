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

		View(const lir::File& file)
			: ptr(file.ptr), end(ptr + file.size()) {}

		View(const char* s)
			: ptr(s), end(ptr + 1) {}

		View(const char* s, const char* e)
			: ptr(s), end(e) {}



		// Gets the difference between the start and end pointer.
		auto size() const {
			return static_cast<std::string_view::size_type>(end - ptr);
		}


		// Implicit conversions.
		operator std::string_view() const {
			return std::string_view{ptr, size()};
		}

		operator std::string() const {
			return std::string{ptr, size()};
		}

		std::string str() const {
			return *this; // Call implicit conversion operator.
		}



		// GNU extension bloat.
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


		// Skip characters until predicate succeeds.
		template <typename P, typename... Ts>
		void skip_until(P pred, Ts&&... args) {
			// Switch function body depending on whether arguments are provided.
			if constexpr(sizeof...(Ts) > 0) {
				while (not pred(*this, std::forward<Ts>(args)...) and remaining())
					++ptr;

			} else {
				while (not pred(*this) and remaining())
					++ptr;
			}
		}



		// Consume characters while predicate is satisfied.
		template <typename P, typename... Ts>
		inline lir::View read_until(P pred, Ts&&... args) {
			auto begin = get();

			// Switch function body depending on whether arguments are provided.
			if constexpr(sizeof...(Ts) > 0) {
				while (not pred(*this, std::forward<Ts>(args)...) and remaining())
					++ptr;

			} else {
				while (not pred(*this) and remaining())
					++ptr;
			}

			return {begin, ptr + 1};
		}
	};



	// Compare two views.
	inline bool operator==(const lir::View& lhs, lir::View rhs) {
		return (lhs.ptr == rhs.ptr) and (lhs.end == rhs.end);
	}

	inline bool operator!=(const lir::View& lhs, lir::View rhs) {
		return not(lhs == rhs);
	}



	// Compare view contents with string literal.
	inline bool operator==(const lir::View& lhs, const char* rhs) {
		return lhs == std::string_view{rhs};
	}

	inline bool operator!=(const lir::View& lhs, const char* rhs) {
		return not(lhs == std::string_view{rhs});
	}


	// Output
	inline std::ostream& operator<<(std::ostream& os, const lir::View& v) {
		return (os << std::string_view{v});
	}
}
