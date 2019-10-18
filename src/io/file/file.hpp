#pragma once

#ifdef _WIN32
	#include <io/file/file_other.hpp>

#elif defined __unix__
	#include <io/file/file_unix.hpp>

#elif defined __APPLE__
	#include <io/file/file_other.hpp>

#endif


