/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.4.2
 *  Last modified: 2018.4.2
 *
 *  Function:
 *      to get the Euler path or Euler circuit of graph
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <list>
#include <array>
#include <deque>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <forward_list>
#include <initializer_list>

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using GraphList = vector<vector<int>>;

/**
 * loop method to get Euler path of the undirected graph
 * Time complexity: O(|E|)
 * @param graph: adjacent list of the undirected graph
 * @param src: source vertex of the graph
 * @return: Euler path
 */
vector<int> loop_method(GraphList &graph, int src=0){
    size_t size = graph.size();

    stack<int> s;
    vector<int> seq;
    vector<vector<int>> visited(size, vector<int>(size, false)); //mark whether the edges are visited

    s.push(src);
    while(!s.empty())
    {
        int u = s.top();
        bool flag = false;
        for(const auto &v: graph[u])
            if(!visited[u][v])
            {
                visited[u][v] = true;
                visited[v][u] = true;
                s.push(v);
                flag = true;
                break;
            }
        if(!flag)
        {
            s.pop();
            seq.push_back(u);
        }
    }
    return seq;
}

int main(){
    size_t num;
    cout << "请输入顶点数:"; cin >> num;
    GraphList graph(num);

    cout << "请依次输入有向图的边,以0 0结束:" << endl;
    int u, v;
    while (cin >> u >> v && !(u == 0 && v == 0))
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto seq = loop_method(graph, 0);
    for(const auto &vertex: seq)
        cout << vertex << " ";
    cout<<endl;

    return 0;
}

/*
 9
 0 7
 0 8
 1 2
 1 3
 2 8
 3 8
 4 5
 4 6
 5 6
 6 7
 6 8
 0 0
 */