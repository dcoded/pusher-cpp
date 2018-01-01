#pragma once
#include <string>
#include <cstdint>

#include "connection.hpp"
#include "websocket.hpp"
#include "event_emitter.hpp"


class pusher : public event_emitter
{
	/*	WebSocket connection

		Clients should make a WebSocket connection to
		[scheme]://ws.pusherapp.com:[port]/app/[key]

		The following query parameters should be supplied:
	*/

	/*	key

		The app key for the application connecting to Pusher
		The following query parameters should be supplied:
	*/
	private: const std::string key_;


	/*	scheme

		ws - for a normal WebSocket connection
		wss - for a secure WebSocket connection
	*/
	private: const std::string SCHEME = "wss";


	/*	port

		Default WebSocket ports: 80 (ws) or 443 (wss)
		For Silverlight clients ports 4502 (ws) and 4503 (wss) may be used.
	*/
	private: const std::uint16_t PORT = 443;


	/* 	client [string]
	
		Identifies the client which is connecting. This string should be of the
		form platform-library - for example the iOS library identifies itself 
		as iOS-libPusher.
	*/
	private: const std::string CLIENT = "cpp-upusher";


	/*	version [string]
		The version of the library which is connecting, for example 1.9.3.
		For example
	*/
	private: const std::string VERSION = "0.1.0";


	/*	protocol [integer]

		The protocol version to use. If this is not supplied the protocol
		version to use is inferred from the version parameter (to support old
		javascript clients which relied on this behaviour). Failing that
		protocol 1 is used (this behaviour is deprecated and will in future be
		replaced by a 4008 error code)
	*/
	private: const std::uint8_t PROTOCOL = 7;




	private: std::unique_ptr<connection> connection_;

	public: explicit pusher(const std::string app_key /* , options */)
	:	connection_(new nop_connection())
	{
		connection_->connect(app_key);
	}

	public: void subscribe(const std::string channel_name)
	{
		const std::string event_name = "pusher:" + channel_name;
		// bind(event_name,);
	}

	public: void unsubscribe(const std::string channel_name)
	{
		const std::string event_name = "pusher:" + channel_name;
		//bind(event_name);
	}

	public: void disconnect()
	{
		connection_->disconnect();
	}
};
