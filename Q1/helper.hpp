#include <bits/stdc++.h>
using namespace std;

class Treenode
{
public:
    double ans;
    string val;
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
        val = str;
        left = right = nullptr;
    }

    Treenode(string val, double ans, Treenode *left, Treenode *right)
    {
        this->val = val;
        this->ans = ans;
        this->left = left;
        this->right = right;
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
    }
};