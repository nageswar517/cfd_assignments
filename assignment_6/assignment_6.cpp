#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;

const double lx = 1;
const double ly = 1;
const int m = 400;
const int n = 400;
const double grid_size = lx/m;
const double acc = 0.1;

long long int pgs_it = 0;
long long int psor_it = 0;

const double T_inf = 300;
const double h = 10;
const double k = 50;
const double dirichlet_bc = 1000;

void InitValues(vector<vector<double>>& domain){
    for(int j=0; j<n+2; j++){
        for(int i=0; i<m+1; i++){
            if(j==0) {domain[j][i] = dirichlet_bc; continue;}
            if(i==0) {domain[j][i] = dirichlet_bc; continue;}
            if(i==m) {domain[j][i] = dirichlet_bc; continue;}
            domain[j][i] = (T_inf+dirichlet_bc)/2;
        }
    }
}

void WriteToFile(const vector<vector<double>>& domain){
    ofstream out;
    out.open("pgs.dat");
    for(int i=0; i<m+1; i++){
        for(int j=0; j<n+1; j++){
            out << i*grid_size << " " << j*grid_size << " " << domain[j][i] << "\n";
        }
        out << "\n";
    }
    out.close();

    
}

void PGS(vector<vector<double>>& domain, vector<vector<double>>& new_domain){
    auto start_time = chrono::high_resolution_clock::now();
    double e = 1000;
    while(e > acc){
        double sum_e = 0;
        swap(domain, new_domain);

        // update bc
        for(int i=1; i<m; i++){
            new_domain[n+1][i] = domain[n-1][i] + (((2*h*grid_size)/k)*(T_inf - domain[n][i]));
        }

        //iterate
        for(int j=1; j<n+1; j++){
            for(int i=1; i<m; i++){
                new_domain[j][i] = (new_domain[j][i-1]+domain[j][i+1]+new_domain[j-1][i]+domain[j+1][i]) * 0.25;
                double diff = new_domain[j][i] - domain[j][i];
                sum_e += diff*diff;
            }
        }
        e = sqrt(sum_e/(m*(n-1)));
        pgs_it++;
    }

    WriteToFile(new_domain);
    ofstream out;
    out.open("pgs_x0.dat");
    for(int j=0; j<n+1; j++){
        out << j*grid_size << " " << new_domain[j][0] << "\n";
    }
    out.close();

    out.open("pgs_x25.dat");
    for(int j=0; j<n+1; j++){
        out << j*grid_size << " " << new_domain[j][100] << "\n";
    }
    out.close();

    out.open("pgs_x50.dat");
    for(int j=0; j<n+1; j++){
        out << j*grid_size << " " << new_domain[j][200] << "\n";
    }
    out.close();
}

int main(){
    vector<vector<double>> domain(n+2, vector<double>(m+1));
    vector<vector<double>> new_domain(n+2, vector<double>(m+1));

    InitValues(domain);
    InitValues(new_domain);
    PGS(domain, new_domain);

    return 0;
}
