#include <iostream>
#include <windows.h> // U�̵Ĳ����⣬��Ҫ����windows.hͷ�ļ�
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
        cout << "��ӭʹ��U�̹���\n" << "��������Ҫ���еĲ�����\n" << endl;
        cout << "1). ���ñ����ļ���·��  2). �����ļ�" << endl;
        cout << "3). �����ļ���ָ��·��  0). �˳�����" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                Usteal::setPath();
                break;
            default:
                cout << "�����������������" << endl;
                break;
        }
    };
    void setPath() {
        cout << "�����뱣���ļ���·��(��֤Ŀ¼Ϊ��Ŀ¼):";
        string path;
        cin >> path;
        fs::path dir_path(path);

        while (!fs::exists(dir_path) || !fs::is_directory(dir_path) || !fs::is_empty(dir_path)) {
            cout << "·�������ڡ������ļ��л�Ϊ�գ�����������: ";
            cin >> path;
            dir_path = fs::path(path);
        }

        this->path_save_own = path;
        cout << "·�����óɹ�: " << path << endl;
    }

    void uInsertTest(char* path) {
        unsigned allDisk; // �����̷���λͼ
        char Up = 'A';

        cout << "���ڼ��U��..." << endl;
        while (true) {
            allDisk = GetLogicalDrives(); // ��ȡ�����̷���λͼ
            for (int i = 0; i < 26; i++) {
                if ((allDisk & 1) == 1) {
                    sprintf(path, "%c:\\", Up); // ����̷�ת��Ϊ�ַ���������path�����У���������ʹ��
                    if (GetDriveType(path) == DRIVE_REMOVABLE) { // �ж��̷������Ƿ�Ϊ���ƶ���U��
                        cout << "��⵽U�̲���: " << path << endl;
                        return; // ��⵽U�̺��˳�ѭ��
                    }
                }
                allDisk = allDisk >> 1; // λ������ж��̷�
                Up++;
            }
            Sleep(2000); // ��ʱ2��
        }
    }

    void FindFile(const char *path) {
        cout << "���ڲ����ļ�: " << path << endl;
        char temppath[260] = {0}; // �ļ��ĵ�ַ����󳤶�Ӧ�ò��ᳬ��260
        sprintf(temppath, "%s\\*.*", path);

        WIN32_FIND_DATA findData; // �ļ���Ϣ
        HANDLE hFind = FindFirstFile(temppath, &findData); // ���ҵ�һ�������������ļ�
        if (hFind == INVALID_HANDLE_VALUE) {
            cout << "FindFirstFile failed with error: " << GetLastError() << endl;
            return;
        }

        do { // ѭ���������з����������ļ�
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { // �ж��Ƿ�ΪĿ¼
                if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
                    sprintf(temppath, "%s\\%s", path, findData.cFileName);
                    cout << "�ҵ�Ŀ¼: " << temppath << endl;
                    FindFile(temppath); // �ݹ����Ŀ¼�µ��ļ�
                }
            } else {
                sprintf(temppath, "%s\\%s", path, findData.cFileName);
                cout << "�ҵ��ļ�: " << temppath << endl;
            }
        } while (FindNextFile(hFind, &findData)); // ������һ���ļ�

        FindClose(hFind); // �رղ��Ҿ��
    }

};

int main() {
//    char path[4] = {0}; // ֻ��Ҫ�洢�̷���ð��
//
//    Usteal usteal;
//    usteal.setPath();
//    usteal.uInsertTest(path);
//    usteal.FindFile(path); // ����������·��
    return 0;
}

