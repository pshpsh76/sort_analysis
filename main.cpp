#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

class Heap{
public:
    vector<int> array;
    int size = 0;
    Heap() {
        return;
    }
    int sift_down(int i) {
        --i;
        while (2 * i + 1 < array.size()) {
            int left = 2 * i + 1;
            int right = left + 1;
            int j = left;
            if (right < array.size() && array[right] > array[left]) {
                j = right;
            }
            if (array[i] >= array[j]) {
                break;
            }
            swap(array[i], array[j]);
            i = j;
        }
        return i;
    }
    explicit Heap(vector<int>& inp) {
        array = inp;
        size = inp.size();
        for (int i = size / 2; i > -1; --i) {
            sift_down(i);
        }
    }
    int extract_max() {
        int ans = array[0];
        array[0] = array[size - 1];
        array.pop_back();
        --size;
        if (size == 0) {
            return ans;
        }
        sift_down(1);
        return ans;
    }
};

int randint(int l, int r) {
    return rand() % (r - l + 1) + l;
}

vector<int> gen_random_array(int n) {
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = rand();
    }
    return res;
}

vector<int> gen_sorted_array(int n) {
    vector<int> res = gen_random_array(n);
    sort(res.begin(), res.end());
    return res;
}

vector<int> gen_reversed(int n) {
    vector<int> res = gen_sorted_array(n);
    reverse(res.begin(), res.end());
    return res;
}

vector<int> gen_almost_sorted(int n) {
    vector<int> res = gen_sorted_array(n);
    for (int i = 0; i < n / 10; ++i) {
        int ind = randint(0, n - 2);
        res[ind] = res[ind + 1] + rand();
    }
    return res;
}

void bubble_sort(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; ++i) {
        for (int j = 0; j < a.size() - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void better_bubble_sort(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; ++i) {
        bool flag = false;
        for (int j = 0; j < a.size() - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                flag = true;
                swap(a[j], a[j + 1]);
            }
        }
        if (!flag) {
            return;
        }
    }
}

void selection_sort(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; ++i) {
        int m = i;
        for (int j = i + 1; j < a.size(); ++j) {
            if (a[j] < a[m]) {
                m = j;
            }
        }
        swap(a[m], a[i]);
    }
}

void insertion_sort(vector<int>& a) {
    for (int i = 1; i < a.size(); ++i) {
        int j = i - 1;
        while (j >= 0 && a[j] > a[j + 1]) {
            swap(a[j], a[j + 1]);
            --j;
        }
    }
}

void stupid_quick_sort(vector<int>& a, int l, int r) {
    if (l < r) {
        int x = a[(l + r) / 2];
        int i = l;
        int j = r;
        while (i <= j) {
            while (a[i] < x) {
                ++i;
            }
            while (a[j] > x) {
                --j;
            }
            if (i >= j) {
                break;
            }
            swap(a[i++], a[j--]);
        }
        stupid_quick_sort(a, l, j);
        stupid_quick_sort(a, j + 1, r);
    } else {
        return;
    }
}

void stupid_quick_sort(vector<int>& a) {
    int n = a.size();
    stupid_quick_sort(a, 0, n - 1);
}

void merge(vector<int>& a, int l, int m, int r) {
    vector<int> res(r - l);
    int i = 0, j = 0;
    while (i + l < m && j + m < r) {
        if (a[i + l] < a[j + m]) {
            res[i + j] = a[l + i];
            ++i;
        } else {
            res[i + j] = a[m + j];
            ++j;
        }
    }
    while (i + l < m) {
        res[i + j] = a[i + l];
        ++i;
    }
    while (m + j < r) {
        res[i + j] = a[j + m];
        ++j;
    }
    for (int z = 0; z < i + j; ++z) {
        a[z + l] = res[z];
    }
}

void merge_sort(vector<int>& a, int l, int r) {
    if (r - l <= 1) {
        return;
    }
    int m = (r + l) / 2;
    merge_sort(a, l, m);
    merge_sort(a, m, r);
    merge(a, l, m, r);
}

void merge_sort(vector<int>& a) {
    merge_sort(a, 0, (int)a.size());
}

void heap_sort(vector<int>& a) {
    Heap h(a);
    int i = 1;
    while (h.size > 1) {
        a[a.size() - i] = h.extract_max();
        ++i;
    }
    a[0] = h.array[0];
}

void quick_sort(vector<int>& a, int l, int r) {
    if (l >= r) {
        return;
    }
    if (r - l <= 16) {
        for (int i = l + 1; i < r; ++i) {
            int j = i - 1;
            while (j >= 0 && a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                --j;
            }
        }
    } else {
        vector<int> b = {a[l], a[(r + l) / 2], a[r]};
        sort(b.begin(), b.end());
        int x = b[1];
        int i = l;
        int j = r;
        while (i <= j) {
            while (a[i] < x) {
                ++i;
            }
            while (a[j] > x) {
                --j;
            }
            if (i >= j) {
                break;
            }
            swap(a[i++], a[j--]);
        }
        quick_sort(a, l, j);
        quick_sort(a, j + 1, r);
    }
}

void quick_sort(vector<int>& a) {
    quick_sort(a, 0, (int)a.size() - 1);
}

double test(void (*sort_function)(vector<int>&), vector<int>& a) {
    double start = clock();
    sort_function(a);
    return (clock() - start) / (double)CLOCKS_PER_SEC;
}

void test_slow_algo(vector<int>& b) {
    vector<int> a = b;
    cout << "Bubble sort: " << test(bubble_sort, a) << endl;
    a = b;
    cout << "Bubble sort(lvl up): " << test(better_bubble_sort, a) << endl;
    a = b;
    cout << "Selection sort: " << test(selection_sort, a) << endl;
    a = b;
    cout << "Insertion sort: " << test(insertion_sort, a) << endl;
}

void test_fast_algo(vector<int>& b) {
    double start = 0, sort_time = 0;
    vector<int> a = b;
    cout << "Quick sort with selection of the middle element "
            "of the array as a pivot: " << test(stupid_quick_sort, a) << endl;
    a = b;
    cout << "Merge sort: " << test(merge_sort, a) << endl;
    a = b;
    cout << "Heap sort: " << test(heap_sort, a) << endl;
    a = b;
    cout << "Default ""sort"" from STL: ";
    start = clock();
    sort(a.begin(), a.end());
    sort_time = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << sort_time << endl;
    a = b;
    cout << "stable sort from STL: ";
    start = clock();
    stable_sort(a.begin(), a.end());
    sort_time = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << sort_time << endl;
    cout << "Improved quick sort: " << test(quick_sort, a) << endl;
}

int main() {
    srand(time(nullptr));
    cout << "Slow sort test" << endl;
    int n = 1;
    //cin >> n;
    vector<int> b = gen_random_array(n);
    cout << "On random array:" << endl;
    test_slow_algo(b);
    cout << endl;
    b = gen_sorted_array(n);
    cout << "On sorted array:" << endl;
    test_slow_algo(b);
    cout << endl;
    b = gen_reversed(n);
    cout << "On sorted reverse array:" << endl;
    test_slow_algo(b);
    b = gen_almost_sorted(n);
    cout << "On almost sorted array:" << endl;
    test_slow_algo(b);
    cout << endl << endl << endl;
    cout << "Fast sort test" << endl;
    //cin >> n;
    n = 1e6;
    b = gen_random_array(n);
    cout << "On random array:" << endl;
    test_fast_algo(b);
    cout << endl;
    b = gen_sorted_array(n);
    cout << "On sorted array:" << endl;
    test_fast_algo(b);
    cout << endl;
    b = gen_reversed(n);
    cout << "On sorted reverse array:" << endl;
    test_fast_algo(b);
    cout << endl;
    b = gen_almost_sorted(n);
    cout << "On almost sorted array:" << endl;
    test_fast_algo(b);
}
