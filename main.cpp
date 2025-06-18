#include "Command_Handler.h"
#include "MyString.h"
#include <iostream>
#include <string>

int main() 
{
    Command_Handler command_handler;
    std::cout << "Enter command:\n";

    while (true) 
    {
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line);

        try 
        {
            command_handler.handle(MyString(line.c_str()));
        }
        catch (const std::invalid_argument& e) 
        {
            std::cout << e.what() << std::endl;
        }
        catch (const std::runtime_error& e) 
        {
            std::cout << e.what() << std::endl;
        }
        catch (...) 
        {
            std::cout << "Unknown error occurred." << std::endl;
        }
    }
    return 0;
}