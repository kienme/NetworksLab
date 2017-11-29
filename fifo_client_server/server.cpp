#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX 1024
#define PERM 0777
#define REQ_FILE "request.fifo"
#define RES_FILE "response.fifo"

using namespace std;

int main()
{	
	mkfifo(REQ_FILE, PERM);
	mkfifo(RES_FILE, PERM);	

	cout << "Waiting for request...\n";
	
	int req = open(REQ_FILE, O_RDONLY);
	int res = open(RES_FILE, O_WRONLY);	

	char fname[MAX];
	read(req, fname, sizeof(fname));

	cout << "Received request for " << fname << endl;

	ifstream f(fname);
	if(f)
	{
		cout << "Sending file data\n";

		char buf[MAX];
		f.read(buf, sizeof(buf));
		write(res, buf, sizeof(buf));
	}
	else
	{
		cout << "Sending error response\n";

		char err[] = "File not found";
		write(res, err, sizeof(err));
	}
	f.close();

	close(req);
	close(res);

	unlink(REQ_FILE);
	unlink(RES_FILE);

	return 0;
}