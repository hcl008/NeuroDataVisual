/*#include "stdafx.h"*/
#pragma once;
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>



using namespace std;
typedef struct
{
	bitset<16> index;
	bitset<24> time;
	vector<bitset<19>> neuro_address;
	vector<bitset<40>> neuro_data;
}Frame;
class GenerateFakeData
{
public:
	ofstream ofile;
	GenerateFakeData();
	
	void WriteFile(vector<int>);
	void GenerateHeader(int time, int index);//return length = 128 string 
	vector<int> String128_2_int16(string);
	void GenerateAddress(int Intensity); //write Address
	void GenerateData(int Intensity);
	void GenerateFrame(int time, int index, int Intensity);
	void GeneratePackage();
	vector<int> Generate16int8(int Intensity, int Marker);
	string GenerateRand(int Intensity =0 );//generate a Random data with bonder 
	bitset<8> GenerateSeed(int step);
private:

};
class GetDataProcess
{

private:
	int RowNum;
	int RowStep;
	string tempData;
	string sumData;
	vector<vector<string>> Data;
	vector<vector<vector<string>>> PackageWithFrame;
	bitset<8> m_byte;
	ifstream infile;

// 	/*vector<Frame> m_FrameList;*/
// 	typedef struct
// 	{
// 		bitset<16> index;
// 		bitset<24> time;
// 		vector<bitset<19>> neuro_address;
// 		vector<bitset<40>> neuro_data;
// 	}Frame;
public:
	GetDataProcess();
	~GetDataProcess(){};
	int Input();
	void init();
	bool do_Facade_Data();
	vector<vector<vector<string>>> GetFrame(vector<vector<string>> Package); //input package with 128 bit vector and return package with frame vector
	void DecodePackage(vector<vector<vector<string>>>);
	vector<Frame> m_FrameList;
	
};
