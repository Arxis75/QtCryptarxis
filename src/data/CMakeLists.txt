file(GLOB SOURCES "*.h" "*.cpp")

target_sources(QtCryptarxis PUBLIC ${SOURCES})
target_link_libraries(QtCryptarxis PUBLIC givaro::givaro ethash::keccak)