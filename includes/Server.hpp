#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
# define MAX_CLIENTS 10 



#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

// add for othmane

#include <map>
#include "Channel.hpp"

#include <stdlib.h>
#include <netdb.h>       // getnameinfo, NI_MAXHOST
#include <sys/socket.h>  // sockaddr, sockaddr_storage
#include <netinet/in.h>  // sockaddr_in, sockaddr_in6
#include <arpa/inet.h>   // AF_INET, AF_INET6

class Client;
extern int g_num_fds;

void sendError(int fd, const std::string& msg);
bool isalpha_string(std::string str);

class Server {
	private:
		int server_Fd;                    // Server socket fd
		int port;                        // Port number
		std::string password;            // Server password
		char buffer[512];       // Buffer for incoming data
		struct pollfd _fds[MAX_CLIENTS];  // Poll array
		// int _numFds;                      // Number of active fds
		std::map<std::string, Channel*> _channels;

	public:
		Server();
		Server(const Server& other);
		Server& operator=(const Server& other);
		Server(int port, std::string password);
		~Server();
	
	Client* clients[MAX_CLIENTS];    // Array of client pointers
	
	// Core server functions
	void start();                     // Main server loop
	void setupSocket();               // socket() + bind() + listen()
	void accept_NewClient();           // accept() new connection
	void handle_ClientData(int index); // Process client messages
	// void removeClient(int index);     // Disconnect and cleanup
	
	// Message handling
	// void processCommand(Client* client, std::string message);
	// void broadcastToChannel(std::string channelName, std::string message, Client* sender);
	void processCommand(int index, std::string &message);
	
	// Utilities
	Client* getClientByNick(std::string nickname);
	bool isNicknameTaken(std::string nickname, int excludeIndex);
	bool check_passok(std::string command, std::string argument, int index);
	bool check_authentication(std::string command, std::string argument, int index);

	// for add channel
	#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <iostream>
#include <set>
#include "Client.hpp"
#include <string>
class Channel {
	private:
		std::string _name;
		std::set<Client*> _users;
	public:
		Channel();
		Channel(const std::string& name);
		Channel(const Channel& other);
		Channel& operator=(const Channel& other);
		~Channel();
		// getters/setters...

		void addUser(Client *client);
		void removeUser(Client *client);
		bool hasUser(Client *Client) const;

		const std::string& getName() const;
		const std::set<Client*>& getUsers() const;

		void broadcast(const std::string& message, Client* exclude);


};
#endif
};


#endif