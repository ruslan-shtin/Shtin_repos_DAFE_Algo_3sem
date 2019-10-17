#include <iostream>
#include <vector>
#include <unordered_set>


using namespace std;

//граф
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

    unordered_set<size_t> GetVertices(size_t P) const { return vertices[P]; }
private:
    vector<unordered_set<size_t>>  vertices;
};

void Show_Graph(const ListGraph& Graph)
{
    size_t Size = Graph.GetVerticesCount();
    for (size_t i = 0; i < Size; i++)
    {
        cout << i << ":";
        if (Graph.GetVertices(i).size() == 0) cout << "NO path from";
        else
            for (const size_t item : Graph.GetVertices(i))
            {
                cout << item << " ";
            }
        cout << endl;
    }
}


int main()
{
    ListGraph Graph(8);
    Graph.Add(1, 2);
    Graph.Add(1, 4);
    Graph.Add(1, 5);
    Graph.Add(1, 6);
    Graph.Add(2, 4);
    Graph.Add(2, 3);
    Graph.Add(2, 4);
    Graph.Add(2, 6);
    Graph.Add(3, 7);
    Graph.Add(2, 4);
    Graph.Add(5, 6);
    Show_Graph(Graph);

    ListGraph Graph1(6);
    Graph1.Add(0, 1);
    Graph1.Add(0, 2);
    Graph1.Add(1, 3);
    Graph1.Add(2, 3);
    Graph1.Add(3, 4);
    Graph1.Add(3, 5);
    Graph1.Add(4, 5);


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
    \

    ListGraph Graph3(4);
    Graph3.Add(0, 1);
    Graph3.Add(2, 3);


    ListGraph Graph4(4);
    Graph4.Add(0, 1);
    Graph4.Add(0, 2);
    Graph4.Add(0, 3);


    ListGraph Graph5(4);
    Graph5.Add(0, 1);
    Graph5.Add(0, 2);
    Graph5.Add(0, 3);
    Graph5.Add(1, 3);
    Graph5.Add(2, 3);
    Graph5.Add(1, 2);


    ListGraph Graph6(5);
    Graph6.Add(1, 2);
    Graph6.Add(1, 3);
    Graph6.Add(3, 4);
    Graph6.Add(4, 2);


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


    ListGraph Graph9(7);
    Graph9.Add(0, 1);
    Graph9.Add(0, 4);
    Graph9.Add(0, 5);
    Graph9.Add(2, 1);
    Graph9.Add(2, 3);
    Graph9.Add(3, 4);
    Graph9.Add(4, 6);
    Graph9.Add(5, 6);


    cout << endl;

}
