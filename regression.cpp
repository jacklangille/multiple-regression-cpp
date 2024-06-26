#include <vector>
#include <iostream>

using namespace std;

vector<vector<double> > MTRANSPOSE(const vector<vector<double> >& M){
    vector<vector<double> > transposed(M[0].size(), vector<double>(M.size()));
    for(size_t i = 0; i < M.size(); ++i){
        for(size_t j = 0; j < M[0].size(); ++j){
            transposed[j][i] = M[i][j];
        }
    }
    return transposed;
}

vector<vector<double> > MMULT(const vector<vector<double> >& A, const vector<vector<double> >& B){
    vector<vector<double> > product(A.size(), vector<double>(B[0].size(), 0));
    for(size_t i = 0; i < A.size(); ++i){
        for(size_t j = 0; j < B[0].size(); ++j){
            for(size_t k = 0; k < B.size(); ++k){
                product[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return product;
}
vector<vector<double> > MINVERSE(const vector<vector<double> >& M){
    int n = M.size();
    vector<vector<double> > inv(M); // copy initialize inv with M
    vector<vector<double> > I(n, vector<double>(n,0)); // n rows with n columns filled with 0's
    
    // create identity matrix
    for(int i = 0; i<n;++i)
        I[i][i] = 1;
    
    for(int i = 0; i<n; ++i){
        double diag = inv[i][i];
        for(int j = 0; j < n; ++j){
            inv[i][j] /= diag;
            I[i][i] /= diag;
        }
        for(int k = 0; k < n; ++k){
            if(i != k){
                double factor = inv[k][i];
                for(int j = 0; j < n; ++j){
                    inv[k][j] -= factor * inv[i][j];
                    I[k][j] -= factor * I[i][j];
                }
            }
        }
    }

    return I;

}

void MPRINT(const vector<vector<double> >& matrix){
        for (const auto& row : matrix) {
            for (double value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }


int main() {
    
    vector<vector<double> > X {{-1,1.5},{1,-1}};
    vector<vector<double> > coefficients(X.size(), vector<double>(X.size() , 1));

    MPRINT(coefficients);
    


    return 0;
}

