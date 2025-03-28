#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

void input(int** matrix, int m, int n)
{
    srand(time(0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

void print(int** matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j];
            if(j != n-1)
                cout << " ";
        }
        cout << endl;
    }
}

int main()
{
    int m = 0, n = 0;
    cout << "Enter number of rows: ";
    cin >> m;
    cout << "Enter number of columns: ";
    cin >> n;
    int** matrix = new int*[m];
    for (int i = 0; i < m; i++)
    {
        matrix[i] = new int[n];
    }

    input(matrix, m, n);
    print(matrix, m, n);
    int even = 0, sum = 0;

    #pragma omp parallel for num_threads(m)
    for (int i = 0; i < m; i++)
    {
        int roweven = 0, rowsum = 0;
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] % 2 == 0)
            {
                roweven++;
            }
            rowsum += matrix[i][j];
        }
        #pragma omp critical
        {
            even += roweven;
            sum += rowsum;
        }
    }

    cout << "Total even numbers: " << even << endl;
    cout << "Total sum of matrix: " << sum << endl;

    for (int i = 0; i < m; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
