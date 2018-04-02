/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.4.2
 *  Last modified: 2018.4.2
 *
 *  Function:
 *      to get the strong connected components of directed graph
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
using TArray = vector<vector<int>>;

/**
 * DFS for graph using stack
 * @param graph: adjacent list of graph
 * @param visited: mark whether vertices are visited
 * @param topo_seq: reversed topological sequence
 * @param src: start vertex for DFS
 */
void DFS(const GraphList &graph, vector<bool> &visited, vector<int> &topo_seq, int src){
    stack<int> s;
    s.push(src);
    visited[src] = true;
    while(!s.empty())
    {
        int u = s.top();
        bool flag = false;
        for(const auto &v: graph[u])
            if(!visited[v])
            {
                s.push(v);
                visited[v] = true;
                flag = true;
                break;
            }
        if(!flag)
        {
            s.pop();
            topo_seq.push_back(u);
        }
    }
}

/**
 * Kosarju Algorithm:
 *   1.do DFS on the original graph to get the topological sequence
 *   2.do DFS on the reversed graph to get the SCC at order of topological sequence
 * Time complexity:
 *   O(|V|+|E|)
 * @param graph: original directed graph
 * @param rgraph: reversed directed graph
 * @return: all SCC
 */
TArray Kosaraju(const GraphList &graph, const GraphList &rgraph){
    size_t size = graph.size();
    vector<int> topo_seq;
    vector<bool> visited(size, false);
    for(int i=0; i != size; ++i)
        if(!visited[i])
            DFS(graph, visited, topo_seq, i);

    TArray components;
    visited = vector<bool>(size, false);
    for(int i = size-1; i >= 0; --i)
        if(!visited[topo_seq[i]])
        {
            components.emplace_back();
            DFS(rgraph, visited, components[components.size()-1], topo_seq[i]);
        }
    return components;
}

int main(){
    size_t num;
    cout << "请输入顶点数:"; cin >> num;
    GraphList graph(num), rgraph(num);

    int u, v;
    cout << "请依次输入有向图的边,以0 0结束:" << endl;
    while (cin >> u >> v&& !(u == 0 && v == 0))
    {
        graph[u].push_back(v);
        rgraph[v].push_back(u);
    }

    cout << "Kosaraju algorithm: " << endl;
    TArray components = Kosaraju(graph, rgraph);
    if (!components.empty())
        for (int i = 0, sz = components.size(); i != sz; ++i)
        {
            cout << "Component " << i + 1 << ":";
            for (auto ver : components[i])
                cout << ver << " ";
            cout << endl;
        }

    return 0;
}