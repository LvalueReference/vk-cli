#include <locale>
#include "reader/reader.hpp"

int main(){
#ifdef _WIN32
    setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

	reader::chat_reader reader;
	reader.run();

    return EXIT_SUCCESS;
}
