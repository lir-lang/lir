#pragma once


#include <string_view>
#include <utility>
#include <optional>
#include <structures/view.hpp>


namespace lir::lexer {


	#define likely(x)      __builtin_expect(!!(x), 1)
	#define unlikely(x)    __builtin_expect(!!(x), 0)


	// Check if a character is in a set of other characters.
	// in_group<'a', 'b', 'c'>('a')
	template <char... Ts>
	constexpr __attribute__((const)) bool in_group(const char c) noexcept { return ((c == Ts) or ...); }



	// Check a character in the range of L - R inclusive.
	// in_range<'0', '9'>('4')
	template <char L, char R>
	constexpr __attribute__((const)) bool in_range(const char c) noexcept { return c >= L and c <= R; }





	// Aliased functions
	constexpr auto lower = in_range<'a', 'z'>;
	constexpr auto upper = in_range<'A', 'Z'>;

	constexpr auto digit = in_range<'0', '9'>;
	constexpr auto whitespace = in_group<' ', '\t', '\n', '\v', '\r'>;


	constexpr __attribute__((const)) bool alpha(const char c) {
		return lower(c) or upper(c);
	};


	constexpr __attribute__((const)) bool alphanumeric(const char c) {
		return lower(c) or upper(c) or digit(c);
	};




	// Check next char, if matched, increment view and return true else false.
	inline bool match(lir::View& view, char expect) noexcept {
		return (*(view + 1) == expect) and (++view, true);
	}



	// Skip characters until predicate fails.
	template <typename P, typename... Ts>
	inline void skip_while(lir::View& view, P pred, Ts&&... args) {
		// Switch function body depending on whether arguments are provided.
		if constexpr(sizeof...(Ts) > 0) {
			while (pred(view + 1, std::forward<Ts>(args)...)) {
				if (likely(view.remaining()))
					break;
				++view;
			}

		} else {
			while (pred(view + 1)) {
				if (likely(view.remaining()))
					break;
				++view;
			}
		}
	}



	// Consume characters while predicate is satisfied.
	template <typename P, typename... Ts>
	inline lir::View read_while(lir::View& view, P pred, Ts&&... args) {
		auto begin = view.get();

		// Switch function body depending on whether arguments are provided.
		if constexpr(sizeof...(Ts) > 0) {
			while (pred(view + 1, std::forward<Ts>(args)...)) {
				if (likely(view.remaining()))
					break;
				++view;
			}

		} else {
			while (pred(view + 1)) {
				if (likely(view.remaining()))
					break;
				++view;
			}
		}

		return {begin, view + 1};
	}



	// Return the next meaningful token and move the view along.
	template <typename F>
	inline lir::Token advance(lir::View& view, F callback) {
		auto tok = callback(view);
		++view;
		return tok;
	}


	#undef unlikely
	#undef likely
}
