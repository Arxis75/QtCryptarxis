file(GLOB SOURCES "*.h" "*.cpp")

target_sources(QtCryptarxis PUBLIC ${SOURCES})
target_link_libraries(QtCryptarxis PUBLIC OpenSSL::Crypto)

target_sources(QtCryptarxis_test PUBLIC ${SOURCES})
target_link_libraries(QtCryptarxis_test PUBLIC OpenSSL::Crypto)