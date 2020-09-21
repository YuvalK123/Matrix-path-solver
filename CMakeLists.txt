cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 main.cpp Server.h ClientHandler.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp
        MyTestClientHandler.h Solver.h CacheManager.h FileCacheManager.cpp FileCacheManager.h StringReverser.cpp
        StringReverser.h MyParallelServer.cpp MyParallelServer.h classes.h dfs.h bfs.h astar.h State.h Searcher.cpp
        Searcher.h Searchable.cpp Searchable.h ObjectAdapter.h MyClientHandler.cpp MyClientHandler.h bestFirstSearch.h
        Point.h tmp.h minHeap.h boot.h)