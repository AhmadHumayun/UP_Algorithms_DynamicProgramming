#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

vector<int> RH;
vector<int> RL;
vector<int> Mem;
vector<string> MemAns;

int R(int n, string &ans)
{
    if(Mem[n] != -1)
    {
        ans = MemAns[n];
        return Mem[n];
    }
    if(n == 0)
    {
        string cap = "";
        Mem[0] = max(RL[0], RH[0]);
        if(Mem[0] == RL[0])
            cap = "Low ";
        else
            cap = "High ";

        ans = "Week " + to_string(n+1) + ": " + cap + to_string(Mem[0]) + "\n";
        MemAns[n] = ans;
        return Mem[0];
    }
    if(n == 1)
    {
        string subans = "";
        int primed = RH[1];
        int low = RL[1] + R(0, subans);
        if(primed > low)
        {
            Mem[n] = primed;
            ans = "Week " + to_string(n) + ": Priming\n";
            ans += "Week " + to_string(n+1) + ": High " + to_string(RH[n])+ "\n";
            MemAns[n] = ans;
            return primed;
        }
        else
        {
            Mem[n] = low;
            ans = subans + "Week " + to_string(n+1) + ": Low " + to_string(RL[n]) +"\n";
            MemAns[n] = ans;
            return low;
        }
    }

    string subansh = "", subansl = "";
    int primed = RH[n] + R(n-2, subansh);
    int low = RL[n] + R(n-1, subansl);
    if(primed > low)
    {
        Mem[n] = primed;
        ans  = subansh + "Week " + to_string(n) + ": Priming\n";
        ans += "Week " + to_string(n+1) + ": High " + to_string(RH[n]) + "\n";
        MemAns[n] = ans;
        return primed;
    }
    else
    {
        Mem[n] = low;
        ans = subansl + "Week " + to_string(n+1) + ": Low " + to_string(RL[n]) + "\n";
        MemAns[n] = ans;
        return low;
    }
}

int readfile(string file)
{

    ifstream f(file.c_str());
    int n;
    string discard, RHs, RLs;
    
    f >> discard >> n;
    getline(f, discard);
    getline(f, RHs);
    getline(f, RLs);
    stringstream rls(RLs);
    stringstream rhs(RHs);
    rls >> discard;
    rhs >> discard;

    while(1)
    {
        int templ, temph;
        rhs >> temph;
        rls >> templ;
        if(!rhs)
            break;
        RH.push_back(temph);
        RL.push_back(templ);
        Mem.push_back(-1);
    }
    MemAns.resize(n);
    return n;
}

int main(int argc, char** argv)
{
    int n = readfile(argv[1]);
    string ans = "";
    int rev = R(n-1, ans);
    cout << ans << "Total Revenue: " + to_string(rev) << endl;
    //R(n) = max(RH[n] + R(n-2), RL[n] + R(n-1))
    //R(0) = 0
    //R(1) = max(RH[1], RL[1] + R(n-1)) 
	return 0;
}
