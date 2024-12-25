#include "libs/UserInput.h"
#include "libs/ConvertFile.h"
int main(int argc, char** argv){

    if (argc != 3){
        std::cout << argc << std::endl;
        std::cout << argv[0] << " " << argv[1] << " " << argv[2] << std::endl;
        std::cout << " -------------------------------------------------" << std::endl;
        std::cout << "| You didn't pass any argument                    |" << std::endl;
        std::cout << "| Usage ./<script-name> <path/to/file/filename>.* |" << std::endl;
        std::cout << " -------------------------------------------------" << std::endl;
    }

    UserInputHandler* obj = new UserInputHandler(argv[2]);

    obj->askForParams();
    obj->Print();
    ConvertFile obj2(&obj);
    obj2.convertFile();
}