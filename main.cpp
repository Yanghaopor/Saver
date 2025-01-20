#include "InTypeSendSQL.h"
#include "iostream"
#include "fstream"
#include "stdio.h"
#include "stdlib.h"
#include "iomanip"
#include "stream.h"
//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

//默认端口为"127.0.0.1"
//全局变量
int WHHight = GetSystemMetrics(SM_CYSCREEN); //高
int WHWither = GetSystemMetrics(SM_CXSCREEN);//长
double CpuUserge;	//cpu占用率
bool CpuUsergeButton = true; //CPU线程开关
double CpuMhz;	//cpu占用率
ComeputerInfo::CPUinfor CPU;

//主函数构造器 
//网络连接器
static void OpenNet();
//用户线程(Intel,用户套口)
static void HandleClient(IntelNet::InteS& server, SOCKET clientSocket);

//循环获取CPU占用率
void GetCPUuse() {
	while (CpuUsergeButton) {
		CpuUserge = CPU.getCpuUsage();
	}
}

//循环获取CPU频率
void GetCPUMhz() {
	while (CpuUsergeButton) {
		CpuMhz = CPU.GettoCPUmhz();
		//std::cout << CpuMhz << std::endl;
	}
}

//主函数入口
int main(void) {
	FreeConsole();
	//CPU获取

	system("chcp 65001");
	//初始文件
	ReadFilePrject(&PIIEG, "./Saver/jpeg.txt"); //图片
	ReadFilePrject(&VIDEO, "./Saver/video.txt"); //视频
	ReadFilePrject(&JavaSc, "./Saver/js.txt"); //脚本
	for (auto& pair : VIDEO) {
		//std::cout << pair.Name << std::endl;
		//std::cout << pair.URL << std::endl;
		//std::cout << pair.Type << std::endl;
		//std::cout << pair.Tag << std::endl;
	}

	//初始测试
	//std::cout << ComeputerInfo::GettoCPUmhz() << std::endl;
	//std::cout << CPU.getCpuUsage()*1000 << std::endl;
	//std::cout << Char_Take::wstringToString(CPU.GetCPUNameFromRegistry()) << std::endl;

	//创建CPU获取线程
	std::thread HelCPUusrge(GetCPUuse);
	HelCPUusrge.detach();
	std::thread HelCPUmhz(GetCPUMhz);
	HelCPUmhz.detach();

	//初始进入网页
	IdWebOpen::OpenWeb(R"(\main.html)");
	Sleep(1000);
	OpenNet();

	//内存回收
	CpuUsergeButton = false;

	return 0;
}


//网络连接器
void OpenNet() {

	//获取窗口句柄
	HWND windG = FindWindow(L"Chrome_WidgetWin_1", L"Saver1.2");
	if (windG) { //std::cout << "YesCome" << std::endl; 
	//更改大小
	MoveWindow(windG, WHWither * 0.25, WHHight * 0.25, WHWither * 0.5, WHHight * 0.5, SWP_SHOWWINDOW);
	//设定不可拉伸
	IdWebOpen::WebNotSize(windG);
	//设定窗口透明
	IdWebOpen::SetWebAlpha(windG, 250);
		
	}
	else
	{
		//std::cout << "NoCome" << std::endl;
		return;
	}

	//网络
	IntelNet::InteS* NetSet = new IntelNet::InteS; //网络变量
	NetSet->OpenIntOP(); //打开网络权限
	NetSet->OSset.agreement = true; //网络协议
	NetSet->OSset.Namber = 10; //接收人数
	NetSet->OSset.port = 80; //端口设置
	NetSet->MkIntNet(); //开始创建网络

	SOCKET UserMod; //创建字套存储
	sockaddr_in userADD; //新增用户
	int clientAddrSize = sizeof(userADD);//存储用户大小
	// 获取监听套接字
	SOCKET listenSocket = NetSet->GetScok();
	// 设置为非阻塞模式
	u_long mode = 1; // 1 for non-blocking, 0 for blocking
	ioctlsocket(listenSocket, FIONBIO, &mode);
	
	//为每个用户创建链接
	while (true) {
		//std::cout << CPU.GettoCPUmhz() << std::endl;
		//std::cout << CpuUserge * 10000 << std::endl;
		//显示使用率
		//内存使用率std::cout << ComeputerInfo::GetMemoryUsage() << std::endl;

		//创建线程
		UserMod = accept(NetSet->GetScok(), (struct sockaddr*)&userADD, &clientAddrSize);
		//为每个用户创建线程
		std::thread ThreadNet(HandleClient, std::ref(*NetSet), UserMod);
		ThreadNet.detach();
		//检测是否关闭
		if (!IsWindow(windG)) {
			break;
		}
	}
	delete NetSet;
}

// 处理客户端连接的函数
void HandleClient(IntelNet::InteS& server, SOCKET clientSocket) {
	//std::cout << "用户链接" << std::endl;
	//创建介绍字符
	char buffer[4096] = { 0 };
	int len = recv(clientSocket, buffer, sizeof(buffer), NULL);
	if (len > 0) {
		//链接后执行
		//std::cout << buffer << std::endl;
		std::vector<std::string>Name = IntelNet::GetNAME(buffer,"ID");
		std::vector<std::string>Data = IntelNet::GetData(buffer, "ID");
		//查看请求
		// --------------------------
		//进入初始界面
		//数据传输
		for (auto& name : Name) {
			//获取内存占用率
			if (name == "GetReme") {
				std::string Remem = std::to_string(ComeputerInfo::GetMemoryUsage());
				Remem = IntelNet::CreaPost("text/plain", Remem, Remem.size());
				send(clientSocket, Remem.c_str(), Remem.size(), NULL);
			}

			//获取内存总大小
			if (name == "GetRemeMax") {
				std::string Remem = std::to_string(ComeputerInfo::GetMemoryMax());
				Remem = IntelNet::CreaPost("text/plain", Remem, Remem.size());
				send(clientSocket, Remem.c_str(), Remem.size(), NULL);
			}

			//获取电脑的CPU使用率
			if (name == "GetCPUser") {
				std::string Remem = std::to_string(CpuUserge*1000);
				Remem = IntelNet::CreaPost("text/plain", Remem, Remem.size());
				send(clientSocket, Remem.c_str(), Remem.size(), NULL);
				//std::cout << Remem << std::endl;
			}

			//获取电脑的CPUMHZ
			if (name == "GetCPUmhz") {
				std::string Remem = std::to_string(CpuMhz/100);
				Remem = IntelNet::CreaPost("text/plain", Remem, Remem.size());
				send(clientSocket, Remem.c_str(), Remem.size(), NULL);
				//std::cout << Remem << std::endl;
				//std::cout << "NHZM:" << CpuMhz << std::endl;
				//std::cout << Remem << std::endl;
			}

			//初次获取CPUname
			if (name == "GetCpuName") {
				std::string Remem = Char_Take::wstringToString(CPU.GetCPUNameFromRegistry());
				Remem = IntelNet::CreaPost("text/plain", Remem, Remem.size());
				send(clientSocket, Remem.c_str(), Remem.size(), NULL);
			}
		}

		//内存回收
		Name.clear();
		Data.clear();

	}
	// 关闭客户端连接
	//std::cout << "链接结束" << std::endl;
	closesocket(clientSocket);
}
