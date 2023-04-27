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

    if (CheckLua(L, luaL_dofile(L, "video_example.lua")))
    {
        lua_getglobal(L, "GetPlayer");
        if (lua_isfunction(L, -1))
        {
            lua_pushnumber(L, 1);

            // lua_pcall - number of inputs, number of outputs, error handling
            if (CheckLua(L, lua_pcall(L, 1, 1, 0)))
            {
                if (lua_istable(L, -1))
                {
                    lua_pushstring(L, "Name");
                    lua_gettable(L, -2);
                    player.name = lua_tostring(L, -1);
                    lua_pop(L, 1);

                    lua_pushstring(L, "Family");
                    lua_gettable(L, -2);
                    player.family = lua_tostring(L, -1);
                    lua_pop(L, 1);

                    lua_pushstring(L, "Title");
                    lua_gettable(L, -2);
                    player.title = lua_tostring(L, -1);
                    lua_pop(L, 1);

                    lua_pushstring(L, "Level");
                    lua_gettable(L, -2);
                    player.level = lua_tointeger(L, -1);
                    lua_pop(L, 1);

                    std::cout
                        << "player.title = " << player.title
                        << " player.name = " << player.name
                        << " player.family = " << player.family
                        << " player.level = " << player.level
                        << std::endl;
                }
            }
        }
    }

    system("pause");
    lua_close(L);

    return EXIT_SUCCESS;
}
