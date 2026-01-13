#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <iostream>
#include <set>
#include "Client.hpp"

class Client;
class Channel {
	private:
		std::string _name;
		std::set<Client*> user;
	public:
		Channel();
		Channel(const std::string& name);
		Channel(const Channel& other);
		Channel& operator=(const Channel& other);
		~Channel();
		
		// getters/setters...
};
#endif