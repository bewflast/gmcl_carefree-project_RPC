#include <GarrysMod/InterfacePointers.hpp>
#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/FactoryLoader.hpp>
#include <toolframework/ienginetool.h>
#include <edict.h>

#include "DRPC.h"
#include <iostream>
DRPC*			discord = nullptr;
CGlobalVars*	glob = nullptr;
server*			s_info = nullptr;
IEngineTool*	eng_tools = nullptr;

GMOD_MODULE_OPEN()
{
	SourceSDK::FactoryLoader	engine("engine");
	
	glob = InterfacePointers::GlobalVars();
	s_info = new server(10, glob->mapname.ToCStr(), "112312", 10);
	discord = new DRPC("990599027735281764", s_info);
	std::cout << "HERE";
	return (0);
}

GMOD_MODULE_CLOSE()
{

	return (0);
}