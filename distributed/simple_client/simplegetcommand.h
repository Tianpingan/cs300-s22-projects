//
// Created by raghu on 1/1/20.
//

#ifndef SHARDING_SIMPLEGETCOMMAND_H
#define SHARDING_SIMPLEGETCOMMAND_H


#include "../repl/regexcommand.h"
#include "simpleclient.h"

class SimpleGetCommand : public RegexCommand {
public:
    // matches: get <key>
    explicit SimpleGetCommand(SimpleClient& cl) : RegexCommand("get .+"), client(cl) {}
    void Handle(const std::string& line) override;
    void PrintHelpMessage() override;
private:
    SimpleClient& client;
};


#endif //SHARDING_SIMPLEGETCOMMAND_H
