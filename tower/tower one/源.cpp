#include <iostream>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")                 //��̬����������ص�API
#pragma warning(disable:4996)

//============ȫ�ֳ���=====================
const int BUF_SIZE = 2048;

SOCKET socketSer, socketCLi;
SOCKADDR_IN addrSer, addrCli;
int naddr = sizeof(SOCKADDR_IN);

char sendbuf[BUF_SIZE];
char recvbuf[BUF_SIZE];
byte recdate[22];
byte senddate[19];

int main()
{
    cout << "����������" << endl;
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {                                    //1.�����ϵͳҪsocket
        cout << "����socket����" << endl;
        system("pause");
        return 0;
    }
    else {
        cout << "����socket��ɹ�" << endl;
    }

    socketSer = socket(AF_INET, SOCK_STREAM, 0);
    addrSer.sin_addr.S_un.S_addr = inet_addr("192.168.1.100");                           //2.����socket�ĵ�ַ��Ϣ
    addrSer.sin_port = htons(1111);
    addrSer.sin_family = AF_INET;

    bind(socketSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));                             //3.��socket�Ļ�����Ϣ
    senddate[0] = (byte)0x55;       //�½�100
    senddate[1] = (byte)0x02;
    senddate[2] = (byte)0x01;
    senddate[3] = (byte)0x02;
    senddate[4] = (byte)0x00;
    senddate[5] = (byte)0x02;
    senddate[6] = (byte)0x00;
    senddate[7] = (byte)0x00;
    senddate[8] = (byte)0x00;
    senddate[9] = (byte)0x00;
    senddate[10] = (byte)0x00;
    senddate[11] = (byte)0x64;
    senddate[12] = (byte)0x00;
    senddate[13] = (byte)0x00;
    senddate[14] = (byte)0x00;
    senddate[15] = (byte)0x00;
    senddate[16] = (byte)0x00;
    senddate[17] = (byte)0x01;
    senddate[18] = (byte)0xAA;
   
    while (true) {
        cout << "��ʼ���ӣ�" << endl;
        listen(socketSer, 7);                                                           //4.��������

        //��������
        socketCLi = accept(socketSer, (SOCKADDR*)&addrCli, &naddr);                     //5.�õ����ӽ�����socket
        if (socketCLi != INVALID_SOCKET) {
            //while (true)
            //{
                cout << "���ӳɹ�" << endl;
                cout << "������Ҫ���͸��ͻ��˵���Ϣ��" << endl;
                //cin >> sendbuf;
                send(socketCLi, (char*)senddate, sizeof(senddate), 0);                           //6.ʹ��send�������з�������
                
                recv(socketCLi, (char*)recdate, sizeof(recdate), 0);                           //7.ʹ��recv�������з�������
                for (int i = 0; i < 22; i++)
                {
                    //cout << "�ͻ��˷���������Ϣ�ǣ�" << (unsigned  char)recdate[i] << endl;
                    printf("�ͻ���������Ϣ�ǣ�%x\n", recdate[i]);
                }
                while ((byte)(recdate[19] >> 1)==0)        //�ж��Ƿ�ִ����
                {
                    recv(socketCLi, (char*)recdate, sizeof(recdate), 0);
                }
                senddate[0] = (byte)0x55;       //ǰ��100
                senddate[1] = (byte)0x02;
                senddate[2] = (byte)0x01;
                senddate[3] = (byte)0x02;
                senddate[4] = (byte)0x00;
                senddate[5] = (byte)0x00;
                senddate[6] = (byte)0x00;
                senddate[7] = (byte)0x01;
                senddate[8] = (byte)0x00;
                senddate[9] = (byte)0x00;
                senddate[10] = (byte)0x00;
                senddate[11] = (byte)0x00;
                senddate[12] = (byte)0x00;
                senddate[13] = (byte)0x64;
                senddate[14] = (byte)0x00;
                senddate[15] = (byte)0x00;
                senddate[16] = (byte)0x00;
                senddate[17] = (byte)0x01;
                senddate[18] = (byte)0xAA;

                send(socketCLi, (char*)senddate, sizeof(senddate), 0);

                recv(socketCLi, (char*)recdate, sizeof(recdate), 0);                           //7.ʹ��recv�������з�������
                for (int i = 0; i < 22; i++)
                {
                    //cout << "�ͻ��˷���������Ϣ�ǣ�" << (unsigned  char)recdate[i] << endl;
                    printf("�ͻ���������Ϣ�ǣ�%x\n", recdate[i]);
                }
                while ((byte)(recdate[19] >> 1)==0)        //�ж��Ƿ�ִ����
                {
                    recv(socketCLi, (char*)recdate, sizeof(recdate), 0);
                }
                if ((byte)(recdate[19] >> 1) == 1)
                {
                    break;
                }
           // }
        }
        else {
            cout << "����ʧ�ܣ�" << endl;
        }
    }
    closesocket(socketSer);
    closesocket(socketCLi);
    system("pause");
    return 0;
}