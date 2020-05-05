#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <algorithm>
using namespace std;
//This implementation of the Huffman Tree
//uses a minHeap style 
#define tree_height 100

//this is the function used to iterate through every word of the
//text file and add them to the array for code generation

int readFile()//int freqArray[33]
{
	//for characters that don't get recognized properly
	int unprocessed = 0;
	//initializing the array
	int freqArray[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	ifstream fileRead;
	fileRead.open("Sakiro.txt");
	while (fileRead.eof() == 0)
	{
		string sTemp;
		fileRead >> sTemp;
		for (int i = 0; i < sTemp.size(); i++)
		{
			char cTemp = sTemp[i];
			if (int(cTemp) >= 65 && int(cTemp) <= 90)
				cTemp = cTemp + 32;

			switch (cTemp) {
			case 'a' :
				freqArray[0]++;
				break;

			case 'b':
				freqArray[1]++;
				break;

			case 'c':
				freqArray[2]++;
				break;

			case 'd':
				freqArray[3]++;
				break;

			case 'e':
				freqArray[4]++;
				break;

			case 'f':
				freqArray[5]++;
				break;

			case 'g':
				freqArray[6]++;
				break;

			case 'h':
				freqArray[7]++;
				break;

			case 'i':
				freqArray[8]++;
				break;

			case 'j':
				freqArray[9]++;
				break;

			case 'k':
				freqArray[10]++;
				break;

			case 'l':
				freqArray[11]++;
				break;

			case 'm':
				freqArray[12]++;
				break;

			case 'n':
				freqArray[13]++;
				break;

			case 'o':
				freqArray[14]++;
				break;

			case 'p':
				freqArray[15]++;
				break;

			case 'q':
				freqArray[16]++;
				break;

			case 'r':
				freqArray[17]++;
				break;

			case 's':
				freqArray[18]++;
				break;

			case 't':
				freqArray[19]++;
				break;

			case 'u':
				freqArray[20]++;
				break;

			case 'v':
				freqArray[21]++;
				break;

			case 'w':
				freqArray[22]++;
				break;

			case 'x':
				freqArray[23]++;
				break;

			case 'y':
				freqArray[24]++;
				break;

			case 'z':
				freqArray[25]++;
				break;

			case ' ':
				freqArray[26]++;
				break;

			case '.':
				freqArray[27]++;
				break;

			case ',':
				freqArray[28]++;
				break;

			case ':':
				freqArray[29]++;
				break;

			case '(':
				freqArray[30]++;
				break;

			case ')':
				freqArray[31]++;
				break;
			//have to use ascii value for apostrophe due to switch case constraints
			case char(39):
				freqArray[32]++;
				break;

			default :
				unprocessed++;
				break;
			}
		}
	}
	cout << "Frequency Table: " << endl;
	int asciiVal = 65;
	for (int i = 0; i < 26; i++)
	{
		char realAscii = asciiVal;
		cout << realAscii << " occurs " << freqArray[i] << " times. " << endl;
		asciiVal++;
	}
	cout << "Period - '.' occurs " << freqArray[27] << " times." << endl;
	cout << "Comma - ',' occurs " << freqArray[28] << " times." << endl;
	cout << "Colon - ':' occurs " << freqArray[29] << " times." << endl;
	cout << "O-Paren - '(' occurs " << freqArray[30] << " times." << endl;
	cout << "C-Paren - ')' occurs " << freqArray[31] << " times." << endl;
	cout << "Apostrophe - ' ' ' occurs " << freqArray[32] << " times." << endl;
	cout << unprocessed << " characters were not properly processed." << endl;
	cout << "\n";
	return freqArray[29];
}

//The node for the huffman tree 
struct heapNode 
{
	char data; //character that is read in
	unsigned freq; //how often the character from 'char data' appears
	struct heapNode* left, * right; //children of this node
};

// Creating a minHeap of nodes
struct MinHeap 
{
	unsigned size; //current size of minHeap
	unsigned capacity; //current capacity of minHeap
	struct heapNode** array; //array of pointers
};

//Used to create a new node based off of the character read in 
struct heapNode* newNode(char data, unsigned freq)
{
	//using malloc to allocate memory needed for the pointer
	struct heapNode* temp = (struct heapNode*)malloc(sizeof(struct heapNode));
	temp->left = temp->right = NULL; //setting both leaves to null, for now
	temp->data = data;
	temp->freq = freq;
	return temp;
}

//Create a minHeap of a certain capacity
struct MinHeap* createMinHeap(unsigned capacity)
{
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));//memory allocation using malloc to create new min heap
	minHeap->size = 0; //size will always start at 0
	minHeap->capacity = capacity; //setting the capacity here
	minHeap->array = (struct heapNode**)malloc(minHeap->capacity * sizeof(struct heapNode*));
	return minHeap;
}

//Swaps two nodes
void swapheapNode(struct heapNode** a, struct heapNode** b)
{
	struct heapNode* t = *a;
	*a = *b;
	*b = t;
}

//Functions to heapify the tree 
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest = idx; //intializing the smallest as the root
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	//checks if left child will be larger than the root
	if (left < minHeap->size && minHeap->array[left]-> freq < minHeap->array[smallest]->freq)
		smallest = left;
	//checks if right child will be larger than the root
	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;
	//if the largest is not the root
	if (smallest != idx) {
		swapheapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest); //recurse to heapify the affected subtree
	}
}

//Simple function used to check if size == 1
int isSizeOne(struct MinHeap* minHeap)
{
	return (minHeap->size == 1);
}

//Get values from nodes
struct heapNode* returnMin(struct MinHeap* minHeap)
{
	struct heapNode* temp = minHeap->array[0]; //creating temp node to
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

//inserts new node onto minimum heap
void insertHeap(struct MinHeap* minHeap, struct heapNode* heapNode)
{
	++minHeap->size;
	int i = minHeap->size - 1;
	//formula used to find where the new node will be inserted
	while (i && heapNode->freq < minHeap->array[(i - 1) / 2]->freq) 
	{
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = heapNode;
}

// A standard function to build min heap 
void buildMinHeap(struct MinHeap* minHeap)
{
	int n = minHeap->size - 1;
	int i;
	//using size of minheap - 1 to build the heap
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n
//later used to print out the huffman codes
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		cout << arr[i];

	cout << "\n";
}

//check if node is a leaf
int isLeaf(struct heapNode* root)
{
	return !(root->left) && !(root->right);
}

//This is the function to create the minimum heap and inserts the data from the array
//that was read in from the file
struct MinHeap* createHeap(char data[], int freq[], int size)
{
	struct MinHeap* minHeap = createMinHeap(size);
	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}

//This is the main function of the program. It uses the minheap that was created
//and the min heap nodes that were created to make the codes for the huffman tree
struct heapNode* buildTree(char data[], int freq[], int size)
{
	//initializing all of the nodes that are needed
	struct heapNode* left, * right, * top;
	//creating a min heap has the same size as the current capacity
	struct MinHeap* minHeap = createHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1 
	while (!isSizeOne(minHeap)) {

		// Step 2: Extract the two minimum 
		// freq items from min heap 
		left = returnMin(minHeap);
		right = returnMin(minHeap);

		//Top is used an internal node whose frequency is the sum of 
		//left + right, the children are added to this node and
		//it is then added on to the to minHeap
		top = newNode('@', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertHeap(minHeap, top);
	}
	//This is the root node
	return returnMin(minHeap);
}

//This function is used to print the codes that are produced from the huffman tree
void printCodes(struct heapNode* root, int arr[], int top)
{
	// Assign 0 to left edge and recurse 
	if (root->left) 
	{
		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	// Assign 1 to right edge and recur 
	if (root->right) 
	{
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	//checks to see if leaf, it is a leaf then it must contain one
	//of the characters
	if (isLeaf(root)) 
	{
		//outputs current data (char value) at the root node and
		//uses top as the n value in the function for 
		//proper output of huffman code
		cout << root->data << ": ";
		printArr(arr, top);
	}
}

//Builds the tree and prints the codes that are made in the 
//main function above
void HuffmanCodes(char data[], int freq[], int size)
{
	//builds the tree
	struct heapNode* root = buildTree(data, freq, size);
	int arr[tree_height], top = 0;
	printCodes(root, arr, top);
}

int main()
{
	//this is simply an array of every character that will be read in 
	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
		'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y','z', '(', ')',  '.', ',' };
	int freq[33]; //= {4, 1, 6, 7, 5, 3, 6, 5, 4, 87, 56, 34, 23, 12, 65, 78, 98, 101, 23, 13,
					//15, 76, 34, 65, 12 ,54 ,34 ,76 ,34};

	readFile();
	int size = sizeof(arr) / sizeof(arr[0]);//used due to no size() function existing for arrays
	
	cout << "Huffman Codes Generated for each character: " << endl;
	HuffmanCodes(arr, freq, size);

	return 0;
}