file(GLOB SOURCES "*.h" "*.cpp")

target_sources(QtCryptarxis PRIVATE ${SOURCES})
target_link_libraries(QtCryptarxis PRIVATE givaro::givaro ethash::keccak)

target_sources(QtCryptarxis_test PRIVATE ${SOURCES})
target_link_libraries(QtCryptarxis_test PRIVATE givaro::givaro ethash::keccak)