#include <iostream>
#include <vector>

using namespace std;

vector<float> ScalarMult(float s, vector<float> col){
    vector<float> out(col.size());
    for(int i=0; i<col.size(); i++){
        out[i] = s*col[i];
    }
    return out;
}

void Add(vector<float>& a, const vector<float>& b){
    for (int i=0; i<a.size(); i++){
        a[i] += b[i];
    }
}

void Sub(vector<float>& a, const vector<float>& b){
    for(int i=0; i<a.size(); i++){
        a[i] -= b[i];
    }
}

void CreateSubMat(vector<vector<float>>& mat, vector<vector<float>>& sub, int col, int n){
    for(int i=1; i<n; i++){
        int subcol = 0;
        for(int j=0; j<n; j++){
            if(j == col) continue;
            sub[i-1][subcol] = mat[i][j];
            subcol++;
        }
    }
}

float Det(int n, vector<vector<float>>& mat){
    if(n == 1) return mat[0][0];
    if(n == 2){
        return (mat[0][0]*mat[1][1])-(mat[0][1]*mat[1][0]);
    }

    float det = 0;
    for(int i=0; i<n; i++){
        vector<vector<float>> temp(n-1, vector<float>(n-1));
        CreateSubMat(mat, temp, i, n);
        int sign = (i%2 == 0) ? 1 : -1;
        float term = sign * mat[0][i] * Det(n-1, temp);
        det += term;
    }
    return det;
}

float GaussianDet(vector<vector<float>>& mat, int n){
    int swaps = 0;
    for(int i=0; i<n; i++){
        if(mat[i][i] == 0){
            bool found_row = false;
            for(int j=i+1; j<n; j++){
                if(mat[j][i] != 0){
                    found_row = true;
                    swap(mat[i], mat[j]);
                    swaps++;
                    break;
                }
            }
            if(!found_row) return 0;
        }
        for(int j=i+1; j<n; j++){
            float factor = mat[j][i]/mat[i][i];
            vector<float> mod_row = ScalarMult(factor, mat[i]);
            Sub(mat[j], mod_row);
        }
    }
    int sign = (swaps%2 == 0) ? 1 : -1;
    float det = mat[0][0];
    for(int i=1; i<n; i++){
        det *= mat[i][i];
    }
    return sign * det;
}

// section a
void SectionA(){
    int ra, ca, rb, cb;
    cout << "Enter the order of matrix A: ";
    cin >> ra >> ca;
    cout << "Enter the order of matrix B: ";
    cin >> rb >> cb;
    if (ca != rb){
        cout << "Cannot multiply the matrices with given order.\n";
        return;
    }
    vector<vector<float>> a(ca, vector<float>(ra));
    cout << "Enter elements of matrix A coloumn wise:\n";
    for (int i=0; i<ca; i++){
        cout << "Enter elements of column " << i+1 << ":\n";
        for(int j=0; j<ra; j++){
            cin >> a[i][j];
        }
    }

    vector<vector<float>> b(cb, vector<float>(rb));
    cout << "Enter elements of matrix B coloumn wise:\n";
    for(int i=0; i<cb; i++){
        cout << "Enter elements of column " << i+1 << ":\n";
        for(int j=0; j<rb; j++){
            cin >> b[i][j];
        }
    }

    vector<vector<float>> c(cb, vector<float>(ra));
    for(int i=0; i<cb; i++){
        vector<float> temp(ra, 0);
        for(int j=0; j<rb; j++){
            Add(temp, ScalarMult(b[i][j], a[j]));
        }
        c[i] = temp;
    }

    cout << "Matrix multiplication result of given matrices is :\n";
    for(int i=0; i<ra; i++){
        for(int j=0; j<cb; j++){
            cout << c[j][i] << "  ";
        }
        cout << "\n";
    }
}

// section b
void SectionB(){
    int n;
    cout << "Enter order of matrix: ";
    cin >> n;
    vector<vector<float>> mat(n, vector<float>(n));
    cout << "Enter the matrix elements row wise:\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> mat[i][j];
        }
    }

    //float det = Det(n, mat);
    float det = GaussianDet(mat, n);
    cout << "Determinant of given matrix is " << det << "\n";
}

int main(){
    int section;
    cout << "Select matrix multiplication or determinant of matrix.\n";
    cout << "Enter 1 for matrix multiplication or 2 for determinant of matrix or -1 to exit: ";
    cin >> section;

    if(section == 1) SectionA();
    else if(section == 2) SectionB();
    else if(section == -1) return 0;

    return 0;
}