// Muddy_Fields.cpp : Defines the entry point for the console application.
//



#include <iostream>
#include <vector>
#include <queue>

#define INF 1000000000
#define ll long long
#define debug printf("DEBUG: On Line #: %d\n",__LINE__);

using namespace std;

int r, c;
vector<int> G[2500];
char field[53][53];
int source, sink, cap[1250][1250];
int flow[2500][2500], pred[2500];

 int bfs() {
	int i, j, k;
	int current[2500];
	memset(current, 0, sizeof(current));
	memset(pred, -1, sizeof(pred));
	pred[source] = -2;
	current[source] = INF;

	queue<int> Q;
	Q.push(source);
	while (!Q.empty()) {
		int from = Q.front();
		Q.pop();

		for (i = 0; i<G[from].size(); i++) {
			int to = G[from][i];
			if (pred[to] == -1 && cap[from][to] - flow[from][to]>0) {
				pred[to] = from;
				current[to] = min(cap[from][to] - flow[from][to], current[from]);
				if (to == sink)
					return current[to];
				Q.push(to);
			}
		}
	}
	return 0;
}

void edmonds_karp() {
	int i, j, k, l, x, y = 0, z, u, v, w;
	memset(flow, 0, sizeof(flow));
	while (1) {
		x = bfs();
		if (x == 0)	break;
		y += x;

		k = sink;
		while (k != source) {
			flow[pred[k]][k] += x;
			flow[k][pred[k]] -= x;
			k = pred[k];
		}
	}
	printf("%d\n", y);
}

int main() {
	int i, j, k, l, x, y, z, u, v, w, t, horiz[55][55], vert[55][55];
	scanf("%d", &t);
	while (t--) {
		for (i = 0; i<2500; i++) G[i].clear();
		memset(horiz, -1, sizeof(horiz));
		memset(vert, -1, sizeof(vert));
		memset(cap, 0, sizeof(cap));

		scanf("%d%d", &r, &c);
		for (i = 0; i<r; i++)
			scanf("%s", field[i]);

		int h = 0;
		v = 0;
		for (i = 0; i<r; i++) {
			for (j = 0; j<c; j++) {
				if (field[i][j] == '.') continue;

				if (j == 0 || horiz[i][j - 1] == -1) {
					h++;
					G[source].push_back(h);
					G[h].push_back(source);
					cap[source][h] = 1;
				}
				horiz[i][j] = h;
			}
		}

		for (i = 0; i<c; i++) {
			for (j = 0; j<r; j++) {
				if (field[j][i] == '.') continue;
				if (j == 0 || vert[j - 1][i] == -1) {
					v++;
				}
				vert[j][i] = v;
			}
		}

		if (v == 0) {	
			printf("0\n");
			continue;
		}

		sink = h + v + 1;
		for (i = h + 1; i <= h + v; i++) {
			G[i].push_back(sink);
			G[sink].push_back(i);
			cap[i][sink] = 1;
		}

		for (i = 0; i<r; i++) {
			for (j = 0; j<c; j++) {
				if (field[i][j] == '*') {
					G[horiz[i][j]].push_back(h + vert[i][j]);
					G[h + vert[i][j]].push_back(horiz[i][j]);
					cap[horiz[i][j]][h + vert[i][j]] = 1;
				}
			}
		}
		edmonds_karp();
	}

	return 0;
}
