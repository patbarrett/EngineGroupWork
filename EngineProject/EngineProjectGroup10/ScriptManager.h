#ifndef LUAMGR_H
#define LUAMGR_H

#pragma once
#pragma comment(lib, "lua5.1.lib")

#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <vector>
#include "Script.h"
#include "lua.hpp"


using namespace std;

class ScriptManager
{
public:
	ScriptManager(void);
	~ScriptManager(void);
	void Initialize();
	void Update(float dt);
	void addScript(string _name, Script* _script);
	Script* getScript(string _name);

private:
	map<string, Script*> scripts;
};
#endif