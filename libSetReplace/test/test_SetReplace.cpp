#include <gtest/gtest.h>
#include <iostream>
#include "IDTypes.hpp"
#include "Match.hpp"
#include "Rule.hpp"
#include "Set.hpp"
#include "SetReplaceIO.hpp"

using namespace SetReplace;
auto & os = std::cout;

TEST(SetReplace, gtest_works) {
    os << "Hi SetReplace" << std::endl;
}

TEST(SetReplace, createSet) {
    // Negative atoms refer to patterns (useful for rules)
    std::vector<Rule> rules;
    auto a_rule = Rule({
            {{-1,-2}, {-2, -3}},
            {{-1,-3}, {-4, -2}, {-1, -4}}
            });
    rules.push_back(a_rule);

    std::vector<AtomsVector> initialExpressions = {{1,2},{2, 3}};
    os << "initialExpressions" << std::endl;
    print(initialExpressions, os);

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
    stepSpec.maxEvents = 100;
    stepSpec.maxGenerationsLocal = 100;
    stepSpec.maxFinalAtoms = 100000;
    stepSpec.maxFinalAtomDegree = 100000;
    stepSpec.maxFinalExpressions = 100000;
    os << "StepSpecification:\n";
    print(stepSpec, os);
    EXPECT_TRUE(a_set.replace(stepSpec, shouldAbort));
    auto expressions = a_set.expressions();
    for(auto exp : expressions) {
        print(exp, os);
        os << "---" << std::endl;
    }
    auto reason = a_set.terminationReason();
    os << "TerminationReason: "; print(reason, os);
    auto max_generation = a_set.maxCompleteGeneration(shouldAbort);
    os << "MaxCompleteGeneration: " << max_generation << std::endl;

}
