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