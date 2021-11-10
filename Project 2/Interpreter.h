//
// Created by Student on 10/13/21.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"
#include "Relation.h"
#include "Header.h"
#include "Predicate.h"
//connects DatalogProgram and Database
class Interpreter {
private:
    DatalogProgram* theDatalogProgram; //stores DatalogProgram as data member

    Database* theDatabase = new Database(); //makes database using schemes and facts and stores as data member
    int howManyTimesRules = 0;
public:
    Interpreter(DatalogProgram* datalogProgram);
    Relation* EvaluatePredicate(Predicate& p);
    string EvaluateAllRules();
    string EvaluateAllQueries();
};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
