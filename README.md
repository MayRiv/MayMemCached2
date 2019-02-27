# MayCachedv2
MayMemCached v2.0

Improved version of https://github.com/MayRiv/MayMemcached.
Goal is to create simplified version of memcached service, that supports command get, set (optional expires time), delete, version, log to educate myself. 
It should be written in a way to support different protocols - simple text, json, maybe protobuf.
It should support in-memory storage and LLV techology storage.
It should support replication with one master-writter and several slaves-readers.
Everything should be configurable.
Technologies that were used - CMake, GTest, Boost.Asio.


Right now it supports basic command with following syntax:
GET <id> - gets value by key if existing, otherwise the answer will EMPTY ;
SET <id> <value> <optional seconds> - sets value by key. It's possible to set time to expire. ; 
DEL <id> - removes value from memory, removes corresponding timeMarker. ;
STOP - shuts down the application

Currently, all the values are stored just in memory,  there is only simple text protocol support, there is not replication logic, the project is not configurable.

How to build?
1. Apply command "git submodule init" and "git submodule update" to fetch https://github.com/Microsoft/GSL

Now the hard part is to get Boost running.
If you are using Linux, you can just "sudo apt-get install libboost-all-dev", enjoy you life and chill.
If you are using Windows, the journy begins
1) Download Boost library from https://www.boost.org/users/download/
2) Unpack it to folder "/toolset/boost_1_67_0"
3) Go the folder, and apply "bootstrap", "b2" from Developer Command Prompt Visual Studio if you want to compile library with Visual Studio compilier.
Why don't use mingw compilier? I coudn't made it compile ".lib" libraries instead of ".a".
4a) Go get CMake extension for Visual Studio.
5a) Use this extension to open the project. For me, this extension works badly and does not allow to navigate through code, so I abadoned Visual Studio.
4b) Go get Qt Creator
5b) Set up Kit with Visual Studio compiliers.
6b) It will not work with default CMake generator, so I used Ninja from (https://ninja-build.org/)
7b) Add path to Ninja to your Path in envirement variables. I also added qt creator tools bin directory as well.
8b) Now you can build & launch the application, but you have no debuger. Who needs it these days? (Me)
Also, these approach does not allow me to build unit tests, I will fix it eventually.
