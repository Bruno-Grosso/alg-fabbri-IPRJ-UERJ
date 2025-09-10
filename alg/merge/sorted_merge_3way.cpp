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
    int prev = INT_MIN;

    for (int j=0; j < na+nb+nc; ++j) {
        int a = (k < na) ? list_a[k] : INT_MAX;
        int b = (l < nb) ? list_b[l] : INT_MAX;
        int c = (y < nc) ? list_c[y] : INT_MAX;

        const int to_add(std::min({a, b, c}));

        // Verifica se a ordenação foi quebrada
        if (to_add < prev) {
            return false;
        }

        list_abc[j] = to_add;
        prev = to_add;

        if (to_add == a) ++k;
        if (to_add == b) ++l;       
	if (to_add == c) ++y;
    }

    return true;
}
