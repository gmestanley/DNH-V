#include "SFML/Network.hpp"
#include <iostream>

class Netplay {
public:
	static std::string port;
	static std::wstring wchar;
	static sf::TcpSocket tcpSocket;
	//static sf::UdpSocket udpSocket;
	static char in[128];
	static char* convertToChar(wchar_t a, int size);
	static std::wstring convertToWString(const std::string &s);
};