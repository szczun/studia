#include "UserInput.h"
#include <cstdint>
#include <iostream>
#include <sstream>

UserInputHandler::UserInputHandler(std::string filepath) {
    this->filepath = filepath;
    this->object_exists = true;
}

// void UserInputHandler::setFilepath(std::string filepath){
//     this->filepath = filepath;
// }

std::string UserInputHandler::getFilepath(){
    return this->filepath;
}

void UserInputHandler::Print(){
    std::cout << this->filepath << std::endl;
}

bool UserInputHandler::isObjectExsists() {
    return this->object_exists;
}

void UserInputHandler::splitFilename() {

    std::istringstream stream(this->filepath);

    for (size_t i = 0; i < 2; i++){
        std::getline(stream, this->filename_parts[i], '.');
        // std::cout << filename_parts[i] << std::endl;
    }
}

void UserInputHandler::askForParams() {
    int number_of_columns;
    std::vector<std::string> column_names;


    if (isObjectExsists()){
        splitFilename();
        std::cout << " -------------------------" << std::endl;
        std::cout << "| Pass number of columns: ";
        std::cout << " -------------------------" << std::endl;

        std::cin >> number_of_columns;
        if (std::cin.fail() || number_of_columns < 2){
            std::cout << "Invalid input." << std::endl;
            return;
        }
        std::cout << number_of_columns << std::endl;

        for(int i = 0; i < number_of_columns; i++){
            std::string col_name;
            std::cout << "Column name #" << (i + 1) << ": ";
            std::cin >> col_name;
            column_names.push_back(col_name);
            col_name = "";
        }

        for(auto i : column_names){
            std::cout << "Wynik printa: " << i << std::endl;
        }
    }
}
