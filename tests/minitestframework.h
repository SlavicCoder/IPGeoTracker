#pragma once

#include <iostream>
#include <functional>
#include <string>

typedef std::function<void()> TestFunction;

struct TestCase {
    std::string name;
    TestFunction testFunction;
};

class TestSuite {
public:
    void addTest(const std::string& name, TestFunction testFunction) {
        testCases.push_back({name, testFunction});
    }

    void runTests() {
        for (const auto& testCase : testCases) {
            std::cout << "Running test: " << testCase.name << std::endl;
            testCase.testFunction();
        }
    }

private:
    std::vector<TestCase> testCases;
};
