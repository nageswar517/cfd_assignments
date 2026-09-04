#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void ReadFileToMat(char* file, vector<vector<float>>& mat){
    ifstream in;
    in.open(file);
    if(!in.is_open()){
        cout << "Error reading file " << file << "\n";
        exit(1);
    }
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

int WriteMatToFile(vector<vector<float>>& mat){
    ofstream out;
    out.open("c.dat");
    if(!out.is_open()){
        cout << "Error writing to output file.\n";
        return 1;
    }
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat[0].size(); j++){
            out << mat[j][i] << " ";
        }
        out << "\n";
    }
    out.close();
    cout << "Matrix saved successfully.\n";
    return 0;
}

void ScaleAndAddVector(vector<float>& out, float s, vector<float>& col){
    for(int i=0; i<col.size(); i++){
        out[i] += s * col[i];
    }
}

int main(int argc, char** argv){
    if(argc < 3) {
        cout << "Usage .\\assignment_3.exe <a.dat> <b.dat>\n";
        return 1;
    }

    vector<vector<float>> arw, brw;

    ReadFileToMat(argv[1], arw);
    ReadFileToMat(argv[2], brw);

    vector<vector<float>> a(arw[0].size(), vector<float>(arw.size()));
    vector<vector<float>> b(brw[0].size(), vector<float>(brw.size()));
    for(int i=0; i<arw.size(); i++){
        for(int j=0; j<arw[0].size(); j++){
            a[j][i] = arw[i][j];
        }
    }
    for(int i=0; i<brw.size(); i++){
        for(int j=0; j<brw[0].size(); j++){
            b[j][i] = brw[i][j];
        }
    }

    int ra, ca, rb, cb;

    ra = a[0].size(); ca = a.size();
    rb = b[0].size(); cb = b.size();

    if(ca != rb){
        cout << "Matrices cannot be multiplied.\n";
        return 0;
    }

    vector<vector<float>> c(cb, vector<float>(ra));
    for(int i=0; i<cb; i++){
        vector<float> temp(ra, 0);
        for(int j=0; j<rb; j++){
            ScaleAndAddVector(temp, b[i][j], a[j]);
        }
        c[i] = temp;
    }

    WriteMatToFile(c);
        
    return 0;
}
