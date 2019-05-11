#pragma once


#include <string_view>
#include <utility>
#include <structures/view.hpp>


namespace lir::lexer {

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


}
