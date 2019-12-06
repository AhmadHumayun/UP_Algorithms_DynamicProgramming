#include <iostream> 
#include <fstream>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std; 
  
void remove(vector<int> &cuts, int c, vector<int> &l, vector<int> &r)
{
    vector<int>::iterator i = find(cuts.begin(), cuts.end(), c);
    l.assign(cuts.begin(), i);
    r.assign(i+1, cuts.end());
}

int C(int l, int h, vector<int> cuts, string &ans)
{
    if(cuts.size() == 0)
        return 0;

    int cost = h-l+1;
    if(cuts.size() == 1)
    {
        ans = to_string(cuts[0]);
        return cost;
    }

    vector<int> costs;
    vector<string> answers;
    for(int c : cuts)
    {
        string al = "", ar = "";
        vector<int> cutsl, cutsr;
        remove(cuts, c, cutsl, cutsr);
        costs.push_back(cost + C(l, c, cutsl, al) + C(c+1, h, cutsr, ar));
        answers.push_back(al + " " + ar);
    }

    vector<int>::iterator iter = min_element(costs.begin(), costs.end());
    int i = distance(costs.begin(), iter);
    ans = to_string(cuts[i]) + " " + answers[i];
    return *iter;
}

int parsefile(string file, vector<int> &cuts)
{
    int n;
    ifstream f(file.c_str());
    string discard;
    f >> discard >> n >> discard;

    while(1)
    {
        int temp;
        f >> temp;
        if(!f)
            break;
        cuts.push_back(temp);
    }

    return n;
}

int main(int argc, char** argv) 
{ 
    vector<int> cuts;
    int n = parsefile(argv[1], cuts);
    string ans = "";
    int leastcost =  C(1, n, cuts, ans);
    cout << "Optimal cut ordering: "  << ans << endl << "Least cost: " << leastcost << endl;
    return 0; 
} 
