#ifndef __PROG_ARGS_HEADER__
#define __PROG_ARGS_HEADER__

#include <vector>

#include "File.h"

class ProgArgs {
	inline bool isArgField(char* arg) {
		return arg[0] == '-';
	};

	bool isFileArg(char* arg);
	bool isPreprocessor(char* arg);
public:
	void processProgramArgs(const int& argc, char* argv[]);
	bool skip_byte_size{ false };
	bool print_all{ false };
	std::vector<File*> files{};
};

#endif	