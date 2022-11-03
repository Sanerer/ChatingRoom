set(EXECUTABE_NAME ChatingRoomTester)

add_executable(${EXECUTABE_NAME} test_main.cpp)

target_link_libraries(${EXECUTABE_NAME} ${LIBRARY_NAME} ${CONAN_LIBS})