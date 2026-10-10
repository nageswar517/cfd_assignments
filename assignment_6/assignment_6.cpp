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
const double acc = 1e-6;

long long int pgs_it = 0;
long long int psor_it = 0;

const double T_inf = 300;
const double h = 10;
const double k = 50;
const double dirichlet_bc = 1000;

void InitValues(vector<double>& domain){
    for(int j=0; j<n+2; j++){
        for(int i=0; i<m+1; i++){
            if(j==0) {domain[(j*(m+1))+i] = dirichlet_bc; continue;}
            if(i==0) {domain[(j*(m+1))+i] = dirichlet_bc; continue;}
            if(i==m) {domain[(j*(m+1))+i] = dirichlet_bc; continue;}
            domain[(j*(m+1))+i] = (3*dirichlet_bc+T_inf)/4;
        }
    }
}

void WriteToFile(const vector<double>& domain, string s){
    ofstream out;
    out.open(s.c_str());
    for(int j=0; j<n+1; j++){
        for(int i=0; i<m+1; i++){
            out << i*grid_size << " " << j*grid_size << " " << domain[(j*(m+1))+i] << "\n";
        }
        out << "\n";
    }
    out.close();
}

void PGS(vector<double>& domain){
    auto start_time = chrono::high_resolution_clock::now();
    double e = 1000;
    double c = (2*h*grid_size)/k;
    while(e > acc){
        double sum_e = 0;

        // update bc
        for(int i=1; i<m; i++){
            domain[((n+1)*(m+1))+i] = domain[((n-1)*(m+1))+i] + (c*(T_inf - domain[(n*(m+1))+i]));
        }

        //iterate
        for(int j=1; j<n+1; j++){
            int j_curr = j*(m+1);
            int j_prev = (j-1)*(m+1);
            int j_next = (j+1)*(m+1);
            for(int i=1; i<m; i++){
                double prev = domain[j_curr+i];
                domain[j_curr+i] = (domain[j_curr+(i-1)]+domain[j_curr+(i+1)]+domain[(j_prev)+i]+domain[(j_next)+i]) * 0.25;
                double diff = domain[(j_curr)+i] - prev;
                sum_e += diff*diff;
            }
        }
        e = sqrt(sum_e/((m-1)*(n)));
        pgs_it++;
    }
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;
    double time = elapsed.count();
    cout << "Point Gauss Seidel Iterations: " << pgs_it << "\n";
    cout << "Time: " << time << " s" << "\n";
    cout << "Iteration rate: " << pgs_it/time << " it/s\n";

    WriteToFile(domain, "pgs.dat");
    ofstream out;
    out.open("pgs_x0.dat");
    for(int j=0; j<n+1; j++){
        out << j*grid_size << " " << domain[j*(m+1)] << "\n";
    }
    out.close();
    cout << "Saved pgs_x0.dat\n";

    out.open("pgs_x25.dat");
    for(int j=0; j<n+1; j++){
        out << j*grid_size << " " << domain[j*(m+1)+100] << "\n";
    }
    out.close();
    cout << "Saved pgs_x25.dat\n";

    out.open("pgs_x50.dat");
    for(int j=0; j<n+1; j++){
        out << j*grid_size << " " << domain[j*(m+1)+200] << "\n";
    }
    out.close();
    cout << "Saved pgs_x50.dat\n";
}

void PSOR(vector<double>& domain){
    double c = (2*h*grid_size)/k;
    double omega;
    
    ofstream data;
    data.open("psor\\omega_vs_it.dat");
    for(int om=11; om<20; om++){
        omega = om/10.0;
        InitValues(domain);
        double e = 1000;
        psor_it = 0;
        auto start_time = chrono::high_resolution_clock::now();
        while(e > acc){
            double sum_e = 0;

            // update bc
            int ghost = (n+1)*(m+1);
            int below_boundary = (n-1)*(m+1);
            int boundary = n*(m+1);
            for(int i=1; i<m+1; i++){
                domain[ghost+i] = domain[below_boundary+i] + c*(T_inf-domain[boundary+i]);
            }

            // iterative solver
            for(int j=1; j<n+1; j++){
                int j_prev = (j-1)*(m+1);
                int j_curr = j*(m+1);
                int j_next = (j+1)*(m+1);
                for(int i=1; i<m; i++){
                    double T_old = domain[j_curr+i];
                    double T_star = (domain[j_curr+(i-1)]+domain[j_curr+(i+1)]+domain[j_prev+i]+domain[j_next+i]) * 0.25;
                    domain[j_curr+i] = T_old + omega*(T_star - T_old);
                    double diff = T_star - T_old;
                    sum_e += diff * diff;
                }
            }
            e = sqrt(sum_e/(n*(m-1)));
            psor_it++;
        }
        auto end_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end_time - start_time;
        double time = elapsed.count();
        cout << "PSOR Iterations: " << psor_it << " for omega " << omega << "\n";
        cout << "Time: " << time << " s" << "\n";
        cout << "Iteration rate: " << psor_it/time << " it/s\n";

        string filename = "psor\\psor_"+to_string(om)+".dat";
        WriteToFile(domain, filename);
        data << psor_it << " " << omega << "\n";
    }
    data.close();
}

int main(){
    vector<double> domain((n+2)*(m+1));
    int choice;

    cout << "Enter 1 for PGS, 2 for PSOR, -1 to exit\nChoose solver: ";
    cin >> choice;

    if(choice == 1){
        InitValues(domain);
        PGS(domain);
        return 0;
    }
    else if(choice == 2){
        InitValues(domain);
        PSOR(domain);
        return 0;
    }
    else return 0;
}
