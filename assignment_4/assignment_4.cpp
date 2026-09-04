#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int length = 1;
const int m = 100;
const int n = 200;
const float dx = (float)length/m;
const float dy = (float)length/n;

void WriteToFile(vector<vector<float>>& mat){
    ofstream out;
    out.open("T.dat");
    if(!out.is_open()){
        cout << "Error writing to file.\n";
        exit(1);
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(j==0){
                out << "[" << dx*i << ", " << dy*j << ", " << mat[i][j] << "]";
                continue;
            }
            out << " [" << dx*i << ", " << dy*j << ", " << mat[i][j] << "]";
        }
        out << "\n";
    }
    out.close();
    cout << "Data written to file successfully.\n";
}

int main(){
    vector<vector<float>> t(m, vector<float>(n));

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(i<50 && j<50) t[i][j] = 1;
            else if(i>=50 && j>=50) t[i][j] = 0.5;
            else t[i][j] = 0.25;
        }
    }
    WriteToFile(t);

    return 0;
}