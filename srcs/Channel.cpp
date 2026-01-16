#include "Channel.hpp"
#include "Client.hpp"
#include <unistd.h>


	Channel::Channel(const std::string& name):_name(name)
	{}

	void Channel::addUser(Client *client)
	{
		if(!client)
		{
			return;
		}
		if(_users.find(client) != _users.end())
		{
			return;
		}
		_users.insert(client);
		client->addChannel(this);
	}

void Channel::removeUser(Client *client)
{
	if(!client)
		{
			return;
		}
		auto it = _users.find(client);
		if(it != _users.end()) 
		{
			_users.erase(it);
			client->removeChannel(this);
		}
}
void Channel::broadcast(const std::string& message, Client* exclude)
{	
	for(Client* client :_users)
	{
		if(client == exclude)
		{
			continue;
		};
		send(client->get_fd(),message.c_str(),message.size(),0);
	}
}

const std::string& Channel::getName() const {
	return _name;
}
const std::set<Client*>& Channel::getUsers() const 
{
return _users;
}
