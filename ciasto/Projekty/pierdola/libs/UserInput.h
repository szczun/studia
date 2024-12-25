#ifndef USER_INPUT_H
#define USER_INPUT_H
#include <string>
#include <iostream>
#include <vector>

class UserInputHandler {
    private:
        std::string filepath;
        std::string filename_parts[2];
        bool object_exists;

        int number_of_columns;
        std::vector<std::string> column_names;

        // setters
        // void setFilepath(std::string filepath);

        // getters

    public:
    
        // constructor
        UserInputHandler(std::string);

        // destructor
        ~UserInputHandler() {};

        std::string getFilepath();
        bool isObjectExsists();
        void askForParams();
        void splitFilename();
        // temp functions
        void Print();
};

#endif 
