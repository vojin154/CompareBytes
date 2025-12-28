#ifndef __BYTE_READER_HEADER__
#define __BYTE_READER_HEADER__

#include <fstream>
#include <vector>

#include "File.h"

#define BYTES_PER_CHUNK_DEF (512 * 1024) // Why this stupid ass abomination? Yeap, I couldn't get to compare constepxr in #if XD
constexpr size_t BYTES_PER_CHUNK{ BYTES_PER_CHUNK_DEF };

#if BYTES_PER_CHUNK_DEF >= 1'000'000
// If BYTES_PER_CHUNK is bigger than 1 MB (Visual Studio default stack size), then create on heap, which is a bit slower, than stack..
	#define HEAP_BYTES
#endif

class ByteReader {
	bool getByte(uint8_t* buff, std::ifstream& handle);
	bool skip_byte_size{ false };
	bool print_all{ false };
public:
	ByteReader(const bool& skip_byte_size, const bool& print_all ) : skip_byte_size{ skip_byte_size }, print_all{ print_all } {}

	void readBytes(File* file);
	bool compareBytes(const std::vector<uint8_t>& bytes_a, const std::vector<uint8_t>& bytes_b);
};

#endif