#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum class Colors
{
    WHITE,
    GRAY
};

void BFS(const vector<vector<int>>& Graph, const int Start, int& cicle_len)
{
    vector<Colors> colors(Graph.size(), Colors::WHITE);
    vector<int> distances(Graph.size(), 0);
    colors[Start] = Colors::GRAY;
    queue<int> Queue;
    Queue.push(Start);
    while (!Queue.empty())
    {
        int front = Queue.front();
        Queue.pop();
        for(auto vertex : Graph[front])
        {
            if (colors[vertex] == Colors::WHITE)
            {
                distances[vertex] = distances[front] + 1;
                colors[vertex] = Colors::GRAY;
                Queue.push(vertex);
            }
            else
                if(distances[vertex] == distances[front])
                {
                    cicle_len = (cicle_len == -1 ? 2*distances[vertex] + 1 : min(cicle_len, 2*distances[vertex] + 1));
                    return;
                }
                else if(distances[vertex] == distances[front] + 1)
                {
                    cicle_len = (cicle_len == -1 ? 2*distances[vertex]: min(cicle_len, 2*distances[vertex]));
                    return;
                }
        }
    }
}

int Find_min_len_of_cycle(const vector<vector<int>>& Graph)
{
    int result = -1;
    vector<Colors> colors(Graph.size(), Colors::WHITE);
    for (int i = 0; i < Graph.size(); i++)
    {
        BFS(Graph,i, result);
    }
    return result;
}

int main()
{

    int N, M;
    cin >> N >> M;
    vector<vector<int>> Graph(N);
    if (N == 0) cout << -1;
    else
    {
        for (int i = 0; i < M; i++)
        {
            int start, end;
            scanf("%d",&start);
            scanf("%d",&end);
            Graph[start].push_back(end);
            Graph[end].push_back(start);
        }
        cout << Find_min_len_of_cycle(Graph);
    }
}
