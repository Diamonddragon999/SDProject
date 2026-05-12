#include <vector>
#include <random>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Apeleaza cu : gen_tests <N> <seed> <type> <output_file>\n");
        printf("Tipuri: 0=random, 1=sortat, 2=sortat_invers, 3=few_unique, 4=almost_sorted, 5=all_equal, 6=neg_poz, 7=sawtooth\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int seed = atoi(argv[2]);
    int type = atoi(argv[3]);
    FILE *fout = fopen(argv[4], "w");
    if (!fout) { printf("Nu pot deschide %s\n", argv[4]); return 1; }

    mt19937 rng(seed);
    vector<int> a(n);

    switch (type)
    {
    case 0: // random
        for (int i = 0; i < n; i++)
            a[i] = (int)rng();
        break;

    case 1: // sortat
        for (int i = 0; i < n; i++)
            a[i] = i + 1;
        break;

    case 2: // sortat invers
        for (int i = 0; i < n; i++)
            a[i] = n - i;
        break;

    case 3: // few unique (doar 10 valori distincte)
        for (int i = 0; i < n; i++)
            a[i] = (int)rng() % 10 + 1;
        break;

    case 4: // almost sorted (sortat + 2% swaps)
        for (int i = 0; i < n; i++)
            a[i] = i + 1;
        for (int i = 0; i < n / 50; i++){
            int x = rng() % n;
            int y = rng() % n;
            int t = a[x];
            a[x] = a[y];
            a[y] = t;
        }
        break;

    case 5: // all equal
        for (int i = 0; i < n; i++)
            a[i] = 243;
        break;

    case 6: // negative si pozitive amestecate
        for (int i = 0; i < n / 2; i++)
            a[i] = i + 1;
        for (int i = n / 2; i < n; i++)
            a[i] = -(i + 1);
        for (int i = n - 1; i > 0; i--){
            int j = rng() % (i + 1);
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        break;

    case 7: // sawtooth (1,2,...,n/2, n/2,...,1)
        for (int i = 0; i < n / 2; i++)
            a[i] = i + 1;
        for (int i = n / 2; i < n; i++)
            a[i] = n - i;
        break;

    default:
        printf("Type invalid\n");
        return 1;
    }

    fprintf(fout, "%d\n", n);
    for (int i = 0; i < n; i++)
        fprintf(fout, "%d\n", a[i]);

    fclose(fout);
    return 0;
}
