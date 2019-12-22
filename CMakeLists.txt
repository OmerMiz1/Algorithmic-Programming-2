cmake_minimum_required(VERSION 3.15)
project(AlgorithmicProgrammingProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(AlgorithmicProgrammingProject main.cpp Lexer.cpp Lexer.h Parser.cpp Parser.h Command.h ConditionParser.cpp ConditionParser.h IfCommand.cpp IfCommand.h LoopCommand.cpp LoopCommand.h OpenServerCommand.cpp OpenServerCommand.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h FuncCommand.cpp FuncCommand.h Print.h MapManager.cpp MapManager.h Var.h Sleep.h)