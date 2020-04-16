#include <gtest/gtest.h>
#include <iostream>
#include "IDTypes.hpp"
#include "Match.hpp"
#include "Rule.hpp"
#include "Set.hpp"

using namespace SetReplace;

TEST(SetReplace, gtest_works) {
    std::cout << "Hi SetReplace" << std::endl;
}

TEST(SetReplace, createSet) {
    // Negative atoms refer to patterns (useful for rules)
    std::vector<Rule> rules;
    auto a_rule = Rule({
            {{-1,-2}},
            {{-1,-3}, {-4, -2}}
            });
    rules.push_back(a_rule);

    std::vector<AtomsVector> initialExpressions = {{1,2}};
    std::cout << "initialExpressions" << std::endl;
    for (auto & av : initialExpressions) {
        for(auto & a: av) {
            std::cout << a << "," ;
        }
        std::cout << std::endl;
    }


    Matcher::OrderingSpec orderingSpec = {
        {Matcher::OrderingFunction::SortedExpressionIDs,
            Matcher::OrderingDirection::Normal},
        {Matcher::OrderingFunction::ReverseSortedExpressionIDs,
            Matcher::OrderingDirection::Normal},
        {Matcher::OrderingFunction::ExpressionIDs,
            Matcher::OrderingDirection::Normal},
        {Matcher::OrderingFunction::RuleID,
            Matcher::OrderingDirection::Normal}};
    unsigned int randomSeed = 0;
    auto a_set = Set(rules, initialExpressions, orderingSpec, randomSeed);

    auto shouldAbort = [](){return false;};
    Set::StepSpecification stepSpec;
    stepSpec.maxEvents = 10;
    stepSpec.maxGenerationsLocal = 100;
    stepSpec.maxFinalAtoms = 100000;
    stepSpec.maxFinalAtomDegree = 100000;
    stepSpec.maxFinalExpressions = 100000;
    EXPECT_TRUE(a_set.replace(stepSpec, shouldAbort));
    auto expressions = a_set.expressions();
    size_t counter = 0;
    for(auto exp : expressions) {
        std::cout << "Generation: "<< counter << std::endl;
        for(auto & a : exp.atoms) {
            std::cout << a << ",";
        }
        std::cout << std::endl;
        counter++;
    }
    auto reason = a_set.terminationReason();
    std::cout << "TerminationReason: " << static_cast<int>(reason) << std::endl;
    auto max_generation = a_set.maxCompleteGeneration(shouldAbort);
    std::cout << "MaxCompleteGeneration: " << max_generation << std::endl;

}
