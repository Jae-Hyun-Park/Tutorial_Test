#undef UNICODE
#undef _UNICODE
#include "headerFiles.h"
#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 512

/*
- 실행할 쪽에 vs2008이상이 설치되어있지 않을 때 msvcr100d.dll 오류 -
- "프로젝트속성:구성속성:C/C++:코드생성:런타임 라이브러리"에서
- 디버그 : 다중 스레드 디버그 DLL(/MDd) => 다중 스레드 디버그(/MTd)
- 릴리즈 : 다중 스레드 DLL(/MD) => 다중 스레드(/MT)
*/



void err_Msg(const char *msg, bool option)
{
	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	if (option) {
		MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
		LocalFree(lpMsgBuf);
		exit(-1);

	}
	else {
		printf("[%s] %s", msg, lpMsgBuf);
		LocalFree(lpMsgBuf);

	}

}


int main(int argc, char* argv[])

{
	int retval;


	//윈속 초기화
	WSADATA    wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;


	//socket(tcp 소켓 생성)
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_Msg("socket()", TRUE);


	//Bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// connect()
	retval = bind(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_Msg("connect()", TRUE);

	// 데이터 통신에 사용할 변수
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	// 클라이언트와 데이터 통신
	while (1) {
		// 데이터 받기
		addrlen = sizeof(clientaddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0,
			(SOCKADDR *)&clientaddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_Msg("recvfrom()", FALSE);
			continue;
		}

		//받은 데이터 출력
		buf[retval] = '\0';
		printf("[UDP\%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), buf);

		//데이터 보내기
		retval = sendto(sock, buf, retval, 0,
			(SOCKADDR *)&clientaddr, sizeof(clientaddr));
		if (retval == SOCKET_ERROR) {
			err_Msg("sendto()", FALSE);
			continue;
		}
	}

	// closesock()
	closesocket(sock);


	//윈속종료
	WSACleanup();
	return 0;

}