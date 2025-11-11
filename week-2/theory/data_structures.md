# Custom Data Structures

## Binary Search Tree
```cpp
template<typename T>
class BST {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left, right;
        Node(const T& value) : data(value) {}
    };
    
    std::unique_ptr<Node> root;
    
    void insert(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            node = std::make_unique<Node>(value);
        } else if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        }
    }
    
    bool search(const std::unique_ptr<Node>& node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        return value < node->data ? search(node->left, value) : search(node->right, value);
    }
    
public:
    void insert(const T& value) { insert(root, value); }
    bool contains(const T& value) const { return search(root, value); }
};
```

## Hash Table
```cpp
template<typename K, typename V, typename Hash = std::hash<K>>
class HashTable {
private:
    struct Entry {
        K key;
        V value;
        bool occupied = false;
        bool deleted = false;
    };
    
    std::vector<Entry> table;
    size_t size_;
    Hash hasher;
    
    size_t hash(const K& key) const {
        return hasher(key) % table.size();
    }
    
    size_t probe(size_t pos) const {
        return (pos + 1) % table.size();
    }
    
public:
    HashTable(size_t capacity = 16) : table(capacity), size_(0) {}
    
    void insert(const K& key, const V& value) {
        if (size_ >= table.size() * 0.75) {
            rehash();
        }
        
        size_t pos = hash(key);
        while (table[pos].occupied && !table[pos].deleted && table[pos].key != key) {
            pos = probe(pos);
        }
        
        if (!table[pos].occupied || table[pos].deleted) {
            ++size_;
        }
        
        table[pos] = {key, value, true, false};
    }
    
    bool find(const K& key, V& value) const {
        size_t pos = hash(key);
        while (table[pos].occupied) {
            if (!table[pos].deleted && table[pos].key == key) {
                value = table[pos].value;
                return true;
            }
            pos = probe(pos);
        }
        return false;
    }
    
private:
    void rehash() {
        auto old_table = std::move(table);
        table = std::vector<Entry>(old_table.size() * 2);
        size_ = 0;
        
        for (const auto& entry : old_table) {
            if (entry.occupied && !entry.deleted) {
                insert(entry.key, entry.value);
            }
        }
    }
};
```

## Graph Representation
```cpp
template<typename T>
class Graph {
private:
    std::unordered_map<T, std::vector<T>> adjacencyList;
    
public:
    void addVertex(const T& vertex) {
        adjacencyList[vertex];  // Creates empty vector if not exists
    }
    
    void addEdge(const T& from, const T& to) {
        adjacencyList[from].push_back(to);
        adjacencyList[to].push_back(from);  // For undirected graph
    }
    
    std::vector<T> bfs(const T& start) const {
        std::vector<T> result;
        std::unordered_set<T> visited;
        std::queue<T> queue;
        
        queue.push(start);
        visited.insert(start);
        
        while (!queue.empty()) {
            T current = queue.front();
            queue.pop();
            result.push_back(current);
            
            for (const T& neighbor : adjacencyList.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }
        
        return result;
    }
    
    std::vector<T> dfs(const T& start) const {
        std::vector<T> result;
        std::unordered_set<T> visited;
        dfsHelper(start, visited, result);
        return result;
    }
    
private:
    void dfsHelper(const T& vertex, std::unordered_set<T>& visited, std::vector<T>& result) const {
        visited.insert(vertex);
        result.push_back(vertex);
        
        for (const T& neighbor : adjacencyList.at(vertex)) {
            if (visited.find(neighbor) == visited.end()) {
                dfsHelper(neighbor, visited, result);
            }
        }
    }
};
```

## Trie (Prefix Tree)
```cpp
class Trie {
private:
    struct TrieNode {
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
        bool isEndOfWord = false;
    };
    
    std::unique_ptr<TrieNode> root;
    
public:
    Trie() : root(std::make_unique<TrieNode>()) {}
    
    void insert(const std::string& word) {
        TrieNode* current = root.get();
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = std::make_unique<TrieNode>();
            }
            current = current->children[c].get();
        }
        current->isEndOfWord = true;
    }
    
    bool search(const std::string& word) const {
        TrieNode* current = root.get();
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children.at(c).get();
        }
        return current->isEndOfWord;
    }
    
    bool startsWith(const std::string& prefix) const {
        TrieNode* current = root.get();
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children.at(c).get();
        }
        return true;
    }
};
```
