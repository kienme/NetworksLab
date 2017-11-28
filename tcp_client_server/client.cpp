#include <iostream>
#include <arpa/inet.h>

#define MAX 255

using namespace std;

int main()
{
	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sd = socket(AF_INET,  SOCK_STREAM, 0);
	connect(sd, (sockaddr*)&addr, sizeof(addr));

	char fname[MAX];
	cout << "Enter filename: ";
	cin >> fname;

	cout << "Sending request...\n";
	send(sd, fname, sizeof(fname), 0);

	char buf[MAX];
	recv(sd, buf, sizeof(buf), 0);

	cout << "Received response: \n";
	cout << buf << endl;

	return 0;
}