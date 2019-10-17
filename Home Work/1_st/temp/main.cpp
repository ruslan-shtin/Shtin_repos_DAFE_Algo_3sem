#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

class ListGraph
{
public:
    ListGraph (size_t _size)
        :vertices{_size} {}

    void Add(size_t Start, size_t End)
    {
        vertices.at(Start).insert(End);  //push_back не проверяет, существует ли точка Start. Поэтому используем метод at
        vertices.at(End).insert(Start); //неорграф
    }

    size_t GetVerticesCount() const { return vertices.size(); }

    set<size_t> GetVertices(size_t P) const { return vertices[P]; }
private:
    vector<set<size_t>>  vertices;
};

enum class Colors
{
    WHITE,
    GRAY,
    BLACK
};

void print_vec(vector<int> vect)
{
    for (auto item : vect)
        cout << item << " ";
    cout << endl;
}

void print_vec(vector<Colors> vect)
{
    for (auto item : vect)
    {
        if (item == Colors::WHITE) cout << "W";
        else if (item == Colors::GRAY) cout << "G";
        else cout <<"B";
        cout << " ";
    }
    cout << endl;
}

int len_of_shortest_path(const ListGraph Graph, const size_t& start, const size_t& finish)
{
    vector<Colors> colors(Graph.GetVerticesCount(),Colors::WHITE);
    vector<int> distance(colors.size());

    queue<size_t> Queue;
    Queue.push(start);
    distance.at(start) = 0;
    colors.at(start) = Colors::GRAY;
    while(!Queue.empty())
    {
        for(size_t item : Graph.GetVertices(Queue.front()))
        {
            if (colors.at(item) == Colors::WHITE && !(Queue.front() == start && item == finish))
            {
                Queue.push(item);
                distance.at(item) = distance.at(Queue.front()) + 1;
                colors.at(item) = Colors::GRAY;
            }
            else if (colors.at(item) == Colors::BLACK && Queue.front() == finish)
            {
                return distance.at(finish);
            }
        }
        colors.at(Queue.front()) = Colors::BLACK;
        Queue.pop();
    }
    return -1;
}


int main()
{
    ListGraph Graph9(7);
    Graph9.Add(0, 1);
    Graph9.Add(0, 4);
    Graph9.Add(0, 5);
    Graph9.Add(2, 1);
    Graph9.Add(2, 3);
    Graph9.Add(3, 4);
    Graph9.Add(4, 6);
    Graph9.Add(5, 6);
    int len = len_of_shortest_path(Graph9, 4, 6);
    cout << len << (len == 3?" OK":" NOT") << endl;

}
