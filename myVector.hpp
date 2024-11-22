#include <iostream>
#include <string>

using namespace std;
template<typename T = int>
class Vector{
    private:
        T* arr = nullptr;
        int size;
        int capacity;
    public:
        
        Vector(int size){
            if (size < 0){
                throw "Invalid vector size";
            }
            this->size = size;
            capacity = size * 2;
            arr = new T[capacity];
        }
        
        Vector() : Vector(0) {}

        Vector(const Vector<T> &arr){
            this->arr = new T[arr.capacity];
            size = arr.size;
            capacity = arr.capacity;
            for(T i = 0; i < size; i++){
                this->arr[i] = arr.arr[i];
            }
        }

        Vector(initializer_list<T> list){
            capacity = list.size()*2;
            size = list.size();
            arr = new T[capacity];
            T i = 0;
            for (T value: list){
                arr[i++] = value;
            }
        }

        int Size() const { return size; }
        int Cap() const { return capacity; }

        void insert(T x, int ind) {
            if (ind < 0 || ind > size) {
                return;
            }

            if (size < capacity) {
                // Shift elements to the right
                for (int i = size; i > ind; i--) {
                    arr[i] = arr[i - 1];
                }
                arr[ind] = x;
            } else {
                // Expand capacity and create a new array
                capacity = (capacity*2)+1;
                T* newArr = new T[capacity * 2];

                // Copy elements into the new array with the new element at `ind`
                for (int i = 0; i < size + 1; i++) {
                    if (i < ind) {
                        newArr[i] = arr[i];
                    } else if (i == ind) {
                        newArr[i] = x;
                    } else {
                        newArr[i] = arr[i - 1];
                    }
                }

                // Free the old array memory and assign the new array
                delete[] arr;
                arr = newArr;
            }
            size++;
        }

        void Append(T a){
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

        void RemoveByValue(T value){
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
            T* newArr = new T[size];
            for(int i = 0; i < size; i++){
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity = size;
        }

        int IndexOf(T value){
            for (int i = 0; i < size; i++){
                if(arr[i] == value){
                    return i;
                }
            }
            return -1;
        }

        void Reverse(){
            T temp;
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
                        T temp = arr[j];
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
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // void RandomFill(int lower, int upper){
        //     for(int i = 0; i < size; i++){
        //         arr[i] = rand() % (upper - lower + 1) + lower;
        //     }
        // }

        bool Equals(const Vector<T>& vect) const {
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

        T Random(){
            if (size == 0) {throw "cant divide by 0";}
            srand(time(0));
            return arr[rand() % size];
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

        T& operator[](int i) {
            if(i < 0 || i >= size){
                throw "Invalid index";
            }
            return arr[i]; 
        } 

        bool operator== (const Vector<T>& v) const {
            return Equals(v);
        }

        Vector<T>& operator= (const Vector<T>& v){
            if (&v == this) {
                return *this;
            }

            this->~Vector();
            *this=v;
            return *this;
        }

        Vector<T>& operator= (int v) {
            *this=v;
            return *this;
        }
        
        ~Vector(){
            if (arr != nullptr){
                delete[] arr;
            }
        }

        template<typename U>
        friend ostream& operator<<(ostream& os, const Vector<U>& vect);
        template<typename U>
        friend istream& operator>>(istream& os, const Vector<U>& vect);
};

template<typename U>
ostream& operator<<(ostream& os, const Vector<U>& vect){
    for (int i = 0; i < vect.size-1; i++){
        os << vect.arr[i] << ", ";
    }
    os << vect.arr[vect.size-1];
    return os;
}

template<typename U>
istream& operator>>(istream& is, Vector<U>& vect){
    int temp = 0;
    cout << "Input Vector size: ";
    cin >> temp;
    if (temp < 0){
        throw "wrong vector size";
    };
    vect = temp;
    return is;
}
