set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
project(MonopolyCpp)
cmake_minimum_required(VERSION 3.0)

include_directories(include)

# Set -O2 option for Release builds only
if(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(-O2)
endif()

add_library(objectModels STATIC src/ObjectModels/GameConfiguration.cpp src/ObjectModels/GameBoard.cpp src/ObjectModels/GameData.cpp src/ObjectModels/GameInfo.cpp src/ObjectModels/ActionInfo.cpp src/ObjectModels/PlayerData.cpp src/ObjectModels/Tile.cpp src/ObjectModels/TurnManager.cpp)
add_library(dependencyInjection STATIC src/DependencyInjection/ServiceProvider.cpp)
add_library(client STATIC src/Client/GameClient.cpp src/Client/Bot.cpp src/Client/Player.cpp)
add_library(engine STATIC src/Engine/GameProcessor.cpp src/Engine/GameRepository.cpp src/Engine/RandomContext.cpp src/Engine/GameContext.cpp include/Engine/GameLogger.h)

add_executable(main src/main.cpp)

target_link_libraries(engine client dependencyInjection objectModels)
target_link_libraries(client engine dependencyInjection objectModels)
target_link_libraries(objectModels engine client dependencyInjection)

target_link_libraries(main engine client dependencyInjection objectModels)