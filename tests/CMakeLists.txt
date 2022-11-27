set(EXECUTABE_NAME ChatingRoomTester)

add_executable(${EXECUTABE_NAME}
    test_main.cpp
    src/test_session.cpp

    src/test_async_tcp.cpp
    src/tcp_server.cpp
    src/tcp_connection.cpp

    # common
    src/common/day_time_string.cpp
)

target_link_libraries(${EXECUTABE_NAME} ${LIBRARY_NAME} ${CONAN_LIBS})