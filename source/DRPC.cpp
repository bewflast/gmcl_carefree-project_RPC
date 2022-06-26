#include "DRPC.h"

void DRPC::init()
{
	this->handler = new DiscordEventHandlers();
	this->presence = new DiscordRichPresence();
	Discord_Initialize(this->cid, this->handler, NULL, NULL);

    this->presence->state = this->server_info->serverName;
    this->presence->startTimestamp = std::time(nullptr);
	this->update();
}

void DRPC::update()
{
    this->presence->details = ((std::string)"Игроков: " + std::to_string(this->server_info->playersCount)  + (std::string)"/" + std::to_string(this->server_info->maxPlayers)).c_str();
	Discord_UpdatePresence(this->presence);
}

DRPC::DRPC(const char* cID, server* server_info)
{
	this->cid = cID;
    this->server_info = server_info;
	this->init();
}