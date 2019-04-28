#include <chrono>
#include <unordered_map>
#include <algorithm>

#include <util/util.hpp>
#include <structures/structures.hpp>
#include <preprocessor/preprocessor.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>




using timer = std::chrono::high_resolution_clock;
using units = std::chrono::milliseconds;
constexpr auto diff = [] (auto a, auto b) {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(a - b).count();
};


using Tokens = std::vector<lir::Token>;
using Positions = std::vector<lir::Position>;





int main(int argc, const char* argv[]) {
	auto start_total = timer::now();

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);



	auto start_recv = timer::now();

	auto input = lir::recv_stdin();


	if (input.empty()) {
		lir::errorln_h("no input from stdin!");
		return 1;
	}


	auto end_recv = timer::now();


	auto start_lexer = timer::now();



	lir::View view{input};

	lir::Token tok;
	while (not tok.eof()) {
		tok = lir::lexer::advance(view, lir::lexer::lexer_callback);
		// std::cerr << tok << '\n';
	}


	auto end_lexer = timer::now();
	auto end_total = timer::now();



	if constexpr(false) {
		view = lir::View{input};

		std::unordered_map<uint8_t, int> freq;
		tok = lir::Token{};

		while (not tok.eof()) {
			tok = lir::lexer::advance(view, lir::lexer::lexer_callback);
			freq[tok.type]++;
		}

		std::vector<std::pair<uint8_t, int>> sorted;

		std::copy(
			freq.begin(), freq.end(),
			std::back_inserter(sorted)
		);

		std::sort(sorted.begin(), sorted.end(), [] (auto a, auto b) {
			return a.second > b.second;
		});

		for (const auto& [type, val]: sorted)
			std::cerr << lir::TokenType::to_str[type] << ", " << val << '\n';
	}



	if constexpr(false) {
		auto fmt_num_str = [] (auto&& val) {
			auto num = std::to_string(val);
			int ins_pos = num.size() - 3;

			for (; ins_pos > 0; ins_pos -= 3)
				num.insert(static_cast<std::string::size_type>(ins_pos), ",");

			return num;
		};



		double total_time_milli = diff(end_total, start_total) / 1000 / 1000;
		double lexer_time_milli = diff(end_lexer, start_lexer) / 1000 / 1000;
		double recv_time_milli  = diff(end_recv, start_recv) / 1000 / 1000;

		double input_size_mb = static_cast<double>(input.size()) / 1024 / 1024;
		double bandwidth = input_size_mb / (lexer_time_milli / 100);


		lir::warnln(bandwidth,  " MB/s");

		lir::println();

		lir::successln_em("read ", " | ", recv_time_milli,  "ms");
		lir::successln_em("lexer", " | ", lexer_time_milli, "ms");
		lir::successln_em("total", " | ", total_time_milli, "ms");

		lir::println();

		lir::noticeln_em("input | ", fmt_num_str(input.size()), " B");
		lir::println();

	} else {
		lir::noticeln_em(diff(end_total, start_total) / 1000 / 1000, "ms");
	}


	return 0;
}
