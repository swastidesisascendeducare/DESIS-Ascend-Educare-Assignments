#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#define PORT 9090
#define BUF_SIZE 1024

// ANSI escape codes for colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"

// Function to receive messages from the server
void receiveMessages(int serverSock) {
    char buf[BUF_SIZE];
    while (true) {
        memset(buf, 0, BUF_SIZE);
        int len = recv(serverSock, buf, BUF_SIZE, 0);
        if (len > 0) {
            buf[len] = '\0';
            cout << CYAN << buf << RESET << endl;
        } else if (len == 0) {
            cout << RED << "Disconnected from server." << RESET << endl;
            close(serverSock);
            exit(0);
        }
    }
}

int main() {
    int clientSock;
    struct sockaddr_in servAddr;
    char buf[BUF_SIZE];

    // Create socket
    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSock == -1) {
        perror(RED "Socket creation failed" RESET);
        return 1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost

    // Connect to the server
    if (connect(clientSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1) {
        perror(RED "Connection to server failed" RESET);
        close(clientSock);
        return 1;
    }

    cout << GREEN << "Connected to server on port " << PORT << RESET << endl;

    // Enter username
    string username;
    cout << YELLOW << "Enter your username: " << RESET;
    cin >> username;
    send(clientSock, username.c_str(), username.size(), 0);

    // thread to handle receiving messages
    thread recvThread(receiveMessages, clientSock);
    recvThread.detach();

    // Send messages
    while (true) {
        string recipient, message;
        cout << YELLOW << "Recipient: " << RESET;
        cin >> recipient;
        cout << YELLOW << "Message: " << RESET;
        cin.ignore(); 
        getline(cin, message);

        string fullMessage = recipient + " " + message;
        send(clientSock, fullMessage.c_str(), fullMessage.size(), 0);
    }

    // Close socket 
    close(clientSock);
    return 0;
}
