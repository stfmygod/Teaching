#include <fstream>

using namespace std;

ifstream fin("robotzi.in");
ofstream fout("robotzi.out");

// Date de intrare
int n, p, matrice[1001][1001], verifica[1001][1001];

// Date de iesire
int aur;

//// Misc
//int i, j;

// Vectori directori (cazul <= p)
int di1[2] = { 1, 0 };
int dj1[2] = { 0, 1 };


// Vectori directori (cazul > p)
int di2[2] = { -1, 0 };
int dj2[2] = { 0, 1 };


// Vectori directori pentru mers invers
// Cazul <= p
int dx1[2] = { 0, -1 };
int dy1[2] = { -1, 0 };
// Cazul > p
int dx2[2] = { 1, 0 };
int dy2[2] = { 0, -1 };


// Aceeasi functie de OK, cu o mica modificare (Verifica daca pozitia nu este un X)
bool ok(int i, int j)
{
    if (i < 1 || j < 1 || i > n || j > n)
        return false;

    if (verifica[i][j] != 0)
        return false;

    if (matrice[i][j] == (int)'x')
        return false;
    return true;
}


// Functia de ok, dar pentru cazul de reverse
bool ok2(int i, int j)
{
    if (i < 1 || j < 1 || i > n || j > n)
        return false;
    if (verifica[i][j] != 1) // Pozitia este valida doar daca a fost accesata de primul fill
        return false;
    if (matrice[i][j] == (int)'x')
        return false;
    return true;
}

// Fill normal, cu vectorii de pozitie, in functie de p
void algFill(int x, int y)
{
    verifica[x][y]++;
    int newI, newJ;

    for (int i = 0; i < 2; i++)
    {
        if (y <= p) // Coloana <= p (1..p)
        {
            newI = x + di1[i];
            newJ = y + dj1[i];
        }
        else // Coloana > p (p+1..n)
        {
            newI = x + di2[i];
            newJ = y + dj2[i];
        }

        if (ok(newI, newJ))
            algFill(newI, newJ);
    }
}

// Fill pentru cazul de reverse, la fel ca functia algFill, dar foloseste ok2 si vectorii de directie pentru cazul de reverse
void algFill2(int x, int y)
{
    verifica[x][y]++;
    int newI, newJ;

    for (int i = 0; i < 2; i++)
    {
        if (y <= p)
        {
            newI = x + dx1[i];
            newJ = y + dy1[i];
        }   
        else
        {   
            newI = x + dx2[i];
            newJ = y + dy2[i];
        }

        if (ok2(newI, newJ))
            algFill2(newI, newJ);
    }
}



int main()
{
    // Citire
    fin >> n >> p;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            char c;
            fin >> c;
            matrice[i][j] = (int)c;
        }


    // Problema se simplifica semnificativ daca o luam matematic.
    // Intai trebuie sa vedem unde pot ajunge robotii care pleaca din (1, 1), asa ca aplicam functia fill din acest punct
    // Dupa trebuie sa vedem unde au ajuns robotii care ajung in (1, n). Pentru asta folosim functia fill, dar cu vectori de directie opusi (sus devine jos, dreapta devine stanga etc)
    // Ca sa vedem pe unde ajung robotii care pleaca din (1, 1) si ajung in (1, n) trebuie sa facem intersectia multimilor de mai devreme. 
    // Pentru a simplifica lucrurile, in functia de ok2 consideram o pozitie valida doar daca a fost validata deja de primul fill (de asta folosim 1 in loc de 0 la verifica[i][j] != 1)
    // Astfel, pozitiile comune celor 2 filluri vor avea valoarea 2

    algFill(1, 1);
    algFill2(1, n);



    // Rezolvarea problemei
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (verifica[i][j] == 2 && matrice[i][j] == (int) '$') // Daca o pozitie este comuna celor doua filluri si are aur
                aur++;
        }
    }

    fout << aur;
    return 0;
}
