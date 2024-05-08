//
// Created by Artthau on 06.05.2024.
//

#include "TestClass.h"
#include <iostream>
#include <string>

void TestClass::saveNumber(int number) {
    this->number = number;
}

void TestClass::saySomething(std::string text) {
    std::cout << text << std::endl;
}

int TestClass::giveNumber() {
    return number;
}