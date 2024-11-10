//
// Created by asus on 2024/11/10.
//
#include <iostream>
#include <windows.h>
using namespace std;

void FindFile(const char* path);

int main() {
    unsigned allDisk; // 所有盘符的位图
    char path[5] = {0};
    char Up = 'A';

    cout << "正在检测U盘..." << endl;
    while (1) {
        allDisk = GetLogicalDrives(); // 获取所有盘符的位图
        //cout << allDisk << endl;
        for (int i = 0; i < 10; i++) {
            if ((allDisk & 1) == 1) {
                sprintf(path, "%c:", Up); //会把盘符转换为字符串并存入path数组中，当作缓存使用
                if (GetDriveType(path) == DRIVE_REMOVABLE) { // 判断盘符类型是否为可移动的U盘
                    cout << path << endl;
                    break;
                }
            }
            allDisk = allDisk >> 1; // 位运算符判断盘符
            Up++;
        }
        if (GetDriveType(path) == DRIVE_REMOVABLE) {
            cout  << "检测到U盘插入 " <<  path <<   endl;
            break;
        }

    }
    FindFile(path);
    return 0;
}

void FindFile(const char* path){
    //cout << "正在查找U盘文件..." << endl;
    char temppath[100] = {0};
    sprintf(temppath, "%s\\*.*", path);

    WIN32_FIND_DATA findData; // 文件信息
    HANDLE hFind = FindFirstFile(temppath, &findData); // 查找第一个符合条件的文件
    while (1) { // 循环查找所有符合条件的文件
        if(findData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){ // 判断是否为目录
            if(findData.cFileName[0] != '.'){
                sprintf(temppath, "%s\\%s", path, findData.cFileName);
                FindFile(temppath); // 递归查找目录下的文件
            }
        }else{
            sprintf(temppath, "%s\\%s", path, findData.cFileName);
        }

        cout << temppath << endl;
        if (!FindNextFile(hFind, &findData)) { // 查找下一个文件
            break;
        }
    }

}
