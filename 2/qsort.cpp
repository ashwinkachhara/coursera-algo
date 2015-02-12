#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int partition(vector<int> &A, int l, int r){
  
    int pivot = A[l];
    int lessthan = l;
    for (int i=l+1; i <= r; i++){
        if (A[i] < pivot){
            if (i == lessthan+1){
                lessthan++;
            } else {
                int temp = A[lessthan+1];
                A[lessthan+1] = A[i];
                A[i] = temp;
                lessthan++;
            }
        }
    }
    
    int temp = A[l];
    A[l] = A[lessthan];
    A[lessthan] = temp;
    
    return lessthan;
}

int findPivot(vector<int> &A, int l, int r, int type=0){
    switch(type){
        case 0: return l;
                break;
        case 1: return r;
                break;
        case 2: int candidates[3];
                candidates[0] = A[l]; candidates[2] = A[r];
                int midpos = l + (((r-l+1)%2 == 0) ? (r-l+1)/2-1 : (r-l)/2);
                //cout << "midpos" << midpos << " " << A[midpos] << " " << l << " " << A[l] << " " << r << " " << A[r] << endl;
                candidates[1] = A[midpos];
                sort(candidates,candidates+3);
                if (candidates[1] == A[l])
					return l;
				if (candidates[1] == A[r])
					return r;
				if (candidates[1] == A[midpos])
					return midpos;
				break;
                
    }
}

void quickSort(vector<int> &A, int l, int r, int &sum){
    if (l < r){
		sum += r-l;
		//cout << r-l+1 << " "<< sum << endl;
		
        int pivot_pos = findPivot (A, l, r, 2);
        //cout << "pivot" << pivot_pos << " " << A[pivot_pos] << endl;
        int temp = A[pivot_pos];
        A[pivot_pos] = A[l];
        A[l] = temp;
        pivot_pos = partition(A, l, r);
        //cout << "pivot" << pivot_pos << " " << A[pivot_pos] << endl;
        
        
        quickSort(A, l, pivot_pos-1, sum);
        //cout << r-l+1 << " "<< sum << endl;
        
        quickSort(A, pivot_pos+1, r, sum);
        
        
        
    }
}

int main(){

    ifstream myfile ("QuickSort.txt");
   
    string line;
    int N = 10000;
    vector<int> A;
    
    if (myfile.is_open()){
        while(getline(myfile, line)){
           A.push_back(stoi(line));
        }
    } else {
		return -1;
	}
    
    int sum = 0;
    //cout << sum <<endl;
    quickSort(A, 0, N-1, sum);
    
    cout << sum << endl;
    
    //cout << A[0] << " " << A[1] << " " << A[2] << endl; 

    return 0;
}
