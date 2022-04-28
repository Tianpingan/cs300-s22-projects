//
// Created by raghu on 12/30/19.
//

#ifndef SHARDING_SIMPLECLIENT_H
#define SHARDING_SIMPLECLIENT_H

#include <grpcpp/grpcpp.h>
#include <vector>
#include <string>
#include <google/protobuf/empty.pb.h>
#include "../common/common.h"


class SimpleClient {
    using Empty = google::protobuf::Empty;
public:
    explicit SimpleClient(std::vector<std::string> v): servers(std::move(v)) {};

    // support get, put, append
    void Get(const std::string& key);

    void Delete(const std::string& key);

    void Put(const std::string& key, const std::string& value, const std::string& user_id);

    void Append(const std::string& key, const std::string& value);

private:
    void logError(const std::string& from, const grpc::Status& status);

    const std::vector<std::string> servers;
};


#endif //SHARDING_SIMPLECLIENT_H
