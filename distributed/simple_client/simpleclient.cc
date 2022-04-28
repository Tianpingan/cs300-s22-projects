//
// Created by raghu on 12/30/19.
//

#include <iostream>

#include "simpleclient.h"
#include "../build/shardkv.grpc.pb.h"

using namespace std;

void SimpleClient::logError(const std::string &from, const grpc::Status &status) {
    assert(!status.ok());
    std::cerr << "method " << from << " failed with status code "
              << status.error_code() << "\nthe error message was: " << status.error_message() << "\n";
}

void SimpleClient::Get(const std::string &key) {
    unsigned int key_id = (unsigned int)extractID(key);
    int serverIdx = key_id % servers.size();
    const string& addr = servers[serverIdx];
    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    auto stub = Shardkv::NewStub(channel);

    ::grpc::ClientContext cc;
    GetRequest req;
    GetResponse res;
    req.set_key(key);

    auto status = stub->Get(&cc, req, &res);
    if(status.ok()) {
        cout << "Get returned: " << res.data() << "\n";
    } else {
        logError("Get", status);
    }
}

void SimpleClient::Delete(const std::string &key) {
    unsigned int key_id = (unsigned int)extractID(key);
    int serverIdx = key_id % servers.size();
    const string& addr = servers[serverIdx];
    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    auto stub = Shardkv::NewStub(channel);

    ::grpc::ClientContext cc;
    DeleteRequest req;
    Empty res;
    req.set_key(key);

    auto status = stub->Delete(&cc, req, &res);
    if(status.ok()) {
        cout << "Delete Completed" << "\n";
    } else {
        logError("Delete", status);
    }
}

void SimpleClient::Put(const std::string &key, const std::string &value, const std::string &user_id) {
    unsigned int key_id = (unsigned int)extractID(key);
    int serverIdx = key_id % servers.size();
    const string& addr = servers[serverIdx];
    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    auto stub = Shardkv::NewStub(channel);

    ::grpc::ClientContext cc;
    PutRequest req;
    Empty res;
    req.set_key(key);
    req.set_data(value);
    req.set_user(user_id);

    auto status = stub->Put(&cc, req, &res);
    if(!status.ok()) {
        logError("Put", status);
    }
}

void SimpleClient::Append(const std::string& key, const std::string& value){
    unsigned int key_id = (unsigned int)extractID(key);
    int serverIdx = key_id % servers.size();
    const string& addr = servers[serverIdx];
    auto channel = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    auto stub = Shardkv::NewStub(channel);

    ::grpc::ClientContext cc;
    AppendRequest req;
    Empty res;
    req.set_key(key);
    req.set_data(value);

    auto status = stub->Append(&cc, req, &res);
    if(!status.ok()) {
        logError("Append", status);
    }
}
