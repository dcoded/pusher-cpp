#include <connection.hpp>

const std::vector<connection::state> connection::states = 
{
	{
		connection_state::INITIALIZED,
		connection_state::CONNECTING
	}
};