#pragma once
#include "vector"
#include "fstream"
#include "string.h"


//资源结构体
struct PrjectURL
{
	std::string Name = " "; //资源名称
	std::string URL = " ";//资源所在地址
	std::string Type = " "; //文件类型
	std::string Tag = " "; //备注
};
std::vector<PrjectURL>PIIEG; //图片存储向量
std::vector<PrjectURL>VIDEO; //视频存储向量
std::vector<PrjectURL>JavaSc; //JS文件存储
std::vector<PrjectURL>HTTP; //HTTP文件存储

//存储向量(向量，文件)
void OutFilePrject(std::vector<PrjectURL>File,std::string outfile) {
	//打开文件
	std::ofstream OutFile(outfile);

	for (auto& pair : File) {
		//依次存入文件
		OutFile << pair.Name + "\n";
		OutFile << pair.URL + "\n";
		OutFile << pair.Type + "\n";
		OutFile << pair.Tag + "\n";
	}
	OutFile.close();
}

//读取文件(向量，文件)
void ReadFilePrject(std::vector<PrjectURL>*File, std::string outfile) {
	//打开文件

	std::ifstream infile(outfile);
	int i = 0;
	std::string line;
	PrjectURL Saver;
	while (std::getline(infile, line)) {
		switch (i)
		{
		case 0:
			Saver.Name = line;
			break;
		case 1:
			Saver.URL = line;
			break;
		case 2:
			Saver.Type = line;
			break;
		}
		if (i == 3) {
			Saver.Tag = line;
			File->push_back(Saver);
			i = 0;
			continue;
		}
		//std::cout << line << std::endl;
		i++;
	}
	infile.close();
}


std::string JSCODE = "document.write(\"<h1>你好</h1>\")";