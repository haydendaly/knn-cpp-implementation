#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <ctime>
#include <bits/stdc++.h> 
using namespace std; 
//Reference: https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
//Reference: https://www.bestprog.net/en/2019/08/23/c-an-example-of-creating-a-template-class-matrix-dynamic-memory-allocation/
template <typename mtrx> 
class Matrix {
	private:
		mtrx** M; 
		int rows;
		int cols;

	public:
		Matrix() {
			rows = 10;	//To be reassigned
			cols = 10;	//To be reassigned
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

			//Helper Methods
			mtrx GetMij(int i, int j) {		//Returns value at matrix[x][y]
			  if ((rows > 0) && (cols > 0))
			    return M[i][j];
			  else
			    return 0;
			}

			void SetMij(int i, int j, mtrx value) {		//Sets value at matrix[x][y]
			  if ((i < 0) || (i >= rows))
			    return;
			  if ((j < 0) || (j >= cols))
			    return;
			  M[i][j] = value;
			}
			

		void Print(const char* obj) {		//Displays entire matrix
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

float Random_Float(float a, float b) { //Generate random number
	float r = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a; 
	return (r*diff) + a; 
}

Matrix<float> create_matrix(int total_tensors, int dimensions, float min_random_value, float max_random_value) {  //for user defined multiple index matrices
	dimensions++; //accomidating for index in 0 column
	Matrix<float> M(total_tensors, dimensions); 

	//Benchmarking
	struct timeval start, end; 
    gettimeofday(&start, NULL); 
    ios_base::sync_with_stdio(false); 

 
	for(int i = 0; i < total_tensors; i++)
		M.SetMij(i, 0, i); 

	//set random gen numbers
	for (int a = 1; a <= dimensions; a++) {		
		for (int i = 0; i < total_tensors; i++)
			M.SetMij(i, a, Random_Float(min_random_value, max_random_value)); 
	}
	//Benchmarking uncomment below to identify runtimes
	/*
	gettimeofday(&end, NULL); 
    double time_taken; 
    time_taken = (end.tv_sec - start.tv_sec) * 1e6; 
    time_taken = (time_taken + (end.tv_usec -  
                              start.tv_usec)) * 1e-6; 
    cout << "Given " << dimensions - 1 << " x " << total_tensors << " Matrix \n"; 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(6); 
    cout << " sec" << endl; 
	std::cout <<endl;  
	*/

  	M.Print("Sample Test Matrix");

  	//Write to .csv file
  	ofstream out("matrix.csv");
  	
  	// Generate column labels 
  	// Add/remove below to include/remove header labels for Tensors 
  	//	 /*
  	out << "Number" << ','; 
  	for (int x = 1; x < dimensions; x++)
  		out << "T" << x << ',';
  	out << '\n'; 
	//	  */

  	//Write to .csv file
	for (int i = 0; i < total_tensors; i++) {
  		for(int j = 0; j < dimensions; j++) {
  			out << M.GetMij(i, j) << ',';
  		}
  		out << '\n'; 
  	}
  	std::cout << "matrix.csv file saved successfully\n"; 
  	std::cout << std::endl;
}


int main() {
	
	//Note: to change dimensions, alter .dat file 

	std::freopen("./matrix.dat", "r", stdin); //.dat dimensional read in file
	int total_tensors; 	//rows
	int dimensions; 	//cols
	float max_random_value; //max testing value
	float min_random_value; //min testing value 

	//read in from .dat
	std::cin >> total_tensors; 
	std::cin >> dimensions;
	std::cin >> max_random_value;
	std::cin >> min_random_value; 

	//generate matrix
	create_matrix(total_tensors, dimensions, min_random_value,max_random_value); 

	return 0; 
}