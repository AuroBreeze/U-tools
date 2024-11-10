#include <iostream>
#include <windows.h> // U盘的插入检测，需要引入windows.h头文件
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

class Usteal {
private:
    string file_name[100];
    string path_save_own;
public:
    int Start() {
        cout << "欢迎使用U盘工具\n" << "请输入你要进行的操作：\n" << endl;
        cout << "1). 设置保存文件的路径  2). 查找文件" << endl;
        cout << "3). 保存文件到指定路径  0). 退出程序" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                Usteal::setPath();
                break;
            default:
                cout << "输入错误，请重新输入" << endl;
                break;
        }
    };
    void setPath() {
        cout << "请输入保存文件的路径(保证目录为空目录):";
        string path;
        cin >> path;
        fs::path dir_path(path);

        while (!fs::exists(dir_path) || !fs::is_directory(dir_path) || !fs::is_empty(dir_path)) {
            cout << "路径不存在、不是文件夹或不为空，请重新输入: ";
            cin >> path;
            dir_path = fs::path(path);
        }

        this->path_save_own = path;
        cout << "路径设置成功: " << path << endl;
    }

    void uInsertTest(char* path) {
        unsigned allDisk; // 所有盘符的位图
        char Up = 'A';

        cout << "正在检测U盘..." << endl;
        while (true) {
            allDisk = GetLogicalDrives(); // 获取所有盘符的位图
            for (int i = 0; i < 26; i++) {
                if ((allDisk & 1) == 1) {
                    sprintf(path, "%c:\\", Up); // 会把盘符转换为字符串并存入path数组中，当作缓存使用
                    if (GetDriveType(path) == DRIVE_REMOVABLE) { // 判断盘符类型是否为可移动的U盘
                        cout << "检测到U盘插入: " << path << endl;
                        return; // 检测到U盘后退出循环
                    }
                }
                allDisk = allDisk >> 1; // 位运算符判断盘符
                Up++;
            }
            Sleep(2000); // 延时2秒
        }
    }

    void FindFile(const char *path) {
        cout << "正在查找文件: " << path << endl;
        char temppath[260] = {0}; // 文件的地址的最大长度应该不会超过260
        sprintf(temppath, "%s\\*.*", path);

        WIN32_FIND_DATA findData; // 文件信息
        HANDLE hFind = FindFirstFile(temppath, &findData); // 查找第一个符合条件的文件
        if (hFind == INVALID_HANDLE_VALUE) {
            cout << "FindFirstFile failed with error: " << GetLastError() << endl;
            return;
        }

        do { // 循环查找所有符合条件的文件
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // 判断是否为目录
                if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
                    sprintf(temppath, "%s\\%s", path, findData.cFileName);
                    cout << "找到目录: " << temppath << endl;
                    FindFile(temppath); // 递归查找目录下的文件
                }
            } else {
                sprintf(temppath, "%s\\%s", path, findData.cFileName);
                cout << "找到文件: " << temppath << endl;
            }
        } while (FindNextFile(hFind, &findData)); // 查找下一个文件

        FindClose(hFind); // 关闭查找句柄
    }

};

int main() {
//    char path[4] = {0}; // 只需要存储盘符和冒号
//
//    Usteal usteal;
//    usteal.setPath();
//    usteal.uInsertTest(path);
//    usteal.FindFile(path); // 传递完整的路径
    return 0;
}

