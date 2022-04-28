//
// Created by raghu on 1/1/20.
//

#ifndef SHARDING_SIMPLEAPPENDCOMMAND_H
#define SHARDING_SIMPLEAPPENDCOMMAND_H

#include "../repl/regexcommand.h"
#include "simpleclient.h"

class SimpleAppendCommand : public RegexCommand {
public:
    // match: append <key> <value>
    explicit SimpleAppendCommand(SimpleClient& cl) : RegexCommand("append .+"), client(cl) {}
    void Handle(const std::string& line) override;
    void PrintHelpMessage() override;
private:
    SimpleClient& client;
};


#endif //SHARDING_SIMPLEAPPENDCOMMAND_H
