#include <iostream>
#include "linked_list.h"

using namespace std;

int main()
{
    myLinkedList <> L;
    L.insertbegin(10);
    L.insertbegin(20);
    L.insertbegin(30);
    L.insertend(40);

    L.display();
    cout << "\n\n";

    cout << "Deleting : " << L.deleteend() << "\n\n";

    L.display();


    return 0;
}
