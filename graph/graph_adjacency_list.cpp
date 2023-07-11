#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>

using namespace std;

struct Vertex
{
    int val;
    Vertex(int x = 0):val(x) {}
    friend ostream &operator<<(ostream &os, Vertex &vet);
};

ostream &operator<<(ostream &os, Vertex &vet)
{
    os << vet.val;
    return os;
}

class GraphList
{
    friend vector<Vertex *> graphBFS(GraphList &graph, Vertex *startVet);
    friend void dfs(GraphList &graph, unordered_set<Vertex *> &vistied, vector<Vertex *> &res, Vertex *vet);

private:
    unordered_map<Vertex *, vector<Vertex *>> adjList;

    //删除vector中的指定节点
    void remove(vector<Vertex *> &vec, Vertex *vet)
    {
        for (auto beg = vec.begin(); beg != vec.end(); ++beg)
        {
            if(*beg == vet)
            {
                vec.erase(beg);
                break;
            }
        }
    }

public:
    GraphList(const vector<vector<Vertex *>> &edges)
    {
        for(const auto &edge : edges)
        {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    //获取顶点数量
    int size()
    {
        return adjList.size();
    }

    //添加顶点
    void addVertex(Vertex *vet)
    {
        if(adjList.count(vet))
            return;
        adjList[vet] = vector<Vertex *>();
    }

    //删除节点
    void removeVertex(Vertex *vet)
    {
        if(!adjList.count(vet))
            throw invalid_argument("There are no vertex.");
        adjList.erase(vet);
        for(auto &adj : adjList)
        {
            remove(adj.second, vet);
        }
    }

    //添加边
    void addEdge(Vertex *vet1, Vertex *vet2)
    {
        if(!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("There are no vertex.");
        adjList[vet1].push_back(vet2);
        adjList[vet2].push_back(vet1);
    }

    //删除边
    void removeEdge(Vertex *vet1, Vertex *vet2)
    {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("There are no vertex.");
        remove(adjList[vet1], vet2);
        remove(adjList[vet2], vet1);
    }

    void printInfo()
    {
        for(auto pair : adjList)
        {
            cout << *(pair.first) << "->";
            for (auto beg = pair.second.begin(); beg != pair.second.end(); ++beg)
            {
                if(((beg+1) != pair.second.end()))
                {
                    cout << **beg << "->";
                }
                else
                {
                    cout << **beg;
                }
            }
            cout << endl;
        }
    }
};

//广度优先搜索
vector<Vertex *> graphBFS(GraphList &graph, Vertex *startVet)
{
    //顶点遍历列表
    vector<Vertex *> res;
    unordered_set<Vertex *> visited{startVet};
    queue<Vertex *> que;
    que.push(startVet);
    while (!que.empty())
    {
        Vertex *vet = que.front();
        que.pop();
        res.push_back(vet);
        for(auto adjVet : graph.adjList[vet])
        {
            //跳过已经访问过的顶点
            if(visited.count(adjVet))
                continue;
            que.push(adjVet);
            visited.emplace(adjVet);
        }
    }
    return res;
}

//深度优先搜索
void dfs(GraphList &graph, unordered_set<Vertex *> &vistied, vector<Vertex *> &res, Vertex *vet)
{
    res.push_back(vet); //记录访问节点
    vistied.emplace(vet); //标记访问过的节点
    for(Vertex *adjVet : graph.adjList[vet])
    {
        if(vistied.count(adjVet))
            continue;
        dfs(graph, vistied, res, adjVet);
    }
}

vector<Vertex *> graphDFS(GraphList &graph, Vertex *startVet)
{
    unordered_set<Vertex *> vistied;
    vector<Vertex *> res;
    dfs(graph, vistied, res, startVet);
    return res;
}
int main()
{
    Vertex *v1 = new Vertex(1);
    Vertex *v2 = new Vertex(3);
    Vertex *v3 = new Vertex(2);
    Vertex *v4 = new Vertex(5);
    Vertex *v5 = new Vertex(4);
    vector<Vertex *> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    vector<vector<Vertex *>> edges = {{v[0], v[1]}, {v[0], v[3]}, {v[1], v[2]}, {v[2], v[3]}, {v[2], v[4]}, {v[3], v[4]}};
    GraphList graph(edges);
    cout << "\n初始化后, 图为: " << endl;
    graph.printInfo();

    /* 添加边 */
    graph.addEdge(v[0], v[2]);
    cout << "\n添加边 1-2 后，图为: " << endl;
    graph.printInfo();

    /* 删除边 */
    // 顶点 1, 3 即 v[0], v[1]
    graph.removeEdge(v[0], v[1]);
    cout << "\n删除边 1-3 后，图为" << endl;
    graph.printInfo();

    /* 添加顶点 */
    Vertex *v6 = new Vertex(6);
    graph.addVertex(v6);
    cout << "\n添加顶点 6 后，图为" << endl;
    graph.printInfo();

    /* 删除顶点 */
    // 顶点 3 即 v[1]
    graph.removeVertex(v2);
    cout << "\n删除顶点 3 后，图为" << endl;
    graph.printInfo();

    for(auto &i : v)
        delete i;
    return 0;
}