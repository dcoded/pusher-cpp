#pragma once

// https://pusher.com/docs/pusher_protocol#error-codes
enum class error_code {
	/*	4000-4099

		Indicates an error resulting in the connection being closed by Pusher, 
		and that attempting to reconnect using the same parameters will not 
		succeed.
	*/

	// 4000: Application only accepts SSL connections, reconnect using wss://
	SSL_ONLY = 4000,

	// 4001: Application does not exist
	APP_NOT_FOUND = 4001,

	// 4003: Application disabled
	APP_DISABLED = 4003,

	// 4004: Application is over connection quota
	APP_OVER_CONN_QUOTA = 4004,

	// 4005: Path not found
	PATH_NOT_FOUND = 4005,

	// 4006: Invalid version string format
	INVALID_VERSION_STRING_FORMAT = 4006,

	// 4007: Unsupported protocol version
	UNSUPPORTED_PROTOCOL_VERSION = 4007,

	// 4008: No protocol version supplied
	NO_PROTOCOL_VERSION_SUPPLIED = 4008,




	/*	4100-4199

		Indicates an error resulting in the connection being closed by Pusher, 
		and that the client may reconnect after 1s or more.
	*/

	// 4100: Over capacity
	OVER_CAPACITY = 4100,




	/*	4200-4299

		Indicates an error resulting in the connection being closed by Pusher, 
		and that the client may reconnect immediately.
	*/

	// 4200: Generic reconnect immediately
	RECONNECT_IMMEDIATELY = 4200,

	// 4201: Pong reply not received: ping was sent to the client, but no reply
	// was received - see ping and pong messages
	PONG_NOT_RECIEVED = 4201,

	// 4202: Closed after inactivity: Client has been inactive for a long time 
	// (currently 24 hours) and client does not support ping. Please upgrade to
	// a newer WebSocket draft or implement version 5 or above of this protocol
	CLOSED_INACTIVITY = 4202,




	/*	4300-4399

		Any other type of error.
	*/

	// 4301: Client event rejected due to rate limit
	REJECTED_DUE_RATE_LIMIT = 4301
};




