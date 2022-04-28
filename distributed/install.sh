#!/bin/bash

# update
sudo apt-get update

# install grpc
sudo apt install -y libgrpc++-dev

# install protobuf
sudo apt install -y protobuf-compiler
sudo apt install -y libprotobuf-dev
sudo apt-get install -y protobuf-compiler-grpc

# install package config
sudo apt install -y pkg-config

cd build
mkdir common_dir
mkdir config_dir
mkdir integrated_tests
mkdir shardkv_dir
mkdir shardkv_tests
mkdir shardmaster_dir
mkdir shardmaster_tests
mkdir simple_shardkv_dir
mkdir simple_shardkv_tests
mkdir client_dir
mkdir simple_client_dir
mkdir repl_dir
mkdir test_utils
cd ..
