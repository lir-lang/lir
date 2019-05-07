#include <chrono>
#include <unordered_map>
#include <algorithm>

#include <lir.hpp>



using timer = std::chrono::high_resolution_clock;
using units = std::chrono::milliseconds;

template <typename T>
constexpr auto diff = [] (auto a, auto b) {
	return std::chrono::duration_cast<T>(a - b).count();
};





int main(int argc, const char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);


	// Read input.
	auto start_total = timer::now();
	auto start_recv = timer::now();
	auto input = lir::recv_stdin();

	if (input.empty()) {
		lir::errorln_h("no input from stdin!");
		return 1;
	}

	auto end_recv = timer::now();


	// Consume tokens.
	auto start_lexer = timer::now();
	lir::View view{input};

	lir::Token tok;
	while (not tok.eof())
		tok = lir::lexer::advance(view, lir::lexer::lexer_callback);

	auto end_lexer = timer::now();
	auto end_total = timer::now();

	lir::successln_em(diff<std::chrono::milliseconds>(end_total, start_total), "ms");


	return 0;
}
