cmake_minimum_required(VERSION 3.10)
project(pw-mgr C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(.)
include_directories(hash)
include_directories(crypto)
include_directories(store)

add_executable(pw-mgr main.c hash/hash.c hash/argon2.c hash/blake2b.c hash/core.c hash/encoding.c hash/opt.c hash/thread.c crypt/crypt.c store/store.c store/parson.c)

