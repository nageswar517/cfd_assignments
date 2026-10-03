#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

const double lx = 2;
const double ly = 1;
const double grid_size = 0.01;
const int m = lx / grid_size;
const int n = ly / grid_size;
const double acc = 1e-5;

long long int jacobi_it = 0;
long long int pgs_it = 0;

void InitValues(vector<vector<double>>& domain){
    for(int j=0; j<n+3; j++){
        for(int i=0; i<m+1; i++){
            if(i==0) domain[j][i] = 1000;
            else if(i==m) domain[j][i] = 500;
            else domain[j][i] = (1000+500)/2;
        }
    }
}

void WriteToFile(const vector<vector<double>>& domain, string name){
    ofstream out;
    out.open(name);
    for(int j=1; j<n+2; j++){
        for(int i=0; i<m+1; i++){
            out << (i)*grid_size << " " << (j-1)*grid_size << " " << domain[j][i] << "\n";
        }
        out << "\n";
    }
    out.close();
}

void Jacobi(vector<vector<double>>& domain, vector<vector<double>>& new_domain){
    auto start_time = chrono::high_resolution_clock::now();
    double e = 250;
    while(e > acc){
        double sum_e = 0;
        swap(domain, new_domain);
        for(int i=0; i<m+1; i++){
            new_domain[0][i] = domain[2][i];
            new_domain[n+2][i] = domain[n][i];
        }

        for(int j=1; j<n+2; j++){
            for(int i=0; i<m+1; i++){
                if(i==0) {new_domain[j][i] = domain[j][i];continue;}
                if(i==m){new_domain[j][i] = domain[j][i]; continue;}
                new_domain[j][i] = (domain[j][i-1]+domain[j][i+1]+domain[j-1][i]+domain[j+1][i]) * 0.25;
                double diff = new_domain[j][i]-domain[j][i];
                sum_e += (diff*diff);

            }
        }
        e = sqrt(sum_e/(m*n));
        jacobi_it++;
    }
    auto end_time = chrono::high_resolution_clock::now();
    cout << "Jacobi Iterations: " << jacobi_it << "\n";
    chrono::duration<double> elapsed = end_time-start_time;
    double time = elapsed.count();
    cout <<"Jacobi iteration rate: " << jacobi_it/time << "it/s\n";
    WriteToFile(new_domain, "jacobi.dat");
}

void PGS(vector<vector<double>>& domain, vector<vector<double>>& new_domain){
    auto start_time = chrono::high_resolution_clock::now();
    double e = 250;
    while(e > acc){
        double sum_e = 0;
        swap(domain, new_domain);
        for(int i=0; i<m+1; i++){
            new_domain[0][i] = domain[2][i];
            new_domain[n+2][i] = domain[n][i];
        }

        for(int j=1; j<n+2; j++){
            for(int i=0; i<m+1; i++){
                if(i==0) {new_domain[j][i] = domain[j][i];continue;}
                if(i==m){new_domain[j][i] = domain[j][i]; continue;}
                new_domain[j][i] = (new_domain[j][i-1]+domain[j][i+1]+new_domain[j-1][i]+domain[j+1][i]) * 0.25;
                double diff = new_domain[j][i]-domain[j][i];
                sum_e += (diff*diff);

            }
        }
        e = sqrt(sum_e/(m*n));
        pgs_it++;
    }
    auto end_time = chrono::high_resolution_clock::now();
    cout << "Point Gauss Seidel Iterations: " << pgs_it << "\n";
    chrono::duration<double> elapsed = end_time-start_time;
    double time = elapsed.count();
    cout << "Point Gauss Seidel Iteration rate: " << pgs_it/time << "it/s\n";
    WriteToFile(new_domain, "pgs.dat");
}

int main(){
    vector<vector<double>> domain(n+3, vector<double>(m+1));
    vector<vector<double>> new_domain(n+3, vector<double>(m+1));

    InitValues(domain);
    InitValues(new_domain);
    Jacobi(domain, new_domain);

    InitValues(domain);
    InitValues(new_domain);
    PGS(domain, new_domain);

    return 0;
}