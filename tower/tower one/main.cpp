#include <iostream>
#include<fstream>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
using namespace std;

#pragma comment(lib,"ws2_32.lib")                 //��̬����������ص�API
#pragma warning(disable:4996)
//ȫ�ֳ���
SOCKET socketSer, socketCLi;
SOCKADDR_IN addrSer, addrCli;
int naddr = sizeof(SOCKADDR_IN);


byte recdate[22];                           //�����ַ�

class sendt
{
public:
    byte senddate[7] = { (byte)0xFF ,(byte)0x01 ,(byte)0x00 ,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0x00 };
    
};

//����������
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
    addrSer.sin_addr.S_un.S_addr = inet_addr("192.168.1.8");                           //2.����socket�ĵ�ַ��Ϣ
    addrSer.sin_port = htons(1111);
    addrSer.sin_family = AF_INET;

    bind(socketSer, (SOCKADDR*)&addrSer, sizeof(SOCKADDR));                             //3.��socket�Ļ�����Ϣ
    while (true) 
    {
        cout << "��ʼ���ӣ�" << endl;
        listen(socketSer, 7);                                                           //4.��������

        //��������
        socketCLi = accept(socketSer, (SOCKADDR*)&addrCli, &naddr);                     //5.�õ����ӽ�����socket
        if (socketCLi != INVALID_SOCKET) {
            //while (true)
            //{
            cout << "���ӳɹ�" << endl;
            cout << "��Ϣ����" << endl;
            int i1;
            cin >> i1;

            towerdown(tower);       //�½�400
            tower.senddate[17] = (byte)0x01;
            shoufa(tower);
            
            if ((byte)(recdate[19] >> 1) == 1 && tower.senddate[17] == (byte)0x01)
            {
                tower0(tower);
                towerqian(tower);       //ǰ��400
                tower.senddate[17] = (byte)0x02;
                shoufa(tower);
                
                if ((byte)(recdate[19] >> 1) == 1 && tower.senddate[17] == (byte)0x02)
                {
                    tower0(tower);
                    towerhou(tower);       //����400
                    tower.senddate[17] = (byte)0x03;
                    shoufa(tower);

                    if ((byte)(recdate[19] >> 1) == 1 && tower.senddate[17] == (byte)0x03)
                    {
                        tower0(tower);
                        towerup(tower);       //����400
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

void towerdown(sendt &s)                //�½�
{
    char a;
    s.senddate[3] = (byte)0x08;
    s.senddate[5] = (byte)0x01;
    a = s.senddate(1);
    a = (s.senddate(1) + s.senddate(2) + s.senddate(3) + s.senddate(4) + s.senddate(5)) && 0xFF;
    s.senddate[6] = (byte)[(s.senddate(1)+ s.senddate(2) + s.senddate(3) + s.senddate(4) + s.senddate(5) )&&0xFF];
}
void towerup(sendt& s)                //����
{
    s.senddate[5] = (byte)0x01;
    s.senddate[10] = (byte)0x01;
    s.senddate[11] = (byte)0x90;
}
void towerqian(sendt& s)                //ǰ��400
{
    s.senddate[7] = (byte)0x01;
    s.senddate[12] = (byte)0x01;
    s.senddate[13] = (byte)0x90;
}
void towerhou(sendt& s)                //����400
{
    s.senddate[7] = (byte)0x02;
    s.senddate[12] = (byte)0x01;
    s.senddate[13] = (byte)0x90;
}
void towerzuo(sendt& s)                //��ת60
{
    s.senddate[9] = (byte)0x01;
    s.senddate[15] = (byte)0x3C;
}
void toweryou(sendt& s)                //��ת60
{
    s.senddate[9] = (byte)0x02;
    s.senddate[15] = (byte)0x3C;
}
void tower0(sendt& s)                //����
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
    send(socketCLi, (char*)tower.senddate, sizeof(tower.senddate), 0);                           //6.ʹ��send�������з�������
    for (int i = 0; i < 19; i++)
    {
        ofs << (int)tower.senddate[i];
        ofs << "\t";

    }

    recv(socketCLi, (char*)recdate, sizeof(recdate), 0);                           //7.ʹ��recv�������з�������
    for (int i = 0; i < 22; i++)
    {
        ofs << (int)recdate[i];
        ofs << "\t";
    }
    while ((byte)(recdate[19] >> 1) == 0)        //�ж��Ƿ�ִ����
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