#pragma once

#include <string>
#include <filesystem>
#include <tinge.hpp>

#include <structures/view.hpp>
#include <io/io.hpp>
#include <frontend/lexer/lexer.hpp>

namespace lir::preprocessor {

	inline lir::Token preprocessor_callback(lir::Position& pos, lir::View& view) {
		namespace Type = lir::Tokens;
		namespace err = lir::except::lexer;


		lir::Token ret;
		char current = *view;



		if (lir::in_group<'\t', ' '>(current)) {
			++view;
			pos.incr_column();
			return preprocessor_callback(pos, view);
		}

		else if (current == '\n') {
			++view;
			pos.incr_line();
			return preprocessor_callback(pos, view);
		}



		else if (lir::alpha(current)) ret = {Type::Identifier, lir::lexer::on_alpha(view)};
		else if (lir::digit(current)) ret = {Type::Number, lir::lexer::on_num(view)};

		else if (current == '"') ret = {Type::String, lir::lexer::on_string(view)};


		// Handle EOF...
		else if (not view.remaining()) ret = {Type::Eof};

		else {
			err::throw_error(pos, "unexpected character '", current, "' in preprocessor directive.");
			++view;
			return preprocessor_callback(pos, view);
		}

		++view;
		pos.incr_column(ret.str.size());

		return ret;
	}



	// Run the preprocessor. Consumes a directive and performs associated action.
	void run(lir::FileStack& files) {
		namespace err = lir::except::preprocessor;

		auto& view = files.view();
		auto& pos  = files.pos();
		auto pos_before = pos;  // store starting position for errors.

		++view; // skip '#'

		// Read the directive. i.e: #load "file.txt"
		auto directive = view.read_until([] (auto c) {
			return *c == '\n';
		});



		// Check next token to see if it is an identifier.
		lir::Token name = preprocessor_callback(pos, directive);
		if (name != lir::Tokens::Identifier)
			err::throw_error(pos_before, "unexpected token '", lir::Tokens::to_str[name.type], "', expecting 'Identifier'.");


		// switch on the directive type.
		if (name == "load") {
			// make sure next token is a string for loading.
			lir::Token arg = preprocessor_callback(pos, directive);

			if (arg != lir::Tokens::String)
				err::throw_error(pos_before, "unexpected token '", lir::Tokens::to_str[arg.type], "', expecting 'String'.");

			try {
				// Open our file and put it on top of the filestack.
				files.newfile(std::move(arg));

			} catch (const std::filesystem::filesystem_error& e) {
				err::throw_error(pos_before, "cannot open file '", arg, "'.");
			}

		} else {
			err::throw_error(pos_before, "unknown directive '", name, "'.");
		}

	}
}


