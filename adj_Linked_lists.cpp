#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;
class Node {
    public:
    int tag;
    Node* next = nullptr;
    Node(int tag) {
        this->tag = tag;
    }
};
class List {
    public:
    Node* head = nullptr;
    int label = 0;
    void set_label(int label) {this->label = label;}
    void add_node(int data);
    string print();
};
void List::add_node(int data) {
    Node* curr_node = head;
    Node* new_node = new Node(data);
    if (curr_node == nullptr) {
        head = new_node;
    } else {
        while (curr_node != nullptr) {
            if (curr_node->next == 0) {
                curr_node->next = new_node;
                break;
            }
            curr_node = curr_node->next;
        }
    }
}
string List::print(){
    Node* curr = head;
    string list = "";
    while (curr != nullptr) {
        // cout << curr->tag << ' ';
        list += to_string(curr->tag);
        if (curr->next != nullptr) {
            list += " ";
        }
        curr = curr->next;
    }
    return list;
}
vector<List> into_link_list(vector<vector<int>>& adj_list) {
    vector<List> linked_lists(0);
    for (int i = 0; i < adj_list.size(); ++i) {
        if (!(adj_list[i].empty())) {
            List curr_list;
            curr_list.set_label(i + 1);
            for (int j = 0; j < adj_list[i].size(); ++j) {
                curr_list.add_node(adj_list[i][j]);
            }
            linked_lists.push_back(curr_list);
        } 
    }
    return linked_lists;
}
void write_to_file(vector<List>& linked_lists, const string& dst_path) {
    ofstream fstr(dst_path);
    for (int i = 0; i < linked_lists.size(); ++i) {
        fstr << linked_lists[i].label << ": " <<linked_lists[i].print() << "\n";
    }
    fstr.close();
}
void run(const string& src_path, const string& dst_path) {
    static bool dumb_file = (src_path == "roadNet-CA.txt");
    vector<vector<int>> adjacency(0);
    fstream file;
    string line;
    stringstream ss;
    vector<vector<int>> adj_list;
    int nodes = 0, edges = 0, max_degree = 0, pos = 0, max_node = 0;
    file.open(src_path);
    
    if (file.is_open() != true) {
        cout << "File error";
    } else {
        while (getline(file, line)) {
            ss << line;
            adjacency.resize(adjacency.size()+1);
            while (ss.tellg() != EOF) {
                int temp;
                ss >> temp;
                adjacency.at(pos).push_back(temp);
            }
            ss.clear();
            pos += 1;
        }
    }
    for (int i = 0; i < adjacency.size(); ++i) {
        for (int j = 0; j < adjacency[i].size(); ++j) {
            if (adjacency[i][j] > max_node) {
                max_node = adjacency[i][j];
            }
        }
    }
    adj_list.resize(max_node);
    if (!dumb_file) {
    for (int i = 0; i < adjacency.size(); ++i) {
        int j = adjacency[i][0];
        int o = adjacency[i][1];
        adj_list.at(j - 1).push_back(o);
        adj_list.at(o - 1).push_back(j);
    }
    } else {
    adj_list.resize(max_node + 1);
    for (int i = 0; i < adjacency.size(); ++i) {
        int j = adjacency[i][0];
        int o = adjacency[i][1];
        adj_list.at(j).push_back(o);
        adj_list.at(o).push_back(j);
    }        
    }
    for (int i = 0; i < adj_list.size(); ++i) {
        sort(adj_list[i].begin(), adj_list[i].end());
        bool duplicate = adjacent_find(adj_list[i].begin(), adj_list[i].end()) != adj_list[i].end();
        while (duplicate) {
            auto dupe_iter = adjacent_find(adj_list[i].begin(), adj_list[i].end());
            adj_list[i].erase(dupe_iter);
            duplicate = adjacent_find(adj_list[i].begin(), adj_list[i].end()) != adj_list[i].end();
        }
        if (!adj_list[i].empty()) {
            nodes += 1;
        }
        edges += adj_list[i].size();
        if (adj_list[i].size() > max_degree) {
            max_degree = adj_list[i].size();
        }
    }
    edges /= 2;
    cout <<"Number of nodes: "<<nodes<<endl<<"Number of edges: "<<edges<<endl<<"Maximum degree: "<<max_degree<<endl;
    vector<List> L_Lists = into_link_list(adj_list);
    write_to_file(L_Lists, dst_path);
}






int main() {
    run("toy.txt", "file.txt");
}