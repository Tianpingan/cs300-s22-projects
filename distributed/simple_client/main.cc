//
// Created by raghu on 12/30/19.
//

#include <iostream>

#include "simpleclient.h"
#include "simplegetcommand.h"
#include "simpleputcommand.h"
#include "simpleappendcommand.h"
#include "../repl/repl.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc == 1) {
        cerr << "usage: ./simple_client <shardkv1> <shardkv2> ... <shardkvN>\n";
        return 1;
    }
    vector<string> servers;
    for(int i = 1; i < argc; i ++) {
        servers.emplace_back(argv[i]);
    }

    SimpleClient client(servers);
    Repl repl;

    SimpleGetCommand gc(client);
    repl.AddCommand(gc);
    SimplePutCommand pc(client);
    repl.AddCommand(pc);
    SimpleAppendCommand ac(client);
    repl.AddCommand(ac);

    repl.Start();
}
