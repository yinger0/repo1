#include <iostream>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")                 //静态加载网络相关的API
#pragma warning(disable:4996)

//============全局常量=====================
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
    cout << "服务器启动" << endl;
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {                                    //1.向操作系统要socket
        cout << "载入socket错误" << endl;
        system("pause");
        return 0;
    }
    else {
        cout << "载入socket库成功" << endl;
    }

    socketSer = socket(AF_INET, SOCK_STREAM, 0);
    addrSer.sin_addr.S_un.S_addr = inet_addr("192.168.1.100");                           //2.建立socket的地址信息
    addrSer.sin_port = htons(1111);
    addrSer.sin_family = AF_INET;

    bind(socketSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));                             //3.绑定socket的基本信息
    senddate[0] = (byte)0x55;       //下降100
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
        cout << "开始连接！" << endl;
        listen(socketSer, 7);                                                           //4.开启监听

        //接受连接
        socketCLi = accept(socketSer, (SOCKADDR*)&addrCli, &naddr);                     //5.拿到连接进来的socket
        if (socketCLi != INVALID_SOCKET) {
            //while (true)
            //{
                cout << "连接成功" << endl;
                cout << "请输入要发送给客户端的信息：" << endl;
                //cin >> sendbuf;
                send(socketCLi, (char*)senddate, sizeof(senddate), 0);                           //6.使用send函数进行发送数据
                
                recv(socketCLi, (char*)recdate, sizeof(recdate), 0);                           //7.使用recv函数进行发送数据
                for (int i = 0; i < 22; i++)
                {
                    //cout << "客户端发送来的信息是：" << (unsigned  char)recdate[i] << endl;
                    printf("客户发来的信息是：%x\n", recdate[i]);
                }
                while ((byte)(recdate[19] >> 1)==0)        //判断是否执行完
                {
                    recv(socketCLi, (char*)recdate, sizeof(recdate), 0);
                }
                senddate[0] = (byte)0x55;       //前进100
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

                recv(socketCLi, (char*)recdate, sizeof(recdate), 0);                           //7.使用recv函数进行发送数据
                for (int i = 0; i < 22; i++)
                {
                    //cout << "客户端发送来的信息是：" << (unsigned  char)recdate[i] << endl;
                    printf("客户发来的信息是：%x\n", recdate[i]);
                }
                while ((byte)(recdate[19] >> 1)==0)        //判断是否执行完
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
            cout << "连接失败！" << endl;
        }
    }
    closesocket(socketSer);
    closesocket(socketCLi);
    system("pause");
    return 0;
}