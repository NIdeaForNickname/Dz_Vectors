#include <iostream>
#include <string>

using namespace std;
class Vector{
    private:
        int* arr = nullptr;
        int size;
        int capacity;
    public:
        
        Vector(int size){
            if (size < 0){
                throw "Invalid vector size";
            }
            this->size = size;
            capacity = size * 2;
            arr = new int[capacity];
        }
        
        Vector() : Vector(0) {}

        Vector(const Vector &arr){
            this->arr = new int[arr.capacity];
            size = arr.size;
            capacity = arr.capacity;
            for(int i = 0; i < size; i++){
                this->arr[i] = arr.arr[i];
            }
        }

        Vector(initializer_list<int> list){
            capacity = list.size()*2;
            size = list.size();
            arr = new int[capacity];
            int i = 0;
            for (int value: list){
                arr[i++] = value;
            }
        }

        int Size() const { return size; }
        int Cap() const { return capacity; }

        void insert(int x, int ind) {
            if (ind < 0 || ind > size) {
                return;
            }

            if (size < capacity) {
                for (int i = size; i > ind; i--) {
                    arr[i] = arr[i - 1];
                }
                arr[ind] = x;
            } else {
                capacity = (capacity*2)+1;
                int* newArr = new int[capacity * 2];

                for (int i = 0; i < size + 1; i++) {
                    if (i < ind) {
                        newArr[i] = arr[i];
                    } else if (i == ind) {
                        newArr[i] = x;
                    } else {
                        newArr[i] = arr[i - 1];
                    }
                }

                delete[] arr;
                arr = newArr;
            }
            size++;
        }

        void Append(int a){
            insert(a, size);
        }

        void RemoveAt(int index){
            if(index < 0 || index >= size){
                return;
            }
            for(int i = index; i < size-1; i++){
                arr[i] = arr[i+1];
            }
            size--;
        }

        void RemoveByValue(int value){
            for (int i = 0; i < size; i++){
                if(arr[i] == value){
                    RemoveAt(i);
                    i--;
                }
            }
        }

        void PopFront(){
            RemoveAt(0);
        }

        void PopBack(){
            RemoveAt(size-1);
        }

        void TrimToSize(){
            int* newArr = new int[size];
            for(int i = 0; i < size; i++){
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity = size;
        }

        int IndexOf(int value){
            for (int i = 0; i < size; i++){
                if(arr[i] == value){
                    return i;
                }
            }
            return -1;
        }

        void Reverse(){
            int temp;
            for(int i = 0; i < size/2; i++){
                temp = arr[i];
                arr[i] = arr[size-i-1];
                arr[size-i-1] = temp;
            }
        }

        void SortAsc(){
            for(int i = 0; i < size-1; i++){ 
                for(int j = 0; j < size-i-1; j++){
                    if(arr[j] > arr[j+1]){
                        int temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                    }
                }
            }
        }

        void SortDesc(){
            SortAsc();
            Reverse();
        }

        void Shuffle(){
            for(int i = 0; i < size; i++){
                int j = rand() % size;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        void RandomFill(int lower, int upper){
            for(int i = 0; i < size; i++){
                arr[i] = rand() % (upper - lower + 1) + lower;
            }
        }

        bool Equals(const Vector& vect) const {
            if (vect.Size() == size){
                for (int i = 0; i < size; i++){
                    if (arr[i] != arr[i]) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        }

        int GetElementAt(int i){ // мне кажеться или был какой-то способ дать функции/методу несколько имён?
            if(i < 0 || i >= size){
                throw "Invalid index";
            }
            return arr[i];// как-то так:
        } // ДругоеИмяФункции1, ДругоеИмяФункции2

        string toString() {
            string ss = "[";
            for(int i = 0; i < size-1; i++){
                ss += to_string(arr[i]);
                ss += ", ";
            }
            if(size-1 >= 0){
                ss += to_string(arr[size-1]);
            }
            ss += "]";
            return ss;
        }

        int& operator[](int i) {
            if(i < 0 || i >= size){
                throw "Invalid index";
            }
            return arr[i]; 
        } 

        bool operator== (const Vector& v) const {
            return Equals(v);
        }

        Vector& operator= (const Vector& v){
            if (&v == this) {
                return *this;
            }

            Vector::~Vector();
            *this=v;
            return *this;
        }

        Vector& operator= (int v) {
            *this=v;
            return *this;
        }
        
        ~Vector(){
            if (arr != nullptr){
                delete[] arr;
            }
        }

        friend ostream& operator<<(ostream& os, const Vector& vect);
        friend istream& operator>>(istream& os, const Vector& vect);
};

ostream& operator<<(ostream& os, const Vector& vect){
    for (int i = 0; i < vect.size-1; i++){
        os << vect.arr[i] << ", ";
    }
    os << vect.arr[vect.size-1];
    return os;
}

istream& operator>>(istream& is, const Vector& vect){
    int temp = 0;
    cout << "Input Vector size: ";
    cin >> temp;
    if (temp < 0){
        throw "wrong vector size";
    };
    return is;
}
