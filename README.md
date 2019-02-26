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


To build you need to execute command "git sumbodule update" to fetch https://github.com/Microsoft/GSL.
You need to install cmake from https://cmake.org/install/.
Than you need to build boost library. You can do whatever you want, I personally use Qt Creator with mingw compilier.
After mingw installation, I added path "D:\Qt\Qt5.12.1\Tools\mingw730_64\bin" to envirement variable, went to toolset/boost and executee commands " bootstrap" and ".\b2 toolset=gcc" to build libraries.
