#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(int argc, char** argv){
    if(argc < 3) {
        cout << "Usage .\assignment_3.exe <a.dat> <b.dat>\n";
        return 0;
    }

    ifstream in;
    in.open(argv[1]);
    if(!in.is_open()) {
        cout << "Error opening file " << argv[1] << ".\n";
        return 1;
    }

    vector<vector<float>> a, b;
    string line;
    
    while(getline(in, line)){
        vector<float> temp;
        stringstream ss(line);
        float num;
        
        while(ss >> num){
            temp.push_back(num);
        }
        a.push_back(temp);
    }
    in.close();

    in.open(argv[2]);    
    while(getline(in, line)){
        vector<float> temp;
        stringstream ss(line);
        float num;
        while(ss >> num){
            temp.push_back(num);
        }
        b.push_back(temp);
    }
    in.close();

    for(int i=0; i<a.size(); i++){
        for(int j=0; j<a[0].size(); j++){
            cout << a[i][j] << "  ";
        }
        cout << "\n";
    }
    for(int i=0; i<b.size(); i++){
        for(int j=0; j<b[0].size(); j++){
            cout << b[i][j] << "  ";
        }
        cout << "\n";
    }

    
    return 0;
}
