//
// Created by Student on 10/13/21.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include <Database.h>
#include <DatalogProgram.h>
#include <Relation.h>
#include <Header.h>
#include <Predicate.h>
//connects DatalogProgram and Database
class Interpreter {
private:
    DatalogProgram* theDatalogProgram; //stores DatalogProgram as data member

    Database* theDatabase = new Database(); //makes database using schemes and facts and stores as data member
public:
    Interpreter(DatalogProgram* datalogProgram) {
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
            //doesnt like this line
            theDatabase->getDatabase().at(nameOfConnectedRelation)->addTuple(tuple);
            //I think this might mean I try and at a tuple that doesnt have a key
            //add the tuple to the relation with the same name as the element
        }
        for (unsigned int i = 0; i < theDatalogProgram->getQueries().size(); i++) {
            //want IDValue that is the name
            //get the relation 'r' with the same name as the query 'q'
            string nameConnectedToRelation = theDatalogProgram->getQueries().at(i)->getParameterType();
            Relation *queryRelation  = theDatabase->getValue(nameConnectedToRelation);

            //select for each constant in query 'q'
            //queryRelation.select() //what do we pass in?

            //select for each pair of matching variables in 'q'
            //queryRelation.select() // other select

            //project using the positions of the variables in 'q'
            //queryRelation.project()

            //this is where I call my evaluatePredicate

            //print the resulting relation
            queryRelation->toString();
        }
    }
    string toString(){
        ostringstream output;
        //
        output << "cool";
        //how do I access the predicate.getStringOrID()
        return output.str();
    }
    Relation* evaluatePredicate(Predicate& p){
        Relation* relationConnectedToPredicate  = theDatabase->getValue(p.getParameterType());
        //we need to convert p.getParameterVector() to header
        //get the tuples or rows
        set<Tuple> rows = relationConnectedToPredicate->getTuples();
        for(const Tuple& t: rows){
            for(unsigned int i =0; i < t.getValues().size(); i++){
                //check if it is a constant
                if(t.getValues().at(i)[0] == '\''){
                    //do the select with int and int
                    relationConnectedToPredicate->select(i, t.getValues().at(i));
                }else{ //it is a variable
                    //have we seen this variable before?
                    //use map and its .find() function
                    map<string,Relation*>::iterator it = theDatabase->getDatabase().find(t.getValues().at(i));
                    if(it != theDatabase->getDatabase().end()){
                        //yes
                        //do a select (type 2)
                        //it->second;
                    }else {
                        //no
                        //mark it to keep for the project and rename
                        //== add it to a vector
                    }

                }
            }
        }
        //Relation* relationToReturn = new Relation(p.getParameterType(),p.getParameterVector());

        //vector<Parameter *> Predicate::getParameterVector()
        //Relation relationToReturn(name, header)
       //need to create an array of strings for the Header

       return relationConnectedToPredicate;
    }
    //have another function called EvaluateAllQueries. It will call evaluatePredicate
    //this will be my run function for interpreter, right?
    //it will use the algorithms given to me...
};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
