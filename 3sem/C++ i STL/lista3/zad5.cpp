#include<iostream>
#include<chrono>
#include<ctime>
#include<vector>

using namespace std;

void fill(int n, vector< vector < double > > &m){
	for(int i = 0 ; i < n; i++){
		for(int j = 0; j < n; j++){
			double r = (double) rand() / RAND_MAX;
			m[i][j] = 0.5 + r * 1.5;
		}
	}
}

void power2(int n, vector < vector < double > > &m){
	vector < vector < double > > ans (n, vector < double > (n));
	for(int row = 0; row < n; row ++){
		for (int j = 0; j < n; j ++){
			ans[row][j] = 0;
			for(int k = 0; k < n; k++){
				ans[row][j] += m[row][k] * m[k][j];
			}
	}
	}
	m = ans;
}

int main(){
	srand(time(NULL));
	vector < vector <double> > m1(100, vector< double >(100));
	vector < vector <double> > m2(1000, vector< double >(1000));
	vector < vector <double> > m3(10000, vector< double >(10000));
	fill(100,m1);
	fill(1000,m2);
	fill(10000,m3);

	chrono::duration < double > time(0);
	for(int i = 0; i < 15; i++){
		auto start = chrono::high_resolution_clock::now();
		power2(100,m1);
    	auto end = chrono::high_resolution_clock::now();
    	time += chrono::duration_cast< chrono::duration < double > > (end - start); 
	}
	cout<< "Squaring m: 100x100 took: "<< time.count() / 15.0 << " seconds" << endl;

	auto start = chrono::high_resolution_clock::now();
	power2(1000,m2);
	auto end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast< chrono::duration < double > > (end - start);
	cout<< "Squaring m: 1000x1000 took: "<< time.count() << " seconds" << endl;
	
	start = chrono::high_resolution_clock::now();
	power2(10000,m3);
	end = chrono::high_resolution_clock::now();
	time = chrono::duration_cast< chrono::duration < double > > (end - start);
	cout<< "Squaring m: 10000x10000 took: "<< time.count() << " seconds" << endl;
	
	return 0;
}