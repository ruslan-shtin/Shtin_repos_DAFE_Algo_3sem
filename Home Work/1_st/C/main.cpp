#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//на каждом шаге появляются дети - вершины, куда ещё не заходили
//в начале нет детей
//когда зайдём в первого ребёнка - все дети исчезнут
int number_of_different_paths(const vector<vector<int>>& Graph, int start, int finish)
{
    vector<int> count_paths(Graph.size(),0);
    vector<bool> is_child(count_paths.size(), false);
    queue<int> Queue;
    Queue.push(start);
    count_paths[start] = 1;
    while (!Queue.empty())
    {
        int front = Queue.front();
        if (is_child[front]) is_child.assign(is_child.size(), false);
        if (front == finish)
            return count_paths[finish];
        else
        {
            for(auto i : Graph[front])
            {
                if (count_paths[i] == 0)
                {
                    count_paths[i] = count_paths[front];
                    is_child[i] = true;
                    Queue.push(i);
                }
                else if (count_paths[i] != -1 && is_child[i])
                {
                    count_paths[i] += count_paths[front];
                }
            }

        }
        Queue.pop();
    }

    return 0;
}

int main()
{
    int V, N;
    cin >> V >> N;
    vector<vector<int>> Graph(V);
    for (int i = 0; i < N; i++)
    {
        int start, end;
        cin >> start >> end;
        Graph[start].push_back(end);
        Graph[end].push_back(start);
    }
    int start, end;
    cin >> start >> end;
    cout << number_of_different_paths(Graph,start, end);
    /*

    ListGraph Graph1(6);
    Graph1.Add(0, 1);
    Graph1.Add(0, 2);
    Graph1.Add(1, 3);
    Graph1.Add(2, 3);
    Graph1.Add(3, 4);
    Graph1.Add(3, 5);
    Graph1.Add(4, 5);
    Show_Graph(Graph1);
    cout << endl << number_of_different_paths(Graph1,0, 4) << (number_of_different_paths(Graph1,0, 4) == 2?" OK":"  NOT");

    ListGraph Graph2(7);
    Graph2.Add(0, 1);
    Graph2.Add(0, 2);
    Graph2.Add(1, 3);
    Graph2.Add(2, 3);
    Graph2.Add(5, 3);
    Graph2.Add(2, 6);
    Graph2.Add(4, 5);
    Graph2.Add(4, 6);
    Graph2.Add(6, 5);
    cout << endl << number_of_different_paths(Graph2,0, 5) << (number_of_different_paths(Graph2,0, 5) == 3?" OK":"  NOT");

    ListGraph Graph3(4);
    Graph3.Add(0, 1);
    Graph3.Add(2, 3);
    cout << endl << number_of_different_paths(Graph3,0, 3) << (number_of_different_paths(Graph3,0, 3) == 0?" OK":"  NOT");

    ListGraph Graph4(4);
    Graph4.Add(0, 1);
    Graph4.Add(0, 2);
    Graph4.Add(0, 3);
    cout << endl << number_of_different_paths(Graph4,1, 3) << (number_of_different_paths(Graph4,1, 3) == 1?" OK":"  NOT");

    ListGraph Graph5(4);
    Graph5.Add(0, 1);
    Graph5.Add(0, 2);
    Graph5.Add(0, 3);
    Graph5.Add(1, 3);
    Graph5.Add(2, 3);
    Graph5.Add(1, 2);
    cout << endl << number_of_different_paths(Graph5,1, 3) << (number_of_different_paths(Graph5,1, 1) == 1?" OK":"  NOT");

    ListGraph Graph6(5);
    Graph6.Add(1, 2);
    Graph6.Add(1, 3);
    Graph6.Add(3, 4);
    Graph6.Add(4, 2);
    cout << endl << number_of_different_paths(Graph6,1, 4) << (number_of_different_paths(Graph6,1, 4) == 2?" OK":"  NOT");

    ListGraph Graph7(10);
    Graph7.Add(0, 1);
    Graph7.Add(0, 2);
    Graph7.Add(2, 1);
    Graph7.Add(3, 5);
    Graph7.Add(3, 4);
    Graph7.Add(4, 5);
    Graph7.Add(6, 7);
    Graph7.Add(6, 9);
    Graph7.Add(8, 7);
    Graph7.Add(9, 8);
    cout << endl << number_of_different_paths(Graph7,3, 4) << (number_of_different_paths(Graph7,3, 4) == 1?" OK":"  NOT");

    ListGraph Graph8(9);
    Graph8.Add(0, 1);
    Graph8.Add(2, 1);
    Graph8.Add(2, 8);
    Graph8.Add(3, 8);
    Graph8.Add(0, 3);
    Graph8.Add(4, 0);
    Graph8.Add(5, 4);
    Graph8.Add(5, 6);
    Graph8.Add(7, 6);
    Graph8.Add(4, 7);
    cout << endl << number_of_different_paths(Graph8,1, 6) << (number_of_different_paths(Graph8,1, 6) == 2?" OK":"  NOT");

    ListGraph Graph9(7);
    Graph9.Add(0, 1);
    Graph9.Add(0, 4);
    Graph9.Add(0, 5);
    Graph9.Add(2, 1);
    Graph9.Add(2, 3);
    Graph9.Add(3, 4);
    Graph9.Add(4, 6);
    Graph9.Add(5, 6);
    cout << endl << number_of_different_paths(Graph9,1, 4) << (number_of_different_paths(Graph9,1, 1) == 1?" OK":"  NOT");

    cout << endl;
*/
}
