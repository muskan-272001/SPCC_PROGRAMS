#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int r = 0, sr = 0;
string s;
void reform(int ind)
{
    if (isdigit(s[ind - 1]) && s[ind + 1] == 't')
    {
        string a = s.substr(0, ind - 2);
        for (int i = 0; i < ind - 2; i++)
        {
            a += s[i];
        }
        r++;
        string b = 't' + to_string(r);
        string c = s.substr(ind + 3, s.size() - 1);
        s = a + b + c;
    }
    else if (isdigit(s[ind - 1]))
    {
        string a = s.substr(0, ind - 2);
        r++;
        string b = 't' + to_string(r);
        string c = s.substr(ind + 2, s.size() - 1);
        s = a + b + c;
    }
    else if (s[ind + 1] == 't')
    {
        string a = s.substr(0, ind - 1);
        r++;
        string b = 't' + to_string(r);
        string c = s.substr(ind + 3, s.size() - 1);
        s = a + b + c;
    }
    else
    {
        string a = s.substr(0, ind - 1);
        r++;
        string b = 't' + to_string(r);
        string c = s.substr(ind + 2, s.size() - 1);
        s = a + b + c;
    }
}
int main()
{
    ofstream coutf;
    coutf.open("output.txt");
    cout << "\nEnter the expresesion : ";
    cin >> s;
    int n = 0;
    for (auto x : s)
        if (x == '/' || x == '*' || x == '+' || x == '-' || x == '~' || x == '=')
            n++;
    string table[n][4];
    int ir = 0, ic = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '/')
        {
            if (isdigit(s[i - 1]) && s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (isdigit(s[i - 1]))
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
        }
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '*')
        {
            if (isdigit(s[i - 1]) && s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (isdigit(s[i - 1]))
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
        }
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '+')
        {
            if (isdigit(s[i - 1]) && s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (isdigit(s[i - 1]))
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
        }
    }
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '-')
        {
            if (isdigit(s[i - 1]) && s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (isdigit(s[i - 1]))
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = 't' + to_string(s[i - 1] - '0');
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else if (s[i + 1] == 't')
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = 't' + to_string(s[i + 2] - '0');
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
            else
            {
                table[ir][ic] = s[i];
                table[ir][++ic] = s[i - 1];
                table[ir][++ic] = s[i + 1];
                table[ir][++ic] = 't' + to_string(++sr);
                ic = 0;
                ir++;
                reform(i);
                i = 1;
            }
        }
    }
    table[ir][ic] = s[1];
    table[ir][++ic] = 't' + to_string(s[3] - '0');
    table[ir][++ic] = '_';
    table[ir][++ic] = s[0];
    ir++;
    ic = 0;
    coutf << "Operator"
          << "\t"
          << "Argument1"
          << "\t"
          << "Argument2"
          << "\t"
          << " Result"
          << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            coutf << "\t" << table[i][j] << "\t"
                  << "\t";
        }
        coutf << "\n";
    }
    coutf.close();
    return 0;
}