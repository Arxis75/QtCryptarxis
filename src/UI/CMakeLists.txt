file(GLOB SOURCES "*.h" "*.cpp" "*.ui")

target_sources(QtCryptarxis PRIVATE ${SOURCES})
target_link_libraries(QtCryptarxis PRIVATE Qt::Gui)
