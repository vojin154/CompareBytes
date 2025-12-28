#include <Windows.h>
#include <time.h>

#include "DebugOnly.h"
#include "ProgArgs.h"
#include "ByteReader.h"

static void readFiles(ByteReader* reader, File* file_a, File* file_b) {
    reader->readBytes(file_a);
    printf("\n");
    reader->readBytes(file_b);
    printf("\n");
}

int main(const int argc, char* argv[]) {
    printf("\n");

    const clock_t start{ clock() };

    ProgArgs args{};
    args.processProgramArgs(argc, argv);

    if (args.files.size() != 2) {
        printf("2 file inputs are required! Got: %i", static_cast<int>(args.files.size()));
        printf("\n");
        return 1;
    }

    ByteReader reader{args.skip_byte_size, args.print_all};
    readFiles(&reader, args.files[0], args.files[1]);
    reader.compareBytes(args.files[0]->bytes, args.files[1]->bytes);

    printf("\n");

    printf("Finished Running.\n");

    printf("Time taken: %.2fs\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}