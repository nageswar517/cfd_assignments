#include <iostream>
#include <vector>

using namespace std;

const float lx = 2;
const float ly = 1;
const float grid_size = 0.01;
const float m = lx / grid_size;
const float n = ly / grid_size;
const float acc = 0.1;

void InitValues(vector<vector<float>>& domain){
    for(int i=0; i<m+1; i++){
        for(int j=0; j<n+1; j++){
            if(i==0) domain[i][j] = 1000;
            else if(i==m) domain[i][j] = 500;
            else domain[i][j] = (1000+500)/2;
        }
    }
}

int main(){
    vector<vector<float>> domain(m+1, vector<float>(n+1));
    InitValues(domain);

    return 0;
}