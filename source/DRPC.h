#ifndef DRPC_H
#define DRPC_H

# include <discord_register.h>
# include <discord_rpc.h>

# include <ctime>
# include <string>

# define UNICODE


typedef struct s_server_info 
{

	const char*		serverName;
	const char*		ip_port;
	time_t			when_connected;
	int				maxPlayers;
	int				playersCount;

	s_server_info(int mp, const char* sn, const char* i_p, int pc) : maxPlayers(mp), serverName(sn), ip_port(i_p), playersCount(pc), when_connected(std::time(nullptr)) {} 

} server;


class DRPC
{
	private:
		DiscordEventHandlers	*handler;
		DiscordRichPresence*	presence;
		const char*				cid;

	public:
		DRPC(const char* cID, server* server_info);
		server*					server_info;
		void					init();
		void					update();
};

#endif 