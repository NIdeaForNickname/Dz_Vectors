#include "myVector.hpp"
#include <iostream>
#include <fstream>

int main(){
    ifstream in;
    in.open("words.txt");
    if(!in.is_open()){
        throw "Error: cannot open";
    }

    string str, temp, result;
    Vector<string> vector, v1;

    while(getline(in, str)){
        vector.Append(str);
    }

    do{
        do{
            str = vector.Random();
        } while(str.size() < 8);
        temp = (str.size() < 6) ? str.substr(str.size()-4) : str.substr(str.size()-6);

        for (int i = 0; i < vector.Size(); i++){
            if (vector[i].substr(0,6) == temp){
                v1.Append(vector[i].substr(6));
            }
        }
    } while (v1.Size() == 0);
    
    result += str.substr(0, str.size()-6);
    result += "-";
    result += temp;
    result += "-";
    result += v1.Random();

    cout << result << endl;

    in.close();
    return 0;
}