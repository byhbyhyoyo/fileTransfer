////server.cpp
//#include<iostream>
//#include<winsock.h>   // windowsƽ̨�������ͷ�ļ�
//#pragma comment(lib,"ws2_32.lib")   // ���ļ�
//using namespace std;
//
//#define PORT 5050
//#define BUFSIZ 512
//
//void initialization() {
//	//��ʼ���׽��ֿ�
//	// WSA  windows socket async  windows�첽�׽���     WSAStartup�����׽���
//	// parm1:�����socket�汾 2.2 2.1 1.0     parm2:��������    ������ʽ��WORD  WSADATA
//	WORD w_req = MAKEWORD(2, 2);//�汾��  
//	WSADATA wsadata;
//	// �ɹ���WSAStartup����������
//	if (WSAStartup(w_req, &wsadata) != 0) {
//		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
//	}
//	else {
//		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
//	}
//}
//
//SOCKET createServeSocket(const char* ip)
//{
//	//1.�����յ�Socket					
//		//parm1:af ��ַЭ���� ipv4 ipv6
//		//parm2:type ����Э������ ��ʽ�׽���(SOCK_STREAM) ���ݱ�
//		//parm3��protocl ʹ�þ����ĳ������Э��
//	SOCKET s_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (s_server == INVALID_SOCKET)
//	{
//		cout << "�׽��ִ���ʧ�ܣ�" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "�׽��ִ����ɹ���" << endl;
//	}
//	//2.��socket��ip��ַ�Ͷ˿ں�
//	struct sockaddr_in server_addr;   // sockaddr_in, sockaddr  �ϰ汾���°������
//	server_addr.sin_family = AF_INET;  // �ʹ���socketʱ����һ��
//	server_addr.sin_port = htons(PORT);       // �˿ں�  ��ˣ���λ���洢(����)��С�ˣ���λ���洢(���磩�������洢˳���Ƿ��ŵ�  htons �������ֽ���תΪ�����ֽ���
//	server_addr.sin_addr.S_un.S_addr = inet_addr(ip); //inet_addr�����ʮ���Ƶ�ip��ַתΪ������
//	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
//		cout << "�׽��ְ�ʧ�ܣ�" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "�׽��ְ󶨳ɹ���" << endl;
//	}
//
//	//3.�����׽���Ϊ����״̬  SOMAXCONN �����Ķ˿��� �Ҽ�ת������Ϊ5
//	if (listen(s_server, SOMAXCONN) < 0) {
//		cout << "���ü���״̬ʧ�ܣ�" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "���ü���״̬�ɹ���" << endl;
//	}
//	return s_server;
//}
//
//int main() {
//	//���巢�ͻ������ͽ��ܻ���������
//	char send_buf[BUFSIZ];
//	char recv_buf[BUFSIZ];
//	//���������׽��֣����������׽���
//	SOCKET s_server;
//	SOCKET s_accept;
//
//	initialization(); // ��ʼ�������׽���
//	s_server = createServeSocket("127.0.0.1");
//	cout << "wait client connect..." << endl;
//	// ����пͻ�����������
//	s_accept = accept(s_server, NULL, NULL);
//	if (s_accept == INVALID_SOCKET) {
//		cout << "����ʧ�ܣ�" << endl;
//		WSACleanup();
//		return 0;
//	}
//	// ���ԺͿͻ��˽���ͨ����
//	while (true) {
//		// recv��ָ����socket������Ϣ
//		if (recv(s_accept, recv_buf, BUFSIZ, 0) > 0) {
//			cout << "�ͻ�����Ϣ:" << recv_buf << endl;
//		}
//		else {
//			cout << "����ʧ�ܣ�" << endl;
//			break;
//		}
//		cout << "������ظ���Ϣ:";
//		cin >> send_buf;
//		if (send(s_accept, send_buf, BUFSIZ, 0) < 0) {
//			cout << "����ʧ�ܣ�" << endl;
//			break;
//		}
//	}
//	//�ر��׽���
//	closesocket(s_server);
//	closesocket(s_accept);
//	//�ͷ�DLL��Դ
//	WSACleanup();
//	return 0;
//}