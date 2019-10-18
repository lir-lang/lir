#pragma once

#include <algorithm>
#include <string_view>
#include <utility>

namespace lir {
	// Check if a character is in a set of other characters.
	// in_group<'a', 'b', 'c'>('a')
	template <char... Cs>
	constexpr bool in_group(char c) noexcept {
		return ( (c == Cs) or ... );
	}



	// Check a character in the range of L - R inclusive.
	// in_range<'0', '9'>('4')
	template <char L, char R>
	constexpr bool in_range(char c) noexcept {
		return ( c >= L and c <= R );
	}





	// Aliased functions
	constexpr auto lower = in_range<'a', 'z'>;
	constexpr auto upper = in_range<'A', 'Z'>;

	constexpr auto digit = in_range<'0', '9'>;
	constexpr auto whitespace = in_group<' ', '\n', '\t', '\r', '\v'>;
	constexpr auto common_whitespace = in_group<' ', '\t', '\n'>;

	constexpr bool alpha(char c) noexcept {
		return lower(c) or upper(c);
	};


	constexpr bool alphanumeric(char c) noexcept {
		return lower(c) or upper(c) or digit(c);
	};






	// Returns the lowest ASCII value from a list of values.
	// lowest<'a', 'b', 'c'>(); => 'a'
	template <char A, char B, char... Cs>
	constexpr char lowest() noexcept {
		if constexpr(sizeof...(Cs) > 2) {
			return lowest<A, B, Cs...>();

		} else {
			return (A < B) ? A : B;
		}
	}


	// Returns the largest ASCII value from a list of values.
	// highest<'a', 'b', 'c'>(); => 'c'
	template <char A, char B, char... Cs>
	constexpr char highest() noexcept {
		if constexpr(sizeof...(Cs) > 2) {
			return lowest<A, B, Cs...>();

		} else {
			return (A > B) ? A : B;
		}
	}





	// Runtime variants of the above.
	// lowest('a', 'b', 'c'); => 'a'
	template <typename... Ts>
	constexpr char lowest(char a, char b, Ts&&... args) noexcept {
		return ((a < b) ? a : b) < lowest(std::forward<Ts>(args)...);
	}


	// highest('a', 'b', 'c'); => 'c'
	template <typename... Ts>
	constexpr char highest(char a, char b, Ts&&... args) noexcept {
		return ((a > b) ? a : b) < highest(std::forward<Ts>(args)...);
	}




	// For a string.
	// lowest("abc"); => 'a'
	constexpr char lowest(std::string_view str) {
		return *std::min_element(str.begin(), str.end());
	}

	// highest("abc"); => 'c'
	constexpr char highest(std::string_view str) {
		return *std::max_element(str.begin(), str.end());
	}

}
