#pragma once
#include "NPCManager.h"
#include <iostream>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

static int lua_add_npc(lua_State* L)
{
	const char* name{ lua_tostring(L, 1) };
	NPCManager::GetInstance().AddNPC(name);
	return 0;	// This is the number of stuff we return in the lua stack
}

static int lua_remove_npc(lua_State* L)
{
	const char* name{ lua_tostring(L, 1) };
	NPCManager::GetInstance().RemoveNPC(name);
	return 0;
}

int main()
{
	lua_State* L{ luaL_newstate() };
	luaL_openlibs(L);

	lua_register(L, "addNPC", lua_add_npc);
	lua_register(L, "removeNPC", lua_remove_npc);

	if (luaL_loadfile(L, "startup.lub") != LUA_OK)
	{
		std::cerr << "Error loading or running script: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}

	NPCManager::GetInstance().Dump();

	lua_close(L);
	return 0;
}