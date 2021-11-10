//
// Created by Abigail Spigarelli on 9/22/21.
//

#include "Predicate.h"
#include <sstream>

Predicate::Predicate(string theIdValue, vector<Parameter*> theVectorOfParameterObjects) {
    IDValue = theIdValue;
    vectorOfParameterObjects = theVectorOfParameterObjects;
}

string Predicate::predicateToString() {
    ostringstream output;
    output << IDValue << "(";

    for(unsigned int i =0; i < vectorOfParameterObjects.size(); i++){
        //so this will just be printing out parameterToString() sep by ,
        output << vectorOfParameterObjects.at(i)->parameterToString();
        if(i!=vectorOfParameterObjects.size()-1){
            output << ",";
        }
    }
    output << ")? ";
    return output.str();
}
string Predicate::predicateToStringForRules() {
    ostringstream output;

    for(unsigned int i =0; i < vectorOfParameterObjects.size(); i++){
        //so this will just be printing out parameterToString() sep by ,
        output << vectorOfParameterObjects.at(i)->parameterToString();
        if(i!=vectorOfParameterObjects.size()-1){
            output << ",";
        }
    }
    return output.str();
}

void Predicate::setParameter(Parameter* parameterToAdd){
    //this adds the parameter into the vector
    vectorOfParameterObjects.push_back(parameterToAdd);
}
string Predicate::getParameterType(){

    return IDValue;
}
//void Predicate::setPredicateVector(Parameter* predVectorToUpdate){
//    vectorOfParameterObjects.push_back(predVectorToUpdate);
//}
vector <Parameter*> Predicate::getParameterVector() {
    return vectorOfParameterObjects;
}
void Predicate::setIDValue(string theIDval){
    IDValue = theIDval;
}
void Predicate::setPredicateVector(vector<Parameter *> vectorOfParam) {
    vectorOfParameterObjects = vectorOfParam;
}