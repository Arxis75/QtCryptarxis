file(GLOB SOURCES "*.h" "*.cpp")

target_sources(QtCryptarxis PUBLIC ${SOURCES})
target_sources(QtCryptarxis_test PUBLIC ${SOURCES})