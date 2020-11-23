#include <iostream>
using namespace std; 

template <typename mtrx> 
class Matrix {
	private:
		mtrx** M; 
		int rows;
		int cols;

	public:
		Matrix() {
			rows = 10; 
			cols = 10;
			//cols = 2; for KNN Implementation
			M = nullptr; 
		}

		Matrix(int totalRows, int totalCols) {
			rows = totalRows;
			cols = totalCols; 

			//allocate memory
			M = (mtrx**) new mtrx*[rows]; 

			//allocate for each ptr
			for(int i = 0; i < rows; i++) {
				M[i] = (mtrx*) new mtrx[cols]; 
			}

			//fill matrix
			for (int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					M[i][j] = 0;
				}
			}
		}

		Matrix(const Matrix& M_IN) {
			rows = M_IN.rows;
			cols = M_IN.cols; 
			M = (mtrx**) new mtrx[rows]; 

			for (int i = 0; i < rows; i++)
				M[i] = (mtrx*) new mtrx[rows];

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					M[i][j] = M_IN.M[i][j];
				}
			}
		}

			//helpers 
			
			mtrx GetMij(int i, int j) {
			  if ((rows > 0) && (cols > 0))
			    return M[i][j];
			  else
			    return 0;
			}

			void SetMij(int i, int j, mtrx value) {
			  if ((i < 0) || (i >= rows))
			    return;
			  if ((j < 0) || (j >= cols))
			    return;
			  M[i][j] = value;
			}
			

		void Print(const char* obj) {
			cout << "Object: " << obj << endl;
			for(int i = 0; i < rows; i++) {
				for(int j = 0 ; j < cols; j++)	
					cout << M[i][j] << "  \t"; 
				cout << endl; 
			}
			cout << "==============================" << endl; 
		}		

		Matrix operator=(const Matrix& M_IN){
			if (rows > 0){
				for (int i = 0; i < rows; i++)
					delete[] M[i]; 
			}

			if (cols> 0) {
				delete[] M; 
			}

			//Copy data from M_IN into M
			rows = M_IN.rows;
			cols = M_IN.cols; 

			//Reallocate Memory for M
			M = (mtrx**) new mtrx*[rows]; //#rows, #ptrs

			for(int i = 0; i < rows; i++)
				M[i] = (mtrx*) new mtrx[rows]; 
			
			//fill matrix
			for (int i = 0; i < rows; i++) {
				for(int j = 0; j < cols; j++) {
					M[i][j] = 0;
				}
			}
			return *this; 
		}

		~Matrix() //destructor
		{
			if (rows > 0){
				for (int i = 0; i < rows; i++)
					delete[] M[i]; 
			}

			if (cols > 0)
				delete[] M; 
		}
};

float Random_Float(float a, float b) {
	float r = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a; 
	return (r*diff) + a; 
}

int main() {

  Matrix<float> M(50, 2);

  // Fill the matrix with values according to the formula

  for (int i = 0; i < 50; i++)
  	//M.SetMij(i, 0, i);
  	M.SetMij(i, 0, Random_Float(-100.0, 100.0)); 
  for (int i = 0; i < 50; i ++)
  	M.SetMij(i, 1, Random_Float(-100.0, 100.0)); 
  /*
    for (int j = 0; j < 3; j++)
      M.SetMij(i, j, rand() % 100);
  */
  M.Print("Sample Test Matrix");
}