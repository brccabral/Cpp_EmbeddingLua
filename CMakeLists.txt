cmake_minimum_required(VERSION 3.21.2)
project(EmbedLua)

include(GNUInstallDirs)

message("LUA_DIR ${LUA_DIR}")
message("CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")
message("CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR}")
message("CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")

include_directories("${LUA_DIR}/include")
link_directories("${LUA_DIR}")

add_executable(embed_lua embed_lua.cpp)
install(TARGETS embed_lua)

if(WIN32)
install(FILES 
"${LUA_DIR}/lua53.dll"
DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")

add_custom_command(TARGET embed_lua POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${LUA_DIR}/lua53.dll" "${CMAKE_CURRENT_BINARY_DIR}/lua53.dll"
)
else()
link_libraries(lua53)
install(FILES 
    "${LUA_DIR}/liblua53.so"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")

add_custom_command(TARGET embed_lua POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${LUA_DIR}/liblua53.so" "${CMAKE_CURRENT_BINARY_DIR}/liblua53.so"
)
endif()

install(FILES 
    "video_example.lua"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")

add_custom_command(TARGET embed_lua POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "../video_example.lua" "${CMAKE_CURRENT_BINARY_DIR}/video_example.lua"
)