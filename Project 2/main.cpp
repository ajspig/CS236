#include "Lexer.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype> //this is for isspace function
#include "DatalogProgram.h"
#include "Interpreter.h"
//should I include all the new classes in here?
#include "Header.h"
using namespace std;

int main(int argc, char** argv) {
    //verify commandline arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }
    string fileName = argv[1];
    ifstream input(fileName);    //open an ifstream object
    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }
    string inputString = "";
    char c = input.get();
    while(input.good()){
        inputString += c;
        c = input.get();
    }
    input.close();

    Lexer* lexer = new Lexer(); //instantiate an instance of the Lexer class
    lexer->Run(inputString); //pass the input to lexer class
    DatalogProgram *parser = new DatalogProgram();
    parser->parseSyntax(lexer->ReturnTokens()); //pass the tokens to my parser class
    //Interpreter *interpreter = new Interpreter(*parser);
    //How do I connect my datalogprogram with my interpreter
    Interpreter *interpreter = new Interpreter(parser);
    //cout << interpreter->toString() <<endl;

//    if(parser->getSyntaxCheck()){
//        cout << "Success!" << endl;
//        cout << parser->datalogProgramToString();
//
//    }else{
//        cout << "Failure!" << endl;
//        cout << "  " << parser->getFailedToken();
//
//    }
    cout << interpreter->EvaluateAllQueries();

    delete lexer;//deallocate memory

    return 0;
}

//    //while get peek != endfile
//    filebuf* pbuf = input.rdbuf();
//    //get file size using buffer's members
//    size_t size = pbuf->pubseekoff(0,input.end, input.in);
//    pbuf->pubseekpos(0,input.in);
//    //allocate memory to contain file data
//    char* buffer = new char[size];
//    //get file data
//    pbuf->sgetn(buffer, size);
//    input.close();
//    stringstream  ss;
//    ss.str(buffer);
//    string s = ss.str();
//
//    delete [] buffer;
//    //read the file into a string with get and peek //didnt do this. Did below with rdbuf. not really sure what it is all I know is that it works
//
//    //take the rdbuf from an ifstream and dump that into a stringstream.
//    // then convert the string stream into a string