#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

bool mergeable(string a, string b, string c, string &ans)
{
    string subans = "";
    if(a == "")
    {
        ans = "2:" + b;
        return b == c;
    }
    if(b == "")
    {
        ans = "1:" + a;
        return a == c;
    }
    string a0 = "1:" + a.substr(0,1);
    string b0 = "2:" + b.substr(0,1);

    if(a[0] == c[0] && b[0] != c[0])
    {
        bool rv = mergeable(a.substr(1), b, c.substr(1), subans);
        if(subans[0] == '1')
            ans = a0+subans.substr(2);
        else
            ans = a0 + "\n"+subans;
        return rv;
    }
    if(b[0] == c[0] && a[0] != c[0])
    {
        bool rv = mergeable(a, b.substr(1), c.substr(1), subans);
        if(subans[0] == '2')
            ans = b0 + subans.substr(2);
        else
            ans = b0 + "\n" + subans;
        return rv;
    }
    if(a[0] == c[0] && b[0] == c[0])
    {
        string s2 = "";
        bool l = mergeable(a.substr(1), b, c.substr(1), subans);
        bool r = mergeable(a, b.substr(1), c.substr(1), s2);
        if(!(l||r))
            return false;

        if(l && subans[0] == '1')
            ans = a0+subans.substr(2);
        else if(l)
            ans = a0 + "\n"+subans;
        else if(r && s2[0] == '2')
            ans = b0 + s2.substr(2);
        else
            ans = b0 + "\n" + s2;

        return true;
    }
    
    return false;
}


int main(int argc, char** argv)
{
    string a, b, c, ans = "";
    ifstream f(argv[1]);
    f >> a >> b >> c;
    cout << (mergeable(a, b, c, ans)? "VALID\n"+ans:"INVALID") << endl;
	return 0;
}
