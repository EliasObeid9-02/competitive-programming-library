#include <bits/stdc++.h>
using namespace std;

const long long INF = 1'000'000'000LL * 1'000'000'000 * 2;

vector<vector<long long>> floydWarshall(int graph_size, const vector<vector<long long>> &weights)
{
    vector<vector<long long>> distances(graph_size, vector<long long>(graph_size, INF));
    for (int start_node = 0; start_node < graph_size; ++start_node)
    {
        for (int end_node = 0; end_node < graph_size; ++end_node)
        {
            distances[start_node][end_node] = min(distances[start_node][end_node],
                                                  (long long)weights[start_node][end_node]);
        }
    }

    for (int middle_node = 0; middle_node < graph_size; ++middle_node)
    {
        for (int start_node = 0; start_node < graph_size; ++start_node)
        {
            for (int end_node = 0; end_node < graph_size; ++end_node)
            {
                distances[start_node][end_node] = min(distances[start_node][end_node],
                                                      distances[start_node][middle_node] +
                                                          distances[middle_node][end_node]);
            }
        }
    }
    return distances;
}

int main()
{
    int graph_size, queries;
    cin >> graph_size >> queries;

    vector<vector<long long>> weights(graph_size, vector<long long>(graph_size));
    for (int i = 0; i < graph_size; ++i)
    {
        for (int j = 0; j < graph_size; ++j)
        {
            cin >> weights[i][j];
        }
    }

    vector<vector<long long>> distances = floydWarshall(graph_size, weights);
    for (int query = 0; query < queries; ++query)
    {
        int start_node, end_node;
        cin >> start_node >> end_node;
        cout << distances[start_node][end_node] << "\n";
    }
    return 0;
}