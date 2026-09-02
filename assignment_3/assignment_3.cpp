#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void ReadFileToMat(char* file, vector<vector<float>>& mat){
    ifstream in;
    in.open(file);
    string line;
    
    while(getline(in, line)){
        vector<float> temp;
        stringstream ss(line);
        float num;
        
        while(ss >> num){
            temp.push_back(num);
        }
        mat.push_back(temp);
    }
    in.close();
}

int main(int argc, char** argv){
    if(argc < 3) {
        cout << "Usage .\assignment_3.exe <a.dat> <b.dat>\n";
        return 0;
    }

    vector<vector<float>> a, b;

    ReadFileToMat(argv[1], a);
    for(int i=0; i<a.size(); i++){
        for(int j=0; j<a[0].size(); j++){
            cout << a[i][j] << "  ";
        }
        cout << "\n";
    }

    ReadFileToMat(argv[2], b);
    for(int i=0; i<b.size(); i++){
        for(int j=0; j<b[0].size(); j++){
            cout << b[i][j] << "  ";
        }
        cout << "\n";
    }
        
    return 0;
}
