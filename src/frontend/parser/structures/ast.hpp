// #pragma once

// #include <structures/token_types.hpp>

// #include <variant>
// #include <string>
// #include <memory>

// namespace lir {
// 	namespace expressions {

// 		// Constant values in code such as strings and numbers
// 		struct Literal {
// 			std::string value;

// 			Literal(const std::string& val)
// 				: value(val) {}

// 		};

// 		// Unary operators such as -
// 		struct Unary {
// 			TokenType op;
// 			Expression expression;

// 			Unary(TokenType o, std::unique_ptr<Expression>& expr)
// 				: op(o), expression(std::move(expr)) {}
// 		};

// 		// Binary operators such as +, - , *, /
// 		struct Binary {
// 			Expression left, right;
// 			TokenType op;

// 			Binary(Expression& l, TokenType o, Expression& r)
// 				: left(std::move(l)), op(o), right(std::move(r)) {}
// 		};

// 		// Parenthesis
// 		struct Grouping {
// 			Grouping(std::unique_ptr<Expression>& expr)
// 				: expression(std::move(expr)) {}

// 			std::unique_ptr<Expression> expression;
// 		};

// 	}

// 	// Will contain all types of AST nodes, right only only expessions exist
// 	using AST = std::unique_ptr<Expression>;

// 	// Simple struct used for printing the AST
// 	struct ASTPrinter {

// 		std::ostream& os = std::cout;

// 		void reset() const {
// 			os << tinge::reset
// 			   << tinge::bg::reset
// 			   << tinge::fg::black;
// 		}

// 		void operator()(const lir::expressions::Literal& node) const {
// 			os << tinge::bg::black
// 			   << tinge::fg::reset
// 			   << node.value
// 			   << tinge::bg::reset
// 			   << tinge::fg::black;
// 		}

// 		void operator()(const lir::expressions::Unary& node) const {
// 			os << "("
// 			   << tinge::style::bold
// 			   << tinge::fg::bright::yellow
// 			   << std::string(lir::Tokens::to_str[node.op])
// 			   << tinge::reset
// 			   << tinge::fg::black
// 			   << " ";

// 			print(node.expression);

// 			os << ")";
// 		}

// 		void operator()(const lir::expressions::Binary& node) const {
// 			os << "("
// 			   << tinge::style::bold
// 			   << tinge::fg::bright::yellow
// 			   << std::string(lir::Tokens::to_str[node.op])
// 			   << tinge::reset
// 			   << tinge::fg::black
// 			   << " ";

// 			print(node.left);

// 			os << " ";

// 			print(node.right);

// 			os << ")";
// 		}

// 		void operator()(const lir::expressions::Grouping& node) const {
// 			os << "("
// 			   << tinge::style::bold
// 			   << tinge::fg::bright::yellow
// 			   << "group"
// 			   << tinge::reset
// 			   << tinge::fg::black
// 			   << " ";

// 			print(node.expression);

// 			os << ")";
// 		}

// 		void print(const lir::AST& ast) const {
// 			reset();
// 			return std::visit(*this, *ast);
// 		}

// 	};

// }

// // Printing the AST using ASTPrinter
// inline std::ostream& operator<<(std::ostream& os, const lir::AST& ast) {
// 	lir::ASTPrinter p = { .os = os };
// 	p.print(ast);
// 	return os;
// }
