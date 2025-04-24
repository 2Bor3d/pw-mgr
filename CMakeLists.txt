cmake_minimum_required(VERSION 3.10)
project(pw-mgr C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(argon2)

add_executable(pw-mgr test-argon.c argon2/argon2.c argon2/argon2.h argon2/blake2b.c argon2/argon2.h argon2/core.c argon2/encoding.c argon2/opt.c argon2/thread.c)

