#pragma once
#include <string>
#include <unordered_set>

class ArgumentParser {
public:
    // Initialize an ArgumentParser for an executable with name `program_name`
    ArgumentParser(std::string program_name);

    // Adds a boolean command line argument -- convention is a dash, and then a character
    // example: -e
    void addFlag(std::string flag, std::string description);

    // Adds an option command line argument that takes an additional parameter
    // example: -c 20
    // example: --input-file myfile.txt
    void addOption(std::string option, std::string parameter, std::string description);

    // Returns a detected option's parameter as a string after processArgs() is called.
    // If not detected, returns the empty string
    std::string getOption(std::string name);

    // Returns a detected flag as a bool after processArgs is called.
    // If not detected, returns false
    bool getFlag(std::string name);

    // Return vertex file and edge file
    std::string getVertexFile();
    std::string getEdgeFile();

    // Display the valid options to pass into 
    void display();

    // Process the arguments, returns true if successful. If unsuccessful, returns false.
    bool processArgs(int argc, char* argv[]);

    // Return argc
    int count();
private:
    std::unordered_map<std::string, std::string> option_descriptions_;
    std::unordered_map<std::string, std::string> option_parameters_;
    std::unordered_map<std::string, std::string> option_values_;
    std::unordered_map<std::string, std::string> flag_descriptions_;
    std::unordered_set<std::string> flag_values_;
    std::string program_name_;
    std::string vertexFile_;
    std::string edgeFile_;
    int count_ = 0;
};
