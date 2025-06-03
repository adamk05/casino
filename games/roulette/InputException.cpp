//
// Created by kamil on 26/05/25.
//

#include "InputException.h"

InputException::InputException(const std::string &message): message(message) {}

const char* InputException::what() const noexcept {
    return message.c_str();
}
