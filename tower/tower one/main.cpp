#include <iostream>
#include<fstream>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")                 //静态加载网络相关的API
#pragma warning(disable:4996)
//全局常量
SOCKET socketSer, socketCLi;
SOCKADDR_IN addrSer, addrCli;
int naddr = sizeof(SOCKADDR_IN);


byte recdate[22];                           //接收字符

class sendt
{
public:
    byte senddate[7] = { (byte)0xFF ,(byte)0x01 ,(byte)0x00 ,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0x00 };
    
};

//方向函数声明
void towerdown(sendt& s);
void towerup(sendt& s);
void towerqian(sendt& s);
void towerhou(sendt& s);
void towerzuo(sendt& s);
void toweryou(sendt& s);
void tower0(sendt& s);
void shoufa(sendt& tower);
void delay(int i);

int main()
{
    sendt tower;
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
    addrSer.sin_addr.S_un.S_addr = inet_addr("192.168.1.8");                           //2.建立socket的地址信息
    addrSer.sin_port = htons(1111);
    addrSer.sin_family = AF_INET;

    bind(socketSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));                             //3.绑定socket的基本信息
    while (true) 
    {
        cout << "开始连接！" << endl;
        listen(socketSer, 7);                                                           //4.开启监听

        //接受连接
        socketCLi = accept(socketSer, (SOCKADDR*)&addrCli, &naddr);                     //5.拿到连接进来的socket
        if (socketCLi != INVALID_SOCKET) {
            //while (true)
            //{
            cout << "连接成功" << endl;
            cout << "信息发送" << endl;
            int i1;
            cin >> i1;

            towerdown(tower);       //下降400
            tower.senddate[17] = (byte)0x01;
            shoufa(tower);
            
            if ((byte)(recdate[19] >> 1) == 1 && tower.senddate[17] == (byte)0x01)
            {
                tower0(tower);
                towerqian(tower);       //前进400
                tower.senddate[17] = (byte)0x02;
                shoufa(tower);
                
                if ((byte)(recdate[19] >> 1) == 1 && tower.senddate[17] == (byte)0x02)
                {
                    tower0(tower);
                    towerhou(tower);       //后退400
                    tower.senddate[17] = (byte)0x03;
                    shoufa(tower);

                    if ((byte)(recdate[19] >> 1) == 1 && tower.senddate[17] == (byte)0x03)
                    {
                        tower0(tower);
                        towerup(tower);       //上升400
                        tower.senddate[17] = (byte)0x04;
                        shoufa(tower);
                    }
                }
            }
            break;
        }
    }

    system("pause");
    return 0;
}

void towerdown(sendt &s)                //下降
{
    char a;
    s.senddate[3] = (byte)0x08;
    s.senddate[5] = (byte)0x01;
    a = s.senddate(1);
    a = (s.senddate(1) + s.senddate(2) + s.senddate(3) + s.senddate(4) + s.senddate(5)) && 0xFF;
    s.senddate[6] = (byte)[(s.senddate(1)+ s.senddate(2) + s.senddate(3) + s.senddate(4) + s.senddate(5) )&&0xFF];
}
void towerup(sendt& s)                //上升
{
    s.senddate[5] = (byte)0x01;
    s.senddate[10] = (byte)0x01;
    s.senddate[11] = (byte)0x90;
}
void towerqian(sendt& s)                //前进400
{
    s.senddate[7] = (byte)0x01;
    s.senddate[12] = (byte)0x01;
    s.senddate[13] = (byte)0x90;
}
void towerhou(sendt& s)                //后退400
{
    s.senddate[7] = (byte)0x02;
    s.senddate[12] = (byte)0x01;
    s.senddate[13] = (byte)0x90;
}
void towerzuo(sendt& s)                //左转60
{
    s.senddate[9] = (byte)0x01;
    s.senddate[15] = (byte)0x3C;
}
void toweryou(sendt& s)                //右转60
{
    s.senddate[9] = (byte)0x02;
    s.senddate[15] = (byte)0x3C;
}
void tower0(sendt& s)                //清零
{
    s.senddate[0] = (byte)0x55;
    s.senddate[1] = (byte)0x02;
    s.senddate[2] = (byte)0x01;
    s.senddate[3] = (byte)0x02;
    s.senddate[4] = (byte)0x00;
    s.senddate[5] = (byte)0x00;
    s.senddate[6] = (byte)0x00;
    s.senddate[7] = (byte)0x00;
    s.senddate[8] = (byte)0x00;
    s.senddate[9] = (byte)0x00;
    s.senddate[10] = (byte)0x00;
    s.senddate[11] = (byte)0x00;
    s.senddate[12] = (byte)0x00;
    s.senddate[13] = (byte)0x00;
    s.senddate[14] = (byte)0x00;
    s.senddate[15] = (byte)0x00;
    s.senddate[16] = (byte)0x00;
    s.senddate[17] = (byte)0x00;
    s.senddate[18] = (byte)0xAA;
}
void shoufa(sendt &tower)
{
    ofstream ofs;
    ofs.open("shoufa.txt", ios::out);
    send(socketCLi, (char*)tower.senddate, sizeof(tower.senddate), 0);                           //6.使用send函数进行发送数据
    for (int i = 0; i < 19; i++)
    {
        ofs << (int)tower.senddate[i];
        ofs << "\t";

    }

    recv(socketCLi, (char*)recdate, sizeof(recdate), 0);                           //7.使用recv函数进行发送数据
    for (int i = 0; i < 22; i++)
    {
        ofs << (int)recdate[i];
        ofs << "\t";
    }
    while ((byte)(recdate[19] >> 1) == 0)        //判断是否执行完
    {
        recv(socketCLi, (char*)recdate, sizeof(recdate), 0);
        for (int i = 0; i < 22; i++)
        {
            ofs << (int)recdate[i];
            ofs << "\t";
        }
    }
}
void delay(int i)
{
    while (i--);
}