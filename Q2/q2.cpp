#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct node{
    int id, degree;
    bool lit;
    vector<node*> neighbours;
    node()
    {
        id = 0;
        degree = 0;
        lit = false;
    }
    node(int _id, int d, vector<node*> n)
    {
        id = _id;
        degree = d;
        neighbours = n;
        lit = false;
    }
};

void parseline(string line, vector<node> &graph)
{
    if(line == "")
        return;
   stringstream ss(line);
   int n, nbr;
   string discard;
   vector <node*> neighbours;
   ss >> n >> discard;

   while(1)
   {
       ss >> nbr;
       if(!ss)
           break;

       neighbours.push_back(&graph[nbr]);
   }

   graph[n] = node(n, neighbours.size(), neighbours);

}

void buildgraph(string file, vector<node> &g)
{
    ifstream f(file.c_str());
    int n;
    string discard;
    
    f >> discard >> n;
    g.resize(n);

    while(!f.eof())
    {
        getline(f, discard);
        parseline(discard, g);
    }
}
int lightup(node *g, node *parent, string &ans)
{
    if(g->degree == 1 && g->neighbours[0] == parent)
        return 0;

    int subans = 0;
    for(node* n : g->neighbours)
        if(n != parent)
            subans += lightup(n, g, ans);

    bool light = false;
    for(node *n : g->neighbours)
        if(n != parent)
            if(!n->lit)
                light = true;

    if(light)
    {
        g->lit = true;
        ans = to_string(g->id) + "," + ans;
        subans++;
    }

    return subans;
}


int main(int argc, char** argv)
{
    vector<node> graph;
    buildgraph(argv[1], graph);
    string ans;
    int c = lightup(&graph[0], NULL, ans);
    ans[ans.length()-1] = '}';
    cout << "Minimum Lights " << c << endl << "{" << ans << endl;
	return 0;
}
