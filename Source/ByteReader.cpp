#include "ByteReader.h"

#include "DebugOnly.h"

#include <execution>
#include <atomic>

void ByteReader::readBytes(File* file) {
	std::ifstream handle{};

	if (!file->openFile(&handle)) {
		IN_DEBUG(printf("[ByteReader::readBytes] Provided file isn't open!\n"));
		file->closeFile();
		return; // Better be safe, than sorry..
	}

	handle.seekg(0, std::ifstream::end);
	std::streamsize file_size{ handle.tellg() };
	handle.seekg(0, std::ifstream::beg);

	file->bytes.reserve(file_size); // Pre-allocate needed bytes

	printf("Reading file!");

	// Create buffer
	#ifdef HEAP_BYTES
		uint8_t* buff{ new uint8_t[BYTES_PER_CHUNK] };
	#else
		uint8_t buff[BYTES_PER_CHUNK];
	#endif

	// Read file bytes
	while (this->getByte(buff, handle)) {
		std::streamsize bytes_read{ handle.gcount() };
		for (std::streamsize byte{ 0 }; byte < bytes_read; byte++) {
			file->bytes.push_back(static_cast<uint8_t>(buff[byte]));
		}
	}

	// If buffer on heap -> clean up buffer
	#ifdef HEAP_BYTES
		delete[] buff;
	#endif

	printf(" -> Success!\n");

	file->closeFile();
}

bool ByteReader::getByte(uint8_t* buff, std::ifstream& handle) {
	handle.read(reinterpret_cast<char*>(buff), BYTES_PER_CHUNK);

	if (handle.gcount() > 0) {
		return true;
	}

	if (handle.bad()) {
		printf(" -> Failed!\n");
		IN_DEBUG(printf("[ByteReader::getByte] There was a problem with reading file bytes!\n"));
	}

	return false;
}

bool ByteReader::compareBytes(const std::vector<uint8_t>& bytes_a, const std::vector<uint8_t>& bytes_b) {
	printf("Comparing bytes!");

	if (!this->skip_byte_size) {
		if (bytes_a.size() != bytes_b.size()) {
			printf(" -> Files are different sizes in bytes!\n");
			return false;
		}
	}

	size_t size{ std::min(bytes_a.size(), bytes_b.size()) }; // Iterate based on the smaller file (DUH, we don't want to go out of range)
	std::atomic<size_t> byte{ 0 };

	std::atomic<bool> different_bytes{ false };
	std::atomic<bool> failed{ false };
	std::atomic<bool> print_all_bytes{ this->print_all };

	// Run in parallel
	std::for_each(std::execution::par, bytes_a.begin(), bytes_a.begin() + size, [&](auto&) {
		size_t current_byte{ byte.fetch_add(1) };

		if (bytes_a[current_byte] != bytes_b[current_byte]) {
			if (failed.load()) { // Insanely hacky, but holy shit is this really the only way to stop a for_each loop, without throwing exceptions??
				return;
			}

			if (!different_bytes.load()) { // Disgusting, but pls print only once..
				different_bytes.store(true);
				printf(" -> Found different bytes!\n");
			}

			printf("[Offset: %X] 0x%X vs 0x%X\n", static_cast<unsigned int>(current_byte), bytes_a[current_byte], bytes_b[current_byte]);

			if (!print_all_bytes.load()) {
				failed.store(true);
				return;
			}
		}
	});

	if (failed.load()) {
		return false;
	}

	printf(" -> Files are same!\n");

	printf("\n");

	return true;
}