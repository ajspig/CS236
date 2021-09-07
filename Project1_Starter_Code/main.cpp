#include "Lexer.h"
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char** argv) {
    //verify commandline arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }
    string fileName = argv[1];
//    ifstream input(fileName);
//    if (!input.is_open()) {
//        cout << "File " << fileName << " could not be found or opened." << endl;
//        return 1;
//    }
    //open an ifstream object
    //read the file into a string with get and peek


    Lexer* lexer = new Lexer(); //instantiate an instance of the Lexer class
    //pass the input to lexer class
    //let it run
    //main needs to get Tokens from the lexer and print them in a specified format

    delete lexer;
    //deallocate memory

    return 0;
}