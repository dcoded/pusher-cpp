#pragma once
#include <uWS/uWS.h>
#include <json.hpp>
#include <boost/signals2.hpp>


#include <error_code.hpp>
#include <connection_state.hpp>

#include <vector>

class event_emitter
{
	using json   = nlohmann::json;
	using signal = boost::signals2::signal <void(json)>;
	using listener_type = std::function<void(json)>;

	private: struct key
	{
		listener_type* listener;
		std::string event_name;
		bool operator()(const key& a, const key& b);
	};

	private: std::map<std::string, signal> signals_;
	private: std::map<key, boost::signals2::connection, key> connections_;

	public: void bind(const std::string event_name, listener_type& listener);
	public: void bind_all(listener_type listener);

	public: void unbind(const std::string event_name, listener_type& listener);
	public: void unbind_all(listener_type listener);
};


class channel : public event_emitter {};
class private_channel : public channel {};
class presence_channel : public private_channel {};