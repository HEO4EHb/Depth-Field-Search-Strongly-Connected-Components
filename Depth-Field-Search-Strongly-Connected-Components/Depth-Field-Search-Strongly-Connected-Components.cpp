#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph
{
    int V;    // колво вершин
    list<int>* adj;    // массив смежных

    // заполняем стак вершинами (в порядке увеличения времени достижения). верхний элемент достигается быстрее всего
    void fillOrder(int v, bool visited[], stack<int>& Stack);

    // рекурсиваня функция DFS для v
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);
    void addEdge(int v, int w);

    // основаня функция для нахождения и вывода сильного соединения
    // 
    void printSCCs();

    // функция которая возвращает обратный граф
    Graph getTranspose();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

// рекурсиваня функция DFS для v
void Graph::DFSUtil(int v, bool visited[])
{
    // Отмечаем вершину как пройденную и выводим
    visited[v] = true;
    cout << v << " ";

    //повторяем для остальных смежных вершин
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// функция которая возвращает обратный граф
Graph Graph::getTranspose()
{
    Graph g(V);
    for (int v = 0; v < V; v++)
    {
        // повторяем для остальных смежных вершин
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

//добавление ребра
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // добавляем w к листу v
}

void Graph::fillOrder(int v, bool visited[], stack<int>& Stack)
{
    // Отмечаем вершину как пройденную и выводим
    visited[v] = true;

    // повторяем для остальных смежных вершин
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, Stack);

    // все достижимые вершины пройдены  пушим v
    Stack.push(v);
}

//основаня функция для нахождения и вывода сильного соединения
void Graph::printSCCs()
{
    stack<int> Stack;

    // Отмечаем все вершины как непройденные 
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    //вписываем вершины в стак в соотвествии с временем достижения
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            fillOrder(i, visited, Stack);

    // создаем обратный граф
    Graph gr = getTranspose();

    // Отмечаем все вершины как непройденные
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // проверяем все вершины в порядке стэка
    while (Stack.empty() == false)
    {
        //удаляем вершину из стека 
        int v = Stack.top();
        Stack.pop();

        // выводим сильные связи удаленные из стека 
        if (visited[v] == false)
        {
            gr.DFSUtil(v, visited);
            cout << endl;
        }
    }
}


int main()
{
    
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    cout << "Following are strongly connected components in "
        "given graph \n";
    g.printSCCs();

    return 0;
}
