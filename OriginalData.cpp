/*#include "stdafx.h"*/
#include "OriginalData.h"

#include <windows.h>
#include <vector>
#include <math.h>
#include <algorithm>
#define ADDRESS_LEN 7
#define DATA_LEN 86
using namespace std;
inline string bitset2string(bitset<8> bi)
{
	string s = "";
	char k;
	unsigned long temp_index1;
	temp_index1 = bi.to_ulong();
	s = bi.to_string();
	return s;
}
inline int bitset2int(bitset<8> bi)
{
	unsigned long temp_index1;
	temp_index1 = bi.to_ulong();
	int a = (int)temp_index1;
	return a;
}
void GetDataProcess::DecodePackage(vector<vector<vector<string>>> tempPackageWithFrame)
{
	vector<vector<string>> vec_frame;
	vector<string> vec_bit128;
	bitset<8> bit8;
	string temp_str;
	string temp_address_step = "";
	string temp_address = "";
	string temp_data_step = "";
	string temp_data;
	vector <bitset<8>> vec_bit8;
	bitset<128> bit128;
	
	
	unsigned long temp_index1, temp_index2;
	for (size_t i = 0; i < tempPackageWithFrame.size(); i++)
	{
		Frame tempframe;
		vec_frame = tempPackageWithFrame[i];
		for (size_t j = 0; j < vec_frame.size(); j++)
		{
			vec_bit8.clear();
			vec_bit128 = vec_frame[j];
			for (size_t k = 0; k < vec_bit128.size(); k++)
			{
					bit8 = (atoi(vec_bit128[k].c_str()));//convert str to bit set in 8 bit
					vec_bit8.push_back(bit8);
			}//for k
			if (j == 0)
			{
				temp_str = "";
				temp_str = bitset2string(vec_bit8[11]); 
				temp_str += bitset2string(vec_bit8[12]);
//				assert(temp_str.length() == 16);
				bitset<16> bit16(temp_str);
				tempframe.index = bit16;    //get index
				
				temp_str = "";
				temp_str = bitset2string(vec_bit8[13]);
				temp_str += bitset2string(vec_bit8[14]);
				temp_str += bitset2string(vec_bit8[15]);
				bitset<24> bit24(temp_str);
				tempframe.time = bit24;
				temp_str = "";

			}
			if (j >= 1 && j <= ADDRESS_LEN)
			{
				for (size_t l = 1; l < 16; l++)
				{
					temp_address_step += bitset2string(vec_bit8[l]);
				}
				temp_address += temp_address_step.substr(5, 114);
				temp_address_step = "";
			}
			if (j > ADDRESS_LEN && j < DATA_LEN + ADDRESS_LEN )
			{
				for (size_t l = 1; l < 16; l++)
				{
					temp_data_step += bitset2string(vec_bit8[l]);
				}
				temp_data += temp_data_step.substr(0,120);
				temp_data_step = "";
			}
		}//for j
		/*get address*/
		for (int q = 0; q < 36; q++)
		{
			string temp_addr19;
			temp_addr19 = temp_address.substr(q * 19, 19);
			bitset<19> bit19(temp_addr19);
			tempframe.neuro_address.push_back(bit19);
		}
		/*last 4 19bit group*/
		bitset<19> bit19_last1(temp_address.substr(778, 19));
		tempframe.neuro_address.push_back(bit19_last1);
		bitset<19> bit19_last2(temp_address.substr(759, 19));
		tempframe.neuro_address.push_back(bit19_last1);
		bitset<19> bit19_last3(temp_address.substr(740, 19));
		tempframe.neuro_address.push_back(bit19_last1);
		bitset<19> bit19_last4(temp_address.substr(721, 19));
		tempframe.neuro_address.push_back(bit19_last1);

		/*get data*/
		for (int q = 0; q < 255; q++)
		{
			bitset<40> bit40(temp_data.substr(q * 40, 40));
			tempframe.neuro_data.push_back(bit40);
		}
		bitset<40> bit40(temp_data.substr(temp_data.size()-41, 40));
		tempframe.neuro_data.push_back(bit40);
//		bitset<40> bit40_last(temp_data.substr)
		m_FrameList.push_back(tempframe);
	}//for i
	
}
vector<string> ReverseVect1(vector<string> input)
{
	vector<string> temp_bit128;
	
	for (int i = 15; i >= 0; i--)
	{
		temp_bit128.push_back(input[i]);
	}
	return temp_bit128;

}
inline vector<string> split_comer(string s)//split comer
{
	vector<string> vec_temp;
	string str_temp;
	string t_comer = ",";
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == t_comer[0])
		{
			if (str_temp.length()>0)
			{
				vec_temp.push_back(str_temp);
				str_temp = "";
			}
		}
		else
		{
			str_temp += s[i];
		}
	}
	return vec_temp;
}
/*handled package with frame contained*/
vector<vector<vector<string>>> GetDataProcess::GetFrame(vector<vector<string>> Package)
{
	vector <string> temp_bit128;
	vector<vector<string>> temp_frame;
	int temp_i = 0;
	bool Isframe = true;
	string temp_str = "";
	for (size_t i = 0; i < Package.size(); i++)
	{
		temp_i = 0;
		temp_bit128 = Package[i];
		if (temp_bit128.size() != 16)//can be modified with assert
		{
			continue;
		}
		for (int j = 15; j > 5; j--)
		{
			temp_i += atoi(temp_bit128[j].c_str());
		}
		if (temp_i == 0)//header get
		{
			temp_frame.push_back(ReverseVect1(temp_bit128)); //pushback header
			
			//todo add temp_bit128 into temp_frame
			if (i + 94 > Package.size())
			{
				break;
			}
			
			for (int k = 1; k <= ADDRESS_LEN; k++)
			{
				temp_bit128 = Package[i + k];
				if (temp_bit128[15] != "2")
				{
					//will record current curser to accerate iteration
					i += k;
					Isframe = false;
					temp_frame.clear();//clear workspack temp frame
					break;
				}
				else
				{
					temp_frame.push_back(ReverseVect1(temp_bit128));
				}
			}
			
			if (!Isframe)
			{
				Isframe = true;
				continue;
			}
			i += ADDRESS_LEN;
			for (int k = 1; k <= DATA_LEN; k++)
			{
				temp_bit128 = Package[i + k];
				if (temp_bit128[15] != "3")
				{
					//will record current curser to accerate iteration
					i += k;
					Isframe = false;
					temp_frame.clear(); //clear workspack temp frame
					break;
				}
				else
				{
					temp_frame.push_back(ReverseVect1(temp_bit128));
				}
			}
			if (!Isframe)
			{
				Isframe = true;
				continue;
			}
			i += DATA_LEN-1;
			PackageWithFrame.push_back(temp_frame);
			temp_frame.clear();
		}

	}
	return PackageWithFrame;
}

GetDataProcess::GetDataProcess()
{
	
	tempchar = new char[30];
	init();
}

int GetDataProcess::Input(int FrameIndex)
{
	vector<string> vectemp;
	int count = 0;
	bool isEof = false;
	string FileHeader = "C:\\Data\\spk_recorded";
	
	if (FrameIndex>=1)
	{
		itoa(FrameIndex, tempchar, 10);
		FileHeader += tempchar;
	}
	infile.open(FileHeader);//C:\\Users\\pc\\Downloads\\data\\O_synthetic.sk
	if (!infile)
	{
		cout << "can't find recorded data";

	}
	for (int i = 0; i < 1; i++)
	{
		if (isEof)
		{
			break;
		}
		for (int j = 0; j < 94; j ++)
		{
			if (infile.eof())
			{
				isEof = true;
				break;
			}
			else
			{
				infile >> tempData;
				vectemp = split_comer(tempData);
				Data.push_back(vectemp);
			}

		}
	}
	infile.close();
	QDir RemoveFile;
	QString QFileHeader = QString::fromStdString(FileHeader);

	//remove file




//	RemoveFile.remove(QFileHeader);






// 	if (infile.eof())
// 	{
// 		return 0;
// 	}
	return 1;
}

void GetDataProcess::init()
{
	int counter = 0;
	RowNum = 0;
	RowStep = 0;
	

}

bool GetDataProcess::do_Facade_Data(int FrameIndex)
{
	if (Input(FrameIndex) == 1)
	{
		PackageWithFrame = GetFrame(Data);
		DecodePackage(PackageWithFrame);
		PackageWithFrame.clear();
		Data.clear();
		return true;
	}
	else
	{
		return false;
	}

}

GenerateFakeData::GenerateFakeData()
{
	ofile.open("O_Fake.sk");
}



void GenerateFakeData::WriteFile(vector<int> vec_int16)
{
	for (int i = vec_int16.size() - 1; i >= 0; i--)
	{
		ofile << vec_int16[i] << ",";
	}
	ofile << endl;
}

void GenerateFakeData::GenerateHeader(int time, int index)
{
	vector<int> vec_int16;
	bitset<88> bit88;//sync data 88bit + 4 bit = 92 bit
	bit88.reset();
	bitset<8> bit8;
	bit8.reset();
	for (int i = 0; i < 11; i++)
	{
		vec_int16.push_back(bitset2int(bit8));
	}
// 	string time = GenerateRand();
// 	time += GenerateRand();
	/*
	for (int i = 0; i < 2; i++)
	{
		bitset<8> temp_bi8(GenerateRand());
		vec_int16.push_back(bitset2int(temp_bi8));
	}*/
	bitset<16> bi_index(index);
	string temp_str16 = bi_index.to_string();
	bitset<8> temp_bi8_1(temp_str16, 0, 8);
	bitset<8> temp_bi8_2(temp_str16, 8, 8);
	vec_int16.push_back(bitset2int(temp_bi8_1));
	vec_int16.push_back(bitset2int(temp_bi8_2));

	bitset<24> bi_time(time);
	string temp_str24 = bi_time.to_string();
	bitset<8> tempt_bi8_1(temp_str24, 0, 8);
	bitset<8> tempt_bi8_2(temp_str24, 8, 8);
	bitset<8> tempt_bi8_3(temp_str24, 16, 8);
	vec_int16.push_back(bitset2int(tempt_bi8_1));
	vec_int16.push_back(bitset2int(tempt_bi8_2));
	vec_int16.push_back(bitset2int(tempt_bi8_3));
//	bitset<16> bit16(time);

// 	string index = GenerateRand();
// 	index += GenerateRand();
// 	index += GenerateRand();
//	bitset<24> bit24(index);
// 	for (int i = 0; i < 3; i++)
// 	{
// 		bitset<8> temp_bi8(GenerateRand());
// 		vec_int16.push_back(bitset2int(temp_bi8));
// 	}
	WriteFile(vec_int16);
	int a1 = 0;
}

void GenerateFakeData::GenerateAddress(int Intensity)
{
	vector<int> vec_int16;
	vector<vector<int>> Address7; // 7 rows
	int marker = 2;
	for (int i = 0; i < 7; i ++)
	{
		Address7.push_back(Generate16int8(Intensity, marker));
	}
	for (int i = 0; i < 7; i++)
	{
		WriteFile(Address7[i]);
	}

}

void GenerateFakeData::GenerateData(int Intensity)
{
	vector<vector<int>> Data86;
	int marker = 3;
	for (int i = 0; i < 86; i++)
	{
		Data86.push_back(Generate16int8(Intensity, marker));
	}
	for (int i = 0; i < 86; i++)
	{
		WriteFile(Data86[i]);
	}
	int a = 0;
}

void GenerateFakeData::GenerateFrame(int time, int index, int Intensity)
{
	GenerateHeader(time, index);
	GenerateAddress(Intensity);
	GenerateData(Intensity);
}

void GenerateFakeData::GeneratePackage()
{

	/*generate a frame with index 0 ~ 4095*/
	for (int k = 1; k <= 5; k++)
	{
		for (int j = 0; j < 409; j++)
		{
			GenerateFrame(0, 409 * (k - 1) + j, k * 2);
		}
	}
	for (int k = 5; k >= 1; k--)
	{
		for (int j = 0; j < 409; j++)
		{
			GenerateFrame(0, 409 * (k - 1) + j, k * 2);
		}
	}
	for (int j = 0; j < 6; j++)
	{
		GenerateFrame(0,4090+j,0);
	}
	/*generate a  frame with index 0 ~ 4095*/
}

std::vector<int> GenerateFakeData::Generate16int8(int Intensity, int Marker)
{
	vector<int> vec_int16;
	vec_int16.push_back(Marker);
	for (int i = 0; i < 15; i++)
	{
		bitset<8> temp_bi8(GenerateRand(Intensity));
		vec_int16.push_back(bitset2int(temp_bi8));
	}
	return vec_int16;
}

std::string GenerateFakeData::GenerateRand(int Intensity)
{
//	Sleep(880);
//	srand((unsigned)time(NULL));

//	int rand_int = rand() % (255) + 0;
	bitset<8> bi = GenerateSeed(10-Intensity);
	string temp_s = bi.to_string();
	return temp_s;
}

bitset<8> GenerateFakeData::GenerateSeed(int step)
{
	int rand_int = rand() % (255) + 0;
	bitset<8> bi8(rand_int);
	for (int i = 0; i < step; i++)
	{
		int rand_int = rand() % (255) + 0;
		bitset<8> bi(rand_int);
		bi8 &= bi;
	}
	return bi8;
}
