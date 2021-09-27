//
// Created by Abigail Spigarelli on 9/22/21.
//

#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H

//schemes facts & queries
//IN THE GRAMMAR predicate is defined as:
//ID, LEFT_PAREN parameter parameterList RIGHT_PAREN

#include <string>
#include "Parameter.h"
#include <vector>
using namespace std;

class Predicate {
private:
    string IDValue;
    vector<Parameter*> vectorOfParameterObjects;

public:
    Predicate(string theIdValue, vector<Parameter*> theVectorOfParameterObjects);
    string predicateToString();
    void setParameter(Parameter* parameterToAdd);
    string getParameterType();
    //void setPredicateVector(Parameter* predVectorToUpdate);
    vector <Parameter*> getParameterVector();
    void setIDValue (string idval);
    void setPredicateVector(vector<Parameter*> vectorOfParam);

};


#endif //PROJECT1_STARTER_CODE_PREDICATE_H
