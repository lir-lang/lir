#include <chrono>
// #include <modules/cxxopts.hpp>
#include <lir.hpp>

#include <backends/treewalk/treewalk.hpp>

// Convenience.
using timer = std::chrono::high_resolution_clock;
using units = std::chrono::milliseconds;

template <typename T>
constexpr auto diff = [] (auto a, auto b) { return std::chrono::duration_cast<T>(a - b).count(); };


struct ASTPrinter {

	std::string operator()(lir::expressions::Literal& node) {
		return node.value;
	}
	std::string operator()(lir::expressions::Unary& node) {
		return "(" + std::string(lir::Tokens::to_str[node.op]) + " " + to_string(node.expression) + ")";
	}
	std::string operator()(lir::expressions::Binary& node) {
		return "(" + std::string(lir::Tokens::to_str[node.op]) + " " + to_string(node.left) + " " + to_string(node.right) +  ")";
	}
	std::string operator()(lir::expressions::Grouping& node) {
		return "(group " + to_string(node.expression) + ")";
	}

	std::string to_string(lir::AST& ast) {
		return std::visit(*this, *ast);
	}
};


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


		/*// Run the lexer.
		while (not tok.eof()) {
			tok = lir::lexer::run(files);
			// lir::println("[L] -> ", tok);  // Print tokens (don't use this for big files.)
		}*/

		lir::AST ast = lir::parser::run(files);

		ASTPrinter p;
		std::cout << p.to_string(ast) << std::endl;

		lir::backend::treewalk::TreeWalk interpreter;
		std::cout << "[RETURN] -> " << interpreter.eval(ast) << std::endl;


	// Just catch any error.
	} catch (const std::exception& e) {
		lir::errorln_em("error: ", e.what());
	}


	lir::successln_em(diff<std::chrono::milliseconds>(timer::now(), start), "ms");


	return 0;
}
