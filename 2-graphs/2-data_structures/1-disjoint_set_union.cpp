#include <bits/stdc++.h>
using namespace std;

template <bool one_indexing_mode = false>
class DSU
{
private:
	int graph_size;
	int component_count;
	vector<int> component_size, parent;

public:
	DSU() {}
	DSU(int _graph_size) : graph_size{_graph_size},
						   component_count{graph_size},
						   component_size(graph_size + (int)one_indexing_mode, 1),
						   parent(graph_size + (int)one_indexing_mode)
	{
		iota(parent.begin(), parent.end(), 0);
	}

	int getSize(int node)
	{
		return component_size[getParent(node)];
	}

	int getParent(int node)
	{
		while (node != parent[node])
		{
			parent[node] = parent[parent[node]];
			node = parent[node];
		}
		return node;
	}

	int getComponentCount()
	{
		return component_count;
	}

	bool sameComponent(int first_node, int second_node)
	{
		return getParent(first_node) == getParent(second_node);
	}

	bool mergeNodes(int first_node, int second_node)
	{
		first_node = getParent(first_node);
		second_node = getParent(second_node);
		if (first_node == second_node)
		{
			return false;
		}

		if (getSize(first_node) < getSize(second_node))
		{
			swap(first_node, second_node);
		}
		component_size[first_node] += component_size[second_node];
		parent[second_node] = first_node;

		component_size[second_node] = 0;
		--component_count;
		return true;
	}
};

int main()
{
	int graph_size, edges_count;
	cin >> graph_size >> edges_count;

	DSU graph(graph_size);
	for (int i = 0; i < edges_count; ++i)
	{
		int first_node, second_node;
		cin >> first_node >> second_node;
		--first_node, --second_node;
		graph.mergeNodes(first_node, second_node);
	}
	cout << (graph.getComponentCount() == 1 ? "Yes" : "No") << "\n";
	return 0;
}