#include "golomboCoder.h"

GolomboCoder::GolomboCoder(){}
GolomboCoder::~GolomboCoder(){}

void GolomboCoder::getCodingStream(vector<unsigned char> &streamForCoding, vector<bool> &encodingStream, int m, int sizeStream)
{
	int r = 0;
	int c = 0;
	int q = 0;
	int n = 0;
	int f = 0;
	int sizeOfFisrtTable = 0;

	c = ceil(log2(float(m)));
	sizeOfFisrtTable = pow((float)2, (float)c) - m;

	for (int i = 0; i < sizeStream; i++)
	{
		n = streamForCoding[i];
		q = floor(n / m);
		r = n - m*q;

		for (int count = 0; count < q; count++)
		{
			encodingStream.push_back(1);
		}
		encodingStream.push_back(0);

		if (r < sizeOfFisrtTable)
		{
			vector<bool> addCode;

			for (int k = 0; k < (c - 1); k++)
			{
				addCode.push_back(r % 2);
				r /= 2;
			}

			for (int k = c - 2; k >= 0; k--)
			{
				encodingStream.push_back(addCode[k]);
			}

		}
		else
		{
			vector<bool> addCode;
			r += sizeOfFisrtTable;
			for (int k = 0; k < c; k++)
			{
				addCode.push_back(r % 2);
				r /= 2;
			}

			for (int k = c - 1; k >= 0; k--)
			{
				encodingStream.push_back(addCode[k]);
			}

		}
	}
}

void GolomboCoder::getDecodingStream(vector<unsigned char> &decodingStream, vector<bool> &streamForDecoding, int m, int sizeStream)
{
	int q = 0;
	int n = 0;
	int c = 0;
	int sizeOfFisrtTable = 0;
	int currPos = 0;

	c = ceil(log2(float(m)));
	sizeOfFisrtTable = pow((float)2, (float)c) - m;

	while (currPos < streamForDecoding.size())
	{
		q = 0;
		while (streamForDecoding[currPos] == 1)
		{
			q++;
			currPos++;
		}
		currPos++;

		n = 0;
		for (int i = currPos; i < currPos + c - 1; i++)
		{
			n = n * 2 + streamForDecoding[i];
		}
		currPos += (c - 1);

		if (n <  sizeOfFisrtTable)
		{
			decodingStream.push_back(q * m + n);
		}
		else
		{
			n = n * 2 + streamForDecoding[currPos];
			decodingStream.push_back(q * m + (n - sizeOfFisrtTable));
			currPos++;
		}
	}
}
