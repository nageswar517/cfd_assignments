#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;

const double L = 1;
const double U = 1;
const double V = 0;

const double nu1 = 0.1;
const double nu2 = 0.01;
const int n1 = 100;
const int n2 = 400;

const double acc = 1e-6;

vector<double> InitValues(vector<double>& psi, vector<double>& omega, int n){
    psi.assign((n+1)*(n+1), 0);
    omega.assign((n+1)*(n+1), 0);
}

void WriteDataToFile(const vector<double>& psi, const vector<double>& omega, const int n, const double del, const double nu){
    // Compute Velocity field
    vector<double> u((n+1)*(n+1));
    vector<double> v((n+1)*(n+1));
    for(int j=0; j<n+1; j++){
        int j_prev = (j-1)*(n+1);
        int j_next = (j+1)*(n+1);
        int j_curr = j*(n+1);
        for(int i=0; i<n+1; i++){
            if(i==0) { u[j_curr+i] = 0; v[j_curr+i] = 0; continue;}
            if(i==n) { u[j_curr+i] = 0; v[j_curr+i] = 0; continue;}
            if(j==0) { u[j_curr+i] = 0; v[j_curr+i] = 0; continue;}
            if(j==n) { u[j_curr+i] = U; v[j_curr+i] = 0; continue;}
            u[j_curr+i] = (psi[j_next+i]-psi[j_prev+i])/(2*del);
            v[j_curr+i] = (psi[j_curr+i+1]-psi[j_curr+i-1])/(-2*del);
        }
    }

    // Writing to Files
    double Re = 1/nu;
    string filename = "out_"+to_string(n)+'_'+to_string((int)Re)+".dat";
    ofstream out;
    out.open(filename.c_str());
    for(int j=0; j<n+1; j++){
        int j_curr = j*(n+1);
        for(int i=0; i<n+1; i++){
            out << i*del << " " << j*del << " " << psi[j_curr+i] << " " << omega[j_curr+i] << " " << u[j_curr+i] << " " << v[j_curr+i] << "\n";
        }
        out << "\n";
    }
    out.close();
    cout << "Data written to " << filename << " file.\n";
}

void Solve(vector<double>& psi, vector<double>& omega, int n, double nu){
    long int it = 0;
    double del = L/n;
    double e_psi = 1000;
    double e_o = 1000;

    cout << "Started solving...\n";
    auto start_time = chrono::high_resolution_clock::now();
    while(e_psi > acc || e_o > acc){
        double sum_e_psi = 0;
        // Update Stream Function
        for(int j=1; j<n; j++){
            int j_prev = (j-1)*(n+1);
            int j_curr = j*(n+1);
            int j_next = (j+1)*(n+1);
            for(int i=1; i<n; i++){
                double psi_old = psi[j_curr+i];
                psi[j_curr+i] = (psi[j_curr+(i-1)]+psi[j_curr+(i+1)]+psi[j_prev+i]+psi[j_next+i]+(omega[j_curr+i]*del*del))*0.25;
                double diff = (psi[j_curr+i]-psi_old);
                sum_e_psi += diff*diff;
            }
        }
        e_psi = sqrt(sum_e_psi/((n-1)*(n-1)));

        // Vertical Wall Vorticity BC 
        for(int j=1; j<n; j++){
            omega[j*(n+1)] = (psi[1+(j*(n+1))]/(del*del))*(-2);
            omega[n+(j*(n+1))] = (psi[(n-1)+(j*(n+1))]/(del*del))*(-2);
        }
        // Horizontal Wall Vorticity BC
        for(int i=1; i<n; i++){
            omega[i+0] = (psi[(n+1)+i]/(del*del))*(-2);
            omega[i+(n*(n+1))] = ((U*del)+psi[i+((n-1)*(n+1))])*(-2/(del*del));
        }

        double sum_e_o = 0;
        // Update Vorticity
        for(int j=1; j<n; j++){
            int j_prev = (j-1)*(n+1);
            int j_curr = j*(n+1);
            int j_next = (j+1)*(n+1);
            for(int i=1; i<n; i++){
                double omega_old = omega[j_curr+i];
                omega[j_curr+i] = ((((psi[j_curr+(i+1)]-psi[j_curr+(i-1)])*(omega[j_next+i]-omega[j_prev+i]))-((psi[j_next+i]-psi[j_prev+i])*(omega[j_curr+(i+1)]-omega[j_curr+(i-1)])))/(16*nu))
                                +((omega[j_curr+(i-1)]+omega[j_curr+(i+1)]+omega[j_prev+i]+omega[j_next+i])/4);
                double diff = omega[j_curr+i]-omega_old;
                sum_e_o += diff*diff;
            }
        }
        e_o = sqrt(sum_e_o/((n-1)*(n-1)));
        it++;
    }
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end_time - start_time;
    double time = elapsed.count();
    cout << "For Re=" << 1/nu << " and resolution of " << n << "X" << n << "\n";
    cout << "Time taken = " << time <<"\n";
    cout << "Number of Iterations = " << it << "\n";
    WriteDataToFile(psi, omega, n, del, nu);
}

int main(){
    vector<double> psi;
    vector<double> omega;
    InitValues(psi, omega, n1);
    Solve(psi, omega, n1, nu1);

    InitValues(psi, omega, n2);
    Solve(psi, omega, n2, nu1);


    return 0;
}