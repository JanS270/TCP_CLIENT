///--- TCP CLIENT ---///

#include "stdafx.h"
#include <winsock2.h>
#include <Windows.h>
#include <locale.h>
#include <string.h>
#include <conio.h>

#pragma comment(lib, "WS2_32.lib")


int main()
{
	setlocale(LC_ALL, "POLISH");

	WSAData wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		printf("Coœ fest posz³o nie tak... %d", WSAGetLastError());
		_getch();
		return 0;
	}

	SOCKET KLIENT_SOCKET = INVALID_SOCKET;
	KLIENT_SOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Gniazdo... byæ musi..

	sockaddr_in DaneSerwera = { 0 }, addr2 = { 0 };  // Dane serva czyli Kaj mom iœæ..
	DaneSerwera.sin_addr.s_addr = inet_addr("127.0.0.1");
	DaneSerwera.sin_family = AF_INET;
	DaneSerwera.sin_port = htons(5678);

	connect(KLIENT_SOCKET, (sockaddr*)&DaneSerwera, sizeof(DaneSerwera)); // PODPINANIE DO SERWERA (tylko raz i tylko klient to robi!)

	char DoWyslania[128] = "Proste ale i tak ujebie :)";

	printf("Naciœnij Knefel aby wys³aæ.\n\n");
	_getch();
	
	printf("Posz³o!\n");
	send(KLIENT_SOCKET, DoWyslania, strlen(DoWyslania), 0);  // Wysy³anie
	printf("Wys³ano: %s\n\n", DoWyslania);


	printf("Naciœnij Knefel Aby Zakoñczyæ Program.\n");
	_getch();


	closesocket(KLIENT_SOCKET);
	WSACleanup();
	return 0;
}// by Johnny