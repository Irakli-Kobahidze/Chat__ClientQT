#include "Chat.h"

bool ChatClient::connectToServer(const std::string& serverAddressStr) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Socket creation error!" << std::endl;
        return false;
    }

    serverAddressInfo.sin_family = AF_INET;
    serverAddressInfo.sin_port = htons(PORT);

    if (inet_pton(AF_INET, serverAddressStr.c_str(), &serverAddressInfo.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        close(serverSocket);
        serverSocket = -1;
        return false;
    }

    if (connect(serverSocket, (struct sockaddr *)&serverAddressInfo, sizeof(serverAddressInfo)) < 0) {
        std::cerr << "Connection failed!" << std::endl;
        close(serverSocket);
        serverSocket = -1;
        return false;
    }

    std::cout << "Connected to server!" << std::endl;
    return true;
}

bool ChatClient::adminLogin(const std::string& login, const std::string& password) {
    std::string command = "5 " + login + " " + password;
    std::string response = sendCommand(command);
    std::cout << "Server response: " << response << std::endl;

    return response.find("successful") != std::string::npos ||
           response.find("Admin") != std::string::npos;
}

std::string ChatClient::sendCommand(const std::string& command) {
    if (serverSocket == -1) {
        std::cerr << "Not connected to server." << std::endl;
        return "Error: Not connected to server";
    }

    // Отправка данных
    size_t bytes_sent = 0;
    while (bytes_sent < command.length()) {
        ssize_t result = send(serverSocket, command.c_str() + bytes_sent, command.length() - bytes_sent, 0);
        if (result < 0) {
            std::cerr << "Send failed." << std::endl;
            return "Error: Send failed";
        }
        bytes_sent += result;
    }

    // Таймаут для получения ответа, добавлено чтобы не было вечного зависани при ошибке со стороны сервера
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    // Получение данных
    std::string buffer;
    buffer.resize(MESSAGE_LENGTH);

    int bytes_received = recv(serverSocket, &buffer[0], MESSAGE_LENGTH - 1, 0);
    if (bytes_received < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            std::cerr << "Receive timeout." << std::endl;
            return "Error: Receive timeout - server not responding";
        } else {
            std::cerr << "Receive failed." << std::endl;
            return "Error: Receive failed";
        }
    }

    buffer[bytes_received] = '\0';
    buffer.resize(bytes_received);

    // Сбрасываем таймаут
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    return buffer;
}

bool ChatClient::registerUser() {
    std::string login, password, name;
    std::cout << "Enter login: ";
    std::getline(std::cin, login);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::string command = "1 " + login + " " + password + " " + name;
    std::string response = sendCommand(command);
    std::cout << "Server response: " << response << std::endl;
    if(response == addUserServer) return true;
    return false;
}

bool ChatClient::login() {
    std::string login, password;
    std::cout << "Enter login: ";
    std::getline(std::cin, login);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    std::string command = "2 " + login + " " + password;
    std::string response = sendCommand(command);
    std::cout << "Server response: " << response << std::endl;
    if(response == suchesfulServer) return true;
    return false;
}

void ChatClient::listUsers() {
    std::string command = "3";
    std::string response = sendCommand(command);
    std::cout << "List of users:\n" << response << std::endl;
}

void ChatClient::sendMessage() {
    std::string recipient, message;
    std::cout << "Enter recipient name: ";
    std::getline(std::cin, recipient);
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

    std::string command = "1 " + recipient + " " + message;
    std::string response = sendCommand(command);
    std::cout << "Server response: " << response << std::endl;
    return;
}

void ChatClient::sendPublicMessage() {
    std::string message;
    std::cout << "Enter public message: ";
    std::getline(std::cin, message);

    std::string command = "2 " + message;
    std::string response = sendCommand(command);
    std::cout << "Server response: " << response << std::endl;
}

void ChatClient::viewPrivateMessages() {
    std::string command = "3";
    std::string response = sendCommand(command);
    std::cout << "Private Messages:\n" << response << std::endl;
}

void ChatClient::viewPublicMessages() {
    std::string command = "4";
    std::string response = sendCommand(command);
    std::cout << "Public Messages:\n" << response << std::endl;
}

void ChatClient::run() {
    if (serverSocket == -1) {
        std::cerr << "Not connected to server.  Call connectToServer() first." << std::endl;
        return;
    }

    bool running = true;
    while (running) {
        std::cout << "Write command: \n1 - register\n";
        std::cout << "2 - login\n";
        std::cout << "3 - Print all users\n";
        std::cout << "4 - Admin login\n";
        std::cout << "5 - end\n";
        std::cout << "> ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            registerUser();
        } else if (choice == "2") {
            if(login()) userPanel();
        } else if (choice == "3") {
            listUsers();
        } else if (choice == "4") {
            std::string login, password;
            std::cout << "Enter admin login: ";
            std::getline(std::cin, login);
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);
            if(adminLogin(login, password)) {
                std::cout << "Admin panel would open here in GUI version\n";
            }
        } else if (choice == "5") {
            serverSocket = -1;
            running = false;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
    close(serverSocket);
    std::cout << "Disconnected from server.\n";
}

void ChatClient::userPanel(){
    bool running = true;
    while (running) {
        std::cout << "Write command: \n1 - send private message\n";
        std::cout << "2 - send public message\n";
        std::cout << "3 - Print private message\n";
        std::cout << "4 - Print public message\n";
        std::cout << "5 - end\n";
        std::cout << "> ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            sendMessage();
        } else if (choice == "2") {
            sendPublicMessage();
        } else if (choice == "3") {
            viewPrivateMessages();
        } else if (choice == "4") {
            viewPublicMessages();
        } else if (choice == "5") {
            sendCommand("5");
            running = false;
        } else {
            std::cout << "Invalid choice!\n";
        }
    }
}
