file(GLOB SOURCES "*.h" "*.cpp")

target_sources(QtCryptarxis PRIVATE ${SOURCES})
target_link_libraries(QtCryptarxis PRIVATE OpenSSL::Crypto  ${CMAKE_DL_LIBS})

target_sources(QtCryptarxis_test PRIVATE ${SOURCES})
target_link_libraries(QtCryptarxis_test PRIVATE OpenSSL::Crypto  ${CMAKE_DL_LIBS})