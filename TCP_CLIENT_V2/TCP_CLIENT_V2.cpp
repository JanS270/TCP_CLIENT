///--- TCP CLIENT ---///

#include "stdafx.h"
#include <winsock2.h>
#include <Windows.h>
#include <locale.h>
#include <string.h>
#include <conio.h>

#pragma comment(lib, "WS2_32.lib")

// SCHEMAT DZIALANIA KLIENTA TCP //
//	1. INICJALIZACJA BIBLIOTEKI WINSOCK
//  2. STWORZENIE GNIAZDA 
//	3. WYPELNIENIE STRUKTURY ADRESOWEJ DANYMI SERWERA
//	4. PODPIECIE SIE DO SERWERA (connect)
//  5. KOMUNIKACJA Z SERWEREM (send, recv)
//	6. ZAKONCZENIE POLACZENIA (closesocket, shutdown)

int main()
{
	setlocale(LC_ALL, "POLISH");
	WSAData wsadata;

	/// --- 1. INICJALIZACJA WINSOCK --- ///

	if (WSAStartup(MAKEWORD(2, 2), &wsadata))							
	{																	
		printf("Coœ fest posz³o nie tak... %d", WSAGetLastError());		
		_getch();														
		return 0;														
	}																	
	printf("Inicjalizacja Winsock przebieg³a poprawnie.\n");				
	
	
	/// --- 2. TWORZENIE GNIAZD --- ///
	
	SOCKET KLIENT_SOCKET = INVALID_SOCKET;
	KLIENT_SOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Gniazdo... byæ musi..
	if (KLIENT_SOCKET == INVALID_SOCKET)
	{
		printf("B³ad przy tworzeniu gniazda: %d", WSAGetLastError());
		closesocket(KLIENT_SOCKET);
		_getch();
		return 0;
	}


	/// --- 3. TWORZENIE I WYPELNIANIE STRUKTURY ADRESOWEJ ---///

	sockaddr_in DaneSerwera = { 0 }, addr2 = { 0 };  // Dane serva czyli Kaj mom iœæ..
	DaneSerwera.sin_addr.s_addr = inet_addr("127.0.0.1");
	DaneSerwera.sin_family = AF_INET;
	DaneSerwera.sin_port = htons(5678);


	/// --- 4. PODPINANIE SIE DO SERWERA --- ///

	int ConResult = connect(KLIENT_SOCKET, (sockaddr*)&DaneSerwera, sizeof(DaneSerwera)); // PODPINANIE DO SERWERA (tylko raz i tylko klient to robi!)
	if (ConResult == SOCKET_ERROR)
	{
		printf("Connect B³¹d: %d\n", WSAGetLastError());
		closesocket(KLIENT_SOCKET);
		WSACleanup();
		getch();
		Sleep(500);
		return 0;
	}


	/// ---  5a. WYSY£ANIE DO SERWERA   --- ///

	float tab[13] = { 1,2,3,4,5,6,7,8,9,10 };
	printf("Naciœnij Knefel aby wys³aæ.\n");
	_getch();
	printf("Posz³o!\n\n");
	printf("//////////////////////////////////////////////////////////////////////////// \n\n");
	
	send(KLIENT_SOCKET, (char*)&tab, sizeof(tab), 0);  // Wysy³anie tablicy z pomiarami do normalizacji
	

	/// --- 5b. ODBIERANIE OD SERWERA --- ///

	char OdServera[1024] = { 0 };

	recv(KLIENT_SOCKET, OdServera, sizeof(OdServera), 0);	
	int LiczbaPomiarow = *(int*)&OdServera;					// odbiera ilosc pomiarów od serwera.
	printf("OD SERWERA: \n\n");
	printf("Liczba Pomiarów odes³anych przez serwer: %d\n", LiczbaPomiarow);


	int Bajty = recv(KLIENT_SOCKET, OdServera, sizeof(OdServera), 0); // odbiera wartoœci pomiarów od serwera.
	printf("Liczba odebranych Bajtow od serwera: %d\n", Bajty); // funkcja recv zwraca iloœæ odebranych bajtów 

	printf("Wynik Normalizacji:\n\n");  // Serwer odsy³a znormalizowane Dane.

	/// --- RZUTOWANIE ODEBRANYCH DANYCH(CHAR) NA FLOAT --- ///

	int LicznikBajtow = 0;
	float znormalizowane[100];
	for (int i = 0; i < (LiczbaPomiarow); i++)
	{
		znormalizowane[i] = *(float*)&OdServera[LicznikBajtow];
		printf("%2.0d. Dane: %0.2f\n", i + 1, znormalizowane[i]);
		LicznikBajtow += 4;
	}


	/// --- 6. KOÑCZENIE PROGRAMU ---///

	printf("\nNaciœnij Knefel Aby Zakoñczyæ Program.\n");
	_getch();

	shutdown(KLIENT_SOCKET, 2);
	closesocket(KLIENT_SOCKET);
	WSACleanup();
	return 0;
}// by Johnny


// Sortowanie Babelkowe
/*
void sortowanie_babelkowe(int *tab, int n)
{
	for (int i = 1; i<n; i++)
	{
		for (int j = n - 1; j >= 1; j--)
		{
			if (tab[j]<tab[j - 1])
			{
				int bufor;
				bufor = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = bufor;
			}
		}
	}
}
*/