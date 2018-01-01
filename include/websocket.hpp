// #pragma once
// #include <uWS/uWS.h>

// #include "fsm/state_machine.hpp"
// #include "fsm/cond/if_not.hpp"
// #include "fsm/cond/if_all.hpp"
// #include "fsm/cond/if_any.hpp"

// #include "connection.hpp"
// #include "json.hpp"

// class websocket : public connection {
// 	using WebSocket = uWS::WebSocket<uWS::CLIENT>;
// 	using OpCode    = uWS::OpCode;
// 	using json      = nlohmann::json;

// 	private: fsm::state_machine	<connection_state> fsm_;
// 	private: connection_state state_;
// 	private: uWS::Hub hub_;

// 	private: std::string endpoint_ = "";

// 	private: bool connected_ = false;
// 	private: bool disconnect_ = false;

// 	public: explicit websocket()
// 	:	fsm_ 
// 	{
// 		connection_state::INITIALIZED,
// 		// Given a supported browser and functioning internet connection, the 
// 		// following states are expected:

// 		// initialized -> connecting -> connected

// 		// Temporary failure of the Pusher connection will cause
// 		// connected -> connecting -> connected

// 		// If an internet connection disappears
// 		// connected -> connecting -> unavailable (after ~ 30s)

// 		// When the internet connection becomes available again
// 		// unavailable -> connected

// 		// In the case that Pusher is not supported:
// 		// initialized -> failed
// 		{
// 			{
// 				connection_state::INITIALIZED,
// 				connection_state::INITIALIZED,
// 				[] () {},
// 				if_not(boost::bind(&websocket::endpoint_defined, this))
// 			},

// 			{
// 				connection_state::INITIALIZED,
// 				connection_state::CONNECTING,
// 				boost::bind(&websocket::connect, this),
// 				if_any(boost::bind(&websocket::endpoint_defined, this))
// 			},

// 			{
// 				connection_state::CONNECTING,
// 				connection_state::CONNECTED,
// 				[] () {},
// 				if_any(boost::bind(&websocket::connected, this))
// 			},

// 			{
// 				connection_state::CONNECTED,
// 				connection_state::DISCONNECTING,
// 				[] () {},
// 				if_any(boost::bind(&websocket::disconnected, this))
// 			},

// 			{
// 				connection_state::CONNECTED,
// 				connection_state::DISCONNECTED,
// 				[] () {},
// 				if_all(
// 					if_any(boost::bind(&websocket::disconnected, this)),
// 					if_not(boost::bind(&websocket::connected, this)))
// 			},

// 			{
// 				connection_state::CONNECTING,
// 				connection_state::FAILED,
// 				[] () {},
// 				if_not(boost::bind(&websocket::connected, this))
// 			},

// 			{
// 				connection_state::UNAVAILABLE,
// 				connection_state::CONNECTING,
// 				boost::bind(&websocket::connect, this)
// 			},

// 			{
// 				connection_state::FAILED,
// 				connection_state::UNAVAILABLE,
// 			},
// 		}
// 	}
// 	{}

// 	public: void connect(const std::string endpoint)
// 	{
// 		endpoint_ = endpoint;
// 		fsm_.next();
// 	}

// 	public: connection_state state() const
// 	{
// 		return connection_state::INITIALIZED;
// 	}

// 	private: bool endpoint_defined()
// 	{
// 		return endpoint_ != "";
// 	}

// 	private: bool connected()
// 	{
// 		return connected_;
// 	}

// 	private: bool disconnected()
// 	{
// 		return disconnect_;
// 	}

// 	private: void connect()
// 	{
// 		hub_.onConnection([this](WebSocket* ws, uWS::HttpRequest req) {
// 			connected_ = true;
// 			fsm_.next();
// 		});
// 		hub_.onError([this](std::conditional<false, int, void*>::type error) {
// 			connected_ = false;
// 			fsm_.next();
// 		});
// 		hub_.connect(endpoint_);
// 		hub_.run();

// 		fsm_.next();
// 	}

// 	public: void disconnect()
// 	{
// 		hub_.onDisconnection
// 		([this] (WebSocket* ws, int code, char* msg, size_t len) {
// 			connected_ = false;
// 			fsm_.next();
// 		});
// 		hub_.uWS::Group<false>::terminate();
// 		disconnect_ = true;
// 		fsm_.next();
// 	}
// };

