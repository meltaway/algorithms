#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;

struct Node 
{ 
    Node * parent = nullptr;
    string key; 
    string value;
    vector<Node *>child; 
}; 

class html_parser
{
    vector<int> path;
    string folder_path;
    vector<string> html_text;
    Node * root;
    Node * select_node;

public:
    explicit html_parser(const string = "");
    ~html_parser(){}
    void read_html();
    void parse_text();
    void split_line(string & line);
    void check_text();

    //tree
    Node * newNode(string & key);
    void printTree(Node * node);
    Node * getRoot();

};

int main()
{
    html_parser dom("/home/bujhmt/acdshka/term2/labs/lab4/data.html");
    //html_parser dom;
    dom.read_html();
    dom.check_text();
    dom.parse_text();
    cout << "Tree" << endl << endl;
    dom.printTree(dom.getRoot());
}


                                //parse line


void html_parser::split_line(string & line) 
{
    string body;
    string tmp;
    size_t first = 0;
    size_t last = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '<')
        {
            first = i + 1;

            //body
            if (last != 0 && last != line.length() - 1)
            {
                body = line.substr(last + 1, first - 2 - last);
                if (body != " " && !body.empty()) 
                {
                    //cout << "-----" << body << endl;
                    select_node->child.push_back(newNode(body));
                }
            }

            //teg
            for (int j = first; j < line.length(); j++)
            {
                if (line[j] == '>' || line[j] == '<')
                {
                    last = j;
                    break;
                }
            }
            tmp = line.substr(first, last - first);

            if (tmp[0] != '/')
            {
                //cout << tmp <<  endl;
                Node * tmpNode = newNode(tmp);
                tmpNode->parent = select_node;
                select_node->child.push_back(tmpNode);
                select_node = tmpNode;
            }
            else
            {
               if (select_node->parent != nullptr) select_node = select_node->parent;
            }
            

            i += last - first;
        }
    }
}


void html_parser::parse_text()
{
    for (int i = 0; i < html_text.size(); i++)
    {
        string line = html_text[i];
        split_line(line);
    }
}


void html_parser::check_text()
{
    int check_counter = 0;
    int check_counter2 = 0;

    for (int j = 0; j < html_text.size(); j++)
    {
        string item = html_text[j];
        for (int i = 0; i < item.size() ; i++)
        {
            //test 1
            // if (item[i] == '<') check_counter++;
            // if (item[i] == '>') check_counter--;

            // //test 2
            // if (item[i] == '<') check_counter2++;
            // if (item[i] == '<' && item[i+1] == '/') check_counter2 -= 2;
        }
    }
    // cout << check_counter << endl;
    // cout << check_counter2 << endl;
    if (check_counter != 0 || check_counter2 != 0)
    {
        system("clear");
        cout << "html text is broken" << endl;
        exit(1);
    }
}

html_parser::html_parser(string path) : folder_path{path}
{
    string teg = "root";
    root = newNode(teg);
    select_node = root;
}

void html_parser::read_html()
{
    if (!folder_path.empty())
    {
        ifstream file_stream(folder_path);
        string line;
        while (getline(file_stream, line))
        {
            html_text.push_back(line);
        }
    }
    else
    {
        system("clear");
        cout << " Enter html text lines. Enter ""end"" to finish" << endl;
        string buf;
        while(buf != "end")
        {
            getline(cin, buf);
            html_text.push_back(buf);
        }
    }
    
}


// tree


Node * html_parser::newNode(string & key) 
{ 
    Node * new_node = new Node; 
    new_node->key = key; 
    return new_node; 
} 

int checkDepth(Node * node)
{
    int count = 0;
    while(node->parent != nullptr)
    {
        count++;
        node = node->parent;
    }
    return count;
}

void html_parser::printTree(Node * node)
{
    for (int i = 0; i < node->child.size(); i++)
    {
        for(int j = 0; j < checkDepth(node); j++)
        {
            cout << "     ";
        }
        cout << node->child[i]->key << endl;
        printTree(node->child[i]);
        
    }

}

Node * html_parser::getRoot()
{
    return root;
}