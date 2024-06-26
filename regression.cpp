#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
    vector<vector<double> > I(n, vector<double>(n,0)); 
    
    // create identity matrix
    for(int i = 0; i<n;++i)
        I[i][i] = 1;
    
    for(int i = 0; i<n; ++i){
        double diag = inv[i][i];
        if (diag == 0) {
            cerr << "Matrix is singular and cannot be inverted!" << endl;
            return {};  
        }
        for(int j = 0; j < n; ++j){
            inv[i][j] /= diag;
            I[i][j] /= diag;
        }
        for(int k = 0; k < n; ++k){
            if(k != i){
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


vector<vector<double>> readData(const string& filename) {
    ifstream file(filename);

    string header;
    getline(file, header);

    vector<vector<double>> X;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<double> row;
        double num;
        while (iss >> num) {
            row.push_back(num);
        }
        X.push_back(row);
    }

    file.close(); // Close the file after reading

    return X; // Return the filled vector of vectors
}

vector<vector<double>> vectorToMatrix(const vector<double>& vec) {
   vector<vector<double>> mat;
    for (double num : vec) {
        mat.push_back(vector<double>{num});
    }
    return mat;
}

template<typename T>
void printMatrix(const vector<vector<T>>& matrix) {
    for (const auto& row : matrix) {
        for (T elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}



int main() {
    
    vector<vector<double> > X; 
    vector<double> Y_vector; 
    vector<vector<double> > error; 
    string fileName = "data.txt";
    auto data = readData(fileName);
    
    for(const auto& row : data){
        X.push_back({row[0], row[2], row[3]});
        Y_vector.push_back(row[1]);
    }
    cout << "Data successfully loaded...\n";
    cout << "Predictor matrix X:\n";
    printMatrix(X);
    auto Y = vectorToMatrix(Y_vector);
    cout << "Target vector Y:\n";
    printMatrix(Y);

    size_t numberOfPredictors = X[0].size();
    vector<double> coefficients(numberOfPredictors + 1, 1.0); 
    cout << "Fitting model...\n";
    auto XT = MTRANSPOSE(X);
    auto XT_X = MMULT(XT, X);
    auto XT_X_INV = MINVERSE(XT_X);
    auto XT_Y = MMULT(XT, Y);
    auto beta_hat = MMULT(XT_X_INV, XT_Y);
    
    printMatrix(beta_hat);

    return 0;
}

