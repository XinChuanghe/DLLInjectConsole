#include <Windows.h>
#include <iostream>
#include <cstring>
using namespace std;
string::size_type pos = 0;
string str_arr;
int pID;
void MenuTools();
void Inject(int pid,char * Path);
void UnInjectDLL(int Pid);
void InjectInfo();
void Info();
int main() {
	//���ÿ���̨��С
	system("mode con cols=55 lines=10  ");
	//���ÿ���̨������ɫ
	system("color a");              
	//���ÿ���̨����
	SetConsoleTitle("DLLע����v1.0 XinuxQQ:913499532");   
	int enter;
	while (true)
	{
		
		system("cls");
		MenuTools();
		cin >> enter;
		switch (enter)
		{
		case 1:
			system("cls");
			InjectInfo();
			break;
		case 2:
			system("cls");
			{
				cout << "����ж�ؽ��̵�PID��";
				cin >> pID;
				UnInjectDLL(pID);
			}
			break;
		case 0:
			exit(-1);
			break;
		default:
			cout << "���������������룡" << endl;
			break;
		}
		system("pause");
	}
}

//ע��DLL
void Inject(int pID ,char * Path) {
	//��ȡ���̾��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	//����һ�������ڴ��DLL·��
	LPVOID pReturnAddres = VirtualAllocEx(hProcess, NULL, strlen(Path) + 1, MEM_COMMIT, PAGE_READWRITE);
	//��DLL����λ�� д���ϱ��ǿ�����������ڴ��� 
	WriteProcessMemory(hProcess, pReturnAddres, Path, strlen(Path) + 1, NULL);

	//��ȡLoadLibraryA�����ĵ�ַ
	HMODULE hModule = LoadLibrary("Kernel32.dll");
	GetProcAddress(hModule,"LoadLibraryA");

	//����Զ���߳�
	HANDLE hThread = CreateRemoteThread(hProcess, NULL,0,(LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryA"), pReturnAddres, 0, NULL);
	if (hThread == NULL)
	{
		system("cls");
		cout << "--------------------www.xinux.vip---------------------" << endl;
		cout << "[-] ע��ʧ�ܣ�������Ϣ:" << GetLastError() << endl;
		return;
	}


	//��ֹ�����߳�����
	
	WaitForSingleObject(hThread, 2000);
	//��ֹ�ڴ�й©
	CloseHandle(hThread);
	CloseHandle(hProcess);
	//FreeLibrary(,)
	cout << "[+] ע��ɹ���" << endl;
}
//Menu
void UnInjectDLL(int Pid) {
	cout << "--------------------www.xinux.vip---------------------" << endl;
	//��ȡ���̾��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	//����һ�������ڴ��DLL·�� ���ж��ֱ��ѰַKERNEL32.DLL��ַ
	LPVOID pReturnAddres = (LPVOID)0x7ae00000;   //VirtualAllocEx(hProcess, NULL, strlen(Path) + 1, MEM_COMMIT, PAGE_READWRITE);
	

	//��ȡLoadLibraryA�����ĵ�ַ
	//HMODULE hModule = LoadLibrary("Kernel32.dll");//0x76370000
	//GetProcAddress(hModule, "LoadLibraryA");      //0x763889c0

	//����Զ���߳�
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)0x763889c0, pReturnAddres, 0, NULL);
	if (hThread == NULL)
	{
		cout << "ж��ʧ�ܣ�������Ϣ:" << GetLastError() << endl;
		return;
	}


	//��ֹ�����߳�����

	WaitForSingleObject(hThread, 2000);
	//��ֹ�ڴ�й©
	CloseHandle(hThread);
	CloseHandle(hProcess);
	//FreeLibrary(,)
	cout << "ж��DLL�ɹ���" << endl;


}
void InjectInfo() {
	//Menu();
	cout << "--------------------www.xinux.vip---------------------" << endl;
	cout << "ע��Ŀ��Ľ���Pid:";
	cin >> pID;
	cout << "ע��DLL���ڵ�·��:";
	cin >> str_arr;
	//cout << "ԭ·����" << str_arr << endl;
	while ((pos = str_arr.find("\\", pos)) != string::npos)
	{
		str_arr.insert(pos, "\\");
		pos = pos + 2;

	}
	//cout << "��·����" << str_arr << endl;
	cout << "���������ID��" << pID << " ע��InjectDLL..." << endl;
	Inject(pID, (char*)str_arr.c_str());
}
void MenuTools() {
	cout << "--------------------www.xinux.vip---------------------" << endl;
	//cout << "Remote DLL Inject Tools" << endl;
	cout << "[1].Զ��ע��DLL" << endl;
	cout << "[2].Զ��ж��DLL(Ŀǰ����Bug)" << endl;
	cout << "[0].�˳�" << endl;
	cout << "����:" ;
}