#include <chrono>
// #include <modules/cxxopts.hpp>
#include <lir.hpp>



using timer = std::chrono::high_resolution_clock;
using units = std::chrono::milliseconds;

template <typename T>
constexpr auto diff = [] (auto a, auto b) { return std::chrono::duration_cast<T>(a - b).count(); };





int main(int argc, char* argv[]) {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);


	// Handle arguments.
	// ...


	// Read file/stdin.
	auto start_total = timer::now();
	auto start_recv = timer::now();

	lir::FileStack files;
	files.newfile(argv[1]);


	if (not files.file().is_open()) {
		lir::errorln_h("no input from stdin!");
		return 1;
	}

	auto end_recv = timer::now();



	// Consume tokens.
	auto start_lexer = timer::now();
	{
		namespace lex   = lir::except::lexer;
		namespace pre   = lir::except::preprocessor;
		namespace parse = lir::except::parser;

		try {
			lir::Token tok;
			while (not tok.eof()) {
				tok = lir::lexer::run(files);
				// lir::println("[L] -> ", tok);
			}

		} catch (const lex::LexerError& e) {
			lex::catch_error(e);
			return 1;

		} catch (const pre::PreprocessorError& e) {
			pre::catch_error(e);
			return 2;

		} catch (const parse::ParserError& e) {
			parse::catch_error(e);
			return 3;
		}
	}



	auto end_lexer = timer::now();
	auto end_total = timer::now();

	lir::successln_em(diff<std::chrono::milliseconds>(end_total, start_total), "ms");


	return 0;
}
