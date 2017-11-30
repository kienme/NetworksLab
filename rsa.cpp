#include <iostream>
#include <vector>

#define MAX 255

using namespace std;

long p, q, n, phi, e, d;
string msg;
vector<long> crypt, plain;

bool is_prime(long num)
{
	if(num < 2)
		return false;

	for(long i = 2; i < num; ++i)
		if(num % i == 0)
			return false;

	return true;
}

long gcd(long a, long b)
{
	if(b == 0)
		return a;

	return gcd(b, a % b);
}

void gen_params()
{
	for(p = rand() % MAX; !is_prime(p); ++p, p %= MAX);
	for(q = rand() % MAX; !is_prime(q) || (p == q); ++q, q %= MAX);

	n = p * q;
	phi = (p-1) * (q-1);

	for(e = 2; gcd(e, phi) != 1; ++e);
	for(d = 2; ((d*e) % phi != 1) || (d == e); ++d);

	cout << "p\tq\tn\tphi\te\td\n";
	cout << p << "\t" << q << "\t" << n << "\t" << phi << "\t" << e << "\t" << d << "\n";
}

void encrypt()
{
	for(long m : msg)
	{
		long c = m;
		for(long  i = 1; i < e; ++i)
			c = (c*m) % n;
		
		crypt.push_back(c);
	}
	
	cout << "\nEncrypted message: ";
	for(auto c : crypt)
		cout << c << " ";
}

void decrypt()
{
	for(long c : crypt)
	{
		long m = c;
		for(long i = 1; i < d; ++i)
			m = (m*c) % n;

		plain.push_back(m);
	}

	cout << "\nDecrypted message: " ;
	for(char p : plain)
		cout << p;
	cout << endl;
}

int main()
{
	srand(time(NULL));			

	gen_params();		
	
	cout << "\nEnter message: ";
	getline(cin, msg);
	
	encrypt();
	decrypt();	

	return 0;
}