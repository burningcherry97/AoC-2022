#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Monkey {
    long long int number;
    string identifier = "";
    string arg1 = "";
    string arg2 = "";
    char operation;
    bool investigated = false;
    bool calculated = false;

    Monkey(string ident, string arg1, string arg2, int n, char op, bool calc) {
        number = n;
        identifier = ident;
        this->arg1 = arg1;
        this->arg2 = arg2;
        investigated = false;
        if (identifier != "humn") 
            calculated = calc;
        else
            calculated = false;
        operation = op;
    }

    Monkey() {

    }
};

void dfs_visit(map<string,Monkey>& graph, vector<Monkey*>& process_queue, Monkey* node) {
    if (node->investigated)
        return;
    if (node->operation != 0) {
        dfs_visit(graph, process_queue, &graph[node->arg1]);
        dfs_visit(graph, process_queue, &graph[node->arg2]);
    }
    node->investigated = true;
    process_queue.push_back(node);
}

int main(int argc, char** argv) {

    fstream in{"../P1/input.txt"};
    int number; char delim;
    string identifier, arg1, arg2;
    map<string, Monkey> graph;

    while (!in.eof()) {
        in >> identifier; identifier.pop_back();
        in.get();
        int next = in.peek();
        if (next >= '0' && next <= '9') {
            in >> number;
            graph[identifier] = Monkey(identifier, "", "", number, 0, true);
        } else {
            in >> arg1 >> delim >> arg2;
            graph[identifier] = Monkey(identifier, arg1, arg2, 0, delim, false);
        }
    }
    in.close();

    vector<Monkey*> process_queue;
    dfs_visit(graph, process_queue, &graph["root"]);


    for (auto a = process_queue.begin(); a != process_queue.end(); ++a) {
        switch ((*a)->operation)
        {
        case '+': 
        if (graph[(*a)->arg1].calculated && graph[(*a)->arg2].calculated) {
            (*a)->number = graph[(*a)->arg1].number + graph[(*a)->arg2].number;
            (*a)->calculated = true;
        }
            break;
        case '-': 
        if (graph[(*a)->arg1].calculated && graph[(*a)->arg2].calculated) {
            (*a)->number = graph[(*a)->arg1].number - graph[(*a)->arg2].number;
            (*a)->calculated = true;
        }
            break;
        case '*': 
        if (graph[(*a)->arg1].calculated && graph[(*a)->arg2].calculated) {
            (*a)->number = graph[(*a)->arg1].number * graph[(*a)->arg2].number;
            (*a)->calculated = true;
        }
            break;
        case '/': 
        if (graph[(*a)->arg1].calculated && graph[(*a)->arg2].calculated) {
            (*a)->number = graph[(*a)->arg1].number / graph[(*a)->arg2].number;
            (*a)->calculated = true;
        }
            break;
        
        default:
            break;
        }
    }

    Monkey* ptr = &graph["root"];
    Monkey* known, * unknown;
    if (graph[ptr->arg1].calculated) {
        known = &graph[ptr->arg1];
        unknown = &graph[ptr->arg2];
    } else {
        known = &graph[ptr->arg2];
        unknown = &graph[ptr->arg1];
    }
    unknown->number = known->number;
    ptr = unknown;
    while (ptr->identifier != "humn") {
        Monkey* left = &graph[ptr->arg1];
        Monkey* right = &graph[ptr->arg2];
        // cout << ptr->number << ' ' << left->number << ' ' << right->number << endl;
        if (!left->calculated) {
            if (ptr->operation == '+') {
                left->number = ptr->number - right->number;
            }
            if (ptr->operation == '*') {
                left->number = ptr->number / right->number;
            }
            if (ptr->operation == '-') {
                left->number = ptr->number + right->number;
            }
            if (ptr->operation == '/') {
                left->number = ptr->number * right->number;
            }
            ptr = left;
        } else {
            if (ptr->operation == '+') {
                right->number = ptr->number - left->number;
            }
            if (ptr->operation == '*') {
                right->number = ptr->number / left->number;
            }
            if (ptr->operation == '-') {
                right->number = left->number - ptr->number;
            }
            if (ptr->operation == '/') {
                right->number = left->number / ptr->number;
            }
            ptr = right;
        }
    }

    cout << graph["humn"].number; // 3509819803065
}