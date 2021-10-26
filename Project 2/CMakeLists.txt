cmake_minimum_required(VERSION 3.16)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")


include_directories(.)

add_executable(Project1_Starter_Code
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h MatcherAutomaton.cpp MatcherAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h LeftParenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h QMarkAutomaton.cpp QMarkAutomaton.h PeriodAutomaton.cpp PeriodAutomaton.h CommaAutomaton.cpp CommaAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h IDAutomaton.cpp IDAutomaton.h StringAutomaton.cpp StringAutomaton.h CommentAutomaton.cpp CommentAutomaton.h Parser.cpp Parser.h DatalogProgram.cpp DatalogProgram.h Predicate.cpp Predicate.h Rule.cpp Rule.h Parameter.cpp Parameter.h Tuple.h Header.h Relation.cpp Relation.h Database.cpp Database.h Interpreter.h Interpreter.cpp)
