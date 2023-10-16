#include <bits/stdc++.h>
using namespace std;

class Treenode
{
public:
    double ans;
    string val, curExp;
    Treenode *left;
    Treenode *right;

    Treenode(double v)
    {
        ans = v;
        std::stringstream ss;
        ss << v;
        std::string str = ss.str();

        size_t decimalPos = str.find('.');
        if (decimalPos != std::string::npos)
        {
            for (int i = str.length() - 1; i >= decimalPos; --i)
            {
                if (str[i] == '0')
                {
                    str.pop_back();
                }
                else
                {
                    break;
                }
            }

            if (str.back() == '.')
            {
                str.pop_back();
            }
        }
        curExp = val = str;
        left = right = nullptr;
    }

    Treenode(string val, double ans, Treenode *left, Treenode *right)
    {
        this->val = val;
        this->ans = ans;
        this->left = left;
        this->right = right;
        if (left && right == nullptr)
        {
            if (val == "-")
            {
                curExp += " -1 *";
            }
            curExp = left->curExp;
            curExp += " ";
        }
        else
        {
            curExp += left->curExp;
            curExp += " ";
            curExp += val;
            curExp += right->curExp;
            curExp += " ";
        }
    }

    void printTree()
    {
        ofstream out("AST.dot");
        out << "digraph G {" << endl;

        out << "\tnode [shape=\"circle\"];" << endl;
        queue<pair<int, Treenode *>> bfs;

        int count = 0;
        bfs.push({count++, this});

        while (!bfs.empty())
        {
            pair<int, Treenode *> curr = bfs.front();
            bfs.pop();

            out << "\t" << curr.first << " [ label=\"" << curr.second->val << "\" ];" << endl;

            if (curr.second->left)
            {
                out << "\t" << curr.first << " -> " << count << "; " << endl;
                bfs.push({count++, curr.second->left});
            }

            if (curr.second->right)
            {
                out << "\t" << curr.first << " -> " << count << "; " << endl;
                bfs.push({count++, curr.second->right});
            }
        }

        out << "}";
        out.close();
        system("dot -Tpng AST.dot -o AST.png");
        system("feh -F AST.png");
    }

    void printDAG()
    {
        unordered_map<string, pair<int, Treenode *>> nodes;
        queue<pair<int, Treenode *>> bfs;
        int count = 0;
        bfs.push({count++, this});

        while (!bfs.empty())
        {
            pair<int, Treenode *> curr = bfs.front();
            bfs.pop();

            string p = curr.second->curExp;
            nodes[p] = curr;

            if (curr.second->left)
                bfs.push({count++, curr.second->left});

            if (curr.second->right)
                bfs.push({count++, curr.second->right});
        }

        ofstream out("DAG.dot");

        out << "digraph G {" << endl;
        out << "\tnode [shape=\"circle\"];" << endl;

        unordered_set<Treenode *> vis;
        vis.insert(nodes[curExp].second);

        bfs.push(nodes[curExp]);

        while (!bfs.empty())
        {
            pair<int, Treenode *> curr = bfs.front();
            bfs.pop();
            out << "\t" << curr.first << " [ label=\"" << curr.second->val << "\" ];" << endl;

            if (curr.second->left)
            {
                pair<int, Treenode *> next = nodes[curr.second->left->curExp];
                out << "\t" << curr.first << " -> " << next.first << "; " << endl;
                if (vis.find(next.second) == vis.end())
                {
                    vis.insert(next.second);
                    bfs.push(next);
                }
            }

            if (curr.second->right)
            {
                pair<int, Treenode *> next = nodes[curr.second->right->curExp];
                out << "\t" << curr.first << " -> " << next.first << "; " << endl;
                if (vis.find(next.second) == vis.end())
                {
                    vis.insert(next.second);
                    bfs.push(next);
                }
            }
        }

        out << "}" << endl;
        out.close();

        system("dot -Tpng DAG.dot -o DAG.png");
        system("feh -F DAG.png");
    }
};