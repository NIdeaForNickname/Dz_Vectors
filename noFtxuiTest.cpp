#include <iostream>
#include "myVector.hpp"

using namespace std;
int main(){
    Vector myVector(5);

    myVector.Append(1);
    myVector.Append(2);
    myVector.Append(3);
    myVector.Append(4);
    myVector.Append(5);
    myVector.insert(3, 4);

    cout << myVector << "\n";

    myVector.PopBack();

    cout << myVector << "\n";

    cout << "Size: " << myVector.Size() << "\n" << "Capacity: " << myVector.Cap() << "\n";
    myVector.TrimToSize();
    cout << "Size: " << myVector.Size() << "\n" << "Capacity: " << myVector.Cap() << "\n";

    myVector.Shuffle();
    cout << myVector << "\n";

    myVector.SortAsc();
    cout << myVector << "\n";

    myVector.RandomFill(-10, 10);
    cout << myVector << "\n";

    myVector.RemoveByValue(2);
    cout << myVector << "\n";

    cout << "location of 3(-1 if not present): " << myVector.IndexOf(3) << "\n";

    Vector myCopy = myVector;
    cout << myCopy << "\n";

    
    cout << endl;

    return 0;
}