//
// Created by Abigail Spigarelli on 10/23/21.
//
#include "Interpreter.h"

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
        vector<Parameter *> newTuple = theDatalogProgram->getFacts().at(i)->getParameterVector(); //we want to convert this to the header
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

    Relation* Interpreter::EvaluatePredicate(Predicate &p) {
        Relation* relationConnectedToPredicate  = theDatabase->getValue(p.getParameterType());
        map<string, int> mapOfSeenVar;
        vector<string> listOfVar;

        for(unsigned int i =0; i < p.getParameterVector().size(); i++){
            Parameter* currPara = p.getParameterVector().at(i);
                //check if it is a constant
                if(currPara->getToken().at(0) == '\''){
                    //do the select with int and string

                    relationConnectedToPredicate = relationConnectedToPredicate->select(i,currPara->getToken());
                    //this returns a new relation pointer
                }else{ //it is a variable

                    auto it = mapOfSeenVar.find(currPara->getToken());
                    if(it != mapOfSeenVar.end()){
                        vector <string> headerAttr = relationConnectedToPredicate->getHeader()->getAttributes();
                        //the first index will be where we saw the variable first
                        relationConnectedToPredicate = relationConnectedToPredicate->select(it->second, i ); //do a select int int

                    }else {
                        mapOfSeenVar.insert(pair<string, int>(currPara->getToken(),i));
                        listOfVar.push_back(currPara->getToken());
                    }

                }
            }
        vector <int> indexForProject;
        for(unsigned int i =0; i < listOfVar.size(); i++){
            //should I create a new vector of all the indexs of when I saw my variables that are lined up with
            //find the value in the map that lines up with the current value in keepTrackOfLastSeenVariable
            indexForProject.push_back(mapOfSeenVar.find(listOfVar.at(i))->second);
            //project each column we have saved
            //we need to build a vector to pass into project of the new column names
            //is this where we check if they correspond to our header names?
            //if they dont match up with our header names then we call rename
            //relationConnectedToPredicate.p
        }
        relationConnectedToPredicate = relationConnectedToPredicate->project(indexForProject);
        //now we need to create the header for our project
        //reassign the relation pointer to the new relations each time
        Header* renameHeader = new Header(listOfVar);
        relationConnectedToPredicate = relationConnectedToPredicate->rename(renameHeader);

        //preform project and rename based of teh variables in the map
        //then try to do the rename function

        //vector<Parameter *> Predicate::getParameterVector()
        //Relation relationToReturn(name, header)
        //need to create an array of strings for the Header

        return relationConnectedToPredicate;
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
