#pragma once

#include <structures/ast.hpp>
#include <utils/exception.hpp>

#include <string>
#include <variant>

namespace lir::backend::treewalk {

	using TreeWalkValue = std::variant<double, bool>;

	// Simple tree walk interpreter, not complete
	class TreeWalk {
	public:

		// Executes literal nodes
		TreeWalkValue operator()(const lir::expressions::Literal& node) const {
			return { std::stod(node.value) };
		}

		// Executes unary nodes
		TreeWalkValue operator()(const lir::expressions::Unary& node) const {
			auto expr = eval(node.expression);

			switch (node.op) {
				case Tokens::Op_Minus:
					return { -std::get<double>(expr) };

				default:
					lir::except::throw_unreachable({__LINE__, 0, __func__});
					return {}; // Gets rid of end of function warning
			}
		}

		// Executes binary nodes
		TreeWalkValue operator()(const lir::expressions::Binary& node) const {
			auto left  = std::get<double>(eval(node.left));
			auto right = std::get<double>(eval(node.right));

			switch (node.op) {
				// Numerical operations
				case Tokens::Op_Plus: 
					return { left + right };
				case Tokens::Op_Minus:
					return { left - right };
				case Tokens::Op_Multiply:
					return { left * right };
				case Tokens::Op_Divide:
					return { left / right };

				// Boolean operations
				case Tokens::Cmp_Less:
					return { left < right };
				case Tokens::Cmp_More:
					return { left > right };
				case Tokens::Cmp_Eq:
					return { left == right };
				case Tokens::Cmp_LessEq:
					return { left <= right };
				case Tokens::Cmp_MoreEq:
					return { left >= right };
				case Tokens::Cmp_NotEq: 
					return { left != right };
				
				default:
					lir::except::throw_unreachable({__LINE__, 0, __func__});
					return {}; // Gets rid of end of function warning
			}
		}

		// Executes grouping
		TreeWalkValue operator()(const lir::expressions::Grouping& node) const {
			return eval(node.expression);
		}

		// Recusive function to execute tree using vistor pattern
		TreeWalkValue eval(const lir::AST& ast) const {
			return std::visit(*this, *ast);
		}

	};

	auto interpret(const lir::AST& ast) {
		TreeWalk interpreter;
		return interpreter.eval(std::forward<decltype(ast)>(ast));
	}

}

// In its own namespace since gcc is super weird about templates
inline std::ostream& operator<<(std::ostream& os, const lir::backend::treewalk::TreeWalkValue& value) {
	if(auto d = std::get_if<double>(&value)) {
		os << *d;
	} else if(auto b = std::get_if<bool>(&value)) {
		os << (std::array<const char*, 2>{"true", "false"}[*b]);
	} else {
		lir::except::throw_unreachable({__LINE__, 0, __func__});
	}
	return os;
}