cmake_minimum_required(VERSION 3.16)
project(TanksGame)

set(CMAKE_CXX_STANDARD 17)

set(SFML_ROOT "C:/SFML-2.6.2")
set(SFML_STATIC_LIBRARIES FALSE)

include_directories(${SFML_ROOT}/include)

link_directories(${SFML_ROOT}/lib)

add_executable(TanksGame main.cpp
        models/managers/GameManager.cpp
        models/managers/Renderer.cpp
        models/managers/TanksGame.cpp
        models/factories/tanks/EnemyTankFactory.cpp
        models/factories/tanks/PlayerTankFactory.cpp
        models/entities/Map.cpp
        models/entities/Block.cpp
        models/entities/tanks/PlayerTank.cpp
        models/entities/tanks/ITank.cpp
        models/entities/tanks/EnemyTank.cpp
        models/entities/Projectile.cpp)

target_link_libraries(TanksGame
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
)

if(WIN32)
    add_custom_command(TARGET TanksGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_ROOT}/bin"
            $<TARGET_FILE_DIR:TanksGame>
            COMMENT "Copying SFML 2.6.2 DLLs to output directory")
endif()

#find_package(glm REQUIRED)
#target_link_libraries(TanksGame glm::glm)
