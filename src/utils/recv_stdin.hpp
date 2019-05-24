#pragma once


#include <string_view>
#include <string>
#include <iostream>
#include <cstdint>


namespace lir {

	inline std::string recv_stdin() {
		// Find the size of the input stream.
		std::cin.seekg(0, std::cin.end);
		const auto size = std::cin.tellg();
		std::cin.seekg(0);


		// Check pipe isn't empty.
		if (size <= 0)
			return std::string{};


		const auto size1 = static_cast<std::string::size_type>(size);
		const auto size2 = static_cast<std::streamsize>(size);


		// Reserve buffer and read pipe.
		std::string str(size1, '\0');
		std::cin.read(str.data(), size2);

		return str;
	}

}
