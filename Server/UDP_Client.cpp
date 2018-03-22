#undef UNICODE
#undef _UNICODE
#include "headerFiles.h"
#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 512

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


	//socket(UDP 소켓 생성)
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_Msg("socket()", TRUE);


	//소켓 주소 구조체 초기화
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = inet_addr("192.168.0.4"); //보낼 ip주소

															   // connect()
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_Msg("connect()", TRUE);

	// 데이터 통신에 사용할 변수
	SOCKADDR_IN peeraddr;
	int addrlen;
	char buf[BUFSIZE + 1];
	int len;

	// 클라이언트와 데이터 통신
	while (1) {
		//데이터 입력
		printf("\n[보낼 데이터] ");
		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		// '\n' 문자 제거
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (strlen(buf) == 0)
			break;

		//데이터 보내기
		retval = sendto(sock, buf, strlen(buf), 0,
			(SOCKADDR *)&serveraddr, sizeof(serveraddr));
		if (retval == SOCKET_ERROR) {
			err_Msg("sendto()", FALSE);
			continue;
		}

		// 데이터 받기
		addrlen = sizeof(peeraddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0,
			(SOCKADDR *)&peeraddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_Msg("recvfrom()", FALSE);
			continue;
		}

		//송신자의 IP 주소체크
		if (memcmp(&peeraddr, &serveraddr, sizeof(peeraddr))) {
			printf("[오류] 잘못된 데이터입니다!\n");
			continue;
		}

		//받은 데이터 출력
		buf[retval] = '\0';
		printf("[UDP 클라이언트] %d바이트를 받았습니다.\n", retval);
		printf("[받은 데이터] %s\n", buf);


	}

	// closesock()
	closesocket(sock);


	//윈속종료
	WSACleanup();
	return 0;

}