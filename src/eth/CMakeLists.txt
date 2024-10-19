file(GLOB SOURCES "*.h" "*.cpp")

target_sources(QtCryptarxis PRIVATE ${SOURCES})
target_sources(QtCryptarxis_test PRIVATE ${SOURCES})