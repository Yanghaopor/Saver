#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <Pdh.h>
#include <PdhMsg.h>
std::mutex mtx;
std::atomic<bool>running(true);
#pragma comment(lib,"pdh.lib") 

bool WM_ML = false;//�ж�����������
ExMessage msg;//��Ϣ��

void DWhUBL(std::wstring *WINcode) { //����ϵͳ�汾��ȡ
	OSVERSIONINFOEX osvi = { sizeof(osvi) };
	*WINcode = L"��ǰϵͳ�汾(WIN8.1����):"+std::to_wstring(osvi.dwMajorVersion) + L"." + std::to_wstring(osvi.dwMinorVersion) + L"." + std::to_wstring(osvi.dwBuildNumber);
}

void SaveALL() { //����ϵͳ
	system("mkdir SYSTEMSAVE");
	system("systeminfo >./SYSTEMSAVE/systeminfo.txt");
	system("ver >./SYSTEMSAVE/ver.txt");
	system("wmic path win32_videoController get name,DriverVersion,VideoProcessor >./SYSTEMSAVE/GPUSAVE.txt");
	system("wmic cpu get name >./SYSTEMSAVE/SAVECPU.txt");
	system("driverquery >./SYSTEMSAVE/alldriverquery.txt ");
	system("ipconfig /all >./SYSTEMSAVE/ipconfig.txt ");
	system("set >./SYSTEMSAVE/set.txt ");
	system("wmic useraccount get name >./SYSTEMSAVE/user.txt");
	system("wmic sounddev list full >./SYSTEMSAVE/sounddev.txt");
}

 void GetCPUmhz( double *GetCPUSPEED) {  //CPUƵ�ʲ���
	 while (true)
	 {
		 HQUERY query;
		 //��PDH
		 PDH_STATUS status = PdhOpenQuery(NULL, NULL, &query);

		 HCOUNTER cpuPerformance;
		 HCOUNTER cpuBasicSpeed;

		 //���CPU��ǰ���ܵļ�����
		 status = PdhAddCounter(query, TEXT("\\Processor Information(_Total)\\% Processor Performance"), NULL, &cpuPerformance);

		 //���CPU��׼Ƶ�ʵļ�����
		 status = PdhAddCounter(query, TEXT("\\Processor Information(_Total)\\Processor Frequency"), NULL, &cpuBasicSpeed);

		 //�ռ����� ��ܶ������Ҫ����ֵ ������Ҫ��������Query(�������1s) Ȼ���ٻ�ȡ����ֵ
		 PdhCollectQueryData(query);
		 Sleep(1000);
		 PdhCollectQueryData(query);

		 PDH_FMT_COUNTERVALUE pdhValue;
		 DWORD dwValue;

		 status = PdhGetFormattedCounterValue(cpuPerformance, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		 double cpu_performance = pdhValue.doubleValue / 100.0;

		 status = PdhGetFormattedCounterValue(cpuBasicSpeed, PDH_FMT_DOUBLE, &dwValue, &pdhValue);
		 double basic_speed = pdhValue.doubleValue;

		 //�ر�PDH
		 PdhCloseQuery(query);

		 *GetCPUSPEED=(double)(cpu_performance * basic_speed);
	 }
}

void MouseMsg(int Hes,int Wes) //��Ϣѭ���̺߳���
{
	while (running)
	{
		msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) { WM_ML = true; } //�ж�������
		else if (msg.message == WM_LBUTTONUP) { WM_ML = false; }
	}
	return;
}

void MesgBox(int Wes,int Hes) {
	while (true) {
		//Wes*0.85, Hes*0.05, Wes*0.95, Hes * 0.1
		std::cout << WM_ML << std::endl;
		if(msg.x>= Wes * 0.85&&msg.y>= Hes * 0.05&&msg.x<= Wes * 0.95&&msg.y <= Hes * 0.1&&WM_ML==true)
		{
			MessageBox(NULL,L"��վδ������ȫ", L"��ʾ",NULL );
		}
		//Wes * 0.85, Hes * 0.15, Wes * 0.95, Hes * 0.2
		if(msg.x >= Wes * 0.85 && msg.y >= Hes * 0.15 && msg.x <= Wes * 0.95 && msg.y <= Hes * 0.2 && WM_ML == true)
		{
			MessageBox(NULL, L"����ɹ��������ڱ�Ӧ������λ��SYSTEMSAVE�ļ�", L"��ʾ", NULL);
			SaveALL();
		}
	}
}

 std::wstring GetNameSave() {  //��ȡ�ļ�����
	std::string FillName = "save.txt";
	std::string line;
	std::ifstream cots(FillName);

	std::getline(cots, line);
	std::getline(cots, line);

	std::wstring Line = L"CPU:";
	for (int i = 0; i <= line.length(); i++) {
		Line = L""+line[i];
		std::wcout << Line << std::endl;
	}

	return Line;
}

void Presd(UINT16 PRS,wchar_t Gh[],int Hes,int Wes) //�ܹ����ͷֱ�
{
	switch (PRS)
	{
	case 0:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:X86");
		break;
	case 1:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:MIPS");
		break;
	case 2:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:ARM");
		break;
	case 3:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:POWERPC");
		break;
	case 4:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:SHX");
		break;
	case 5:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:PC:X86");
		break;
	case 6:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:ltanium");
		break;
	case 7:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:Alpha");
		break;
	case 8:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:MSIL");
		break;
	case 9:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:X64/AMD64");
		break;
	case 10:
		outtextxy(Wes * 0.06, Hes * 0.06, L"CPU�ܹ�:IA32");
		break;
	}
	return;
}

void CPUType(UINT32 les, int Hes, int Wes) 
{
	switch (les)
	{
	case 386:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:Intel80386");
		break;
	case 486:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:Intel40486");
		break;
	case 586:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:Intel-Pentium");
		break;
	case 2200:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:Intel-Itanium");
		break;
	case 8664:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:X86_X64");
		break;
	case 4000:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:MIPS4000");
		break;
	case 7000:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:ARM 7TDMI");
		break;
	case 397:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:SHX");
		break;
	case 601:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:PowerPc601");
		break;
	case 603:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:PowerPc603");
		break;
	case 604:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:PowerPc604");
		break;
	case 107:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:Hitachi SH3");
		break;
	case 108:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:Hitachi SH4");
		break;
	case 821:
		outtextxy(Wes * 0.06, Hes * 0.09, L"CPU����:Motorola 821");
		break;
	default:
		break;
	}

}

void Grgp(int *Hes,int *Wes,int RGBsTake[])//initgrph���洴�� 
{
	while (true) 
	{
		system("cls");
		std::cout << "HPD:����ߺͿ�" << std::endl;
		std::cin >> *Hes;
		std::cin >> *Wes;
		system("cls");
		std::cout << "�������RGB��ɫ(0-255) RGBs-->0-2" << std::endl;
		std::cout << "RGBs[0]:";
		std::cin >> RGBsTake[0];
		std::cout << "\nRGBs[1]:";
		std::cin >> RGBsTake[1];
		std::cout << "\nRGBs[2]:";
		std::cin >> RGBsTake[2];
		break;
	}
	return;
}

int RedTake(int Hes, int Wes, int RGBsTake[]) //����
{
	A1:
	std::string BlasRes;
	while (true) 
	{
		system("cls");
		std::cout << "Your Setting H&W->" << Hes << " " << Wes << std::endl;
		std::cout << "RGBs:" << RGBsTake[0] << " " << RGBsTake[1] << " " << RGBsTake[2] << std::endl;
		std::cout << "Input Yes/No" << std::endl;
		std::cin >> BlasRes;
		if (BlasRes == "Yes") 
		{
			return 1;
		}
		else if (BlasRes == "No") 
		{
			return 2;
		}
		else { system("cls"); goto A1; }
	}
}

void DrendGrps(int Hes,int Wes,int RGBsT[]) //�������� 
{
	initgraph(Wes,Hes);
	wchar_t PrsCPU[50];
	std::wstring CPUprName;//cpu�ͺ�
	CPUprName = GetNameSave();//��ȡCPU��Ϣ
	const wchar_t* UINAME_cpu;
	std::wstring CPUprName1 = L"CPU:��ΪEasyx���ַ�����Save.txt�鿴" + CPUprName;
	
	cleardevice();
	setbkcolor(RGB(RGBsT[0], RGBsT[1], RGBsT[2]));

	SYSTEM_INFO SystemInfo;
	MEMORYSTATUSEX memlnfo;

	UINT16 CPUprsen; //�ܹ�
	UINT32 CPUTyer;  //����
	UINT64 MinCPUROM, MaxCPUROM; //cpu��С�������ַ

	double CPUMSG;//cpu�ٶ�
	std::thread FolldTakeMsg(MouseMsg,Hes,Wes);//�̴߳���
	std::thread TakeCPUmsg(GetCPUmhz, &CPUMSG);
	std::thread MesgB(MesgBox, Wes, Hes);

	FolldTakeMsg.detach();
	TakeCPUmsg.detach();
	MesgB.detach();
	while (true) 
	{

		setbkmode(TRANSPARENT);
		GetSystemInfo(&SystemInfo);//��ȡCPU��Ϣ
		memlnfo.dwLength = sizeof(MEMORYSTATUSEX);

		CPUprsen = SystemInfo.wProcessorArchitecture;
		CPUTyer = SystemInfo.dwProcessorType;
		MinCPUROM = (unsigned long long )SystemInfo.lpMinimumApplicationAddress;
		MaxCPUROM = (unsigned long long)SystemInfo.lpMaximumApplicationAddress;
		std::wstring MA = L"CPU����ڴ��ַ:"+std::to_wstring(MaxCPUROM);
		std::wstring MN = L"CPU��С�ڴ��ַ:"+std::to_wstring(MinCPUROM);
		std::wstring CPUcode = L"CPU������:" + std::to_wstring(SystemInfo.dwNumberOfProcessors);
		std::wstring CPUsRsize = L"�ڴ�ҳ��С:" + std::to_wstring(SystemInfo.dwPageSize);
		std::wstring OldOEM = L"ԭʼ�����̱�ʶ:" + std::to_wstring(SystemInfo.dwOemId);
		std::wstring VecCode = L"��ǰCPUλ����:" + std::to_wstring(SystemInfo.dwActiveProcessorMask);
		std::wstring RomTake = L"�ڴ��������:" + std::to_wstring(SystemInfo.dwAllocationGranularity);
		std::wstring CPUNAME = CPUprName1;
		std::wstring CPUXD = L"CPU�޶��汾:" + std::to_wstring(SystemInfo.wProcessorRevision);
		std::wstring CPUSP = L"CPU��ǰƵ��:" + std::to_wstring(CPUMSG)+L"Mhz";
		std::wstring WINXX; DWhUBL(&WINXX);//��ȡϵͳ�汾

		const wchar_t* MAXR = MA.c_str();
		const wchar_t* MINR = MN.c_str();
		const wchar_t* CCODE = CPUcode.c_str();
		const wchar_t* CPRSZ = CPUsRsize.c_str();
		const wchar_t* OEM = OldOEM.c_str();
		const wchar_t* VCPU = VecCode.c_str();
		const wchar_t* ROMT = RomTake.c_str();
		const wchar_t* CPUname = CPUprName1.c_str();
		const wchar_t* CPUSPEED = CPUSP.c_str();
		const wchar_t* WINX = WINXX.c_str();

		//std::cout << CPUprsen << std::endl;
		//std::cout << CPUTyer << std::endl;
		

		BeginBatchDraw();

		//����ɫ����
		clearcliprgn();
		setbkcolor(RGB(RGBsT[0] - 10, RGBsT[1] - 10, RGBsT[2] - 10));

		setfillcolor(RGB(RGBsT[0], RGBsT[1], RGBsT[2]));
		fillrectangle(Wes * 0.05, Hes * 0.05, Wes * 0.8, Hes * 0.8);
		//��ѧ
		setfillcolor(RGB(RGBsT[0], RGBsT[1], RGBsT[2]));
		fillrectangle(Wes*0.85, Hes*0.05, Wes*0.95, Hes * 0.1);
		outtextxy(Wes * 0.86,Hes*0.06, L"��ѧ");
		//����
		fillrectangle(Wes * 0.85, Hes * 0.15, Wes * 0.95, Hes * 0.2);
		outtextxy(Wes * 0.86, Hes * 0.16, L"����");

		settextstyle(Hes*0.04, NULL,NULL);
		settextcolor(RGB(0, 0, 0));

		//�������
		Presd(CPUprsen, PrsCPU,Hes,Wes);
		CPUType(CPUTyer, Hes, Wes);
		outtextxy(Wes * 0.06, Hes * 0.12, MAXR);
		outtextxy(Wes * 0.06, Hes * 0.15, MINR);
		outtextxy(Wes * 0.06, Hes * 0.18, CCODE);
		outtextxy(Wes * 0.06, Hes * 0.21, CPRSZ);
		outtextxy(Wes * 0.06, Hes * 0.24, OEM);
		outtextxy(Wes * 0.06, Hes * 0.27, VCPU);
		outtextxy(Wes * 0.06, Hes * 0.30, ROMT);
		outtextxy(Wes * 0.06, Hes * 0.33, CPUprName1.c_str());
		outtextxy(Wes * 0.06, Hes * 0.36, CPUXD.c_str());
		outtextxy(Wes * 0.45, Hes * 0.12, CPUSPEED);
		outtextxy(Wes * 0.45, Hes * 0.15, L"GPU(�Կ�)ͬCPU���ͺŲ鿴gpu.txt");
		outtextxy(Wes * 0.45, Hes * 0.18, WINX);
		outtextxy(Wes * 0.45, Hes * 0.6, L"�����ߣ�Gura/��������   С��");
		outtextxy(Wes * 0.45, Hes * 0.9, L"�汾��Alpha0.0.1");


		if (GlobalMemoryStatusEx(&memlnfo)) //�ڴ�ʶ��
		{
			std::wstring ROMTKING = L"�ڴ�ʹ����:" + std::to_wstring(memlnfo.dwMemoryLoad)+L"%";
			std::wstring ALLROM = L"�����ڴ�����:" + std::to_wstring(memlnfo.ullTotalPhys);
			std::wstring USERROM = L"�����ڴ�����:" + std::to_wstring(memlnfo.ullAvailPhys);
			std::wstring UROMALL = L"��ҳ���С:" + std::to_wstring(memlnfo.ullTotalPageFile);
			std::wstring USERUROM = L"����ҳ���С:" + std::to_wstring(memlnfo.ullAvailPageFile);
			std::wstring ULLUROM = L"�������ڴ�:" + std::to_wstring(memlnfo.ullTotalVirtual);
			std::wstring USULLROM = L"���������ڴ�:" + std::to_wstring(memlnfo.ullAvailVirtual);
			std::wstring KEULLROM = L"���õ���չ�����ڴ��С:" + std::to_wstring(memlnfo.ullAvailExtendedVirtual);
			const wchar_t* ROMTDING = ROMTKING.c_str();
			const wchar_t* ALLTOROM = ALLROM.c_str();
			const wchar_t* USEROM = USERROM.c_str();
			const wchar_t* TROMTALL = UROMALL.c_str();
			const wchar_t* USERUROMT = USERUROM.c_str();
			const wchar_t* ULLROMALL = ULLUROM.c_str();
			const wchar_t* USULROM = USULLROM.c_str();
			const wchar_t* KEULROM = KEULLROM.c_str();
			outtextxy(Wes * 0.06, Hes * 0.42, L"�ڴ����:");
			outtextxy(Wes * 0.06, Hes * 0.45, ROMTDING);
			outtextxy(Wes * 0.06, Hes * 0.48, ALLTOROM);
			outtextxy(Wes * 0.06, Hes * 0.51, USEROM);
			outtextxy(Wes * 0.06, Hes * 0.54, TROMTALL);
			outtextxy(Wes * 0.06, Hes * 0.57, USERUROMT);
			outtextxy(Wes * 0.06, Hes * 0.60, ULLROMALL);
			outtextxy(Wes * 0.06, Hes * 0.63, USULROM);
			outtextxy(Wes * 0.06, Hes * 0.66, KEULROM);
		}


		EndBatchDraw();
	}
}

int main() 
{
	system("chcp65001");
	MAIN1:
	int Hes, Wes;//�߿�
	int RGBsTake[2];
	int Hlsop = 0;//������
	Grgp(&Hes,&Wes,RGBsTake);
	Hlsop=RedTake(Hes, Wes, RGBsTake);
	if (Hlsop == 2) { goto MAIN1; }
	system("wmic cpu get name > save.txt"); //��ȡCPU��Ϣ
	system("wmic path win32_VideoController get name > gpu.txt");

	DrendGrps(Hes,Wes,RGBsTake);
	running = false;
}


















