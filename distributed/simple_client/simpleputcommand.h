//
// Created by raghu on 1/1/20.
//

#ifndef SHARDING_SIMPLEPUTCOMMAND_H
#define SHARDING_SIMPLEPUTCOMMAND_H


#include "../repl/regexcommand.h"
#include "simpleclient.h"

class SimplePutCommand : public RegexCommand {
public:
    // match: put <key> <value>
    explicit SimplePutCommand(SimpleClient& cl) : RegexCommand("put .+"), client(cl) {}
    void Handle(const std::string& line) override;
    void PrintHelpMessage() override;
private:
    SimpleClient& client;
};


#endif //SHARDING_SIMPLEPUTCOMMAND_H
