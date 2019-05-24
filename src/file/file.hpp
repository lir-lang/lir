#pragma once

#ifdef _WIN32
	#include <file/file_other.hpp>

#elif defined __unix__
	#include <file/file_unix.hpp>

#elif defined __APPLE__
	#include <file/file_other.hpp>

#endif


