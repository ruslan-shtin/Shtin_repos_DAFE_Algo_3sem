#include <iostream>
#include <vector>
#include <queue>

using namespace std;


// МОЖНО УСКОРИТЬ
int index(const vector<int>& vect, int elem) //найти индекс первого вхождения
{//я точно знаю, что elem в vect есть и он единственнен
    for (int i = 0; i < vect.size(); i++)
        if (vect[i] == elem) return i;
}

bool is_here(const vector<int>& vect, int elem)
{
    for (int i = 0; i < vect.size(); i++)
        if (vect[i] == elem) return true;
    return false;
}

void delete_from_vect(vector<int>& vect, int elem)
{
    int ind = index(vect, elem);
    for (int i = ind; i < vect.size()-1; i++)
        vect[i] = vect[i+1];
    vect.pop_back();
}
void delete_from_vect(vector<vector<int>>& vect, int ind)
{
    for (int i = ind; i < vect.size()-1; i++)
        vect[i] = vect[i+1];
    vect.pop_back();
}

//-------------------------------------------------------STAGE_1------------------------------------
vector<vector<int>> make_subgraph(const vector<vector<int>>& Graph, const vector<int>& vertices_in_comp)
{
    vector<vector<int>> result(vertices_in_comp.size());
    //подграф будет иметь новую нумерацию. Пусть новый номер вершины совпадает с её индексом в vertices_in_comp
    for(int vert : vertices_in_comp)
        for (int neib_vert : Graph[vert])
            if (is_here(vertices_in_comp, neib_vert))
                result[index(vertices_in_comp, vert)].push_back(index(vertices_in_comp, neib_vert));
    return result;
}

void DFS(const vector<vector<int>>& Graph, int vertex, vector<bool>& used, vector<int>& vertices_in_comp)
{
    used[vertex] = true;
    vertices_in_comp.push_back(vertex);
    for (int neib_vert : Graph[vertex])
    {
        if (!used[neib_vert]) DFS(Graph, neib_vert, used, vertices_in_comp);
    }
}

void find_component(const vector<vector<int>>& Graph, vector<vector<vector<int>>>& components)
{
    vector<bool> used(Graph.size(), false);
    for (int i = 0; i < Graph.size(); i++)
        if (!used[i])
        {
            vector<int> vertices_in_new_comp; //все вершины компоненты
            DFS(Graph, i, used, vertices_in_new_comp);
            components.push_back(make_subgraph(Graph, vertices_in_new_comp));
        }
}
//ДАЛЕЕ ГРАФ СВЯЗНЫЙ
//-------------------------------------------------------------STAGE 2---------------------------------------
bool DFS_has_cicle(const vector<vector<int>>& graph, int vertex, int parent, vector<bool>& used)
{
    used[vertex] = true;
    for (int neib_vert : graph[vertex])
        if (used[neib_vert])
        {
            if ((neib_vert != parent))
                return true; //нашли цикл
        }
        else if (DFS_has_cicle(graph, neib_vert, vertex, used)) return true;
    return false;
}
//МОЖНО ОПТИМИЗИРОВАТЬ, ИСПОЛЬЗОВАВ ФАКТ, ЧТО ГРАФ СВЯЗНЫЙ
bool graph_has_cicle(const vector<vector<int>>& Graph)
{
    vector<bool> used(Graph.size(), false);
    if(DFS_has_cicle(Graph, 0, -1, used)) return true;

    return false;
}
//----------------------------------------------------------STAGE 3--------------------------------------------
void DFS_find_bridge(vector<vector<int>>& Graph, int vertex, int parent, vector<bool>& used,
                     vector<int>& tin, vector<int>& fup, int& timer, int& counter_bridge)
{
    used[vertex] = true;
    tin[vertex] = timer;
    fup[vertex] = timer;
    timer++;
    for (int to : Graph[vertex])
    {
        if (to == parent) continue;
        if (used[to])
            fup[vertex] = min(fup[vertex],tin[to]);
        else
        {
            DFS_find_bridge(Graph, to, vertex, used, tin, fup, timer, counter_bridge);
            fup[vertex] = min(fup[vertex], fup[to]);
            if (fup[to] > tin[vertex])
            {
                //НАШЛИ МОСТ (VERTEX,TO)
                counter_bridge++;
                delete_from_vect(Graph[vertex], to);
                delete_from_vect(Graph[to], vertex);
            }
        }
    }
}
int find_and_delete_bridges(vector<vector<int>>& Graph)
{
    vector<int> tin(Graph.size(), 0); //время захода в вершину
    vector<int> fup(Graph.size());
    vector<bool> used(Graph.size(), false);
    int timer = 0;
    int counter_bridge = 0;
    for (int i = 0; i < Graph.size(); i++)
    {
        if (!(used[i])) DFS_find_bridge(Graph, i, -1, used, tin, fup, timer, counter_bridge);
    }
    return counter_bridge;
}
//-------------------------------------------STAGE 4-------------------------------
void delete_point(vector<vector<int>> Graph, int V)
{
    for (int neib_v : Graph[V])
    {
        delete_from_vect(Graph[neib_v], V);
    }
    delete_from_vect(Graph, V);
}
void DFS_find_cutpoint(vector<vector<int>>& Graph, int vertex, int parent, vector<bool>& used,
                       vector<int>& tin, vector<int>& fup, int& timer, int& children, int& counter_cutpoint)
{
    used[vertex] = true;
    tin[vertex] = timer;
    fup[vertex] = timer;
    timer++;
    for (int to : Graph[vertex])
    {
        if (to == parent) continue;
        if (used[to])
            fup[vertex] = min(fup[vertex], tin[to]);
        else
        {
            DFS_find_cutpoint(Graph, to, vertex, used, tin, fup, timer, children, counter_cutpoint);
            fup[vertex] = min(fup[vertex], fup[to]);
            ++children;
            if (fup[to] >= tin[vertex] && parent != -1)
            {
                //НАШЛИ ТОЧКУ СОЧЛЕНЕНИЯ
                delete_point(Graph, vertex);
                counter_cutpoint++;
            }
        }
    }
    if (parent == -1 && children > 1)
    {
        //НАШЛИ ТОЧКУ СОЧЛЕНЕНИЯ
        delete_point(Graph, vertex);
        counter_cutpoint++;
    }

}
int find_and_delete_connect_component(vector<vector<int>> Graph)
{
    vector<int> tin(Graph.size(), 0); //время захода в вершину
    vector<int> fup(Graph.size());
    vector<bool> used(Graph.size(), false);
    int timer = 0;
    int counter_cutpoint = 0;
    int children = 0;
    for (int i = 0; i < Graph.size(); i++)
    {
        if (!(used[i])) DFS_find_cutpoint(Graph, i, -1, used, tin, fup, timer, children, counter_cutpoint);
    }
    return counter_cutpoint;
}
//----------------------------------MAIN PROGRAM-----------------------------
enum class Stage
{
    find_connect_component,
    find_cicle_before_deleting_bridges,
    find_bridges,
    find_cicle_before_deleting_connect_point,
    find_connect_point,
    find_cicle_before_inicialization,
    inicialization,
    general_step,

};

bool is_planar(vector<vector<int>>& Graph, Stage stage)
{
    if (stage == Stage::find_connect_component)
    {
        vector<vector<vector<int>>> components; //вектор компонент связности (каждая компонента - граф)
        find_component(Graph, components);
        if (components.size() == Graph.size()) return true;
        else
        {
            for(auto comp : components)
                if (!is_planar(comp, Stage::find_cicle_before_deleting_bridges)) return false;
            return true;
        }
    }

    if (stage == Stage::find_cicle_before_deleting_bridges)
    {
        if (!graph_has_cicle(Graph)) return true;
        stage = Stage::find_bridges;
    }

    if (stage == Stage::find_bridges)
    {
        int count = find_and_delete_bridges(Graph); //количество удалённых мостов
        if (count == 0) stage = Stage::find_cicle_before_deleting_connect_point;
        else
        {
            vector<vector<vector<int>>> components; //вектор компонент связности (каждая компонента - граф)
            find_component(Graph, components);
            for(auto comp : components)
                if (!is_planar(comp, Stage::find_cicle_before_deleting_connect_point)) return false;
            return true;
        }
    }

    if (stage == Stage::find_cicle_before_deleting_connect_point)
    {
        if (!graph_has_cicle(Graph)) return true;
        stage = Stage::find_connect_point;
    }

    if (stage == Stage::find_connect_component)
    {
        int count = find_and_delete_connect_component(Graph); //количество удалённых точек сочленения
        if (count == 0) stage = Stage::find_cicle_before_inicialization;
        else
        {
            vector<vector<vector<int>>> components; //вектор компонент связности (каждая компонента - граф)
            find_component(Graph, components);
            for(auto comp : components)
                if (!is_planar(comp, Stage::find_cicle_before_inicialization)) return false;
            return true;
        }
    }

    if (stage == Stage::find_cicle_before_inicialization)
    {
        if (!graph_has_cicle(Graph)) return true;
        stage = Stage::inicialization;
    }

    /*
     *
     *
     *
     *
     *
     *
     *
     *          ГАММА-АЛГОРИТМ НА ПОЛУЧЕННОМ ГРАФЕ
     *
     *
     *
     *
     *
     *
     * */


}

bool is_planar(vector<vector<int>>& Graph)
{
    return is_planar(Graph, Stage::find_connect_component);
}


//-------------------------------------------------
void show_graph(const vector<vector<int>> graph)
{
    cout << "show_graph: \n";
    for (int vert = 0; vert < graph.size(); vert++)
    {
        cout << vert << ":";
        for (int neib_vert : graph[vert])
            cout << " " << neib_vert;
        cout << endl;
    }
}

int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<int>> Graph(V);
    for (int i = 0; i < E; i++)
    {
        int vert1, vert2;
        scanf("%d", &vert1);
        scanf("%d", &vert2);
        Graph[vert1].push_back(vert2);
        Graph[vert2].push_back(vert1);
    }


    cout << (graph_has_cicle(Graph) ? " yes \n" : "no \n");

    //    vector<vector<vector<int>>> components; //вектор компонент связности (каждая компонента - граф)
    //    find_component(Graph, components);

    //    for (auto comp : components)
    //        show_graph(comp);


    //    if (is_planar(Graph)) printf("YES");
    //    else printf("NO");


}
