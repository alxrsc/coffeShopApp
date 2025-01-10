cmake_minimum_required(VERSION 3.29)
project(coffeeShopApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(coffeeShopApp main.cpp
        Classes/Barista.h
        Classes/Barista.cpp
        Classes/Client.h
        Classes/Client.cpp
        Classes/Employee.h
        Classes/Employee.cpp
        Classes/Manager.h
        Classes/Manager.cpp
        Classes/Server.h
        Classes/Server.cpp
        Utils/CSVHandler.h
        Utils/CSVHandler.cpp
        Utils/Utils.cpp)
