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
        calculated = calc;
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

    fstream in{"input.txt"};
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
            (*a)->number = graph[(*a)->arg1].number + graph[(*a)->arg2].number;
            break;
        case '-':
            (*a)->number = graph[(*a)->arg1].number - graph[(*a)->arg2].number;
            break;
        case '*':
            (*a)->number = graph[(*a)->arg1].number * graph[(*a)->arg2].number;
            break;
        case '/':
            (*a)->number = graph[(*a)->arg1].number / graph[(*a)->arg2].number;
            break;
        
        default:
            break;
        }
    }

    cout << graph["root"].number; // 159591692827554
}