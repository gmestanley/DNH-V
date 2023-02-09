#include "Networking.hpp"

////////////////////////////////////////////////////////////
// General
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Netplay
////////////////////////////////////////////////////////////
std::string Netplay::port = "";
std::wstring Netplay::wcharBuffer = L"";
sf::TcpSocket Netplay::tcpSocket{
	
};
/*sf::UdpSocket Netplay::udpSocket{

};*/
char Netplay::in[128]{

};
char* Netplay::convertToChar(wchar_t a, int size) {
	int i;
	char* s;
	for (i = 0; i < size; i++) {
		s = s + a[&i];
	}
	return s;
}
std::wstring Netplay::convertToWString(const std::string &s) {
	std::wstring wsTmp(s.begin(), s.end());

	return wsTmp;
}

