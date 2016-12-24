#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <bitset>
#include"golomboTools.h"
#include "golomboCoder.h"

using namespace std;

//parametrs	for generation stream
const float p = 0.9;
const int sizeStream = 1000;
char *nameStreamFile = "stream.txt";
char *nameDecodingStreamFileNonOptimal = "decodingStreamNonOptimal.txt";
char *nameDecodingStreamFileOptimal = "decodingStreamOptimal.txt";
char *nameCodingStreamFileNonOptimal = "codingStreamNonOptimal.txt";
char *nameCodingStreamFileOptimal = "codingStreamOptimal.txt";

int main()
{
	GolomboTools *golomboTools = new GolomboTools();
	GolomboCoder *golomboCoder = new GolomboCoder();
	int m = 3; // not optimal coding parametr
	int mBest = 0; // best coding parametr

	vector <unsigned char> stream;
	
	//generate stream and write in file
	//golomboTools->generateStream(sizeStream, p, nameStreamFile);
	
	//read stream from file
	golomboTools->readStremFromFile(nameStreamFile, stream, sizeStream);
	
	golomboTools->getStatistics(stream, p);

	//////////////////////////NOT OPTIMAL PARAMETR M///////////////////////////////
	
	{
		vector<bool> encodingStream;
		vector<unsigned char> decodingStream;
		
		printf("non-optimal parametr M - %d\n", m);

		//coding and write 
		golomboCoder->getCodingStream(stream, encodingStream, m, sizeStream);
		golomboTools->writeBits(nameCodingStreamFileNonOptimal, encodingStream);

		//read and decoding stream write in file
		golomboCoder->getDecodingStream(decodingStream, encodingStream, m, sizeStream);
		golomboTools->writeStremInFile(nameDecodingStreamFileNonOptimal, decodingStream, sizeStream);

		//test diffs
		for (int i = 0; i < decodingStream.size(); i++)
		{
			int dif = decodingStream[i] - stream[i];
			if (dif != 0)
			{
				printf("Erorr dif = %d/n", dif);
			}
		}
		printf("Code rate for non-optimal parametr M \t%f\n", float(encodingStream.size()) / sizeStream);
	}

	//////////////////////////BEST PARAMETR M///////////////////////////////
	{
		vector<bool> encodingStream;
		vector<unsigned char> decodingStream;
		
		mBest = golomboTools->getBestM(p);
		printf("best parametr M - %d\n", mBest);

		//coding and write 
		golomboCoder->getCodingStream(stream, encodingStream, mBest,sizeStream);
		golomboTools->writeBits(nameCodingStreamFileOptimal, encodingStream);

		//read and decoding stream write in file
		golomboCoder->getDecodingStream(decodingStream, encodingStream, mBest, sizeStream);
		golomboTools->writeStremInFile(nameDecodingStreamFileOptimal, decodingStream, sizeStream);

		//test diffs
		for (int i = 0; i < decodingStream.size(); i++)
		{
			int dif = decodingStream[i] - stream[i];
			if (dif != 0)
			{
				printf("Erorr dif = %d/n", dif);
			}
		}
		printf("Code rate for best parametr M \t%f\n", float(encodingStream.size()) / sizeStream);
	}
	
	
	system("pause");
	return 0;
}



