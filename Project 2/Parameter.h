//
// Created by Abigail Spigarelli on 9/22/21.
//

#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H
#include <string>

//grammer:
//String | ID

using namespace std;
class Parameter {
private:
    string tokenDescription; //string or ID
    //should I also have the ID name
    //bool isStringOrID = false;//this will help out in project 3

public:
    Parameter(string description );
    string parameterToString();


};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
