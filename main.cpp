#include <chrono>
// #include <modules/cxxopts.hpp>
#include <lir.hpp>



// Convenience.
using timer = std::chrono::high_resolution_clock;
using units = std::chrono::milliseconds;

template <typename T>
constexpr auto diff = [] (auto a, auto b) { return std::chrono::duration_cast<T>(a - b).count(); };





int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto start = timer::now();



	// Handle arguments.
	// ...



	try {
		lir::FileStack files;
		lir::Token tok;

		try {
			files.newfile(argv[1]);

		} catch (const std::filesystem::filesystem_error&) {
			lir::errorln("cannot open file '", argv[1], "'.");
			return 1;
		}


		// Run the lexer.
		while (not tok.eof()) {
			tok = lir::lexer::run(files);
			// lir::println("[L] -> ", tok);  // Print tokens (don't use this for big files.)
		}


	// Just catch any error.
	} catch (const std::exception& e) {
		lir::errorln_em("error: ", e.what());
	}


	lir::successln_em(diff<std::chrono::milliseconds>(timer::now(), start), "ms");


	return 0;
}
