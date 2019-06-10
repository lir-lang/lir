#pragma once

#include <stack>
#include <deque>
#include <vector>
#include <utility> // std::forward
#include <file/file.hpp>
#include <structures/view.hpp>
#include <structures/position.hpp>

namespace lir {

	struct FileView {
		lir::File file;
		lir::View view;
		lir::Position pos;

		// Create a new file object here and store it.
		FileView(const std::string& fname)
			: file(fname), view(file), pos(1, 1, fname) {}
	};




	class FileStack {
		using element_t   = FileView;
		using container_t = std::stack<element_t, std::vector<element_t>>;

		private:
			container_t stack;

		public:

			bool empty() const {
				return stack.empty();
			}

			typename container_t::size_type size() const {
				return stack.size();
			}



			element_t& top() {
				return stack.top();
			}

			const element_t& top() const {
				return stack.top();
			}


			// Getters
			lir::View& view() {
				return top().view;
			}

			decltype(FileView::file)& file() {
				return top().file;
			}

			lir::Position& pos() {
				return top().pos;
			}


			const lir::View& view() const {
				return top().view;
			}

			const decltype(FileView::file)& file() const {
				return top().file;
			}

			const lir::Position& pos() const {
				return top().pos;
			}




			// Add a new file to the stack.
			void newfile(std::string fname) {
				stack.emplace(fname);
			}

			void pop() {
				stack.pop();
			}


			// Implicit conversions
			operator lir::View&() {
				return view();
			}

			operator decltype(FileView::file)&() {
				return file();
			}
	};
}
