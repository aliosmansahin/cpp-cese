#include "Net.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Logger.h"

struct sockaddr_in server;
socklen_t serAddrLen;
int client_socket;

int sockfd;
struct sockaddr_in servaddr;
int n;
socklen_t len;

Net::Net()
{
}

Net::~Net()
{
    closesocket(client_socket);
    closesocket(sockfd);
    WSACleanup();
}

std::string Net::ws2s(const std::wstring& str) {
    const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &str.at(0), (int)str.size(), nullptr, 0, NULL, NULL);
    if (size_needed <= 0) {
        exit(0); //EMPTY WSTRING
    }
    std::string con(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &str.at(0), (int)str.size(), &con.at(0), size_needed, NULL, NULL);
    return con;
}

std::wstring Net::s2ws(const std::string& str) {
    const auto size_needed = MultiByteToWideChar(CP_UTF8, 0, &str.at(0), (int)str.size(), nullptr, 0);
    if (size_needed <= 0) {
        exit(0); //EMPTY WSTRING
    }
    std::wstring con(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str.at(0), (int)str.size(), &con.at(0), size_needed);
    return con;
}

bool Net::Init(std::wstring nick, std::wstring url, std::wstring& map, float& x, float& y, float& z, int& exitCode)
{
    // initialise winsock
    WSADATA ws;
    printf("Initialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return false;
    }
    printf("Initialised.\n");

    //create a socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error...\n");
        return false;
    }

    //server socket address
    server.sin_family = AF_INET;
    server.sin_port = htons(3000);
    inet_pton(AF_INET, ws2s(url).c_str(), &server.sin_addr);

    int status;
    if ((status = connect(client_socket, (struct sockaddr*)&server, sizeof(server))) < 0) {
        perror("socket creation error...\n");
        return false;
    }

    json jsonNick;
    jsonNick["mode"] = "0";
    jsonNick["nick"] = ws2s(nick);

    std::string sNick = jsonNick.dump();
    // send the message
    if (send(client_socket, sNick.c_str(), sNick.length(), 0) < 0) {
        perror("sending error...\n");
        return false;
    }

    //UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        return false;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(3000);
    inet_pton(AF_INET, ws2s(url).c_str(), &servaddr.sin_addr);

    len = sizeof(servaddr);

    char buff[512];
    ZeroMemory(buff, sizeof(buff));

    int readStatus = recv(client_socket, buff, sizeof(buff), 0);
    int err = WSAGetLastError();
    if (readStatus < 0) {
        perror("recv error...\n");
        return false;
    }
    json recvJson = json::parse(buff);
    if (recvJson["code"] == "1") {
        exitCode = 1;
        return false;
    }

    map = s2ws(recvJson["map"].get<std::string>());
    x = recvJson["x"].get<float>();
    y = recvJson["y"].get<float>();
    z = recvJson["z"].get<float>();

    exitCode = 0;
    return true;
}

bool Net::LeaveServer()
{
    json j;
    j["mode"] = "1";
    j["command"] = "leave";
    std::string s = j.dump();
    if (send(client_socket, s.c_str(), s.length(), 0) < 0) {
        perror("sending error...\n");
        closesocket(client_socket);
        exit(-1);
    }
    
    closesocket(client_socket);
    WSACleanup();
    return true;
}

json Net::GetData(int& recvBytes)
{
    //RECV THE BUFFER
    char tmp[512];
    ZeroMemory(tmp, sizeof(tmp));
    n = recvfrom(sockfd, tmp, sizeof(tmp), 0, (struct sockaddr*)&servaddr, &len);
    if (n < 0) {
        int err = GetLastError();
        Logger::Log("Net error: " + err);
        perror("reading error...\n");
        recvBytes = 0;
        return NULL;
    }
    else if (n > 0) {
        json data = json::parse(tmp);

        recvBytes = n;
        return data;
    }
    else
        return NULL;
}

json Net::GetTCP(int& recvBytes)
{
    char buff[512];
    ZeroMemory(buff, sizeof(buff));

    int readStatus = recv(client_socket, buff, sizeof(buff), 0);
    int err = WSAGetLastError();
    if (readStatus < 0) {
        perror("recv error...\n");
        recvBytes = 0;
        return NULL;
    }
    json recvJson = json::parse(buff);
    recvBytes = readStatus;

    return recvJson;
}

bool Net::SendData(float x, float y, float z, float yaw, std::wstring nick)
{
    json data;
    data["nick"] = ws2s(nick);
    data["x"] = x;
    data["y"] = y;
    data["z"] = z;
    data["YAW"] = yaw;

    std::string strdata = data.dump();

    sendto(sockfd, strdata.c_str(), strdata.length(),
        0, (struct sockaddr*)&servaddr,
        sizeof(servaddr));
    
    return true;
}

bool Net::SendBullet(float x, float y, float z, float lx, float ly, float lz)
{
    json sendJson;
    sendJson["mode"] = "2";
    sendJson["lookX"] = lx;
    sendJson["lookY"] = ly;
    sendJson["lookZ"] = lz;

    std::string strdata = sendJson.dump();
    send(client_socket, strdata.c_str(), strdata.length(), 0);

    return true;
}