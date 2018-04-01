/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.4.1
 *  Last modified: 2018.4.1
 *
 *  Function:
 *      traversal algorithms for graph
 *      coding for graph saved by adjacent list
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
using GraphMatrix = vector<vector<pair<int, int>>>

/**
 * BFS for graph using queue
 * Time complexity: O(n)
 * @param graph: adjacent list of the graph
 * @param src: source vertex of the graph, default 0
 * @return: traversal sequence
 */
vector<int> BFS(const GraphList &graph, size_t src=0){
    size_t size = graph.size();

    vector<bool> visited(size, false);
    vector<int> seq;
    queue<int> q;

    q.push(src);
    visited[src] = true;
    seq.push_back(src);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        for(const auto &v: graph[u])
            if(!visited[v])
            {
                q.push(v);
                visited[v] = true;
                seq.push_back(v);
            }
    }
    return seq;
}

/**
 * DFS for graph using stack
 * Time complexity: O(n)|O(n^2)?
 * @param graph: adjacent lsit of the graph
 * @param src: source vertex of the graph, default 0
 * @return: traversal sequence
 */
vector<int> DFS(const GraphList &graph, size_t src=0){
    size_t size = graph.size();
    vector<int> visited(size, false);
    vector<int> seq;
    stack<int> s;

    s.push(src);
    visited[src] = true;
    seq.push_back(src);
    while(!s.empty())
    {
        int u = s.top();
        bool flag = false;
        for(const auto &v: graph[u])
            if(!visited[v])
            {
                s.push(v);
                visited[v] = true;
                seq.push_back(v);
                flag = true;
                break;
            }
        if(!flag)
            s.pop();
    }
    return seq;
}

/**
 * recursive DFS for graph
 * @param graph: adjacent list of the graph
 * @param src: source vertex of the graph, default 0
 * @return: traversal sequence
 */
void rDFS_child(const GraphList &graph, vector<int> &seq, vector<bool> &visited, int pos)
{
    visited[pos] = true;
    seq.push_back(pos);
    for(const auto &v: graph[pos])
        if(!visited[v])
            rDFS_child(graph, seq, visited, v);
}

vector<int> rDFS(const GraphList &graph, size_t src=0){
    size_t size = graph.size();
    vector<bool> visited(size, false);
    vector<int> seq;
    rDFS_child(graph, seq, visited, src);
    return seq;
}

int main(){
    size_t num;
    cout << "请输入顶点数:"; cin >> num;
    vector<vector<int>> graph(num);

    cout << "请依次输入有向图的边,以0 0结束:" << endl;
    int u, v;
    while (cin >> u >> v && !(u == 0 && v == 0))
        graph[u].push_back(v);

    auto seq1 = BFS(graph, 0);
    for(const auto &v: seq1)
        cout << v << " ";
    cout << endl;

    auto seq2 = DFS(graph, 0);
    for(const auto &v: seq2)
        cout << v << " ";
    cout << endl;

    auto seq3 = rDFS(graph, 0);
    for(const auto &v: seq3)
        cout << v << " ";
    cout << endl;

    return 0;
}
