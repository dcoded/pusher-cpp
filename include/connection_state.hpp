#pragma once


// https://pusher.com/docs/client_api_guide/client_connect#connection-states
enum class connection_state {
	INITIALIZED, // Initial state. No event is emitted in this state.

	CONNECTING,	 // All dependencies have been loaded and Pusher is trying to
				 // connect. The connection will also enter this state when it 
				 // is trying to reconnect after a connection failure.

	CONNECTED,	 // The connection to Pusher is open and authenticated with 
				 // your app.

	UNAVAILABLE, // The connection is temporarily unavailable. In most cases 
				 // this means that there is no internet connection. It could 
				 // also mean that Pusher is down, or some intermediary is 
				 // blocking the connection. In this state, Pusher will 
				 // automatically retry the connection every ten seconds. 
				 // connecting_in events will still be triggered.

	FAILED,		 // Pusher is not supported by the browser. This implies that 
				 // WebSockets are not natively available and an HTTP-based 
				 // transport could not be found.

	DISCONNECTING,

	DISCONNECTED // The Pusher connection was previously connected and has now 
				 // intentionally been closed.
};
// Given a supported browser and functioning internet connection, the following states are expected:

// initialized -> connecting -> connected
// Temporary failure of the Pusher connection will cause

// connected -> connecting -> connected
// If an internet connection disappears

// connected -> connecting -> unavailable (after ~ 30s)
// When the internet connection becomes available again

// unavailable -> connected
// In the case that Pusher is not supported:

// initialized -> failed



