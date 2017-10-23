#undef UNICODE
#undef _UNICODE
#include "headerFiles.h"
#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 512

/*
- ������ �ʿ� vs2008�̻��� ��ġ�Ǿ����� ���� �� msvcr100d.dll ���� -
- "������Ʈ�Ӽ�:�����Ӽ�:C/C++:�ڵ����:��Ÿ�� ���̺귯��"����
- ����� : ���� ������ ����� DLL(/MDd) => ���� ������ �����(/MTd)
- ������ : ���� ������ DLL(/MD) => ���� ������(/MT)
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


	//���� �ʱ�ȭ
	WSADATA    wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;


	//socket(tcp ���� ����)
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

	// ������ ��ſ� ����� ����
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	// Ŭ���̾�Ʈ�� ������ ���
	while (1) {
		// ������ �ޱ�
		addrlen = sizeof(clientaddr);
		retval = recvfrom(sock, buf, BUFSIZE, 0,
			(SOCKADDR *)&clientaddr, &addrlen);
		if (retval == SOCKET_ERROR) {
			err_Msg("recvfrom()", FALSE);
			continue;
		}

		//���� ������ ���
		buf[retval] = '\0';
		printf("[UDP\%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), buf);

		//������ ������
		retval = sendto(sock, buf, retval, 0,
			(SOCKADDR *)&clientaddr, sizeof(clientaddr));
		if (retval == SOCKET_ERROR) {
			err_Msg("sendto()", FALSE);
			continue;
		}
	}

	// closesock()
	closesocket(sock);


	//��������
	WSACleanup();
	return 0;

}