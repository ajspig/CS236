//
// Created by Abigail Spigarelli on 10/23/21.
//
#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter(DatalogProgram *datalogProgram) {
    theDatalogProgram = datalogProgram;//Store the DatalogProgram as a data member
    for (unsigned int i = 0; i < theDatalogProgram->getSchemes().size(); i++) {
        vector<Parameter *> nameAndHeader = theDatalogProgram->getSchemes().at(
                i)->getParameterVector(); //we want to convert this to the header
        vector<string> stringsForHeader;
        //converting a vector of Parameters to a vector of strings to a vector of headers
        for (unsigned int j = 0; j < nameAndHeader.size(); ++j) {
            stringsForHeader.push_back(nameAndHeader.at(j)->getToken());
        }
        Header *newHeader = new Header(stringsForHeader);
        Relation *relation = new Relation(theDatalogProgram->getSchemes().at(i)->getParameterType(), newHeader);

        string key = theDatalogProgram->getSchemes().at(i)->getParameterType();
        theDatabase->setValue(key, relation);
    }
    for (unsigned int i = 0; i < theDatalogProgram->getFacts().size(); i++) {
        vector<Parameter *> newTuple = theDatalogProgram->getFacts().at(
                i)->getParameterVector(); //we want to convert this to the header
        string nameOfConnectedRelation = theDatalogProgram->getFacts().at(i)->getParameterType();
        vector<string> stringsForTuple;
        //converting a vector of Parameters to a vector of strings to a vector of tuples
        for (unsigned int j = 0; j < newTuple.size(); ++j) {
            stringsForTuple.push_back(newTuple.at(j)->getToken());
        }
        //TODO: should this be a tuple pointer as well?
        Tuple tuple(stringsForTuple);
        //first use the database map to find the right vector
        theDatabase->getDatabase().at(nameOfConnectedRelation)->addTuple(tuple);
    }
}

Relation *Interpreter::EvaluatePredicate(Predicate &p) {
    Relation *relationConnectedToPredicate = theDatabase->getValue(p.getParameterType());
    map<string, int> mapOfSeenVar;
    vector<string> listOfVar;

    for (unsigned int i = 0; i < p.getParameterVector().size(); i++) {
        Parameter *currPara = p.getParameterVector().at(i);
        //check if it is a constant
        if (currPara->getToken().at(0) == '\'') {
            //do the select with int and string

            relationConnectedToPredicate = relationConnectedToPredicate->select(i, currPara->getToken());
            //this returns a new relation pointer
        } else { //it is a variable

            auto it = mapOfSeenVar.find(currPara->getToken());
            if (it != mapOfSeenVar.end()) {
                vector<string> headerAttr = relationConnectedToPredicate->getHeader()->getAttributes();
                //the first index will be where we saw the variable first
                relationConnectedToPredicate = relationConnectedToPredicate->select(it->second, i); //do a select int int

            } else {
                mapOfSeenVar.insert(pair<string, int>(currPara->getToken(), i));
                listOfVar.push_back(currPara->getToken());
            }

        }
    }
    vector<int> indexForProject;
    for (unsigned int i = 0; i < listOfVar.size(); i++) {
        indexForProject.push_back(mapOfSeenVar.find(listOfVar.at(i))->second);
    }
    relationConnectedToPredicate = relationConnectedToPredicate->project(indexForProject);
    //now we need to create the header for our project
    //reassign the relation pointer to the new relations each time
    Header *renameHeader = new Header(listOfVar);
    relationConnectedToPredicate = relationConnectedToPredicate->rename(renameHeader);

    return relationConnectedToPredicate;
}

string Interpreter::EvaluateAllRules() {
    //want to keep track of how many times we call EvaluateAllRules

    ostringstream output;
    bool moreTuplesToAdd = true;
    while(moreTuplesToAdd) {
        moreTuplesToAdd = false;
    for (unsigned int w = 0; w < theDatalogProgram->getRules().size(); w++) {
            cout << theDatalogProgram->getRules().at(w)->ruleToString();
            //this outputs the rules and should be run everytime

            Rule *currRule = theDatalogProgram->getRules().at(w);
            Predicate *firstPred = currRule->getRightPredicate().at(0);
            Relation *firstRelation = EvaluatePredicate(*firstPred);
            for (unsigned int p = 1; p < theDatalogProgram->getRules().at(w)->getRightPredicate().size(); p++) {
                if (currRule->getRightPredicate().size() != p) {
                    Predicate *currPred = currRule->getRightPredicate().at(p);
                    Relation *currRelation = EvaluatePredicate(*currPred);
                    firstRelation = firstRelation->naturalJoin(currRelation);

                }
            }
            //at this point firstRelation should be all the predicates on teh right side of teh rules joined together
            //if there is just one relation just use the results from 1
            //project the columns that occur in head predicate
            //turn the head predicate's vector of parameters into a vector of ints for thier indexs in the header
            vector<int> headerForFinal;
            //loop through combined header and find the indexs for the overlap in the headpredicate vector

            for (unsigned int i = 0; i < currRule->getHeadPredicate()->getParameterVector().size(); i++) {
                for (unsigned int j = 0; j < firstRelation->getHeader()->getAttributes().size(); ++j) {
                    if (currRule->getHeadPredicate()->getParameterVector().at(i)->getToken() ==
                        firstRelation->getHeader()->getAttributes().at(j)) {
                        headerForFinal.push_back(j);
                    }
                }
            }
            firstRelation = firstRelation->project(headerForFinal);
            //now we need to convert the parameter vector of Head Predicate into a header
            //first convert predicates of headpredicate to a vector of strings
            //then convert the vector of strings into a header
//            vector<string> headPredTo;
//            for (int i = 0; i < currRule->getHeadPredicate()->getParameterVector().size(); i++) {
//                headPredTo.push_back(currRule->getHeadPredicate()->getParameterVector().at(i)->getToken());
//            }
            firstRelation->setName(currRule->getHeadPredicate()->getParameterType());
            //now we preform the union of this firstRelation and the database
            //what do I get my database relation off of?

            Relation *databaseRelation = theDatabase->getValue(firstRelation->getName());

            firstRelation = firstRelation->rename(databaseRelation->getHeader());

            if (databaseRelation->unionWithDatabase(firstRelation)) {

                moreTuplesToAdd = true;
                //databaseRelation = firstRelation;
                //output << databaseRelation->toStringForRules();
                //this outputs the things inside the relations and should only be run if it is updated
                //I dont think we want to print out the whole relation. I could be wrong though
                //output << toOutputIfRelationsWhereAdded;
            }else{
            }
        }
        //firstRelation = firstRelation->rename()
        //rename the relation to make it union-compatable
        //union with the relation in the database
        ++howManyTimesRules;
    }
    output << endl << "Schemes populated after " << howManyTimesRules << " passes through the Rules." << endl;

    return output.str();
}

string Interpreter::EvaluateAllQueries() {
    ostringstream output;

    //for each query
    for (unsigned int w = 0; w < theDatalogProgram->getQueries().size(); w++) {
        output << theDatalogProgram->getQueries().at(w)->predicateToString();
        output << EvaluatePredicate(*theDatalogProgram->getQueries().at(w))->toString();

    }
    return output.str();
}
