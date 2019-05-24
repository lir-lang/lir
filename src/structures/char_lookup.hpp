#pragma once

#include <limits>
#include <algorithm>
#include <vector>
#include <array>
#include <initializer_list>
#include <utility> // std::pair

namespace lir {
	template <typename T>
	class CharLookup {
		using lookup_t = std::array<T, 256>;
		using size_type = typename lookup_t::size_type;

		using init_val  = typename std::pair<const char, const T>;
		using init_list = typename std::initializer_list<init_val>;


		private:
			T table[256] = {T{}};


		public:
			constexpr CharLookup(const init_list& init) {
				for (const auto& [chr, val]: init)
					*(table + chr) = val;
			}





			constexpr __attribute__((pure)) const T at(char i) const {
				return *(table + i);
			}


			constexpr __attribute__((pure)) const T operator[](char i) const {
				return *(table + i);
			}
	};

}


