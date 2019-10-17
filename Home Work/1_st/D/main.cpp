#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum class Colors
{
    WHITE,
    GRAY,
    BLACK,
};

//является ли граф двудольным
bool Is_bipartial(const vector<vector<int>>& graph)
{
    queue<size_t> visit;
    vector<Colors> colors (graph.size(), Colors::WHITE);
    for (size_t i = 0; i < colors.size(); i++)
    {
        if (colors[i] == Colors::WHITE)
        {
            colors[i] = Colors::BLACK;
            visit.push(i);
            while (visit.size())
            {
                int front = visit.front();
                for( auto vertex : graph[front] )
                {
                    if (colors[vertex] == colors[front])
                    {
                        return false;
                    }
                    else if (colors[vertex] == Colors::WHITE)
                    {
                        colors[vertex] = (colors[front] == Colors::BLACK ? Colors::GRAY : Colors::BLACK);
                        visit.push(vertex);
                    }
                }
                visit.pop();
            }
        }
    }
    return true;
}

int main()
{
    int V, E;
    scanf("%d",&V);
    scanf("%d",&E);
    vector< vector<int> > Graph(V);
    for (int i = 0; i < E; i++)
    {
        int vert1, vert2;
        scanf("%d",&vert1);
        scanf("%d",&vert2);
        Graph[vert1].push_back(vert2);
        Graph[vert2].push_back(vert1);
    }
    cout << (Is_bipartial(Graph) ? "YES" : "NO" );

}
