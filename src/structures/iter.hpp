
// #pragma once


// #include <cmath>
// #include <string_view>

// #include <structures/view.hpp>


// namespace lir {
// 	struct Iter {
// 		const char* ptr;
// 		// lir::LargeView str;


// 		// bool remaining() {
// 		// 	return ptr < str.end();
// 		// }




// 		// operator char() {
// 		// 	return *ptr;
// 		// }


// 		// operator const char*() {
// 		// 	return ptr;
// 		// }


// 		// operator lir::StrView() {
// 		// 	return {ptr, 1};
// 		// }


// 		// char operator*() {
// 		// 	return *ptr;
// 		// }


// 		// Iter& operator+=(const int& rhs) {
// 		// 	ptr += rhs;
// 		// 	return *this;
// 		// }


// 		// Iter& operator-=(const int& rhs) {
// 		// 	ptr -= rhs;
// 		// 	return *this;
// 		// }


// 		// Iter& operator++() {
// 		// 	ptr++;
// 		// 	return *this;
// 		// }


// 		// Iter& operator--() {
// 		// 	ptr--;
// 		// 	return *this;
// 		// }


// 		// Iter operator++(int) {
// 		// 	Iter tmp(*this);
// 		// 	operator++();
// 		// 	return tmp;
// 		// }


// 		// Iter operator--(int) {
// 		// 	Iter tmp(*this);
// 		// 	operator--();
// 		// 	return tmp;
// 		// }


// 		// friend Iter operator+(Iter lhs, const int& rhs) {
// 		// 	lhs += rhs;
// 		// 	return lhs;
// 		// }


// 		// friend Iter operator-(Iter lhs, const int& rhs) {
// 		// 	lhs -= rhs;
// 		// 	return lhs;
// 		// }


// 		// friend bool operator<(const Iter& lhs, const Iter& rhs) {
// 		// 	return lhs < rhs;
// 		// }


// 		// friend bool operator>(const Iter& lhs, const Iter& rhs) {
// 		// 	return rhs < lhs;
// 		// }


// 		// friend bool operator<=(const Iter& lhs, const Iter& rhs) {
// 		// 	return !(lhs > rhs);
// 		// }


// 		// friend bool operator>=(const Iter& lhs, const Iter& rhs) {
// 		// 	return !(lhs < rhs);
// 		// }

// 		friend bool operator==(const Iter& lhs, char rhs) {
// 			return *lhs.ptr == rhs;
// 		}


// 		friend bool operator!=(const Iter& lhs, char rhs) {
// 			return not(lhs == rhs);
// 		}

// 	};




// 	// uint8_t diff(const char* lhs, const char* rhs) {
// 	// 	auto a = static_cast<const char*>(lhs);
// 	// 	auto b = static_cast<const char*>(rhs);

// 	// 	return a - b + 1;
// 	// }


// }



