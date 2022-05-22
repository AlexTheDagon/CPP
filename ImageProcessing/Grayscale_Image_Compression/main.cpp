// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include <queue>
#include <random>
#include <fstream>
#include <stdio.h>

using namespace std;

struct treeNode{
	int id;
	int index;
	int freq;
	string code;
	int leftChildIndex;
	int rightChildIndex;
};

struct cmp
{
	bool operator()(treeNode N1, treeNode N2) { 
		return N1.freq > N2.freq; 
	};
};

struct trieNode {
	int val;
	trieNode* fiu[2];
	trieNode() {
		val = -1;
		memset(fiu, 0, sizeof(fiu));
	}
};

priority_queue<treeNode, vector<treeNode>, cmp> PQ;

treeNode combineNodes(treeNode &N1, treeNode &N2, int newIndex) {
	treeNode parent;
	parent.id = -1;
	parent.index = newIndex;
	parent.freq = N1.freq + N2.freq;
	parent.code = "";
	parent.leftChildIndex = N1.index;
	parent.rightChildIndex = N2.index;
	return parent;
}

void add(trieNode* T, string s, int i, int val) {
	if (i == s.size()) {
		T->val = val;
		return;
	}
	if (T->fiu[s[i] - '0'] == 0) {
		T->fiu[s[i] - '0'] = new trieNode;
	}
	add(T->fiu[s[i] - '0'], s, i + 1, val);
}

vector<int>  computeHistogram(Mat_<uchar> src) {
	vector<int> histogram(256, 0);
	int height = src.rows;
	int width = src.cols;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			uchar val = src(i, j);
			histogram[(int)val] ++;
		}
	}

	return histogram;
}

int differentNumberOfPixels(Mat_<uchar> src) {
	int differentNumberOfPixels = 0;
	vector<int> histogram = computeHistogram(src);
	for (auto p : histogram)
		if (p > 0) ++differentNumberOfPixels;
	return differentNumberOfPixels;
}

void DFS(treeNode &nod, vector<treeNode> &allNodes) {
	if (nod.id != -1) return;
	
	allNodes[nod.leftChildIndex].code = nod.code + '0';
	allNodes[nod.rightChildIndex].code = nod.code + '1';

	DFS(allNodes[nod.leftChildIndex], allNodes);
	DFS(allNodes[nod.rightChildIndex], allNodes);
}

// Converts an integer value to a byte string of lenght 8
string convertCharToByteString(int val) {
	string binaryString = "";
	for (int i = 7; i >= 0; --i) {
		if ((1 << i) & val) binaryString += '1';
		else binaryString += '0';
	}
	return binaryString;
}

// Converts an integer value to a byte string of lenght 32
string convertIntegerToByteString(int val) {
	string binaryString = "";
	for (int i = 31; i >= 0; --i) {
		if ((1 << i) & val) binaryString += '1';
		else binaryString += '0';
	}
	return binaryString;
}

//Converts from string s, from index, len chars to the coressponding integer value
int convertByteStringToIntegerValue(string s, int len, int &index) {
	int rez = 0;
	for (int i = 0; i < len; i++) {
		rez <<= 1;
		rez = s[index + i] - '0' + rez;
	}
	index += len;
	return rez;
}

void EncodeImage() {
	char fname[MAX_PATH];
	openFileDlg(fname);

	Mat_<uchar> src = imread(fname, IMREAD_GRAYSCALE) ;
	int height = src.rows;
	int width = src.cols;

	// Huffman encoding the value
    int ind = 0;
	treeNode root;
	vector<treeNode> huffmanTree;
	vector<treeNode> leafNodes;
	vector<int> histogram = computeHistogram(src);

	// For each different symbol that appears in our image we will create a leaf node in the huffman tree
	for (int i = 0; i < 256; ++i) {
		if (histogram[i]) {
			treeNode nod;
			nod.id = i;
			nod.index = ind++;
			nod.freq = histogram[i];
			nod.code = "";
			nod.leftChildIndex = -1;
			nod.rightChildIndex = -1;

			leafNodes.push_back(nod);
			huffmanTree.push_back(nod);
			PQ.push(nod);
		}
			
	}

	// While we still have more than 1 node with no parent in the huffman tree, we extract the 2 nodes with the least amount of 
	// occurences, we merge them, and we put the new node into the tree (Priority Queue)
	while (PQ.size() > 1) {
		treeNode N1 = PQ.top(); PQ.pop();
		treeNode N2 = PQ.top(); PQ.pop();		
		treeNode N3 = combineNodes(leafNodes[N2.index], leafNodes[N1.index], leafNodes.size());
		leafNodes.push_back(N3);
		PQ.push(leafNodes[N3.index]);
	}
		
	// We extract the root of the huffman tree
	root = PQ.top(); PQ.pop();
	
	// Now we will extract the codes corresponding to each symbol present in the original image, 
	// by doing a depth-first-search starting from the root of the huffman tree, until we reach a leaf.
	string codes[256];
	DFS(leafNodes[root.index], leafNodes);
	int totalCodesLenght = 0;
	for (auto e : leafNodes) {
		if (e.id != -1) {
			codes[e.id] = e.code;
			huffmanTree.push_back(e);
			totalCodesLenght += e.code.size();
		}
	}
	cout << "Average lenght of codes for encoding = " << totalCodesLenght * 1.0 / differentNumberOfPixels(src);





	// Using the newly obtained symbols, we will encode our image as such: 
	// totalEncodingLenght (how many bits we have in the message)
	// numberOfDifferentSymbols (how many different symbols we have)
	// {symbolValue | huffmanCodeLenght | huffmanCode} (triplet for each one of the different symbols)
	// nrRows (number of rows in the original img)
	// nrCols (number of cols in the original img)
	// huffmanCode (for each symbol in the original picture)

	string huffmanEncoding = "";

	// numberOfDifferentSymbols (how many different symbols we have)
	huffmanEncoding += convertCharToByteString(differentNumberOfPixels(src));

	// {symbolValue | huffmanCodeLenght | huffmanCode} (triplet for each one of the different symbols)
	for (auto e : leafNodes) {
		if (e.id != -1) {
			huffmanEncoding += convertCharToByteString(e.id);
			huffmanEncoding += convertCharToByteString(e.code.size());
			huffmanEncoding += e.code;
		}
	}

	// nrRows (number of rows in the original img)
	huffmanEncoding += convertIntegerToByteString(src.rows);

	// nrCols (number of cols in the original img)
	huffmanEncoding += convertIntegerToByteString(src.cols);

	// huffmanCode (for each symbol in the original picture)
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int v = src(i, j);
			huffmanEncoding += codes[v];
		}
	}
		
	// totalEncodingLenght (how many bits we have in the message)
	string huffmanEncodingSizeToByteString = convertIntegerToByteString(huffmanEncoding.size());

	// Now we will PREPEND the messeage lenght at the beginning of the encoding
	huffmanEncoding = huffmanEncodingSizeToByteString + huffmanEncoding;

	// We will append '0' until we reach a message size which is a multiple of 8, so we can easly convert 8 character (0 & 1) to a char value and write it in the file.
	while (huffmanEncoding.size() % 8 != 0) huffmanEncoding += '0';
		
	// We compress the byte string and write it intro a file.

	string compressedText;
	int compressedTextSize = huffmanEncoding.size() / 8;


	char val = 0;
	for (int i = 0; i < huffmanEncoding.size(); ++i) {
		int bitValue = huffmanEncoding[i] - '0';
		bitValue <<= (7 - (i % 8));
		val = (val + bitValue);
		if (i % 8 == 7) {
			compressedText += val;
			val = 0;
		}
	}

	FILE* f;
	f = fopen("compressedImg.txt", "wb");
	for (int i = 0; i < compressedTextSize; ++i) {
		char c = compressedText[i];
		fwrite(&c, sizeof(c), 1, f);
	}
	fclose(f);
	


		
	
}

void DecodeImage() {
	
	string huffmanEncoded = "";
	char c;
	unsigned char uc;

	FILE* f;
	f = fopen("compressedImg.txt", "rb");

	// read the encoded messeage size
	int huffmanEncodedSize = 0;
	for (int i = 0; i < 4; ++i) {
		fread(&c, sizeof(char), 1, f);
		uc = c;
		huffmanEncodedSize <<= 8;
		huffmanEncodedSize += uc;
	}

	// Next we need to find the size of the messeage after padding with '0'
	int paddedHuffmanEncodedSize = huffmanEncodedSize;
	while (paddedHuffmanEncodedSize % 8) ++paddedHuffmanEncodedSize;

	for (int i = 0; i < paddedHuffmanEncodedSize / 8; ++i) {
		fread(&c, sizeof(char), 1, f);
		uc = c;
		for (int j = 7; j >= 0; --j) {
			if (c & (1 << j)) huffmanEncoded += '1';
			else huffmanEncoded += '0';
		}
	}
	fclose(f);
	
	// We remove the padded 0s at the end
	huffmanEncoded = huffmanEncoded.substr(0, huffmanEncodedSize);
	
	// We will try to reconstruct the image & the huffman tree based on the encoding:
	// totalEncodingLength (how many bits we have in the message)
	// numberOfDifferentSymbols (how many different symbols we have)
	// {symbolValue | huffmanCodeLenght | huffmanCode} (triplet for each one of the different symbols)
	// nrRows (number of rows in the original img)
	// nrCols (number of cols in the original img)
	// huffmanCode (for each symbol in the original picture)

	// Current index in the encoded msg
	int index = 0;

	// numberOfDifferentSymbols (how many different symbols we have)
	int nrCodes = 0;
	nrCodes = convertByteStringToIntegerValue(huffmanEncoded, 8, index);
	
	// {symbolValue | huffmanCodeLenght | huffmanCode} (triplet for each one of the different symbols)
	vector<int> val;
	vector<string> codes;
	for (int i = 0; i < nrCodes; ++i) {
		val.push_back(convertByteStringToIntegerValue(huffmanEncoded, 8, index));
		int len = convertByteStringToIntegerValue(huffmanEncoded, 8, index);
		codes.push_back(huffmanEncoded.substr(index, len));
		index += len;
	}
	
	// Now we will interate through the codes to build the huffman tree from root down
	trieNode* root = new trieNode;
	for (int i = 0; i < nrCodes; ++i) {
		add(root, codes[i], 0, val[i]);
	}

	// nrRows (number of rows in the original img)
	int height = convertByteStringToIntegerValue(huffmanEncoded, 32, index);

	// nrCols (number of cols in the original img)
	int width = convertByteStringToIntegerValue(huffmanEncoded, 32, index);

	// huffmanCode (for each symbol in the original picture)
	Mat_<uchar> rez = Mat_<uchar>(height, width);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j){
			trieNode* currNode = root;
			while (currNode->val == -1) { // while a leaf node is not reached
				currNode = currNode->fiu[huffmanEncoded[index] - '0'];
				index++;
			}
			rez(i, j) = (uchar)currNode->val;
		}
	}
	cout << "Original image was " << height << " x " << width << " for a total of " << height * width * 8 << " bits\n";
	cout << "The compressed image uses " << huffmanEncodedSize << " bits.\n";
	cout << "CR = " << huffmanEncodedSize * 100.0 / height / width / 8.0 << '\n';
	imshow("Rez", rez);
	waitKey(1000);
}

int main()
{

	
	int op;

	do
	{
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 1 - Encode image\n");
		printf(" 2 - Decode image\n");
		printf(" 0 - Exit\n");

		printf("Option: ");
		scanf("%d",&op);
		switch (op)
		{
			case 1:
				EncodeImage();
				break;
			case 2:
				DecodeImage();
				break;
			default:
				return 0;
		}
	}
	while (op!=0);
	return 0;
}