#include "DRPC.h"


void DRPC::init()
{

	this->handler	=	new DiscordEventHandlers();
	this->presence	=	new DiscordRichPresence();

	memset(this->handler,	0, sizeof(DiscordEventHandlers));
	memset(this->presence,	0, sizeof(DiscordRichPresence));

	Discord_Initialize(this->cid, this->handler, 1, nullptr);

	this->update();

}


void DRPC::update()
{

	Discord_ClearPresence();

	this->presence->buttons[0].label	=	"Присоединяйся!";
	this->presence->buttons[0].url		=	(std::string("steam://connect/") + this->server_info->ip_port).c_str();

	this->presence->buttons[1].label	=	"Discord-сервер";
	this->presence->buttons[1].url		=	"https://discord.gg/8J658BTBT7";

	this->presence->details				=	this->server_info->serverName;
	this->presence->startTimestamp		=	this->server_info->when_connected;

	this->presence->largeImageKey		=	"logo";
	this->presence->largeImageText		=	"Sandbox-сервер";
	this->presence->state				=	("Игроков: " + std::to_string(this->server_info->playersCount) + "/" + std::to_string(this->server_info->maxPlayers)).c_str();

	Discord_UpdatePresence(this->presence);

}


DRPC::DRPC(const char* cID, server* server_info)
{

	this->cid			=	cID;
    this->server_info	=	server_info;
	this->init();

}
