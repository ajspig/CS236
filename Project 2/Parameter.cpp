//
// Created by Abigail Spigarelli on 9/22/21.
//

#include "Parameter.h"
Parameter::Parameter(string descript) {
    tokenDescription = descript;
}
string Parameter::parameterToString(){

    return tokenDescription; //this should be S or 12345
}