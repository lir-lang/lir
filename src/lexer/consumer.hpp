#pragma once


#include <string_view>
#include <utility>
#include <optional>

#include <structures/iter.hpp>


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
	inline bool match(lir::Iter& iter, char expect) noexcept {
		return (*(iter + 1) == expect) and (++iter, true);
	}







	// Skip characters until predicate fails.
	template <typename P, typename... Ts>
	inline void skip_while(lir::Iter& iter, P pred, Ts&&... args) {
		while (pred(iter, std::forward<Ts>(args)...) and iter.remaining())
			++iter;
	}


	// Skip characters until predicate fails.
	template <typename P>
	inline void skip_while(lir::Iter& iter, P pred) {
		while (pred(iter) and iter.remaining())
			++iter;
	}







	// Consume characters while predicate is satisfied.
	template <typename P, typename... Ts>
	inline lir::StrView read_while(lir::Iter& iter, P pred, Ts&&... args) {
		auto begin = iter.ptr;

		while (pred(iter, std::forward<Ts>(args)...) and iter.remaining())
			++iter;

		return {begin, lir::diff(iter.ptr, begin)};
	}



	// Consume characters while predicate is satisfied.
	template <typename P>
	inline lir::StrView read_while(lir::Iter& iter, P pred) {
		auto begin = iter.ptr;

		while (pred(iter) and iter.remaining())
			++iter;

		return {begin, lir::diff(iter.ptr, begin)};
	}







	template <typename F, typename... Ts>
	inline void run_lexer(lir::Iter& iter, F callback, Ts&&... args) {
		while (iter.remaining()) {
			callback(iter, std::forward<Ts>(args)...);
			++iter;
		}
	}





	template <typename F>
	inline lir::Token advance(lir::Iter& iter, F callback) {
		auto tok = callback(iter);
		++iter;
		return tok;
	}

}
