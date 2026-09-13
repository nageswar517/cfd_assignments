#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Variables initialisation
const int length = 1;
const int m = 100;
const int n = 200;
const float dx = (float)length/m;
const float dy = (float)length/n;

// Helper function to write grid to .dat file
void WriteGridToFile(){
    ofstream out;
    out.open("grid.dat");
    if(!out.is_open()){
        cout << "Error writing to file grid.dat\n";
        exit(1);
    }
    for(int i=0; i<m+1; i++){
        for(int j=0; j<n+1; j++){
            out << dx*i << "\t" << dy*j << "\n";
        }
    }
    out.close();
    cout << "Grid written successfully.\n";
}

// Helper function to write temperature to .dat file
void WriteToFileT(const vector<vector<float>>& mat){
    ofstream out;
    out.open("T.dat");
    if(!out.is_open()){
        cout << "Error writing to file.\n";
        exit(1);
    }
    for(int i=0; i<m+1; i++){
        for(int j=0; j<n+1; j++){
            out << dx*i << "\t" << dy*j << "\t" <<  mat[i][j] << "\n";
        }
    }
    out.close();
    cout << "T written to file successfully.\n";
}

int main(){
    vector<vector<float>> t(m+1, vector<float>(n+1));

    // Initialising temperatures at all nodes
    for(int i=0; i<m+1; i++){
        for(int j=0; j<n+1; j++){
            if(i<50 && j<50) t[i][j] = 1;
            else if(i>=50 && j>=50) t[i][j] = 0.5;
            else t[i][j] = 0.25;
        }
    }

    WriteGridToFile();
    WriteToFileT(t);

    return 0;
}