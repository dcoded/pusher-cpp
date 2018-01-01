#pragma once
#include <cstdint>
#include <json.hpp>
#include <uWS/uWS.h>


class client {

	using WebSocket = uWS::WebSocket<uWS::CLIENT>;
	using OpCode    = uWS::OpCode;
	using json      = nlohmann::json;

	private: uWS::Hub hub_;
	private: std::map<std::string, std::function<void(WebSocket*, json)> > handlers_;

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


	public: explicit client(const std::string key)
	:	key_(key)
	{
		hub_.connect(url());
    	hub_.onConnection([this] (WebSocket* ws, uWS::HttpRequest req) {
    	
    	});

    	/* 	WebSocket data messages

			Data is sent bidirectionally over a WebSocket as text data
			containing UTF8 encoded JSON.

			Note: Binary WebSocket frames are not supported.

			Every JSON message contains a single event and has an event 
			property which is known as the event name. See events below for a 
			description of the event types.

		*/
    	hub_.onMessage([this] (WebSocket* ws, char* msg, size_t len, OpCode opCode) {
			json message = json::parse(msg);
			// pusher:connection_established
			// pusher:error
			// pusher:subscription_succeeded
			// pusher_internal:member_added
			// pusher_internal:member_removed

		});


    	/* 	Ping and pong messages

			If the WebSocket connection supports ping & pong (i.e. advertises
			itself as draft 01 or above), Pusher will send ping messages to the
			client in order to verify that it is active.

			In protocol versions 5 and above, when using an old version of the 
			WebSocket protocol, Pusher will send pusher:ping event (see events)
			to the client. The client should respond with a pusher:pong event.
		*/
		hub_.onPing([] (WebSocket* ws, char* msg, size_t len) {
			ws->send("", 0, uWS::OpCode::PONG);	
		});

		/* 	Ping and pong messages

			In protocol versions 5 and above, when using an old version of the 
			WebSocket protocol, Pusher will send pusher:ping event (see events)
			to the client. The client should respond with a pusher:pong event.
		*/
		handlers_["pusher:ping"] = [this] (WebSocket* ws, json data) {
			send_json(ws, {
				{"event", "pusher:pong"}
			});
		};
	}

	private: void send_json(WebSocket* ws, json data) {
		/* 	WebSocket data messages

			Data is sent bidirectionally over a WebSocket as text data
			containing UTF8 encoded JSON.

			Note: Binary WebSocket frames are not supported.

			Every JSON message contains a single event and has an event 
			property which is known as the event name. See events below for a 
			description of the event types.

		*/

		if (is_event(data)) {
			std::string str = data.dump();
			ws->send(str.c_str(), str.size(), uWS::OpCode::TEXT);
		}
	}

	private: bool is_event(const json& root) {
		if (root.find("event") == root.end() ||
			root.find("data")  == root.end()) {
			return false;
		}

		json data = root["data"];

		if (root["event"] == "pusher::subscribe" &&
			data.find("channel") != data.end()) {
			return true;
		}
		
		if (root["event"] == "pusher::unsubscribe" &&
			data.find("channel") != data.end()) {
			return true;
		}

		return false;
	}

	public: void subscribe()
	{

	}

	public: void unsubscribe()
	{

	}

	public: const std::string url() const
	{
		// ws://ws.pusherapp.com:80/app/APP_KEY?client=js&version=4.1&protocol=5
		return 
			SCHEME 
		+ 	"://ws.pusherapp.com:" 
		+	std::to_string(PORT) 
		+ 	"/app/" 
		+ 	key_
		+	"?client="
		+	CLIENT 
		+	"&version="
		+	VERSION
		+	"&protocol="
		+	std::to_string(PROTOCOL)
		;
	}
};