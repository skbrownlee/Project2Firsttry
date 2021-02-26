#include <iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++) {
		A[i] = '\0';
	}
}

// copy a string A to B of length n
void stringCopy (char* A, char* B, int n) {
	for (int i=0; i < n; i++) {
		B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;
	int size;
	void strCpy (char* A, char* B, int n);
public:
	myString ();
	myString(char* inpStr);
	myString (myString& B);
	int Size();
	char* getWord();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0')
		i++;
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j=0; j < size; j++)
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy(B.strArray, strArray, size);
}
char* myString::getWord()
{
	return strArray;
}
// getter for size of myString
int myString::Size () {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {

	// TODO done
	int length = sizeof(B);
	if (this->strArray == B) {
			return *this;
		}
		else {
			this->strArray = new char[length];
			for (int i=0;i<(length); i++) {
				this->strArray[i] = B[i];
			}
			this->size = length;
		}
		return *this;
}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {

	// TODO done
	if (this == &B) {
		return *this;
	}

	else {
		this->strArray = new char[B.size];
		for (int i=0;i<B.size; i++) {
			this->strArray[i] = B.strArray[i];
		}
		this->size = B.size;
	}
	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	// TODO
	if (this->size != B.size) {
		return false;
	}
	for (int i=0; i < size; i++) {
		if (this->strArray[i] != B.strArray[i]) {
			return false;
		}
	}
	return true;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {
	if (size <= B.size) {
		for (int i=0; i < size; i++) {
			if (strArray[i] > B.strArray[i]) {
				return false;
			}
		}
	}
	else {
		for(int i=0; i<B.size; i++) {
			if (strArray[i] > B.strArray[i]) {
				return false;
			}
		}
	}
	return true;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {
	if (size <= B.size) {
			for (int i=0; i < size; i++) {
				if (strArray[i] < B.strArray[i]) {
					return false;
				}
			}
		}
		else {
			for(int i=0; i<B.size; i++) {
				if (strArray[i] < B.strArray[i]) {
					return false;
				}
			}
		}
	return true;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
	char* str = new char[20]; //assumes a max token size of 20
	emptyString (str, 20);

	char c;
	int i = 0;
	while (!cin.eof()) {
		cin.get(c);
		if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) {
				if ( ((c >= 'a') && (c <= 'z')) ||
					 ((c >= 'A') && (c <= 'Z')) ||
					 ((c >= '0') && (c <= '9')) )
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
				return str;
			else if ((c == ' ') && (i > 0))
				return str;
		}
	}
	if (i > 0) return str;
	else {return NULL;}
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords {
private:
	int binarySearchAndInsert (myString& W);
protected:
	myString* _words;
	int* _frequencies;
	int _size;

public:
	bagOfWords ();
	bagOfWords (int numOfWords);

	myString* get_Words();
	int* get_Freq();
	int get_size();

	void setSize(int i);

	void addWord (myString& W);//insert word w into the array _words - keep it sorted alphabetically
	void sortFreq(); //sort words array based on frequency
	void sortWords(); //sort words array alphabetically
	void display(); //print word followed by a colon followed by a single space and frequencuy
	bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
	~bagOfWords();
};

// default constructor - initializes with no words
bagOfWords::bagOfWords()
{
	_size = 0;
	_words = new myString[0];
	_frequencies = new int[0];
}
// the destructor
bagOfWords::~bagOfWords() {
	for (int i=0; i < this->_size;i++) {
		this->_words[i] = NULL;
		this->_frequencies[i] = 0;
	}
	this->_size = 0;
	delete _words;
	delete _frequencies;
}
// non default constructor - initializes with a known number of words
bagOfWords::bagOfWords (int numOfWords)
{
	_size = numOfWords;
	_words = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

myString* bagOfWords::get_Words()
{
	return _words;
}

int* bagOfWords::get_Freq()
{
	return _frequencies;
}

int bagOfWords::get_size()
{
	return _size;
}

void bagOfWords::setSize(int i)
{
	_size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display()
{
	cout << "displaying";
	for (int i=0; i < this->_size; i++) {
		cout << this->_words[i] << ": " << this->_frequencies[i] << "\n";
	}

}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq() // bubble sort
{
	for (int i=0; i<this->_size; i++) {
			int swapFlag = 0;
			for (int j=0; j<this->_size-i-1; j++) {
				if (this->_frequencies[j] > this->_frequencies[j+1]) {
					myString temp;
					int tempF;
					tempF = this->_frequencies[j];
					temp = this->_words[j];
					this->_words[j] = this->_words[j+1];
					this->_frequencies[j] = this->_frequencies[j+1];
					this->_words[j+1] = temp;
					this->_frequencies[j+1] = tempF;
					swapFlag = 1;
				}
			}
			if (!swapFlag) {
				break;
			}
		}
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords() //bubble sort
{

	for (int i=0; i<this->_size; i++) {
		int swapFlag = 0;
		for (int j=0; j<this->_size-i-1; j++) {
			if (this->_words[j] > this->_words[j+1]) {
				myString temp;
				int tempF;
				tempF = this->_frequencies[j];
				temp = this->_words[j];
				this->_words[j] = this->_words[j+1];
				this->_frequencies[j] = this->_frequencies[j+1];
				this->_words[j+1] = temp;
				this->_frequencies[j+1] = tempF;
				swapFlag = 1;
			}
		}
		if (!swapFlag) {
			break;
		}
	}


}

bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords)
{
	bagOfWords* returner = new bagOfWords(numStopWords);
	for (int i=0; i<numStopWords; i++) {
		returner->_words[i] = stopWords[i];
		returner->_frequencies[i] = 1;
	}

	return returner;
}

// to search for a given word in _words - returns -1 if not found, index if found
int bagOfWords::binarySearchAndInsert (myString& wordToFind)
{
	int mid;
	int L = 0;
	int R = this->_size - 1;
	while((L < R)) {
		mid = (L + R)/2;
		if (this->_words[mid] == wordToFind) {
			return mid;
		}
		else if(this->_words[mid] < wordToFind) L = mid + 1;
		else R = mid - 1;
	}

	return -1;
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString& newWord)
{
	_size++;
	this->_words[_size] = newWord;
	/*
	if (this->_size == 0) {
		myString* temp = new myString[this->_size + 1];
		temp[0] = newWord;
		this->_words = temp;
		this->_size++;
		delete [] temp;
	}

	int index = this->binarySearchAndInsert(newWord);
	if (index >= 0) {
		this->_frequencies[index]++;
	}
	int mid;
	int L = 0;
	int R = this->_size - 1;
	while((L < R)) {
		mid = (L + R)/2;
		if(this->_words[mid] < newWord) L = mid + 1;
		else R = mid - 1;
	}

	// insert at L
	myString* temp = new myString[this->_size + 1];
	for (int i=0; i < L;i++) {
		temp[i] = this->_words[i];
	}
	temp[L] = newWord;
	for (int i=L+1; i < this->_size+1; i++) {
		temp[i] = this->_words[i];
	}
	this->_words = temp;
	this->_size++;
	delete [] temp;
	*/



}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {

	int numStopWords;
	char* token;
	myString* tokenString;

    //read the first number from the file that contains the number of stop words
	cin >> numStopWords;
	cout << "Number of Stop words: " << numStopWords << endl;
	myString* stopWordsList = new myString[numStopWords];

	//read the stop words
	for (int i=0; i < numStopWords; i++)
	{
		token = getNextToken ();
		stopWordsList[i] = token; //calls the overloaded = operator on myString class
	}

	//Now read a text and put them in the bagOfWords instance.
	bagOfWords* myBag = new bagOfWords ();

	token = getNextToken (); // v2: this was the error.

	while (token != NULL)
	{
		tokenString = new myString (token); //create a myString object with the token
		(*myBag).addWord(*tokenString); //add token to myBag
		token = getNextToken ();
	}

	// this should display the token and frequency;
	// note that becuase you are using binary search and insert the tokens will
	// be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*myBag).display ();

	(*myBag).sortFreq ();
	cout << endl;
	cout << "myBag - Sorted based on frequency:" << endl;
	(*myBag).display ();

	(*myBag).sortWords();
	cout << endl;
	cout << "myBag - Sorted alphabetically:" << endl;
	(*myBag).display ();

	bagOfWords* newBag = (*myBag).removeStopWords(stopWordsList, numStopWords); // new parameter added here
	cout << endl;
	cout << "newBag - Sorted alphabetically:" << endl;
	(*newBag).display();

	(*newBag).sortFreq ();
	cout << endl;
	cout << "newBag - Sorted based on frequency:" << endl;
	(*newBag).display ();
	cout << "finished";
	// TODO : destructors
	delete [] stopWordsList;
	delete myBag;
	delete newBag;

}
