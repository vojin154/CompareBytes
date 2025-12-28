#ifndef __FILE_HEADER__
#define __FILE_HEADER__

#include <fstream>
#include <string>
#include <vector>

class File {
	std::string path{};
	std::ifstream* handle{};
public:
	std::vector<uint8_t> bytes{};

	File(const std::string& file_path) : path{ file_path } {};

	bool openFile(std::ifstream* file_handle);
	void closeFile();
};

#endif