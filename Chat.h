#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7777
#define MESSAGE_LENGTH 1024

class ChatClient {
public:
    ChatClient() : serverSocket(-1) {}
    //Ответы от сервера
    std::string addUserServer = "User added successfully!";
    std::string suchesfulServer = "Login successful!";
    std::string adminSuccess = "Admin login successful!";

    bool connectToServer(const std::string& serverAddress);
    void run();
    int serverSocket;
    struct sockaddr_in serverAddressInfo;

    // Методы для отправки команд серверу и получения ответа:
    std::string sendCommand(const std::string& command);
    bool registerUser();
    bool login();
    bool adminLogin(const std::string& login, const std::string& password);
    void listUsers();
    void sendMessage();
    void sendPublicMessage();
    void viewPrivateMessages();
    void viewPublicMessages();
    void userPanel();

    // Админ команды
    std::string showAllUsers() { return sendCommand("3"); }
    std::string showOnlineUsers() { return sendCommand("admin_2"); }
    std::string showBannedUsers() { return sendCommand("admin_6"); }
    std::string banUser(const std::string& login) { return sendCommand("admin_3 " + login); }
    std::string unbanUser(const std::string& login) { return sendCommand("admin_4 " + login); }
    std::string deleteUser(const std::string& login) { return sendCommand("admin_5 " + login); }
    std::string showPublicMessages() { return sendCommand("4"); }
};
