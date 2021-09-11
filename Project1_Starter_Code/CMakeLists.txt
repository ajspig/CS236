cmake_minimum_required(VERSION 3.17)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)

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
        Token.h MatcherAutomaton.cpp MatcherAutomaton.h SchemesAutomaton.cpp SchemesAutomaton.h LeftParenAutomaton.cpp LeftParenAutomaton.h RightParenAutomaton.cpp RightParenAutomaton.h QMarkAutomaton.cpp QMarkAutomaton.h PeriodAutomaton.cpp PeriodAutomaton.h CommaAutomaton.cpp CommaAutomaton.h MultiplyAutomaton.cpp MultiplyAutomaton.h AddAutomaton.cpp AddAutomaton.h FactsAutomaton.cpp FactsAutomaton.h RulesAutomaton.cpp RulesAutomaton.h QueriesAutomaton.cpp QueriesAutomaton.h)
