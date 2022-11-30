set(EXECUTABE_NAME AllocationServer)

add_executable(${EXECUTABE_NAME}
    server.cpp
)

target_link_libraries(${EXECUTABE_NAME} ${LIBRARY_NAME} ${CONAN_LIBS})