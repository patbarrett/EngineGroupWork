#ifndef SCRIPT_H
#define SCRIPT_H

#pragma once

#include <iostream>
#include <string>
#include "lua.hpp"
#pragma comment(lib, "lua5.1.lib")


class Script
{

	private:
		lua_State *luaState;

	public:
		Script();
		Script(std::string scriptfile);
		virtual ~Script();
		
		bool loadScript(std::string scriptfile);

		void registerFunction(std::string _functionName, lua_CFunction _func);
		void invokeFunction(std::string _name);

		std::string getGlobalString(std::string name);
		void setGlobalString(std::string name, std::string value);
		
		double getGlobalNumber(std::string name);
		void setGlobalNumber(std::string name, double value);
		
		bool getGlobalBoolean(std::string name);
		void setGlobalBoolean(std::string name, bool value);
		
		void runFunction(std::string name);
};

#endif