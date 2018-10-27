# MayCachedv2
MayMemCached v2.0

Improved version of https://github.com/MayRiv/MayMemcached.
Goal is to create simplified version of memcached service, that supports coomand get, set (optional expires time), delete, version, log and  to educate myself. 
It should be written in a way to support different protocols - simple text(Examples will be added), json, maybe protobuf.
It should support in-memory storage and LLV techology storage.
It should support replication with one master-writter and several slaves-readers.
Everything should be configurable.
Technologies that were used - CMake, GTest, Boost.Asio.
