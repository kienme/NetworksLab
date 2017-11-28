#include <iostream>
#include <fstream>
#include <arpa/inet.h>

#define MAX 255

using namespace std;

int main()
{
	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	cout << "Waiting for request...\n";

	int sd = socket(AF_INET, SOCK_STREAM, 0);
	bind(sd, (sockaddr*)&addr, sizeof(addr));
	listen(sd, 10);

	while(true)
	{
		int src = accept(sd, NULL, NULL);

		char fname[MAX];
		recv(src, fname, sizeof(fname), 0);
		cout << "Received request for " << fname << endl;

		ifstream f(fname);
		if(f)
		{
			cout << "Sending file data\n";

			char buf[MAX];
			f.read(buf, sizeof(buf));			
			send(src, buf, sizeof(buf), 0);
		}
		else
		{
			cout << "Sending error response\n";

			char err[] = "File not found";
			send(src, err, sizeof(err), 0);
		}
		f.close();
	}

	return 0;
}