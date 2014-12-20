#include "Script.h"

Script::~Script()
{
	lua_close(luaState);	
}

Script::Script()
{
	luaState = lua_open();
	luaL_openlibs(luaState);
}

Script::Script(std::string scriptfile)
{
	Script();
	loadScript(scriptfile);
}

bool Script::loadScript(std::string scriptfile)
{
	try {
		luaL_dofile(luaState, scriptfile.c_str());
	}
	catch(...) {
		return false;
	}
	return true;
}

void Script::registerFunction(std::string _functionName, lua_CFunction _func)
{
	lua_register(luaState, _functionName.c_str(), _func);
}

void Script::invokeFunction(std::string _name)
{
	lua_getglobal(luaState, _name.c_str());
	lua_call(luaState, 0, 0);
}

std::string Script::getGlobalString(std::string name)
{
	std::string value = "";
	try {
		lua_getglobal(luaState, name.c_str());
		value = lua_tostring(luaState, -1);
		lua_pop(luaState, 1);
	}
	catch(...) {
	}
	return value;
}

void Script::setGlobalString(std::string name, std::string value)
{
	lua_pushstring(luaState, value.c_str());
	lua_setglobal(luaState, name.c_str());
}

double Script::getGlobalNumber(std::string name)
{
	double value = 0.0;
	try {
		lua_getglobal(luaState, name.c_str());
		value = lua_tonumber(luaState, -1);
		lua_pop(luaState, 1);
	}
	catch(...) { 
	}
	return value;
}

void Script::setGlobalNumber(std::string name, double value)
{
	lua_pushnumber(luaState, (int)value);
	lua_setglobal(luaState, name.c_str());
}

bool Script::getGlobalBoolean(std::string name)
{
	bool value = 0;
	try {
		lua_getglobal(luaState, name.c_str());
		value = (bool) lua_toboolean(luaState, -1);
		lua_pop(luaState, 1);
	}
	catch(...) { 
	}
	return value;
}   

void Script::setGlobalBoolean(std::string name, bool value)
{
	lua_pushboolean(luaState, (int)value);
	lua_setglobal(luaState, name.c_str());
}