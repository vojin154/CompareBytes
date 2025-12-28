#include "File.h"

#include "DebugOnly.h"

bool File::openFile(std::ifstream* file_handle) {
	printf("Opening %s", this->path.c_str());

	file_handle->open(this->path, std::ifstream::binary);

	if (!file_handle->is_open()) {
		printf(" -> Failed!\n");
		IN_DEBUG(printf("[File::openFile] Failed to open file! Path: \"%s\"\n", this->path.c_str()));
		return false;
	}

	printf(" -> Opened!\n");

	this->handle = file_handle;

	return true;
}

void File::closeFile() {
	if (this->handle) {
		this->handle->close();
		this->handle = nullptr;
	}
}