#include "ConvertFile.h"

void ConvertFile::convertFile() {
    std::string filename = this->getFilepath();
    std::ifstream input_file(filename);
    std::cout << "Output from convertfile: " << filename << std::endl;
} 