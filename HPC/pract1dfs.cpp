#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

struct TreeNode {
    int val;
    vector<TreeNode*> children;

    // Constructor to initialize val
    TreeNode(int v) : val(v) {}
};

// Sequential DFS
void sequentialDFS(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> s;
    s.push(root);

    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        cout << node->val << " ";

        // Push children in reverse order to mimic depth-first traversal
        for (int i = node->children.size() - 1; i >= 0; --i) {
            s.push(node->children[i]);
        }
    }
}

// Parallel DFS
void parallelDFS(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> s;
    s.push(root);

    #pragma omp parallel
    {
        while (!s.empty()) {
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                s.pop();
            }

            cout << node->val << " ";

            // Push children in reverse order to mimic depth-first traversal
            for (int i = node->children.size() - 1; i >= 0; --i) {
                #pragma omp critical
                {
                    s.push(node->children[i]);
                }
            }
        }
    }
}

int main() {
    int numNodes;
    cout << "Enter the number of nodes in the tree: ";
    cin >> numNodes;

    vector<TreeNode*> nodes(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        int val;
        cout << "Enter the value of node " << i + 1 << ": ";
        cin >> val;
        nodes[i] = new TreeNode(val);
    }

    cout << "Enter the child nodes for each node (space-separated, 0-based indexing)." << endl;
    cout << "Enter -1 for no child." << endl;
    for (int i = 0; i < numNodes; ++i) {
        int numChildren;
        cout << "Enter the number of children for node " << i + 1 << ": ";
        cin >> numChildren;

        cout << "Enter the children for node " << i + 1 << ": ";
        for (int j = 0; j < numChildren; ++j) {
            int childIdx;
            cin >> childIdx;
            if (childIdx >= 0 && childIdx < numNodes) {
                nodes[i]->children.push_back(nodes[childIdx]);
            } else {
                cout << "Invalid child index. Please enter a valid index." << endl;
                j--; // Decrement j to re-enter the child index
            }
        }
    }

    TreeNode* root = nodes[0];

    cout << "Sequential DFS: ";
    double start = omp_get_wtime();
    sequentialDFS(root);
    double end = omp_get_wtime();
    cout << "\nTime taken: " << end - start << " seconds" << endl;

    cout << "\nParallel DFS: ";
    start = omp_get_wtime();
    parallelDFS(root);
    end = omp_get_wtime();
    cout << "\nTime taken: " << end - start << " seconds" << endl;

    return 0;
}
