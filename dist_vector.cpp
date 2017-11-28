#include <iostream>

#define MAX 50

using namespace std;

struct Router
{
	int from[MAX];
	int dist[MAX];	
};

int main()
{
	int N;
	int graph[MAX][MAX];
	Router nodes[MAX];

	cout << "Enter number of nodes: ";
	cin >> N;

	cout << "Enter cost matrix: \n";
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
		{
			cin >> graph[i][j];
			
			nodes[i].from[j] = j;
			nodes[i].dist[j] = graph[i][j];
		}

	//Floyd Warshall algorithm
	for(int k = 0; k < N; ++k)
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < N; ++j)
			{
				int d = graph[i][k] + graph[k][j];
				if(d < graph[i][j])
				{
					graph[i][j] = d;

					nodes[i].from[j] = nodes[i].from[k];
					nodes[i].dist[j] = d;
				}
			}

	for(int i = 0; i < N; ++i)
	{
		cout << "\nRouter " << i+1 << "'s table\n";
		cout << "Destination\tNext hop\tDistance\n";
		for(int j = 0; j < N; ++j)
			cout << j+1 << "\t\t" << nodes[i].from[j]+1 << "\t\t" << nodes[i].dist[j] << "\n";
	}

	int src, dest;
	cout << "\nEnter source and destination: ";
	cin >> src >> dest;
	--src; --dest;

	cout << "Shortest path of cost " << nodes[src].dist[dest] << " via node " << nodes[src].from[dest]+1 << endl;

	return 0;
}