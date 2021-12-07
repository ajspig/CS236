//
// Created by Abigail Spigarelli on 10/23/21.
//
#include "Interpreter.h"
#include "graph.h"
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
    ostringstream output;
    cout << "Dependency Graph" << endl;
    map<int, set<int>> mapOfHeadPredicates;
    //first key is the number of the rule
    set<int> emptyEdgesForDeclaringTheMap;
    //I think I will need to make an empty set and insert that into with my key
    // I will add the values to my set later
    //create a vector of bools the same size as my rules and initialize them all to false
    vector<bool> marker;
    for (unsigned int i = 0; i < theDatalogProgram->getRules().size(); i++) {
        bool nodeMarker = false;
        //add each head predicate with the empty set into my map
        mapOfHeadPredicates.insert ( pair<int, set<int>>(i, emptyEdgesForDeclaringTheMap) );
        marker.push_back(nodeMarker);
    }

    graph forwardGraph(mapOfHeadPredicates);
    graph reverseGraph(mapOfHeadPredicates);


    for (unsigned int i = 0; i < theDatalogProgram->getRules().size(); i++) {
        //for rule_i in rules:
        //    head_name = rule_i.head.name
        string headName = theDatalogProgram->getRules().at(i)->getHeadPredicate()->getParameterType();
        for (unsigned int j = 0; j < theDatalogProgram->getRules().size(); j++) {
            //    for rule_j in rules:
            //        for body_pred in rule_j.body:
            for(unsigned int fun = 0; fun < theDatalogProgram->getRules().at(j)->getRightPredicate().size(); fun++){
                //            if body_pred.name == head_name:
                if(theDatalogProgram->getRules().at(j)->getRightPredicate().at(fun)->getParameterType() == headName){
                    //rule_j depends on rule_i
                    forwardGraph.addEdge(j,i);
                    //so I should add that to dependency graph
                    //and also put it in the inverse so that rule_i depends on rule_j
                        //thats right, right?
                    reverseGraph.addEdge(i,j);
                    break;
                }
            }
        }
    }
    //print out the rule evaluation
    cout << forwardGraph.toString() << endl;

    //now we need to change our rule evaluation based off our graphs

    cout <<"Rule Evaluation" << endl;

    //run my Depth first search forest on my reverse.graph to get post-order
    for(unsigned int i = 0; i < reverseGraph.getMapOfEdges().size(); ++i) {//for key in map
        if(!marker.at(i)){ //if ! visited
            reverseGraph.DFS(i,reverseGraph.getMapOfEdges().find(i)->second, marker); //DFS(key)
        }
    }

    stack<int> postOrder = reverseGraph.getPostOrder();
    for(unsigned int i =0; i < marker.size(); i++){
        marker.at(i) = false;
    }

    //SCC
    vector<set<int>> ForestOfSCC;

    while(!postOrder.empty()){
        set<int> currentSCC;
        if(!marker.at(postOrder.top())){ //if ! visited
            currentSCC = forwardGraph.DFSWithSCC(postOrder.top(), marker);
            //run DFS on node that returns a SCC
            //strongly connected component
        }
        //add the returned SCC to the vector
        if(!currentSCC.empty()) {
            ForestOfSCC.push_back(currentSCC);
        }
        postOrder.pop();
    }
    ///////////////////////////////////////////////////////////////////////////////////////////
    // now we are going to loop through all my ForestOfSCC
    // and for each I will loop through everything in my SCCs
    for (unsigned int i = 0; i < ForestOfSCC.size(); i++) {
        set<int> index = ForestOfSCC.at(i);
        cout << "SCC: ";
        unsigned int increment =0;
        for(int rule : index) {
            increment++;
            cout << "R" << rule;
            if(increment<index.size() ){
                cout << ',';
            }

        }
        cout <<endl;
        //for(int rule: index){
        bool moreTuplesToAdd = true;
        howManyTimesRules =0;
        while(moreTuplesToAdd) {
            ++howManyTimesRules;
            moreTuplesToAdd = false;
            for(int rule: index){

                Rule *currRule = theDatalogProgram->getRules().at(rule);
                cout << currRule->ruleToString();

                Predicate *firstPred = currRule->getRightPredicate().at(0);
                Relation *firstRelation = EvaluatePredicate(*firstPred);

                for (unsigned int p = 1; p < currRule->getRightPredicate().size(); p++) {
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

                for (unsigned int f = 0; f < currRule->getHeadPredicate()->getParameterVector().size(); f++) {
                    for (unsigned int k = 0; k < firstRelation->getHeader()->getAttributes().size(); ++k) {
                        if (currRule->getHeadPredicate()->getParameterVector().at(f)->getToken() ==
                            firstRelation->getHeader()->getAttributes().at(k)) {
                            headerForFinal.push_back(k);
                        }
                    }
                }
                firstRelation = firstRelation->project(headerForFinal);

                firstRelation->setName(currRule->getHeadPredicate()->getParameterType());

                Relation *databaseRelation = theDatabase->getValue(firstRelation->getName());

                firstRelation = firstRelation->rename(databaseRelation->getHeader());

                if (databaseRelation->unionWithDatabase(firstRelation)) {
                    //if it is a SCC that depends on itself or it has more then one dependency use the fixed point algorithm
                    moreTuplesToAdd = true;
                }
                map<int, set<int>> mapToCheck = forwardGraph.getMapOfEdges();
                set<int>::iterator it = mapToCheck.at(rule).find(rule);
                //if((index.size() == 1) && (*it != rule)){
                if((index.size() == 1) && (it == mapToCheck.at(rule).end())){
                    moreTuplesToAdd = false;
                    //we need to chek our dependency graph to make sure it doesnt depend on itself

                }
////////////////////////////////////////////////////////////////////////////////////////////////

            }
            //evaluate the rules and print out the newly create tuples like I did in project 4
            //print out the iteratiosn that ti took fro that SCC

            //if my index is only of size one that means I should only run my Rule Evaluation once
            // if index >1
            // evaluate rules with in SCC in Numerical Order
        }
        cout << howManyTimesRules << " passes: ";
        increment = 0;
        for(int rule : index) {
            increment++;
            cout << "R" << rule;
            if (increment < index.size()) {
                cout << ',';
            }
        }
        cout << endl;
            //figure out how to print out all of the rules
            // I am thinking another for loop?

    }

        //evaluate the rules in each component

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
