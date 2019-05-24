#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <utility>

extern "C" {
	#include <sys/mman.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
}

namespace lir {

	struct File {
		const char* ptr;
		std::uintmax_t filesize;
		bool is_file_open;
		int fd;


		File(const std::string& fname);
		~File();
		File(const File& other) = delete; // copy
		File(File&& other) noexcept;      // move


		File& operator=(File&& other) noexcept { // move assignment
			std::swap(ptr, other.ptr);
			std::swap(filesize, other.filesize);
			std::swap(is_file_open, other.is_file_open);
			std::swap(fd, other.fd);

			return *this;
		}

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

		is_file_open = true;


		filesize = fs::file_size(p);
		fd = open(p.c_str(), O_RDONLY, 0);

		if (fd == -1) {
			is_file_open = false;
			return;
		}

		void* mapped = mmap(nullptr, static_cast<size_t>(filesize), PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);

		if (mapped == MAP_FAILED) {
			is_file_open = false;
			return;
		}


		// it doesnt matter if this fails.
		madvise(mapped, static_cast<size_t>(filesize), MADV_SEQUENTIAL | MADV_WILLNEED);


		ptr = static_cast<const char*>(mapped);
	}



	File::~File() {
		munmap(const_cast<char*>(ptr), filesize);
		close(fd);

		ptr = nullptr;
		fd = 0;
		filesize = 0;
		is_file_open = false;
	}



	File::File(File&& other) noexcept
		: ptr(std::exchange(other.ptr, nullptr)),
		  filesize(other.filesize),
		  is_file_open(other.is_file_open),
		  fd(other.fd)
	{

	}
}


inline std::ostream& operator<<(std::ostream& os, const lir::File& f) {
	return (os << std::string_view{f.ptr, f.filesize});
}
