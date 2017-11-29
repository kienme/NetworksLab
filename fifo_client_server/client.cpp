#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX 1024
#define REQ_FILE "request.fifo"
#define RES_FILE "response.fifo"

using namespace std;

int main()
{
	int req = open(REQ_FILE, O_WRONLY);
	int res = open(RES_FILE, O_RDONLY);

	char fname[MAX];
	cout << "Enter filename: ";
	cin >> fname;

	cout << "Sending request...\n";
	write(req, fname, sizeof(fname));

	char buf[MAX];
	read(res, buf, sizeof(buf));
	cout << "Received response: \n";
	cout << buf << endl;

	close(req);
	close(res);

	return 0;
}