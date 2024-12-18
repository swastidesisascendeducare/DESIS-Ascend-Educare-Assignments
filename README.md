# Real-time Chat Server

This is a simple real-time chat server built in C++ that lets multiple users connect, chat, and send private messages to each other. It's a basic implementation using sockets, and it logs all messages and user events to a file.

## Features
- **Private Messaging**: Users can send messages to specific people by mentioning their username.
- **Real-time Communication**: Clients and server communicate instantly.
- **Chat Logging**: All messages and user connections are saved to a `chat_log.txt` file.
- **User Identification**: Each user is identified by a unique username.

-   The server will start and listen for connections on port 9090.

## How It Works
- When a client connects, they send their username to the server.
- Clients can send messages to other users by typing their username followed by the message.
- The server checks if the recipient is online and forwards the message to them.
- Every connection, disconnection, and message is saved to a log file (`chat_log.txt`).

## File Structure
- `chat_server.cpp`: The main C++ code for the server logic.
- `chat_log.txt`: The log file where all chat interactions are stored.
