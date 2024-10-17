#include <bits/stdc++.h>
using namespace std;

// Defining macros for sizes for matrix and threads
#define MAX 3
#define MAX_THREAD 3

// Declaring three matrices, two for input and one for displaying and storing result.
int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];

int step_i = 0; // to track current row processed.

// Function performing multiplication.
void* multiply(void* arg){

	int i = step_i++;// denotes row no of  resultant matrix

	for(int  j=0;j<MAX;j++){
		for(int k =0;k<MAX;k++){
			matC[i][j] += matA[i][k] * matB[k][j];
		}
	}

	return nullptr;
}


int main(){
	// Taking user input for the matrix A and B.
	cout << "Enter Matrix A"<<endl;
	for(int i=0;i<MAX;i++){
		for(int j= 0;j<MAX;j++){
			cout << "Enter the element at " << i+1 << "th ," << j+1<<"th index: ";
			cin >> matA[i][j];
		}
	}

	cout <<endl << "Enter Matrix B"<<endl;
	for(int i=0;i<MAX;i++){
		for(int j= 0;j<MAX;j++){
			cout << "Enter the element at " << i+1 << "th ," << j+1<<"th index: ";
			cin >> matB[i][j];
		}
	}


	// Displaying matA
    	cout << endl << "Matrix A" << endl;
    	for (int i = 0; i < MAX; i++) {
        	for (int j = 0; j < MAX; j++){ 
            	cout << matA[i][j] << " ";
		}
        cout << endl;
    	}

    	// Displaying matB
   	 cout << endl << "Matrix B" << endl;
    	for (int i = 0; i < MAX; i++) {
        	for (int j = 0; j < MAX; j++){ 
            	cout << matB[i][j] << " ";
		}
        	cout << endl;
	 }
	//declaring three threads
	pthread_t threads[MAX_THREAD];
	//creating four threads, each evaluating its own part.
	for(int i=0;i<MAX;i++){
		pthread_create(&threads[i],NULL,multiply,nullptr);
	}
	//joining and waiting for all threads to complete its task.
	for(int i=0;i<MAX;i++){
		pthread_join(threads[i],NULL);
	}
	// Displaying the result matrix.
    	cout << endl << "Multiplication of A and B" << endl;
    	for (int i = 0; i < MAX; i++) {
        	for (int j = 0; j < MAX; j++){
            	cout << matC[i][j] << " ";
		}
        	cout << endl;
 	 }

	return 0;
}
