#include <vector>
#include <iostream>

using namespace std;

class LinearRegression{
  private:
  vector<double> X;
  vector<vector<double> > mtranspose(const vector<vector<double> >& m){
      vector<vector<double> > transposed(m[0].size(), vector<double>(m.size()));
      for(size_t i = 0; i < m.size(); ++i){
        for(size_t j = 0; j < m[0].size(); ++j){
          transposed[j][i] = m[i][j];
        }
      }
      return transposed;
    }
    
  vector<vector<double> > mmult(const vector<vector<double> >& a, const vector<vector<double> >& b){
    vector<vector<double> > product(a.size(), vector<double>(b[0].size(), 0));
    for(size_t i = 0; i < a.size(); ++i){
      for(size_t j = 0; j < b[0].size(); ++j){
        for(size_t k = 0; k < b.size(); ++k){
          product[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    return product;
  }


  // inverse function here
  
  void mprint(const vector<vector<double> >& matrix){
    for (const auto& row : matrix) {
      for (double value : row) {
        cout << value << " ";
      }
      cout << endl;
    }
  }

  public:
    LinearRegression() {}
  
};




int main() {
  vector<vector<double> > A {{1,2},{2,4}};
  vector<vector<double> > B {{3,1},{2,2}};


  return 0;
}

