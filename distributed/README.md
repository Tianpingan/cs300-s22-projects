Project 6: Distributed Store
============================

In this project, you will build the infrastructure for a small social network. In particular, you will work on a distributed, sharded key-value store that stores the social graph and user information for the social network.

# How to Run:

Run `./install.sh` to install gRPC and its dependencies.

To build your code, run `make` from inside the build directory.

To test you code, run `./test.sh` or `make check` inside the build directory.

## Running the frontend

Inside the course container, after making all of the executables, start up a shardmaster on port 9095, shardkv servers, and a client in separate terminals.

```
./shardmaster 9095

./client <SHARDMASTER_HOST> 9095

./shardkv <PORT> <SHARDMASTER_HOST> 9095
```

Start as many shardkv servers as you would like and add them using the client's `join` command (e.g. `join <SHARDMASTER_HOST>:<PORT>`). You can verify that they've been added using the client's `query` command.
The shardmaster host name will be printed after starting up the shardmaster -- this is should be the ID of the cs300 docker container.

Outside of the course container, navigate to this directory and run `docker compose up`. The Bacefook UI should be now viewable at http://localhost:3000 in your browser!

Note: In order for the frontend to work correctly, you must enter `user_<NUM>` and `post_<NUM>` in the user/post ID fields where NUM is between 0 and 1000.

<!-- TODO: Fill this out. -->
## Design Overview:

## Collaborators:

## Conceptual Questions:

## Extra Credit Attempted:

## How long did it take to complete Distributed Store?
