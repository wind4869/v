#include "hashtable.h"
#include <iostream>

template <typename T>
struct identity {
    const T& operator()(const T& x) const { return x; }
};

int main()
{
    hashtable<int, int, hash<int>, identity<int>, equal_to<int>> ht;

    cout << ht.size() << endl;
    cout << ht.bucket_count() << endl;
    cout << ht.max_bucket_count() << endl;

    ht.insert_unique(59);
    ht.insert_unique(63);
    ht.insert_unique(108);
    ht.insert_unique(2);
    ht.insert_unique(53);
    ht.insert_unique(55);
    cout << ht.size() << endl;

    for (int i = 0; i < ht.bucket_count(); ++i) {
        int n = ht.elems_in_bucket(i);
        if (n != 0)
            cout << "bucket[" << i << "] has " << n << " elems." << endl;
    }

    for (int i = 0; i <= 47; ++i)
        ht.insert_equal(i);
    cout << ht.size() << endl;
    cout << ht.bucket_count() << endl;

    for (int i = 0; i < ht.bucket_count(); ++i) {
        int n = ht.elems_in_bucket(i);
        if (n != 0)
            cout << "bucket[" << i << "] has " << n << " elems." << endl;
    }

    hashtable<int, int, hash<int>, identity<int>, equal_to<int>> iht;
    iht.copy_from(ht);
    cout << iht.size() << endl;
    cout << iht.bucket_count() << endl;

    cout << ht.find(2) << endl;
    cout << ht.count(2) << endl;
}
