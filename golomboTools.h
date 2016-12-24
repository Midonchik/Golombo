#ifndef GOLOMBO_TOOLS
#define GOLOMBO_TOOLS

#include <stdio.h>
#include <vector>
#include <bitset>

using namespace std;
class GolomboTools
{
private:
public:
	GolomboTools();
	~GolomboTools();

	void readStremFromFile(char *nameStreamFile, vector<unsigned char> &stream, int sizeStream);
	void writeStremInFile(char *nameStreamFile, vector<unsigned char> &stream, int sizeStream);
	void generateStream(int sizeStream, float p, char* nameStreamFile);
	int getBestM(float p);
	void writeBits(char *nameStreamFile, vector <bool> &encodingStream);
	void getStatistics(vector<unsigned char> stream, float p);
};

#endif