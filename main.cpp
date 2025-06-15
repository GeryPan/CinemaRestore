// Kino_Restore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
﻿#include "Command_Handler.h"
#include <iostream>
#include <string>

int main() {
    try {
        Command_Handler handler;
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error catched." << std::endl;
    }
    Command_Handler handler;
    std::string line;

    std::cout << " Type command:\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        try {
            handler.handle(line);
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Unknown error catched." << std::endl;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
