#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> Revers_Graph(const vector<vector<int>>& Graph)
{
    vector<vector<int>> reversed_graph(Graph.size());
    for (int from = 0; from < Graph.size(); from++)
        for ( int to : Graph[from]) reversed_graph[to].push_back(from);
    return reversed_graph;
}

void DFS_make_order_of_vertices(const vector<vector<int>>& Graph, const int vertex, vector<bool>& used, vector<int>& order)
{
//    cout << "enter in DFS_make_order_of_vertices. vertex = " << vertex << endl;

    used[vertex] = true;
    for(int item : Graph[vertex])
    {
        if (!used[item])
        {
            DFS_make_order_of_vertices(Graph, item, used, order);
        }
    }
    order.push_back(vertex);
}

//функция возвращает перевёрнутый порядок обхода вершин
vector<int>  reversed_order_of_vertices(const vector<vector<int>>& Graph)
{
//    cout << "enter in reversed_order_of_vertices" << endl;

    vector<int> order;
    vector<bool> used(Graph.size(), false);
    for (int i = 0; i < Graph.size(); i++)
        if (!used[i]) DFS_make_order_of_vertices(Graph, i, used, order);
    reverse(begin(order), end(order));
    return order;
}

void DFS_in_CSC(const vector<vector<int>>& Graph, const int vertex, vector<bool>& used, const int component_number,
                vector<int>& CSC_vertex_belongs, vector<int>& vertex_of_this_CSC)
{
//    cout << "enter in DFS_in_CSC. vertex = " << vertex << ", comp_numb = " << component_number << endl;

    used[vertex] = true;
    CSC_vertex_belongs[vertex] = component_number;
    vertex_of_this_CSC.push_back(vertex);
    for (int neib_vert : Graph[vertex])
    {
        if (!used[neib_vert]) DFS_in_CSC(Graph, neib_vert, used, component_number, CSC_vertex_belongs, vertex_of_this_CSC);
    }
}

//функция найдёт компоненты сильной связности (для этого ей нужен порядок обхода)
//и каждой компоненте соотнесёт вектор вершин, а каждой вершине - её компоненту связности
void find_CSC(const vector<vector<int>>& Graph, const vector<int>& bypass_order,
              vector<int>& CSC_vertex_belongs, vector<vector<int>>& vertex_of_CSC)
{
//    cout << "enter in find_CSC" << endl;

    int component_number = 0;
    vector<bool> used(Graph.size(),false);
    for (int i : bypass_order)
    {
        if (!used[i])
        {
            vector<int> vertex_of_this_CSC;
            DFS_in_CSC(Graph, i, used, component_number, CSC_vertex_belongs, vertex_of_this_CSC);
            vertex_of_CSC.push_back(vertex_of_this_CSC);
            component_number++;
        }
    }
}

//ответ = max {количество компонент сильной связности, не имеющих исходящих рёбер ,
//               количество компонент сильной связности, не имеющих входящих рёбер  }
int number_of_required_edges(const vector<vector<int>>& Graph, const vector<vector<int>>& Reversed_Graph)
{
//    cout << "enter in number_of_required_edges. Arguments: Graph(" << Graph.size() << "), " <<
//            "Reversed_Graph(" << Reversed_Graph.size() << ")" << endl;

    //найдём компоненты сильной связности (алгоритм Косарайю)

    //хотим узнать, в каком порядке нужно пройти исходный граф, чтобы найти компоненты сильной связности
    vector<int> reverse_bypass_order = reversed_order_of_vertices(Reversed_Graph);

    //вектор компонент сильной связности, которым принадлежат вершины
    //Component of Strong Connectivity to which the vertex belongs
    vector<int> CSC_vertex_belongs(Graph.size());
    
    //вектор векторов вершин, которые принадлежат конкретной компоненте связности
    vector<vector<int>> vertex_of_CSC;

    find_CSC(Graph, reverse_bypass_order, CSC_vertex_belongs, vertex_of_CSC);

//    cout << "start calculating answer" << endl;

    if (vertex_of_CSC.size() == 1) return 0;
    else
    {
        int count_IN_edges = 0;
        int count_OUT_edges = 0;
        for(int component = 0; component < vertex_of_CSC.size(); component++)
        {
//            cout << "calculating edges for comp = " << component << endl;

            bool flag_IN = false; //есть ли ребро входящее
            bool flag_OUT = false; //есть ли ребро исходящее

            for(int vert : vertex_of_CSC[component])
            {
                if (flag_IN && flag_OUT)
                {

//                    cout << "\t component " << component << " has as IN, as OUT edges" << endl;

                    break;
                }
                else
                {

//                    cout << "\t checking vert " << vert << endl;

                    for(int neib_vert : Graph[vert])
                    {
                        if(CSC_vertex_belongs[neib_vert] != component)
                        {

//                            cout << "\t\t there is OUT edge to " << neib_vert << "  from comp=" << CSC_vertex_belongs[neib_vert] << endl;

                            flag_OUT = true;
                            break;
                        }
                    }
                    for(int r_neib_vert : Reversed_Graph[vert])
                    {
                        if(CSC_vertex_belongs[r_neib_vert] != component)
                        {

//                            cout << "\t\t there is IN edge from " << r_neib_vert << "  from comp=" << CSC_vertex_belongs[r_neib_vert] << endl;

                            flag_IN = true;
                            break;
                        }
                    }
                }
            }
            if (!flag_IN) count_IN_edges++;
            if (!flag_OUT) count_OUT_edges++;
        }
//        cout << "count_IN_edges = " << count_IN_edges << ", count_OUT_edges = " << count_OUT_edges << endl;
        return max(count_IN_edges, count_OUT_edges);
    }

}

int main()
{
    int V, E;
    scanf("%d", &V);
    scanf("%d", &E);
    vector< vector<int> > Graph(V);
    vector< vector<int> > Reversed_Graph(V);

    for (int i = 0; i < E; i++)
    {
        int start, end;
        scanf("%d", &start);
        scanf("%d", &end);
        //вершины нумеруются, начиная с 1
        start--; end--;
        if (start != end)
        {
            Graph[start].push_back(end);
            Reversed_Graph[end].push_back(start);
        }
    }
    cout << number_of_required_edges(Graph, Reversed_Graph) << endl;

/*
    vector<vector<int>> graph1(4);//просто 4 точки
    cout << number_of_required_edges(graph1, Revers_Graph(graph1)) << (number_of_required_edges(graph1, Revers_Graph(graph1)) == 4? " OK\n" : " NOT\n");

    vector<vector<int>> graph2(4);
    graph2[0].push_back(1);
    graph2[2].push_back(3);
    cout << number_of_required_edges(graph2, Revers_Graph(graph2)) << (number_of_required_edges(graph2, Revers_Graph(graph2)) == 2? " OK\n" : " NOT\n");

    vector<vector<int>> graph3(4);
    graph3[0].push_back(1);
    graph3[0].push_back(3);
    graph3[1].push_back(2);
    graph3[2].push_back(3);
    cout << number_of_required_edges(graph3, Revers_Graph(graph3)) << (number_of_required_edges(graph3, Revers_Graph(graph3)) == 1? " OK\n" : " NOT\n");

    vector<vector<int>> graph4(4);
    graph4[0].push_back(1);
    graph4[1].push_back(2);
    graph4[2].push_back(0);
    graph4[3].push_back(2);
    cout << number_of_required_edges(graph4, Revers_Graph(graph4)) << (number_of_required_edges(graph4, Revers_Graph(graph4)) == 1? " OK\n" : " NOT\n");

    vector<vector<int>> graph5(5);
    graph5[0].push_back(2);
    graph5[1].push_back(2);
    graph5[2].push_back(3);
    graph5[2].push_back(4);
    cout << number_of_required_edges(graph5, Revers_Graph(graph5)) << (number_of_required_edges(graph5, Revers_Graph(graph5)) == 2? " OK\n" : " NOT\n");
*/
}
