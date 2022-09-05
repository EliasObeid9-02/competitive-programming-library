#include <bits/stdc++.h>
using namespace std;

template <typename number_type, int alphabet_size>
class BinaryTrie
{
private:
    struct TrieNode
    {
        const static int BITS = 2;
        array<int, BITS> freq;
        array<int, BITS> next_nodes;
        TrieNode()
        {
            freq.fill(0);
            next_nodes.fill(-1);
        }
    };

    int root;
    vector<TrieNode> nodes;
    int fetchNode()
    {
        nodes.emplace_back(TrieNode());
        return (int)nodes.size() - 1;
    }

    // type is true if adding value otherwise false
    void modifyTrie(number_type value, bool type)
    {
        int current_node = root;
        for (int bit = alphabet_size; bit >= 0; --bit)
        {
            int value_bit = (value >> bit & 1);
            if (nodes[current_node].next_nodes[value_bit] == -1)
            {
                nodes[current_node].next_nodes[value_bit] = fetchNode();
            }
            nodes[current_node].freq[value_bit] += (type ? +1 : -1);
            current_node = nodes[current_node].next_nodes[value_bit];
        }
    }

public:
    BinaryTrie()
    {
        root = fetchNode();
    }

    BinaryTrie(const vector<number_type> &initial_array)
    {
        root = fetchNode();
        for (int i = 0; i < (int)initial_array.size(); ++i)
        {
            insert(initial_array[i]);
        }
    }

    void insert(number_type value)
    {
        modifyTrie(value, true);
    }

    void erase(number_type value)
    {
        modifyTrie(value, false);
    }

    bool find(number_type value)
    {
        int current_node = root;
        for (int bit = alphabet_size; bit >= 0; --bit)
        {
            int value_bit = (value >> bit & 1);
            if (nodes[current_node].next_nodes[value_bit] == -1 ||
                nodes[current_node].freq[value_bit] == 0)
            {
                return false;
            }
            current_node = nodes[current_node].next_nodes[value_bit];
        }
        return true;
    }

    number_type getMinimumXor(number_type value)
    {
        number_type minimum_xor{};
        int current_node = root;
        for (int bit = alphabet_size; bit >= 0; --bit)
        {
            int value_bit = (value >> bit & 1);
            if (nodes[current_node].next_nodes[value_bit] != -1 &&
                nodes[current_node].freq[value_bit] > 0)
            {
                current_node = nodes[current_node].next_nodes[value_bit];
            }
            else if (nodes[current_node].next_nodes[value_bit ^ 1] != -1)
            {
                minimum_xor |= (1LL << bit);
                current_node = nodes[current_node].next_nodes[value_bit ^ 1];
            }
            else
            {
                return -1;
            }
        }
        return minimum_xor;
    }

    number_type getMaximumXor(number_type value)
    {
        number_type maximum_xor{};
        int current_node = root;
        for (int bit = alphabet_size; bit >= 0; --bit)
        {
            int value_bit = (value >> bit & 1);
            if (nodes[current_node].next_nodes[value_bit ^ 1] != -1 &&
                nodes[current_node].freq[value_bit ^ 1] > 0)
            {
                maximum_xor |= (1LL << bit);
                current_node = nodes[current_node].next_nodes[value_bit ^ 1];
            }
            else if (nodes[current_node].next_nodes[value_bit] != -1)
            {
                current_node = nodes[current_node].next_nodes[value_bit];
            }
            else
            {
                return -1;
            }
        }
        return maximum_xor;
    }
};

int main()
{
    int array_size, queries;
    cin >> array_size >> queries;

    vector<int> initial_array(array_size);
    for (int i = 0; i < array_size; ++i)
    {
        cin >> initial_array[i];
    }

    BinaryTrie<int, 20> trie(initial_array);
    for (int i = 0; i < queries; ++i)
    {
        int value;
        string operation;
        cin >> operation >> value;
        if (operation == "add")
        {
            trie.insert(value);
        }
        else if (operation == "remove")
        {
            trie.erase(value);
        }
        else if (operation == "find")
        {
            cout << (trie.find(value) ? "Yes" : "No") << "\n";
        }
        else if (operation == "minimum")
        {
            cout << trie.getMinimumXor(value) << "\n";
        }
        else if (operation == "maximum")
        {
            cout << trie.getMaximumXor(value) << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}