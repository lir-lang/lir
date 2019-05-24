#pragma once

#include <stack>
#include <deque>
#include <vector>
#include <utility> // std::forward
#include <file/file.hpp>
#include <structures/view.hpp>

namespace lir {

	struct FileView {
		lir::File file;
		lir::View view;


		FileView(const std::string& fname)
			: file(fname), view(file) {}
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



			lir::View& view() {
				return top().view;
			}

			decltype(FileView::file)& file() {
				return top().file;
			}

			const lir::View& view() const {
				return top().view;
			}

			const decltype(FileView::file)& file() const {
				return top().file;
			}






			void newfile(const std::string& fname) {
				stack.emplace(fname);
			}


			void pop() {
				stack.pop();
			}




			operator lir::View&() {
				return view();
			}

			operator decltype(FileView::file)&() {
				return file();
			}

	};



}
