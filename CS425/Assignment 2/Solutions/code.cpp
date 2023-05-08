#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// This is a stub function to flip bits
char bitFlip(char x)
{
    if (x == '0')
    {
        return '1';
    }
    return '0';
}

// Generates a random bit message
string genMsg(int k)
{
    string msg = "";
    for (int i = 0; i < k; i++)
    {
        if (rand() % 2 == 0)
        {
            msg += '0';
        }
        else
            msg += '1';
    }
    return msg;
}

// This function computes XOR operator
string xorStrings(string a, string b)
{
    string c = "";
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == b[i])
        {
            c += '0';
        }
        else
        {
            c += '1';
        }
    }
    return c;
}

// This function is used to calculate division
string division(string a, string b)
{
    int p = b.length();
    int m = a.length();

    string rem = a.substr(0, p - 1);
    for (int i = 0; i < m - p + 1; i++)
    {
        rem += a[i + p - 1];
        if (rem[0] == '1')
        {
            rem = xorStrings(rem, b);
            rem = rem.substr(1);
        }
        else
        {
            rem = rem.substr(1);
        }
    }

    return rem;
}

// This function is used to calculate CRC frame
string calculatecrc(string msg, string P)
{
    string dividend = msg + string(P.length() - 1, '0');
    return msg + division(dividend, P);
}

// This function is used to insert error in the frame
pair<string, string> errorInsert(string frame)
{
    string err = "";
    string rec = "";
    for (int i = 0; i < frame.length(); i++)
    {
        if (rand() % 16 == 0)
        {
            rec += bitFlip(frame[i]);
            err += '1';
        }
        else
        {
            rec += frame[i];
            err += '0';
        }
    }

    return make_pair(rec, err);
}

// This function is used to verify CRC
string verifycrc(string rec, string P)
{
    string remExp = string(P.length() - 1, '0');

    if (remExp == division(rec, P))
    {
        return "Accept";
    }
    return "Reject";
}

int main()
{
    srand(time(NULL));
    string P;
    int k = 10;
    cout << "Input the value of pattern P : ";
    cin >> P;
    cout << "Input the value of k : ";
    cin >> k;
    string msg = genMsg(k);
    string frame = calculatecrc(msg, P);
    pair<string, string> res = errorInsert(frame);
    string rec = res.first;
    string err = res.second;
    string stat = verifycrc(rec, P);

    cout << "Input message: " << msg << endl;
    cout << "Sent CRC Frame: " << frame << endl;
    cout << "Error Pattern: " << err << endl;
    cout << "Received CRC Frame: " << rec << endl;
    cout << "Received Frame Status: " << stat << endl;

    return 0;
}
