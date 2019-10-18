#include <chrono>
#include <iostream>
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


	try {
		lir::FileStack files;

		try {
			files.newfile(argv[1]);

		} catch (const std::filesystem::filesystem_error&) {
			tinge::errorln("cannot open file '", argv[1], "'.");
			return 1;
		}

		// lir::AST ast = lir::run(files);

	// Just catch any error.
	} catch (const std::exception& e) {
		tinge::errorln_em("error: ", e.what());
	}

	tinge::successln_em(diff<std::chrono::milliseconds>(timer::now(), start), "ms");

	return 0;
}
