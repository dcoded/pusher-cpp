cmake_minimum_required (VERSION 3.0)

cmake_policy (SET CMP0042 NEW)
cmake_policy (SET CMP0002 OLD)

project (pusher-cpp)

    set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    set (CMAKE_CXX_FLAGS "-std=c++1y -Wno-deprecated-declarations")
    set (CMAKE_BUILD_TYPE Debug)


    set (Boost_USE_STATIC_LIBS    OFF) 
    set (Boost_USE_MULTITHREADED  ON)  
    set (Boost_USE_STATIC_RUNTIME OFF) 
    find_package (Boost 1.60 COMPONENTS system thread REQUIRED) 
    find_package (OpenSSL)
    find_package (ZLIB)
    find_package (UV)

    set (PROJECT_SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/src)
    set (PROJECT_LIBS_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include 
        ${Boost_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIRS}
        ${UV_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIRS})

    # include_directories ("${PROJECT_BINARY_DIR}")
    include_directories ("${PROJECT_INCLUDE_DIR}")

    file (GLOB_RECURSE PROJECT_SOURCES 
        "${PROJECT_SOURCE_DIR}/*.cpp" 
        "${PROJECT_SOURCE_DIR}/*.cc" 
        "${PROJECT_SOURCE_DIR}/*.c")

    file (GLOB_RECURSE PROJECT_LIBS
        "${PROJECT_LIBS_DIR}/*.so"
        "${PROJECT_LIBS_DIR}/*.a")

    # add_library (${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
    add_executable (${PROJECT_NAME} ${PROJECT_SOURCES})

    target_include_directories (${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})
    target_link_libraries      (${PROJECT_NAME} ${PROJECT_LIBS}
        ${Boost_LIBRARIES} 
        ${OPENSSL_LIBRARIES} 
        ${UV_LIBRARIES}
        ${ZLIB_LIBRARIES})