# include <GarrysMod/Lua/Interface.h>
# include <GarrysMod/InterfacePointers.hpp>

# include <cdll_int.h>
# include <inetchannelinfo.h>

# include "DRPC.h"


namespace globals
{
    static DRPC*                        discord         =   nullptr;
    static server*                      s_info          =   nullptr;
    static IVEngineClient*              engine_client   =   nullptr;
    static GarrysMod::Lua::ILuaBase*    Lua             =   nullptr;
}

const char* GetHostName()
{
    const char* hostname;

    globals::Lua->GetField(GarrysMod::Lua::INDEX_GLOBAL, "GetHostName");
        globals::Lua->Call(0, 1);
        hostname = globals::Lua->GetString(-1);
    globals::Lua->Pop(1);
   
    return (hostname);
}

int	GetPlayersCount()
{

    int players(0);

    globals::Lua->GetField(GarrysMod::Lua::INDEX_GLOBAL, "player");
    globals::Lua->GetField(-1, "GetCount");
        globals::Lua->Call(0, 1);
        players = (int)globals::Lua->GetNumber(-1);
    globals::Lua->Pop(2);

    return (players);

}


LUA_FUNCTION(UpdateRPC)
{

    globals::discord->server_info->serverName   = GetHostName();
    globals::discord->server_info->playersCount = GetPlayersCount();
    
    globals::discord->update();

    return (0);

}


GMOD_MODULE_OPEN()
{

    globals::Lua = LUA;
    globals::engine_client = InterfacePointers::VEngineClient();

    globals::s_info = new server(globals::engine_client->GetMaxClients(), "Carefree SBOX", globals::engine_client->GetNetChannelInfo()->GetAddress(), GetPlayersCount());
    globals::discord = new DRPC("990599027735281764", globals::s_info);

    globals::discord->update();

    globals::Lua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);

    globals::Lua->PushCFunction(UpdateRPC);
    globals::Lua->SetField(-2, "RPC_Update");

    globals::Lua->Pop();

    return (0);

}


GMOD_MODULE_CLOSE()
{

    Discord_Shutdown();
    delete globals::discord;
    delete globals::s_info;
    globals::discord = nullptr;
    globals::s_info = nullptr;


    return (0);

}
