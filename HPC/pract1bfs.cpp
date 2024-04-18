#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

struct TreeNode {
    int val;
    vector<TreeNode*> children;

    // Constructor to initialize val
    TreeNode(int v) : val(v) {}
};

// Sequential BFS
void sequentialBFS(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";

        for (TreeNode* child : node->children) {
            q.push(child);
        }
    }
}

// Parallel BFS
void parallelBFS(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    #pragma omp parallel
    {
        while (!q.empty()) {
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                q.pop();
            }

            #pragma omp task
            {
                cout << node->val << " ";
                for (TreeNode* child : node->children) {
                    #pragma omp critical
                    {
                        q.push(child);
                    }
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

    cout << "Sequential BFS: ";
    double start = omp_get_wtime();
    sequentialBFS(root);
    double end = omp_get_wtime();
    cout << "\nTime taken: " << end - start << " seconds" << endl;

    cout << "\nParallel BFS: ";
    start = omp_get_wtime();
    parallelBFS(root);
    end = omp_get_wtime();
    cout << "\nTime taken: " << end - start << " seconds" << endl;

    return 0;
}
