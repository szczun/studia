#ifndef CONVERT_FILE_H
#define CONVERT_FILE_H
#include "UserInput.h"
#include <fstream>

class ConvertFile : public UserInputHandler{
    public:
        ConvertFile(UserInputHandler *obj);
        ~ConvertFile() {};
        void convertFile();
};  

#endif