cmake_minimum_required(VERSION 3.10)
project(labev1_skel C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_libraries(-lsodium)

add_executable(server src/server.c src/tcp.c src/util.c)
add_executable(client src/client.c src/tcp.c src/util.c)
add_executable(keygen src/keygen.c src/crypto.c src/util.c)
add_executable(encrypt src/encrypt.c src/crypto.c src/util.c)
add_executable(decrypt src/decrypt.c src/crypto.c src/util.c)

include_directories(include)
