#include <bits/stdc++.h>
using namespace std;
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9090
#define BUF_SIZE 1024

map<int, string> users;
ofstream chatLog("chat_log.txt", ios::app);

// Save messages to a file
void saveMsg(const string &msg) {
    if (chatLog.is_open()) {
        chatLog << msg << endl;
    }
}

// Handle client connection
void clientHandler(int userSock) {
    char buf[BUF_SIZE];
    string userName;

    // Get username
    int nameLen = recv(userSock, buf, BUF_SIZE, 0);
    if (nameLen > 0) {
        buf[nameLen] = '\0';
        userName = buf;
        users[userSock] = userName;
        cout << userName << " connected." << endl;
        saveMsg(userName + " connected.");
    }

    while (true) {
        memset(buf, 0, BUF_SIZE);
        int msgLen = recv(userSock, buf, BUF_SIZE, 0);
        if (msgLen <= 0) {
            cout << userName << " disconnected." << endl;
            saveMsg(userName + " disconnected.");
            users.erase(userSock);
            close(userSock);
            break;
        }

        buf[msgLen] = '\0';
        string fullMsg(buf);

        // Split recipient and message
        size_t delim = fullMsg.find(' ');
        if (delim != string::npos) {
            string recvName = fullMsg.substr(0, delim);
            string chatMsg = fullMsg.substr(delim + 1);

            // Find recipient's socket
            int recvSock = -1;
            for (const auto &u : users) {
                if (u.second == recvName) {
                    recvSock = u.first;
                    break;
                }
            }

            if (recvSock != -1) {
                string formattedMsg = userName + ": " + chatMsg;
                send(recvSock, formattedMsg.c_str(), formattedMsg.size(), 0);
                saveMsg(userName + " to " + recvName + ": " + chatMsg);
            } else {
                string errMsg = "User not found: " + recvName;
                send(userSock, errMsg.c_str(), errMsg.size(), 0);
            }
        }
    }
}

int main() {
    int serverSock;
    struct sockaddr_in servAddr, cliAddr;
    socklen_t cliLen = sizeof(cliAddr);

    // Create server socket
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(serverSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1) {
        perror("Bind failed");
        close(serverSock);
        return 1;
    }

    // Start listening
    if (listen(serverSock, 5) == -1) {
        perror("Listen failed");
        close(serverSock);
        return 1;
    }

    cout << "Server running on port " << PORT << endl;

    while (true) {
        int clientSock = accept(serverSock, (struct sockaddr *)&cliAddr, &cliLen);
        if (clientSock == -1) {
            perror("Accept failed");
            continue;
        }

        thread(clientHandler, clientSock).detach();
    }

    close(serverSock);
    chatLog.close();
    return 0;
}