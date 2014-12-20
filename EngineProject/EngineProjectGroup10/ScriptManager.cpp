#include "ScriptManager.h"

ScriptManager::ScriptManager(void)
{
}

ScriptManager::~ScriptManager(void)
{
}

void ScriptManager::Initialize()
{

}

void ScriptManager::addScript(string _name, Script* _script)
{
	scripts[_name] = _script;
}

Script* ScriptManager::getScript(string _name)
{
	return scripts[_name];
}