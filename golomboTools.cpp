#define _CRT_SECURE_NO_WARNINGS
#include "golomboTools.h"

GolomboTools::GolomboTools(){}
GolomboTools::~GolomboTools(){}

void GolomboTools::writeStremInFile(char *nameStreamFile, vector<unsigned char> &stream, int sizeStream)
{
	FILE *file = fopen(nameStreamFile, "wb");

	for (int i = 0; i < sizeStream; i++)
	{
		fwrite(&stream, 1, sizeof(unsigned char)*sizeStream, file);
	}

	fclose(file);
}

void GolomboTools::readStremFromFile(char *nameStreamFile, vector<unsigned char> &stream, int sizeStream)
{
	FILE *file = fopen(nameStreamFile, "rb");
	unsigned char *ch = new unsigned char [sizeStream];

	fread(ch, 1, sizeof(unsigned char)*sizeStream, file);	
	for (int i = 0; i < sizeStream; i++)
	{
		stream.push_back(ch[i]);
	}
	fclose(file);
}

void GolomboTools::generateStream(int sizeStream, float p, char* nameStreamFile)
{
	vector <unsigned char> stream;
	bool flag;
	int count;
	float tmp;

	for (int i = 0; i < sizeStream; i++)
	{
		flag = false;
		count = 0;
		tmp = float(rand()) / RAND_MAX;

		if (tmp > p)
		{
			flag = true;
		}

		while (!flag)
		{
			tmp = float(rand()) / RAND_MAX;
			if (tmp > p)
			{
				flag = true;
			}
			count++;

			if (count > 255)
			{
				count = 255;
				flag = true;
			}
		}

		stream.push_back(count);
	}

	writeStremInFile(nameStreamFile, stream, sizeStream);
}

int GolomboTools::getBestM(float p)
{
	int m = 1;
	float pr = float(1) / (p + 1);
	bool flag = false;
	float lP = 0;
	float rP = 0;

	while (1)
	{
		lP = pow(p, (float)m);
		rP = pow(p, (float)(m - 1));

		if (pr >= lP && pr < rP)
		{
			flag = true;
			break;
		}
		else
		{
			m++;
		}
	}
	return m;
}

void GolomboTools::writeBits(char *nameStreamFile, vector <bool> &encodingStream)
{
	FILE *file = fopen(nameStreamFile, "wb");
	bitset <8> byte;
	unsigned char ch;
	bool exit = false;

	for (int i = 0; i < encodingStream.size(); i += 8)
	{
		for (int j = i; j < i + 8; j++)
		{
			if (j >= encodingStream.size())
			{
				exit = true;
			}
			else
			{
				byte[j - i] = encodingStream[j];
			}
		}

		ch = byte.to_ullong();
		fwrite(&ch, 1, sizeof(unsigned char), file);
		if (exit == true)
			break;
	}
	fclose(file);
}

void GolomboTools::getStatistics(vector<unsigned char> stream, float p)
{
	float h = 0;
	int maxSizeOfArray = 1000;
	int *statistics = new int[maxSizeOfArray];
	float pTeor;
	float pPr;

	for (int i = 0; i < maxSizeOfArray; i++)
	{
		statistics[i] = 0;
	}

	for (int i = 0; i < stream.size(); i++)
	{
		if (stream[i] < maxSizeOfArray)
		{
			statistics[stream[i]]++;
		}
	}

	for (int i = 0; i < maxSizeOfArray; i++)
	{
		if (statistics[i] > 0)
		{
			float p = (float)statistics[i] / stream.size();
			h += p * log2(p);
		}
	}

	printf("Entropy before coding\t%f\n", -h);

	printf("N\tpTeoria\t\tpPr\n");

	for (int i = 0; i < 20; i++)
	{
		pTeor = pow(p, (float(i))) * (1 - p);
		pPr = (float)statistics[i] / stream.size();
		printf("%d\t%f\t%f\n", i, pTeor, pPr);
	}

	delete[] statistics;
}
