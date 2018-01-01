#include <pusher.hpp>


bool event_emitter::key::operator()(const key& a, const key& b)
{
	return (a.listener < b.listener &&
			a.event_name < b.event_name); 
}


void event_emitter::bind(const std::string event_name, listener_type& fn)
{
	listener_type* ptr = &fn;
	boost::signals2::connection connection;

	connection = signals_[event_name].connect(fn);
	key index  = { ptr, event_name };
	connections_[index] = connection;
}

void event_emitter::bind_all(listener_type fn)
{
	for (auto it = signals_.begin(); it != signals_.end(); it++)
	{
		bind(it->first, fn);
	}
}

void event_emitter::unbind(const std::string event_name, listener_type& fn)
{
	listener_type* ptr = &fn;
	boost::signals2::connection connection;

	key index  = { ptr, event_name };
	connection = connections_[index];	
	connections_.erase(index);
	signals_[event_name].disconnect(connection);
}

void event_emitter::unbind_all(listener_type fn)
{
	for (auto it = signals_.begin(); it != signals_.end(); it++)
	{
		unbind(it->first, fn);
	}
}