#include <iostream>

using namespace std;

string pol = "10001000000100001";

//Checks if dividend is zero
bool stop_div(string str)
{
	for(int i = 0; i < str.length()-pol.length(); ++i)
		if(str[i] == '1')
			return false;

	return true;
}

//Remember to take outp by reference to allow modification
bool crc(string inp, string &outp, bool calc)
{
	outp = inp;

	//For calculating CRC, pad with zeroes.
	//No. of zeroes equals the size of polynomial
	if(calc)
		for(int i = 0; i < pol.length(); ++i)
			outp += "0";

	//Continue division until dividend is zero
	for(int i = 0; i < inp.length() && !stop_div(outp); ++i)
		if(outp[i] == '1')	
			for(int j = 0; j < pol.length(); ++j)
				outp[i+j] = ((outp[i+j] == pol[j]) ? '0' : '1');

	//If generated message is not zero, there is an error in received message
	for(int i = 0; i < outp.length(); ++i)
		if(outp[i] == '1')
			return false;

	return true;		
}

int main()
{
	//REFERENCE: https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Computation

	string inp, outp, rec;
	cout << "Enter message: ";
	cin >> inp;

	//Generate the message
	crc(inp, outp, true);

	//Outp is of the form "zeroes+checksum"
	cout << "Checksum: ";
	for(int i =  inp.length(); i < outp.length(); ++i)
		cout << outp[i];
	cout << endl;

	//Display original_message+checksum
	cout << "Message : " << inp;
	for(int i =  inp.length(); i < outp.length(); ++i)
		cout << outp[i];
	cout << endl;

	cout << "Enter received message: ";
	cin >> rec;

	if(crc(rec, outp, false))
		cout << "No error" << endl;
	else
		cout << "Error" << endl;

	return 0;
}