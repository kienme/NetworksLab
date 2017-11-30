#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int cap;
	cout << "Enter bucket capacity: ";
	cin >> cap;

	int bw;
	cout << "Enter output bandwidth: ";
	cin >> bw;

	int time;
	cout << "Enter burst time: ";
	cin >> time;

	vector<int> in(time);
	cout << "\nEnter number of packets: \n";
	for(int i = 0; i < time; ++i)
	{
		cout << "Time " << i << ": ";
		cin >> in[i];
	}

	int bucket = 0, drop, t;
	cout << "\nTime\tIncoming\tOutgoing\tBucket\tDrop\n";
	for(t = 0; t < time; ++t)
	{
		bucket += in[t];
		if(bucket > cap)
		{
			drop = bucket - cap;
			bucket = cap;
		}
		else
			drop = 0;

		int send = min(bucket, bw);
		bucket -= send;

		cout << t << "\t" << in[t] << "\t\t" << send << "\t\t" << bucket << "\t" << drop << "\n";
	}

	for(; bucket > 0; ++t)
	{
		int send = min(bucket, bw);
		bucket -= send;

		cout << t << "\t" << 0 << "\t\t" << send << "\t\t" << bucket << "\t" << 0 << "\n";
	}

	return 0;
}