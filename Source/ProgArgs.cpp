#include "ProgArgs.h"

#include "DebugOnly.h"

void ProgArgs::processProgramArgs(const int& argc, char* argv[]) {
	IN_DEBUG(printf("Argument count: %i\n", argc));

	for (int i{ 0 }; i < argc; i++) {
		char* arg = argv[i];

		if (!this->isArgField(arg) || this->isPreprocessor(arg)) {
			continue;
		}

		if (this->isFileArg(arg)) {
			std::string path{ argv[i + 1] };
			File* file{ new File{path} };
			this->files.push_back(file);
		}

		IN_DEBUG(printf("Argument [%i] %s\n", i, arg));
	}

	IN_DEBUG(printf("\n"));
}

bool ProgArgs::isPreprocessor(char* arg) {
	if (strcmp(arg, "-skip_byte_size") == 0) {
		this->skip_byte_size = true;
		return true;
	}

	if (strcmp(arg, "-print_all") == 0) {
		this->print_all = true;
		return true;
	}

	return false;
}

bool ProgArgs::isFileArg(char* arg) {
	if (strcmp(arg, "-file_a") == 0) {
		return true;
	}

	if (strcmp(arg, "-file_b") == 0) {
		return true;
	}

	return false;
}