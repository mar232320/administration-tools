#include <iostream>
#include <vector>
#include <winsock2.h>

void check(int typ, int prot, int addr, std::vector<int> &res)
{
	SOCKET s;
	struct sockaddr_in saddr;
	int port;
	for (port = 0; port <= 65535; port++)
	{
		s = socket(AF_INET, typ, prot);
		memset(&saddr, 0, sizeof(struct sockaddr_in));
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(port);
		saddr.sin_addr.s_addr = htonl(addr);
		if (bind(s, (sockaddr *)(&saddr), sizeof(struct sockaddr_in)))
			res.push_back(port);
		closesocket(s);
	}
}

void dispresult(std::string x, std::vector<int> &vec)
{
	int i;
	std::cout << x << std::endl;
	for (i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	std::vector<int> ptl;
	std::vector<int> pth;
	std::vector<int> pul;
	std::vector<int> puh;
	WSADATA wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	check(SOCK_STREAM, IPPROTO_TCP, 0x7f000001, ptl);
	check(SOCK_STREAM, IPPROTO_TCP, 0, pth);
	check(SOCK_DGRAM, IPPROTO_UDP, 0x7f000001, pul);
	check(SOCK_DGRAM, IPPROTO_UDP, 0, puh);
	dispresult("TCP 127.0.0.1:", ptl);
	dispresult("TCP 0.0.0.0:", pth);
	dispresult("UDP 127.0.0.1:", pul);
	dispresult("UDP 0.0.0.0:", puh);	
	WSACleanup();
	return 0;
}