
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

int n, i, j, pi, pj, m;
int arr[200][200];
int sol[200][200];
bitset<4> bin;

struct celula
{
    int N; int E; int S; int V;
};

celula labirint[250][250];

void dectobin(int x)
{
    bin = 0; bin = x;
}

int solutie(int pozi, int pozj, int nr_pasi)
{
    if (pozi == 0 || pozj == 0 || pozi == n + 1 || pozj == m + 1)
        return 1;
    else 
        return 0;
}

void tipar(int nr_pasi)
{
    for (i = 0; i <= nr_pasi - 1; i++)
    {
        cout << "{" << sol[i][1] << " " << sol[i][2] << "} ";
    }
    cout << "AI IESIT IN " << nr_pasi - 1 << " PASI"; // NUMARA SI PRIMA CELULA SI ULTIMA CARE II IN AFARA ARR
    cout << endl;
}

void init(int nr_pasi)
{
    sol[nr_pasi][1] = sol[nr_pasi - 1][1];
    sol[nr_pasi][2] = sol[nr_pasi - 1][2];
}

int succesor(int pozi, int pozj, int nr_pasi)
{

    if (labirint[pozi][pozj].N == 1)
    {
        return 1;
    }
    if (labirint[pozi][pozj].E == 1)
    {
        return 2;
    }
    if (labirint[pozi][pozj].S == 1)
    {
        return 3;
    }
    if (labirint[pozi][pozj].V == 1)
    {
        return 4;
    }
    return 0;
}


void bk(int pozi, int pozj, int nr_pasi)
{
    if (solutie(pozi, pozj, nr_pasi) == 1)
    {
        tipar(nr_pasi);
    }
    else
    {
        int okn = 0, oke = 0, okv = 0, oks = 0;

        init(nr_pasi);

        int verif = 0;

        while (succesor(pozi, pozj, nr_pasi) == 1)
        {
            okn=1;
            sol[nr_pasi][1]--;
            
            labirint[pozi][pozj].N = 0;
            labirint[pozi - 1][pozj].S = 0;

            verif = labirint[pozi-1][pozj].S;
            bk(pozi - 1, pozj, nr_pasi + 1);
            
            if(verif) labirint[pozi - 1][pozj].S = 1;
            
            sol[nr_pasi][1]++;
        }
        while (succesor(pozi, pozj, nr_pasi) == 2)
        {
            oke=1;
            sol[nr_pasi][2]++;

            labirint[pozi][pozj].E = 0;
           
            verif = labirint[pozi][pozj + 1].V;
            labirint[pozi][pozj + 1].V = 0;
            
            bk(pozi, pozj + 1, nr_pasi + 1);
            if(verif)labirint[pozi][pozj + 1].V = 1;
            
            sol[nr_pasi][2]--;
        }
        while (succesor(pozi, pozj, nr_pasi) == 3)
        {
            oks=1;
            sol[nr_pasi][1]++;
            
            labirint[pozi][pozj].S = 0;
            labirint[pozi + 1][pozj].N = 0;
            
            verif = labirint[pozi+1][pozj].N;
            
            bk(pozi + 1, pozj, nr_pasi + 1);
            if(verif)labirint[pozi + 1][pozj].N = 1;
        
            sol[nr_pasi][1]--;
        }
        while (succesor(pozi, pozj, nr_pasi) == 4)
        {
            okv=1;
            sol[nr_pasi][2]--;
    
            labirint[pozi][pozj].V = 0;
            labirint[pozi][pozj - 1].E = 0;

            verif = labirint[pozi][pozj-1].E;

            bk(pozi, pozj - 1, nr_pasi + 1);
            if(verif) labirint[pozi][pozj - 1].E = 1;
        
            sol[nr_pasi][2]++;
        }
        
        labirint[pozi][pozj].N = okn;
        labirint[pozi][pozj].E = oke;
        labirint[pozi][pozj].S = oks;
        labirint[pozi][pozj].V = okv;
    }
}

int main()
{
    cin >> n;
    cin >> m;                // dimensiunea matricii n linii n coloane
    for (i = 1; i <= n; i++) // elementele matricii
    {
        for (j = 1; j <= m; j++)
        {
            cin >> arr[i][j];
            dectobin(arr[i][j]);
            labirint[i][j].N = bin[3];
            labirint[i][j].E = bin[2];
            labirint[i][j].S = bin[1];
            labirint[i][j].V = bin[0];
        }
    }
    cin >> pi >> pj; 
    sol[0][1] = pi;
    sol[0][2] = pj;
    bk(pi, pj, 1);
}