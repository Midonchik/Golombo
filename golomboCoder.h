#ifndef GOLOMBO_CODER
#define GOLOMBO_CODER

#include <stdio.h>
#include <vector>
using namespace std;

class GolomboCoder{
private:
public:
	GolomboCoder();
	~GolomboCoder();
	void getCodingStream(vector<unsigned char> &streamForCoding, vector<bool> &encodingStream, int m, int sizeStream);
	void getDecodingStream(vector<unsigned char> &decodingStream, vector<bool> &streamForDecoding, int m, int sizeStream);
};

#endif