#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("data.in");

// Functie care verifica daca o pozitie este uscata
bool uscata(int i, int j, int img[][100])
{
    if (img[i][j] == 1)
        return true;
    else
        return false;
}


// Aceeasi functie uscata, dar sub o alta forma
bool uscataV2(int i, int j, int img[][100])
{
    return (img[i][j] == 1)? true:false;
}


// Functie care verifica daca o pozitie este valida sau a fost verificata deja
bool OK(int i, int j, int vazut[][100], int n, int m)
{
    // Verificam daca pozitia este pe matrice
    if (i < 1 || j < 1 || i > n || j > m)
        return false;

    // Verificam daca pozitia a fost vazuta deja
    if (vazut[i][j] != 0)
        return false;

    // Daca am ajuns aici e totul ok ;)
    return true;
}


void algFill(int x, int y, int v[][100], int img[][100], int n, int m, int d[], int nrZona)
{
    v[x][y] = nrZona; // Notam in matricea de verificare faptul ca am trecut prin aceasta zona. OBS: In matricea de vazut, elementele din aceeasi zona vor avea aceeasi valoare
    d[nrZona]++; // Incrementam nr de valori care fac parte din aceasta zona
    int dirI[4] = {-1, 0, 1, 0}; // Vectori cu care ne vom muta in
    int dirJ[4] = {0, 1, 0, -1}; // W, N, E, S fata de pozitia curenta

    for(int i = 0; i < 4; i++)
    {
        int newI = x + dirI[i]; // pentru fiecare i dirI si dirJ vor muta pozitia
        int newJ = y + dirJ[i]; // in una din cele 4 directii cardinale
        if (OK(newI, newJ, v, n, m) && img[x][y] == img[newI][newJ]) // Daca pozitia este ok (vezi functia ok)
                                                            // si noua pozitie este de acelasi tip ca actuala
            algFill(newI, newJ, v, img, n, m, d, nrZona);
    }
}

int main()
{
    int n, m, IMG[100][100],vazut[100][100], i, j, nrZona;
    int d[1000];

    fin >> n >> m;

    // Citirea parametrilor din fisier
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= m; j++)
        {
            int nr;
            fin >> nr;
            IMG[i][j] = nr;
        }
    }

    // Initializarea matricei de verificare si a nrZona
    nrZona = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            vazut[i][j] = 0;
        }
    }
    for (i = 0; i < n * m; i++)
        d[i] = 0;

    // Incepem parcurgerea si rezolvarea problemei
    for (i = 1; i <= n; i++)        // Pentru fiecare element din matrice testam daca
        for (j = 1; j <= m; j++)    // Este uscata sau nu
            if (uscata(i, j, IMG))
            {
                if (vazut[i][j] == 0) // Daca n-am trecut inca prin pozitie aplicam algFill
                {
                    nrZona++;
                    algFill(i, j, vazut, IMG, n, m, d, nrZona);
                }
            }


    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            cout << vazut[i][j] << " ";
        }
        cout << endl;
    }
    cout <<  endl << nrZona << endl;
}
