set(PROJECT_SOURCES main.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtCryptarxis MANUAL_FINALIZATION ${PROJECT_SOURCES})
    qt_finalize_executable(QtCryptarxis)
else()
    add_executable(QtCryptarxis ${PROJECT_SOURCES})
endif()

#Defines the root folder(s) for all targets
target_include_directories(QtCryptarxis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/UI)
target_include_directories(QtCryptarxis_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(QtCryptarxis PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_subdirectory(data)
add_subdirectory(crypto)
#add_subdirectory(eth)
#add_subdirectory(UI)