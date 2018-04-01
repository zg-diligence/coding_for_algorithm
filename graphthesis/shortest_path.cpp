/*
 *  Copyright(c) 2018 Gang Zhang
 *  All rights reserved.
 *  Author: Gang Zhang
 *  Creation date: 2018.4.1
 *  Last modified: 2018.4.1
 *
 *  Function:
 *      Shortest path algorithms
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

#define NIL (-1)
#define INFINITY 0x3f3f3f3f
using GraphMatrix = vector<vector<int>>;
using GraphList = vector<vector<pair<int, int>>>;

vector<int> dist; //distance of all vertices to source vertex
vector<int> preV; //prior vertex of all vertices on the shortest path to source vertex

void print_path(int src = 0) {
    auto size = dist.size();
    GraphMatrix path(size, vector<int>());
    for (int i = 0; i != size; ++i) {
        if (i == src) {
            cout << src << "->" << i << ":itself." << endl;
            continue;
        }

        if (dist[i] == INFINITY) {
            cout << src << "->" << i << ":infinity." << endl;
            continue;
        }

        /* collect the shortest path. */
        int cur = i;
        path[i].push_back(i);
        while (preV[cur] != src) {
            path[i].push_back(preV[cur]);
            cur = preV[cur];
        }
        path[i].push_back(src);

        /* print the shortest path. */
        cout << src << "->" << path[i].front() << "(" << dist[i] << "):";
        for (int k = path[i].size() - 1; k >= 0; --k)
            cout << path[i][k] << " ";
        cout << endl;
    }
}

/*
 * push down the pointed vertex in the heap
 * param heap: reference of the heap
 * param position: position of vertices in the heap
 * param pos: the position of target vertex in the heap
 * param qsize: size of the heap
 * return: none
 */
void push_down(vector<int> &heap, vector<int> &position, int pos, int size) {
    int cur = pos;
    int vertex = heap[pos];
    int value = dist[vertex];
    while (cur * 2 <= size) {
        int next = cur * 2;
        if (next + 1 <= size && dist[heap[next + 1]] < dist[heap[next]])
            next += 1;
        if (dist[heap[next]] >= value)
            break;
        heap[cur] = heap[next];
        position[heap[cur]] = cur;
        cur = next;
    }
    heap[cur] = vertex;
    position[vertex] = cur;
}

/*
 * push up the point vertex in the heap
 * param heap: reference of the heap
 * param position: position of vertices in the heap
 * param pos: the position of target vertex in the heap
 * return: none
 */
void push_up(vector<int> &heap, vector<int> &position, int pos) {
    int cur = pos;
    int vertex = heap[pos];
    int value = dist[vertex];
    while (cur > 1) {
        int next = cur / 2;
        if (value >= dist[heap[next]])
            break;
        heap[cur] = heap[next];
        position[heap[cur]] = cur;
        cur = next;
    }
    heap[cur] = vertex;
    position[vertex] = cur;
}

/*
 * Dijkstra algorithm:
 *  it's a greedy algorithm, only applys to non-negative weighted graph
 *  always find the nearest vertex and add it to set, then update all its adjacent vertices
 *  using min-heap to get the nearest vertex
 * Time complexity:
 *   O(|E|*lg|V|) -- adjacent list
 *   O(|V|^2) -- adjacent matrix
 * Note: update the heap after updating all adjacent vertices at one process when using adjacent matrix.
 */
bool Dijkstra(const GraphList &graph, int src = 0) {
    //check whether any negative edge exists
    for (const auto &arr: graph)
        for (const auto &item: arr)
            if (item.second < 0)
                return false;

    auto size = graph.size();
    vector<int> heap(2);
    vector<int> position(size); //save position of vertices in the heap
    int qsize = size;
    dist[src] = 0;

    //init the heap
    heap[1] = src;
    position[src] = 1;
    for (int i = 0; i != size; ++i) {
        if (i == src)
            continue;

        heap.push_back(i);
        position[i] = heap.size() - 1;
    }

    while (qsize > 0) {
        //extract the nearest vertex
        int u = heap[1];
        heap[1] = heap[qsize--];
        position[heap[1]] = 1;
        push_down(heap, position, 1, qsize);

        //update adjacent vertices
        for (const auto &item: graph[u]) {
            int v = item.first;
            if (dist[u] + item.second < dist[v]) {
                preV[v] = u;
                dist[v] = dist[u] + item.second;
                push_up(heap, position, position[v]);
            }//if
        }//for
    }//while
    return true;
}

int main() {
    unsigned num, u, v, w;
    cout << "请输入顶点数:";
    cin >> num;

    GraphList graph(num);
    dist.resize(num, INFINITY);
    preV.resize(num, NIL);

    cout << "请依次输入有向图的边,以0 0 0结束:" << endl;
    while (cin >> u >> v >> w && !(u == 0 && v == 0))
        graph[u].emplace_back(v, w);

    cout << "输入源点:";
    int src;
    cin >> src;

    preV = vector<int>(num, NIL);
    dist = vector<int>(num, INFINITY);
    if (Dijkstra(graph, src))
        print_path(src);
    else
        cout << "There is a negative-weight edge." << endl;

    return 0;
}
