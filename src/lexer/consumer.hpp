#pragma once


#include <string_view>
#include <utility>
#include <optional>

#include <structures/view.hpp>


namespace lir::lexer {

	// Check if a character is in a set of other characters.
	// in_group<'a', 'b', 'c'>('a')
	template <char... Ts>
	inline bool in_group(const char c) noexcept { return ((c == Ts) or ...); }



	// Check a character in the range of L - R inclusive.
	// in_range<'0', '9'>('4')
	template <char L, char R>
	inline bool in_range(const char c) noexcept { return c >= L and c <= R; }



	// Aliased functions
	constexpr auto lower = in_range<'a', 'z'>;
	constexpr auto upper = in_range<'A', 'Z'>;
	constexpr auto digit = in_range<'0', '9'>;
	constexpr auto space = in_group<' ', '\t', '\n', '\v', '\r'>;
	constexpr auto alpha = [] (const char c) {
		return lower(c) or upper(c);
	};





	// Returns true if the next character is what is expected.
	inline bool match(lir::View& view, char expect) noexcept {
		return (*(view.ptr + 1) == expect) and (++view.ptr, true);
	}







	// Skip characters until predicate fails.
	template <typename P, typename... Ts>
	inline void skip_while(lir::View& view, P pred, Ts&&... args) {
		if constexpr(sizeof...(Ts) > 0) {
			while (pred(view.ptr + 1, std::forward<Ts>(args)...) and view.remaining())
				++view.ptr;

		} else {
			while (pred(view.ptr + 1) and view.remaining())
				++view.ptr;
		}
	}








	// Consume characters while predicate is satisfied.
	template <typename P, typename... Ts>
	inline lir::View read_while(lir::View& view, P pred, Ts&&... args) {
		auto begin = view.ptr;

		if constexpr(sizeof...(Ts) > 0) {
			while (pred(view.ptr + 1, std::forward<Ts>(args)...) and view.remaining())
				++view.ptr;

		} else {
			while (pred(view.ptr + 1) and view.remaining())
				++view.ptr;
		}

		return {begin, view.ptr + 1};
	}










	template <typename F>
	inline lir::Token advance(lir::View& view, F callback) {
		auto tok = callback(view);
		++view.ptr;
		return tok;
	}

}
