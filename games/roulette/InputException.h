//
// Created by kamil on 26/05/25.
//

#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H
#include <exception>
#include <string>

/*
 * A class representing exception made by user input
 */
class InputException : public std::exception {
public:
    /*
     * constructor
     * @param message - exception message
     */
    InputException(const std::string& message);

    /*
     * returns a message from the exception
     */
    const char* what() const noexcept;

private:
    /*
     * A message of the exception
     */
    const std::string message;
};



#endif //INPUTEXCEPTION_H
