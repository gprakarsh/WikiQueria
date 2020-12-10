#include <string>
#include <iostream>
#include <unordered_map>
#include "ArgumentParser.h"

ArgumentParser::ArgumentParser(std::string program_name) {
    /* nothing */
    program_name_ = program_name;
}

void ArgumentParser::addFlag(std::string flag, std::string description) {
    flag_descriptions_.insert({flag, description});
}

void ArgumentParser::addOption(std::string option, std::string parameter, std::string description) {
    option_descriptions_.insert({option, description});
    option_values_.insert({option, ""});
    option_parameters_.insert({option, parameter});
}

std::string ArgumentParser::getOption(std::string name) {
    return option_values_.at(name);
}

bool ArgumentParser::getFlag(std::string name) {
    return (flag_values_.find(name) != flag_values_.end());
}

void ArgumentParser::display() {
    std::cout << "Usage: ./" << program_name_ << " [ARGS] vertex-file edge-file"<< '\n';
    std::cout << "Arguments:" << '\n';
    for (auto pair : option_descriptions_) {
        std::cout << "  " << pair.first << ' ' << option_parameters_.at(pair.first) << " : " << pair.second << '\n';
    }
    for (auto pair : flag_descriptions_) {
        std::cout << "  " << pair.first << " : " << pair.second << '\n';
    }
}

bool ArgumentParser::processArgs(int argc, char* argv[]) {
    count_ = argc;
    bool filesFound = false;
    // The first argument is the program name, which is trivial for us
    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if (option_values_.find(arg) != option_values_.end()) {
            option_values_.at(arg) = std::string(argv[i+1]);
            i++;
        } else if (flag_descriptions_.find(arg) != flag_descriptions_.end()) {
            flag_values_.insert(arg);
        } else {
            if (i + 1 < argc) {
                vertexFile_ = std::string(argv[i]);
                edgeFile_ = std::string(argv[i+1]);
                filesFound = true;
            }
        }
    }
    if (!filesFound) {
        std::cout << "Please enter a vertex file and edge file." << '\n';
        return false;
    }
    return true;
}

std::string ArgumentParser::getVertexFile() {
    return vertexFile_;
}

std::string ArgumentParser::getEdgeFile() {
    return edgeFile_;
}

int ArgumentParser::count() {
    return count_;
}
