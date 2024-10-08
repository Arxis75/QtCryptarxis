file(GLOB SOURCES "*.h" "*.cpp")

target_sources(QtCryptarxis PUBLIC ${SOURCES})
target_link_libraries(QtCryptarxis PUBLIC givaro::givaro ethash::keccak)

target_sources(QtCryptarxis_test PUBLIC ${SOURCES})
target_link_libraries(QtCryptarxis_test PUBLIC givaro::givaro ethash::keccak)