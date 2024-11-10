//
// Created by asus on 2024/11/10.
//
#include <iostream>
#include <windows.h>
using namespace std;

void FindFile(const char* path);

int main() {
    unsigned allDisk; // �����̷���λͼ
    char path[5] = {0};
    char Up = 'A';

    cout << "���ڼ��U��..." << endl;
    while (1) {
        allDisk = GetLogicalDrives(); // ��ȡ�����̷���λͼ
        //cout << allDisk << endl;
        for (int i = 0; i < 10; i++) {
            if ((allDisk & 1) == 1) {
                sprintf(path, "%c:", Up); //����̷�ת��Ϊ�ַ���������path�����У���������ʹ��
                if (GetDriveType(path) == DRIVE_REMOVABLE) { // �ж��̷������Ƿ�Ϊ���ƶ���U��
                    cout << path << endl;
                    break;
                }
            }
            allDisk = allDisk >> 1; // λ������ж��̷�
            Up++;
        }
        if (GetDriveType(path) == DRIVE_REMOVABLE) {
            cout  << "��⵽U�̲��� " <<  path <<   endl;
            break;
        }

    }
    FindFile(path);
    return 0;
}

void FindFile(const char* path){
    //cout << "���ڲ���U���ļ�..." << endl;
    char temppath[100] = {0};
    sprintf(temppath, "%s\\*.*", path);

    WIN32_FIND_DATA findData; // �ļ���Ϣ
    HANDLE hFind = FindFirstFile(temppath, &findData); // ���ҵ�һ�������������ļ�
    while (1) { // ѭ���������з����������ļ�
        if(findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){ // �ж��Ƿ�ΪĿ¼
            if(findData.cFileName[0] != '.'){
                sprintf(temppath, "%s\\%s", path, findData.cFileName);
                FindFile(temppath); // �ݹ����Ŀ¼�µ��ļ�
            }
        }else{
            sprintf(temppath, "%s\\%s", path, findData.cFileName);
        }

        cout << temppath << endl;
        if (!FindNextFile(hFind, &findData)) { // ������һ���ļ�
            break;
        }
    }

}
