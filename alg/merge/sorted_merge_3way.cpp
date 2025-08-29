#include <climits>
#include <algorithm>
#include <vector>

bool sorted_merge_3way(
    const int *list_a, int na,
    const int *list_b, int nb,
    const int *list_c, int nc,
    int *list_abc)
{
    int k{0}, l{0}, y{0};

    for (int j=0; j < na+nb+nc; ++j) {
        int a{list_a[k]}, b{list_b[l]}, c{list_c[y]};

        if (k >= na) a = INT_MAX;
        if (l >= nb) b = INT_MAX;
        if (y >= nc) c = INT_MAX;

        const int to_add(std::min({a, b, c}));

        if (to_add == a) ++k;
        if (to_add == b) ++l;
        if (to_add == c) ++y;

        list_abc[j] = to_add;
    }

    // Declaração corrigida para a variável 'atual'
    int prev = INT_MIN;
    int atual;

    for (int j=0; j < na+nb+nc; ++j) {
        atual = list_abc[j];
        if (atual < prev) {
            return false;
        }
        prev = atual;
    }

    return true;
}
