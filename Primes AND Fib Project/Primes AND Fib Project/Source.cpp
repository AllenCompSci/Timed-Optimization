#pragma region Prime&Fibonacci_Project
#pragma region LIBs
#include <iostream> // cout
#include <string> // string *.length() *.c_str()
#include <sstream> // *.c_str() binary
#include <fstream> // ofstream 
#include <chrono> // now() duration *.count()
#include <Windows.h> // Update Project Resources
using namespace std;
#pragma endregion
#pragma region Function_Protypes
//Function Prototypes
#pragma region Files
/// opens ofstream outFile via fileName
void openOFile(string fileName);
/// closes any open ofstream outFile
void closeOFile();
/// writes the sstream ss to an open ofstream outFile
void writeFile();
#pragma endregion 
#pragma region Fibonacci
/// Generating fibonacci sequence as well as file generation
void fibSeq();
/// Generator of next term, from global n1, n2 terms.
void addFib();

#pragma endregion
#pragma region Utility
/// functional stopwatch functions both as start & stop updates a double currTime
void click();
/// Build both files in timely manner
void build();
/// setup global variables necessary for file generation as well as term creation.
void init();
/// Clear sstream ss of current contents readying it for next use.
void endl();
#pragma endregion
#pragma region TIMER_FUNCTIONS
/// Generating terms Fibonacci Sequence, without sstream or file generation
void timeFIB();
/// Generating terms Primes, without sstream or file generation
void timeSieve();
#pragma endregion
#pragma region PrimeSieve
/// Prime Generation and File Creation Function
void primeSieve();
/// Remove Composite numbers from Sieve with Prime Base
void composite(int);
#pragma endregion
#pragma endregion
#pragma region Global_Variables
// Global Variables
#pragma region Global_StopWatch_Vars
// elapsed for duration
chrono::duration<double> elapsed;
// TIMES 
chrono::time_point<chrono::system_clock> start, stop;
chrono::time_point<chrono::system_clock> genPrimB, genPrimE, genFibB, genFibE;
// BEST TIMES OVER EXAGGERATED TO MAKE INIT BETTER
double bestTime = 10000;
double bestPTime = 100;
double bestFTime = 100;
// DEFINE AND SET CURR TIMES to Zero
double curPrime = 0;
double curFib = 0;
double currTime = 0;
// set stopWatch to be true to start cycle, zero values
bool stopWatch = true;
// initalize variables that could be used to how Fib and Prime best times
string bestFTimeSTR, bestPTimeSTR;

#pragma endregion
#pragma region CONST_Defining_Limits
const int limit = 4000000; // How large the Sieve will be, and the limit of the largest prime to be less than
const int digitLimit = 100; // How many digits the fibonacci number will reach
const int LimitMinusOne = limit - 1; // Calculates the limit minus 1 once instead of optimize times
const int optimize = int(sqrt((double)(limit))); // Optimizes search parameters to exclude unnecessary loops
const int runTime = 88; // Defines how many times a better time is recorded
bool Sieve[limit]; // Defines/Declares a boolean Sieve
#pragma endregion
#pragma region Prime_Fibonacci_BASE-VARS
				   // first prime is one, PrimeCount++ increase to 2
int PrimeCount = 1;
// fibCount base 2, because 0,1, & 1 are known and defined
int fibCount = 2;
// f(n) = f(n-1) + f(n-2)
string n1 = "1"; // n-1
string n2 = "1"; // n-2
#pragma endregion
#pragma region Utility_Vars
				 /* outFile is the ofstream used to write to the files*/
ofstream outFile;
/* converts all output to the string stream using ss to write more efficently*/
stringstream ss(stringstream::out | stringstream::binary);
// fib1 and fib2 are string outputs for line format
string fib1 = "Fib(";
string fib2 = ") : ";
// space is for prime printout
string spacer = ". ";
// char newline
char close = '\n';
// variable that denotes if a change occured to printout
bool cng = false;
// counts the number of changes
int change = 0;
#pragma endregion
#pragma endregion
#pragma region MAIN
void main() {
	build();
	/// Only triggers at death of cycle program
	system("pause");
}
#pragma endregion
#pragma region Functions
void openOFile(string fileName) {
	closeOFile(); // closes any open file as precaution
	outFile.open(fileName.c_str()); // converts string into C-string
}
void closeOFile() {
	if (outFile.is_open()) { outFile.close(); } // closes any open outFile ofstream
}
void writeFile() {
	if (outFile.is_open()) {
		outFile.write(ss.str().c_str(), ss.str().length()); // writes the ss stream to open ofstream outFile
	}
}
void click() {
	// stopWatch is the switch
	if (stopWatch) { start = chrono::system_clock::now(); } // start if stopWatch is true
	else { // stop if stopWatch is false
		stop = chrono::system_clock::now();
		elapsed = stop - start; // calculates differnce 
		currTime = elapsed.count() * 1000; // * 1000 converts seconds to milliseconds
		if (currTime < bestTime) { // checks currTime against bestTime
			bestTime = currTime; // stores new Best time
			change++; // counts a change
			cng = true; // sets cng to true for print
		}
		timeFIB(); // calculates fib w/o string stream or print to file
		timeSieve(); // calculates prime w/o string stream or print to file
	}
	stopWatch = !stopWatch; // switch stopWatch
}
void addFib() {
	// n1 always larger than n2
	int siz = n1.length();
	if ((int)n2.length() < siz) // n1 only one digit larger at most
		n2 = "0" + n2;
	int CARRY = 0; // carry value declared
	for (int i = siz - 1; i >= 0; i--) {
		n2[i] += n1[i] - 48 + CARRY;
		CARRY = 0; // resets carry
				   // checks to see if sum of n2 and n1 at position index i is larger than 9
		if (n2[i] > '9') { n2[i] -= 10; CARRY++; }
	}
	if (CARRY != 0) // carrys value past size of n1
		n2 = "1" + n2;
	swap(n1, n2); // swaps values of variables 
}
void fibSeq()
{
	endl(); // resets ss stream to clear
			// inits ss to hold the values from term 0 - 2
	ss << fib1 << 0 << fib2 << "0 \n";
	ss << fib1 << 1 << fib2 << "1 \n";
	ss << fib1 << 2 << fib2 << "1 \n";
	// checks n1 length for number of digits
	while ((int)n1.length() != digitLimit) {
		addFib(); // does the string math 
		ss << fib1 << ++fibCount << fib2 << n1 << close; // stores the new n1 into the stringstream
	}
}
void timeFIB() {
	// Check fibSeq for update
	n1 = n2 = "1";
	int len = 2;
	genFibB = chrono::system_clock::now();
	while ((int)n1.length() != digitLimit) {
		len++;
		addFib();
	}
	genFibE = chrono::system_clock::now();
	curFib = (((chrono::duration<double>(genFibE - genFibB)).count()) * 1000);
	if (curFib < bestFTime) {
		bestFTime = curFib;
		cng = true;
	}
	endl();
	ss << "Generated " << len << " Fibonacci terms in " << bestFTime << " ms. \n";
	bestFTimeSTR = ss.str();
	endl();
}
void composite(int p) { // used like a cycle of primeSieve
	int j = (LimitMinusOne) / p;
	for (; j >= p; j--) {
		Sieve[j*p] = false;
	}
}
void timeSieve() {
	// like prime Sieve just no store to string stream 
	memset(Sieve, true, sizeof(Sieve));
	Sieve[0] = Sieve[1] = false;
	int len = 1;
	genPrimB = chrono::system_clock::now();
	composite(2);
	int i = 3;// Starting position
	for (; i < optimize; i++) {
		if (Sieve[i]) {
			// only check up to 2000
			len++;
			int j = (LimitMinusOne) / i;
			for (; j >= i; j--) {
				Sieve[j*i] = false;
			}
		}
		i++;
	}
	genPrimE = chrono::system_clock::now();
	i = 2001;
	for (; i < limit; i++) {
		if (Sieve[i++])
			len++;
	}
	curPrime = (((chrono::duration<double>(genPrimE - genPrimB)).count()) * 1000);
	if (curPrime < bestPTime) {
		bestPTime = curPrime;
		cng = true;
	}
	endl();
	ss << "Generated " << len << " Prime numbers in " << bestPTime << " ms. \n";
	bestPTimeSTR = ss.str();
	endl();
}
void primeSieve()
{
	endl(); // clears string stream
			//TEST
	composite(2); // unique function for 2, does the same as loop but does outside for single even prime
	ss << ++PrimeCount << spacer << 2 << '\n';
	int i = 3; // starts at odd first prime
	for (; i < optimize; i++) { // optimize == sqrt(limit) 
		if (Sieve[i]) { // checks to see if Sieve[i] is true, if so is prime
			ss << ++PrimeCount << spacer << i << '\n'; // stores to string stream
			int j = (LimitMinusOne) / i; // finds the largest multiplier capable that still exists inside the array
			for (; j >= i; j--) { // decrease from the j to i 
				Sieve[j*i] = false; // sets all j*i to false
			}
		}
		i++; // increase outside for to skip all even
	}
	i = 2003; // TEST Skips 2001 multiple of 3,  2 + 0 + 0 + 1 = 3 hence 2001 is a multiple of 3
	for (; i < limit; i++)
	{
		if (Sieve[i]) { // finds all future primes
			ss << ++PrimeCount << spacer << i << '\n'; // stores to the string stream
		}
		i++; // skips all evens. 
	}
}
void init() {
	endl(); // clears sstream
			// initializes values of the function
	cng = false;
	// sets all values of sieve to true
	memset(Sieve, true, sizeof(Sieve));
	// 0 current Primes found
	PrimeCount = 0;
	// 2 fib terms known
	fibCount = 2;
	// they are 
	n1 = "1";
	n2 = "1";
	// 0 and 1 are not prime
	Sieve[0] = Sieve[1] = false; // Declare what we know about Primes 2, 3, 5
}
void endl() {
	ss.str(""); // reset
	ss.clear(); // clear to be sure
}
void build() {
	while (change < 88) { // runs till 88 changes have been found
		init(); // initialize values
		click(); // start time
		openOFile("primes" + to_string(change) + ".txt"); // open ofstream
		primeSieve(); // prime sieve build and ss stream update
		writeFile(); // write from string stream
					 //closeOFile(); // close file un-necessary
		openOFile("fib" + to_string(change) + ".txt"); // opens ofstream
		fibSeq(); // builds terms writes to ss
		writeFile(); // writes from ss
		closeOFile(); // closes ofstream
		click(); // stops time updates time, checks generations without files. 
		if (cng) { // if a change is found update bestTime.txt
			openOFile("bestTime.txt");
			cout << bestFTimeSTR << bestPTimeSTR;
			cout << "Found " << PrimeCount << " primes  & \n";
			cout << "Found " << fibCount << " fibonacci terms in " << bestTime << " ms.\n";
			endl();
			ss << bestFTimeSTR << bestPTimeSTR;
			ss << "Found " << PrimeCount << " primes  & \n";
			ss << "Found " << fibCount << " fibonacci terms in " << bestTime << " ms.\n";
			writeFile();
			closeOFile();
		}
		endl();
	}
}
#pragma endregion
#pragma endregion
//ProgamEND