#include <chrono>
// #include <modules/cxxopts.hpp>
#include <lir.hpp>

// Basic compile time flags
constexpr bool debug_mode = false;


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

		lir::AST ast = lir::parser::run(files);

		if constexpr(debug_mode) {
			std::cout << "[T] -> " << ast << std::endl;
		}

		auto result = lir::backend::treewalk::interpret(ast);

		if constexpr(debug_mode) {
			std::cout << "[R] -> "
					<< lir::colour::bg::normal
					<< lir::colour::fg::black
					<< "["
					<< lir::colour::bg::black
					<< lir::colour::fg::normal
					<< result
					<< lir::colour::bg::normal
					<< lir::colour::fg::black
					<< "]"
					<< std::endl;
		}

	// Just catch any error.
	} catch (const std::exception& e) {
		lir::errorln_em("error: ", e.what());
	}


	lir::successln_em(diff<std::chrono::milliseconds>(timer::now(), start), "ms");


	return 0;
}
