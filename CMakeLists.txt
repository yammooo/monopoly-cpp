set(CMAKE_CXX_STANDARD 11)
project(MonopolyCpp)
cmake_minimum_required(VERSION 3.0)

include_directories(include)

# add_library(${PROJECT_NAME} SHARED src/Book.cpp src/BookShelf.cpp src/Date.cpp)

add_executable(main src/main.cpp src/Client/GameClient.cpp src/Engine/GameProcessor.cpp src/Engine/GameRepository.cpp src/Engine/RandomContext.cpp src/Engine/GameContext.cpp src/ObjectModels/GameBoard.cpp src/ObjectModels/GameData.cpp src/ObjectModels/GameInfo.cpp src/ObjectModels/ActionInfo.cpp src/ObjectModels/PlayerData.cpp src/ObjectModels/Tile.cpp src/DependencyInjection/ServiceProvider.cpp src/ObjectModels/GameConfiguration.cpp "src/Client/Bot.cpp")
# target_link_libraries(main ${PROJECT_NAME})