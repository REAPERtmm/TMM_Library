# TMM_Library

## Projects Libraries
- TMM_Setup         => A Central point to every libs
- TMM_Collection    => for data structure
- TMM_Debugger      => a debugger for console, window and logs
- TMM_Files         => file manipulation
- TMM_Maths         => vectors, matrices, etc...
- TMM_Functional    => encapsulation for any callable (function, lambda, methods, etc...)
- TMM_UI            => various implementation with unique graphic API (ex. SFML)
- TMM_Audio         => (WORK IN PROGRESS) audio manipulation
- TMM_AI            => (WORK IN PROGRESS) State Machine and deep learning

## How to import ?

The various project are in the Projects folder.
You have to know :
- They have various dependecies between themself.
- They all depends on TMM_Setup

Each project have some REQUIRED dependencies and some NOT REQUIRED dependencies but if you dont get the NOT REQUIRED ones, there will be missing feature corresponding to the missing projects.

So if you want any Projects, simply copy paste the folders somwhere and use the add_subdirectory("TMM_...") with a taget_include_library(${PROJECT_NAME} PRIVATE TMM_..._LIB) to add them to a project 

## Dependecies Table
