#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <fstream>

namespace lir {

	struct File {
		const char* ptr;
		std::uintmax_t filesize;
		bool is_file_open;
		std::string str;


		File(const std::string& fname);

		auto size() const {
			return filesize;
		}

		auto is_open() const {
			return is_file_open;
		}
	};


	File::File(const std::string& fname) {
		namespace fs = std::filesystem;

		auto p = fs::current_path() / fname;
		filesize = fs::file_size(p);

		std::ifstream is(p, std::ios::binary);

		is_file_open = is.is_open();

		str = std::string(filesize, '\0');
		is.read(str.data(), static_cast<std::streamsize>(filesize));

		ptr = str.c_str();
	}
}


inline std::ostream& operator<<(std::ostream& os, const lir::File& f) {
	return (os << std::string_view{f.ptr, f.filesize});
}

