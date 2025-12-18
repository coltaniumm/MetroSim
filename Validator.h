#pragma once
#include <string>

class Validator {
public:
    static int getIntInRange(int minVal, int maxVal, const std::string& prompt);
    static int getNonNegativeInt(const std::string& prompt);

   
    static void waitForEnter();
};
