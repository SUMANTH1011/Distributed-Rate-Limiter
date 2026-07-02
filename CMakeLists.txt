cmake_minimum_required(VERSION 3.20)

project(DistributedRateLimiter)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Crow CONFIG REQUIRED)
find_package(redis++ CONFIG REQUIRED)
find_package(hiredis CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/main.cpp"
)

message(STATUS "========== SOURCE FILES ==========")
foreach(src ${SOURCES})
    message(STATUS "${src}")
endforeach()

add_executable(DistributedRateLimiter
    ${SOURCES}
)

target_include_directories(DistributedRateLimiter PRIVATE
    ${PROJECT_SOURCE_DIR}
)

if(TARGET redis++::redis++)
    set(REDIS_TARGET redis++::redis++)
elseif(TARGET redis++::redis++_static)
    set(REDIS_TARGET redis++::redis++_static)
else()
    message(FATAL_ERROR "redis++ target not found")
endif()

target_link_libraries(DistributedRateLimiter PRIVATE
    Crow::Crow
    ${REDIS_TARGET}
    hiredis::hiredis
    nlohmann_json::nlohmann_json
)

if(WIN32)
    target_compile_definitions(DistributedRateLimiter PRIVATE
        _WIN32_WINNT=0x0A00
    )
endif()