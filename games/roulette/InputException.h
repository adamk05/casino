//
// Created by kamil on 26/05/25.
//

#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H
#include <exception>
#include <string>

// a class for exceptions caused by user input
class InputException : public std::exception {
public:
    // a constructor
    InputException(const std::string& message);

    // returns the exception message
    const char* what() const noexcept;

private:
    // a message for the exception
    const std::string message;
};



#endif //INPUTEXCEPTION_H
