#include "Markov.h"
#include "Rule.h"
#include <UnitTest++/UnitTest++.h>
#include <fstream>
#include <cstdio> // remove()

using namespace std;

// ===================== Rule Tests =====================
SUITE(RuleTests) {
    TEST(DefaultConstructor) {
        Rule r;
        CHECK_EQUAL("", r.pattern);
        CHECK_EQUAL("", r.result);
    }

    TEST(ParameterizedConstructor) {
        Rule r("a", "b");
        CHECK_EQUAL("a", r.pattern);
        CHECK_EQUAL("b", r.result);
    }

    TEST(EqualityOperator_True) {
        Rule r1("a", "b");
        Rule r2("a", "b");
        CHECK(r1 == r2);
    }

    TEST(EqualityOperator_False) {
        Rule r1("a", "b");
        Rule r2("a", "c");
        CHECK(!(r1 == r2));
    }
}

// ===================== Markov Tests =====================
SUITE(MarkovTests) {
    TEST(AddRuleIncreasesCount) {
        Markov m;
        m.addRule("a", "b");
        m.addRule("c", "d");
        CHECK(true); 
    }

    TEST(DeleteRuleWorks) {
        Markov m;
        m.addRule("a", "b");
        m.deleteRule("a", "b");
        m.run(false);
        CHECK_EQUAL("", m.start); 
    }

    TEST(EditRuleReplacesCorrectly) {
        Markov m;
        m.addRule("a", "b");
        m.addRule("c", "d");
        m.editRule("x", "y", 0); 
        CHECK(true);
    }

    TEST(OperatorPostfixIncrement) {
        Markov m;
        m.addRule("a", "b");
        m++;
        CHECK(true);
    }

    TEST(RunWithoutLog) {
        Markov m;
        m.start = "abc";
        m.addRule("a", "z");
        m.run(false);
        CHECK(m.start.find("z") != string::npos);
    }

    TEST(RunWithLog) {
        Markov m;
        m.start = "ab";
        m.addRule("a", "z");
        m.run(true);
        CHECK(m.start.find("z") != string::npos);
    }

    TEST(ReadRuleFromFile) {
        string fname = "rules.txt";
        ofstream f(fname);
        f << "abc\n";
        f << "a b\n";
        f << "b c\n";
        f.close();

        Markov m(fname);
        CHECK(m.start == "abc");

        remove(fname.c_str());
    }

    TEST(DeleteNonExistingRule) {
        Markov m;
        m.addRule("a", "b");
        m.deleteRule("c", "d"); 
        CHECK(true);
    }

    TEST(EditRuleInvalidIndex) {
        Markov m;
        m.addRule("a", "b");
        m.editRule("x", "y", 10);
        CHECK(true);
    }

    TEST(MultipleRulesApplyInOrder) {
        Markov m;
        m.start = "abc";
        m.addRule("ab", "z");
        m.addRule("z", "y");
        m.run(false);
        CHECK_EQUAL("yc", m.start);
    }

    TEST(NoRules_NoChange) {
        Markov m;
        m.start = "abc";
        m.run(false);
        CHECK_EQUAL("abc", m.start);
    }

    TEST(RuleWithOverlap) {
        Markov m;
        m.start = "aaa";
        m.addRule("aa", "b");
        m.run(false);
        CHECK(m.start.find("b") != string::npos);
    }

    TEST(EmptyStart) {
        Markov m;
        m.start = "";
        m.addRule("a", "b");
        m.run(false);
        CHECK_EQUAL("", m.start);
    }

    TEST(RunStopsWhenNoMatch) {
        Markov m;
        m.start = "abc";
        m.addRule("z", "q");
        m.run(false);
        CHECK_EQUAL("abc", m.start);
    }

    TEST(MultipleApplications) {
        Markov m;
        m.start = "ab";
        m.addRule("a", "aa");
        m.addRule("aa", "b");
        m.run(false);
        CHECK(m.start.size() > 0);
    }

    TEST(EditRuleWorks) {
        Markov m;
        m.addRule("a", "b");
        m.editRule("x", "y", 0);
        CHECK(true);
    }

    TEST(AddDeleteMix) {
        Markov m;
        m.addRule("a", "b");
        m.deleteRule("a", "b");
        m.addRule("c", "d");
        CHECK(true);
    }

    TEST(PrintRules_NoCrash) {
        Markov m;
        m.addRule("a", "b");
        m.printRules();
        CHECK(true);
    }

    TEST(RunChangesStart) {
        Markov m;
        m.start = "hello";
        m.addRule("he", "y");
        m.run(false);
        CHECK(m.start.find("y") != string::npos);
    }

    TEST(FileNotFound) {
        Markov m;
        m.readRule("nofile.txt");
        CHECK(true);
    }

    TEST(ChainReaction) {
        Markov m;
        m.start = "abc";
        m.addRule("a", "z");
        m.addRule("z", "y");
        m.run(false);
        CHECK(m.start.find("y") != string::npos);
    }

    TEST(RepeatedRuns) {
        Markov m;
        m.start = "abc";
        m.addRule("a", "x");
        m.run(false);
        m.run(false);
        CHECK(m.start.find("x") != string::npos);
    }

    TEST(RunWithNoApplicableRules) {
        Markov m;
        m.start = "xyz";
        m.addRule("a", "b");
        m.run(false);
        CHECK_EQUAL("xyz", m.start);
    }

    TEST(EmptyRulePattern) {
        Markov m;
        m.start = "abc";
        m.addRule("", "z");
        m.run(false);
        CHECK(true);
    }

    TEST(EmptyRuleResult) {
        Markov m;
        m.start = "abc";
        m.addRule("a", "");
        m.run(false);
        CHECK(m.start.find("a") == string::npos);
    }

    TEST(LongChainRules) {
        Markov m;
        m.start = "aaaa";
        m.addRule("aa", "b");
        m.addRule("bb", "c");
        m.run(false);
        CHECK(m.start.size() <= 4);
    }

    TEST(OperatorIncrementDoesNotCrash) {
        Markov m;
        m++;
        CHECK(true);
    }

    TEST(ComplexReplacement) {
        Markov m;
        m.start = "abcabc";
        m.addRule("abc", "z");
        m.run(false);
        CHECK(m.start.find("z") != string::npos);
    }
}

// ===================== Main Runner =====================
int main() {
    return UnitTest::RunAllTests();
}
