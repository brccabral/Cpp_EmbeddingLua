#include <iostream>
#include <string>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#ifdef _WIN32
#pragma comment(lib, "lua53.lib")
#endif

// Little error checking utility function
bool CheckLua(lua_State *L, int r)
{
    if (r != LUA_OK)
    {
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
    return true;
}

int lua_HostFunction(lua_State *L)
{
    // this funtion will be called by Lua

    float a = (float)lua_tonumber(L, 1);
    float b = (float)lua_tonumber(L, 2);
    std::cout << "[C++] HostFunction(" << a << ", " << b << ") called." << std::endl;
    float c = a * b;
    lua_pushnumber(L, c);

    return 1; // * number of values the Lua function will return
}

int main()
{
    struct Player
    {
        std::string title;
        std::string name;
        std::string family;
        int level;
    } player;

    lua_State *L = luaL_newstate();

    // * tell Lua to add standard libraries (like math)
    luaL_openlibs(L);

    // tell Lua that HostFunction in Lua is lua_HostFunction in C++
    lua_register(L, "HostFunction", lua_HostFunction);

    if (CheckLua(L, luaL_dofile(L, "video_example.lua")))
    {
        lua_getglobal(L, "DoAThing");
        if (lua_isfunction(L, -1))
        {
            lua_pushnumber(L, 5.0f);
            lua_pushnumber(L, 6.0f);

            // lua_pcall - number of inputs, number of outputs, error handling
            if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
            {
                std::cout << "[C++] Called in Lua 'DoAThing(5.0f, 6.0f)' got " << (float)lua_tonumber(L, -1) << std::endl;
            }
        }
    }

    system("pause");
    lua_close(L);

    return EXIT_SUCCESS;
}
