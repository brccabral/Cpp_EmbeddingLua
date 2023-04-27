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

int main()
{
    // std::string cmd = "a = 7 + 11";
    // std::string cmd = "a = 7 + 11asas"; // ERROR

    std::string cmd = "a = 7 + 11 + math.sin(23.7)";

    lua_State *L = luaL_newstate();

    // * tell Lua to add standard libraries (like math)
    luaL_openlibs(L);

    if (CheckLua(L, luaL_dostring(L, cmd.c_str())))
    {
        lua_getglobal(L, "a");
        if (lua_isnumber(L, -1))
        {
            float a_in_cpp = (float)lua_tonumber(L, -1);
            std::cout << "a_in_cpp = " << a_in_cpp << std::endl;
        }
    }

    system("pause");
    lua_close(L);

    return EXIT_SUCCESS;
}
