#include <iostream>

using namespace std;

int matrice[512][512];

void functie(int i, int j, int n)
{
    if (n > 0)
    {
        int nr = 1;

    matrice[i][j] = n;

    for (int i = 1; i <= n - 2; i++)
        nr *= 2;

    functie(i - nr, j - nr, n-1);
    functie(i - nr, j + nr, n-1);
    functie(i + nr, j - nr, n-1);
    functie(i + nr, j + nr, n-1);
    }

}

int main()
{
    int n, nr = 1;
    cin >> n;

    for (int i = 1; i<= n; i++)
        nr*= 2;


    functie(nr/2,nr/2,n);

    for (int i = 1; i < nr; i++)
    {
        for(int j = 1; j < nr; j++)
            cout << matrice[i][j] << " ";

        cout << endl;
    }

    return 0;
}
