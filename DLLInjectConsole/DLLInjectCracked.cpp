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
	//设置控制台大小
	system("mode con cols=55 lines=10  ");
	//设置控制台字体颜色
	system("color a");              
	//设置控制台标题
	SetConsoleTitle("DLL注入器v1.0 XinuxQQ:913499532");   
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
				cout << "输入卸载进程的PID：";
				cin >> pID;
				UnInjectDLL(pID);
			}
			break;
		case 0:
			exit(-1);
			break;
		default:
			cout << "输入有误！重新输入！" << endl;
			break;
		}
		system("pause");
	}
}

//注入DLL
void Inject(int pID ,char * Path) {
	//获取进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	//申请一块虚拟内存给DLL路径
	LPVOID pReturnAddres = VirtualAllocEx(hProcess, NULL, strlen(Path) + 1, MEM_COMMIT, PAGE_READWRITE);
	//把DLL所在位置 写到上边那块申请的虚拟内存中 
	WriteProcessMemory(hProcess, pReturnAddres, Path, strlen(Path) + 1, NULL);

	//获取LoadLibraryA函数的地址
	HMODULE hModule = LoadLibrary("Kernel32.dll");
	GetProcAddress(hModule,"LoadLibraryA");

	//创建远程线程
	HANDLE hThread = CreateRemoteThread(hProcess, NULL,0,(LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryA"), pReturnAddres, 0, NULL);
	if (hThread == NULL)
	{
		system("cls");
		cout << "--------------------www.xinux.vip---------------------" << endl;
		cout << "[-] 注入失败，错误信息:" << GetLastError() << endl;
		return;
	}


	//防止程序线程阻塞
	
	WaitForSingleObject(hThread, 2000);
	//防止内存泄漏
	CloseHandle(hThread);
	CloseHandle(hProcess);
	//FreeLibrary(,)
	cout << "[+] 注入成功！" << endl;
}
//Menu
void UnInjectDLL(int Pid) {
	cout << "--------------------www.xinux.vip---------------------" << endl;
	//获取进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	//申请一块虚拟内存给DLL路径 这个卸载直接寻址KERNEL32.DLL基址
	LPVOID pReturnAddres = (LPVOID)0x7ae00000;   //VirtualAllocEx(hProcess, NULL, strlen(Path) + 1, MEM_COMMIT, PAGE_READWRITE);
	

	//获取LoadLibraryA函数的地址
	//HMODULE hModule = LoadLibrary("Kernel32.dll");//0x76370000
	//GetProcAddress(hModule, "LoadLibraryA");      //0x763889c0

	//创建远程线程
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)0x763889c0, pReturnAddres, 0, NULL);
	if (hThread == NULL)
	{
		cout << "卸载失败，错误信息:" << GetLastError() << endl;
		return;
	}


	//防止程序线程阻塞

	WaitForSingleObject(hThread, 2000);
	//防止内存泄漏
	CloseHandle(hThread);
	CloseHandle(hProcess);
	//FreeLibrary(,)
	cout << "卸载DLL成功！" << endl;


}
void InjectInfo() {
	//Menu();
	cout << "--------------------www.xinux.vip---------------------" << endl;
	cout << "注入目标的进程Pid:";
	cin >> pID;
	cout << "注入DLL所在的路径:";
	cin >> str_arr;
	//cout << "原路径：" << str_arr << endl;
	while ((pos = str_arr.find("\\", pos)) != string::npos)
	{
		str_arr.insert(pos, "\\");
		pos = pos + 2;

	}
	//cout << "现路径：" << str_arr << endl;
	cout << "尝试向进程ID：" << pID << " 注入InjectDLL..." << endl;
	Inject(pID, (char*)str_arr.c_str());
}
void MenuTools() {
	cout << "--------------------www.xinux.vip---------------------" << endl;
	//cout << "Remote DLL Inject Tools" << endl;
	cout << "[1].远程注入DLL" << endl;
	cout << "[2].远程卸载DLL(目前存在Bug)" << endl;
	cout << "[0].退出" << endl;
	cout << "命令:" ;
}