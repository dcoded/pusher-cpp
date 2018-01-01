#pragma once
#include <functional>
#include <string>
#include <vector>

#include "connection_state.hpp"
#include "event_emitter.hpp"
#include "json.hpp"
#include "fsm/state_machine.hpp"
#include "fsm/cond/if_not.hpp"
#include "fsm/cond/if_all.hpp"
#include "fsm/cond/if_any.hpp"

class connection : public event_emitter
				 , public fsm::state_machine <connection_state>
{
	using state = fsm::state_machine<connection_state>::state;
	const static std::vector<state> states;

	//public: virtual connection_state state() const = 0;
	public: explicit connection()
	:	fsm::state_machine <connection_state>(
		connection_state::INITIALIZED, states)
	{}

	public: virtual void connect(const std::string endpoint) = 0;
	public: virtual void disconnect() = 0;

	// public: virtual void write(json data) = 0;
};


class nop_connection : public connection
{
	using connection::connection;
	public: virtual void connect(const std::string endpoint) {}
	public: virtual void disconnect() {}
};