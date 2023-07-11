#include<iostream>
#include<vector>

using namespace std;

class GraphMatrix
{
private:
    vector<int> vertices;//顶点列表
    vector<vector<int>> adjMat; //邻接矩阵

public:
    GraphMatrix(const vector<int> &vertices, const vector<vector<int>> &edges)
    {
        for(auto val : vertices)
        {
            addVertex(val);
        }

        for(auto &edge : edges)
        {
            addEdge(edge[0], edge[1]);
        }
    }

    int size() const
    {
        return vertices.size();
    }

    void addVertex(int val)  //添加顶点
    {
        int n = size();
        vertices.push_back(val);
        adjMat.emplace_back(n, 0);
        for(auto &row : adjMat)
        {
            row.push_back(0);
        }
    }

    void removeVertex(int index) //删除节点
    {
        if(index >= size())
        {
            throw out_of_range("The vertex does not exist.");
        }
        //在顶点列表中删除顶点
        vertices.erase(vertices.begin() + index);
        //删除一行
        adjMat.erase(adjMat.begin() + index);
        //删除一列
        for(auto &row : adjMat)
        {
            row.erase(row.begin() + index);
        }
    }

    //添加边
    void addEdge(int i, int j)
    {
        if(i < 0 || j < 0 || i >= size() || j >= size() || i == j)
        {
            throw out_of_range("The vertex does not exist.");
        }
        adjMat[i][j] = 1;
        adjMat[j][i] = 1;
    }

    //删除边
    void removeEdge(int i, int j)
    {
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j)
        {
            throw out_of_range("The vertex does not exist.");
        }
        adjMat[i][j] = 0;
        adjMat[j][i] = 0;
    }

    void printInfo()
    {
        cout << "GraphMatrix: \n" << "  ";
        for(auto i : vertices)
            cout << i << " ";
        cout << "\n  ---------\n";
        int count = 0;
        for (auto row : adjMat)
        {
            cout << vertices[count++] << "|";
            for (auto col : row)
            {
                cout << col << " ";
            }
            cout << '\n';
        }
        cout << endl;
    }
};

int main()
{
    vector<int> vertices = {1, 3, 2, 5, 4};
    vector<vector<int>> edges = {{0, 1}, {0, 3}, {1, 2}, {2, 3}, {2, 4}, {3, 4}};
    GraphMatrix graph(vertices, edges);
    cout << "\n初始化后, 图为" << endl;
    graph.printInfo();
    return 0;
}