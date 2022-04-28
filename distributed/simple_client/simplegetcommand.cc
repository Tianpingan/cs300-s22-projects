//
// Created by raghu on 1/1/20.
//

#include "simplegetcommand.h"
#include "../common/common.h"

using namespace std;

void SimpleGetCommand::Handle(const std::string &line) {
    vector<string> tokens = split(line);
    assert(tokens.size() == 2);
    string key = tokens[1];
    client.Get(key);
}

void SimpleGetCommand::PrintHelpMessage() {
    std::cout << "get <key>\nretrieves the value associated with <key>, prints an error if the key is not found\n";
}
