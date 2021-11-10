//
// Created by Abigail Spigarelli on 9/22/21.
//

#include <sstream>
#include "Rule.h"

Rule::Rule(Predicate *headPreddy, vector<Predicate *> bodyPreddy) {
    headPredicate = headPreddy;
    listOfPredicateBody = bodyPreddy;
}

string Rule::ruleToString(){
    ostringstream output;
    output << headPredicate->getParameterType() << "(" << headPredicate->predicateToStringForRules() <<")";
    output << " :- ";
    for(unsigned int i=0; i < listOfPredicateBody.size(); ++i){
        output << listOfPredicateBody.at(i)->getParameterType() << "(" <<
        listOfPredicateBody.at(i)->predicateToStringForRules() << ")";
        if(i!=listOfPredicateBody.size()-1){
            output << ",";
        }

    }
    output << "." << endl;
    return output.str();
}

Predicate* Rule::getHeadPredicate() {
    return headPredicate;
}
vector<Predicate*> Rule::getRightPredicate() {
    return listOfPredicateBody;
}
void Rule::setHeadPredicate(string idVal, vector <Parameter*> headPred) {
    headPredicate = new Predicate(idVal, headPred);

}
