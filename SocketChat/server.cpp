#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
using namespace std;

#define PORT 9090
#define BUF_SIZE 1024

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

map<int, string> users; // Maps client socket to username
mutex userMutex;        
ofstream chatLog("chat_log.txt", ios::app);

// Function to put messages in a file
void saveLog(const string &msg) {
    lock_guard<mutex> lock(userMutex);
    if (chatLog.is_open()) {
        chatLog << msg << endl;
    }
}

// handles a single client
void handleClient(int clientSock) {
    char buf[BUF_SIZE];
    string username;

    // Receives username
    int nameLen = recv(clientSock, buf, BUF_SIZE, 0);
    if (nameLen > 0) {
        buf[nameLen] = '\0';
        username = buf;

        {
            lock_guard<mutex> lock(userMutex);
            users[clientSock] = username;
        }

        cout << GREEN << username << " connected." << RESET << endl;
        saveLog(username + " connected.");
    }

    // Handles client messages
    while (true) {
        memset(buf, 0, BUF_SIZE);
        int msgLen = recv(clientSock, buf, BUF_SIZE, 0);
        if (msgLen <= 0) {
            {
                lock_guard<mutex> lock(userMutex);
                cout << RED << username << " disconnected." << RESET << endl;
                saveLog(username + " disconnected.");
                users.erase(clientSock);
            }
            close(clientSock);
            break;
        }

        buf[msgLen] = '\0';
        string fullMessage(buf);

        // Extract recipient and message
        size_t delim = fullMessage.find(' ');
        if (delim != string::npos) {
            string recipient = fullMessage.substr(0, delim);
            string message = fullMessage.substr(delim + 1);

            int recipientSock = -1;
            {
                lock_guard<mutex> lock(userMutex);
                for (const auto &user : users) {
                    if (user.second == recipient) {
                        recipientSock = user.first;
                        break;
                    }
                }
            }

            if (recipientSock != -1) {
                // Send message 
                string formattedMsg = username + ": " + message;
                send(recipientSock, formattedMsg.c_str(), formattedMsg.size(), 0);
                saveLog(username + " to " + recipient + ": " + message);
            } else {
                // user not found case 
                string errMsg = "User not found: " + recipient;
                send(clientSock, errMsg.c_str(), errMsg.size(), 0);
            }
        }
    }
}

int main() {
    int serverSock;
    struct sockaddr_in servAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // Create server socket
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == -1) {
        perror(RED "Failed to create socket" RESET);
        return 1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface
    servAddr.sin_port = htons(PORT);

    // Bind socket to the port
    if (bind(serverSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1) {
        perror(RED "Bind failed" RESET);
        close(serverSock);
        return 1;
    }

    // Start listening for connections
    if (listen(serverSock, 5) == -1) {
        perror(RED "Listen failed" RESET);
        close(serverSock);
        return 1;
    }

    cout << GREEN << "Server running on port " << PORT << RESET << endl;

    // Main loop to accept clients
    while (true) {
        int clientSock = accept(serverSock, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSock == -1) {
            perror(RED "Accept failed" RESET);
            continue;
        }

        // Spawn a thread for each client
        thread(handleClient, clientSock).detach();
    }

    // Close the server socket and log file
    close(serverSock);
    chatLog.close();
    return 0;
}
