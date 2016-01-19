#include <iostream>
using namespace std;
#include "rb_tree.h"

int main()
{
    rb_tree<int> itree;

    itree.insert(10);
    itree.insert(7);
    itree.insert(8);

    itree.insert(15);
    itree.insert(5);
    itree.insert(6);

    itree.insert(11);
    itree.insert(12);
    itree.insert(13);

    itree.test();

    itree.print();
}
