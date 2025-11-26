#include <iostream>

template <typename T>
class BST {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& v) {
            value  = v;
            left   = nullptr;
            right  = nullptr;
            parent = nullptr;
        }
    };

    Node* root = nullptr;

public:
    void insert(const T& x) {
        if (!root) {
            root = new Node(x);
            return;
        }
        Node* cur = root;
        Node* p = nullptr;

        while (cur) {
            p = cur;
            if (x < cur->value)
                cur = cur->left;
            else if (cur->value < x)
                cur = cur->right;
            else
                return; 
        }

        Node* n = new Node(x);
        n->parent = p;
        if (x < p->value)
             p->left  = n;
        else
            p->right = n;
    }

    
    class iterator {
        Node* node; 

    public:
        iterator(Node* n = nullptr) {
            node = n;
        }
        T& operator*() {
             return node->value; 
        }
        bool operator==(const iterator& other) {
             return node == other.node; 
        }
        bool operator!=(const iterator& other){
            return node != other.node; 
        }

        iterator& operator++() {
            if (node->right) {
                node = node->right;
                while (node->left)
                    node = node->left;
                return *this;
            }
            Node* p = node->parent;
            while (p && node == p->right) {
                node = p;
                p = p->parent;
            }
            node = p;          
            return *this;
        }

        iterator& operator--() {
            if (node->left) {
                node = node->left;
                while (node->right)
                    node = node->right;
                return *this;
            }

            Node* p = node->parent;
            while (p && node == p->left) {
                node = p;
                p = p->parent;
            }
            node = p;
            return *this;
        }
    };

    iterator begin() {
        Node* cur = root;
        if (!cur) 
            return iterator(nullptr);
        while (cur->left)
            cur = cur->left;
        return iterator(cur);
    }

    iterator end() {
        return iterator(nullptr); 
    }
};

int main() {
    BST<int> t;
    t.insert(5);
    t.insert(2);
    t.insert(8);
    t.insert(1);
    t.insert(3);
    t.insert(7);
    t.insert(9);

    std::cout << "For loop: ";
    for (auto it = t.begin(); it != t.end(); ++it)
        std::cout << *it << ' ';
    std::cout << "\n";

    auto it = t.begin();
    ++it; 
    std::cout << "Current: " << *it << "\n";
    --it;
    std::cout << "Prev: " << *it << "\n";
}
