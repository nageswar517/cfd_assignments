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

vector<vector<float>> Transpose(vector<vector<float>>& mat, int n){
    vector<vector<float>> transpose(n, vector<float>(n));
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            transpose[i][j] = mat[j][i];
            transpose[j][i] = mat[i][j];
        }
    }

    return transpose;
}

// section a
// Matrix is stored in coloumn-major form
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
    cout << "Enter elements of matrix A row wise:\n";
    for (int i=0; i<ra; i++){
        for(int j=0; j<ca; j++){
            cin >> a[j][i];
        }
    }

    vector<vector<float>> b(cb, vector<float>(rb));
    cout << "Enter elements of matrix B row wise:\n";
    for(int i=0; i<rb; i++){
        for(int j=0; j<cb; j++){
            cin >> b[j][i];
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
// Matrix is stored in row-major form
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

    vector<vector<float>> transpose = Transpose(mat, n);
    float det = GaussianDet(mat, n);
    cout << "Determinant of given matrix is " << det << "\n";
    cout << "Transpose of the given matrix is:\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << transpose[i][j] << "    ";
        }
        cout << "\n";
    }
}

int main(){
    int section;
    cout << "Select matrix multiplication or determinant of matrix.\n";
    cout << "Enter 1 for matrix multiplication or 2 for determinant and transpose of matrix or -1 to exit: ";
    cin >> section;

    if(section == 1) SectionA();
    else if(section == 2) SectionB();
    else if(section == -1) return 0;
    else {
        cout << "Invalid option.";
    }
    return 0;
}