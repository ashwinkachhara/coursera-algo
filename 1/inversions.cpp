#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
long int merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    
    long int inv = 0;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
            inv += n1-i;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    return inv;
}
 
/* l is for left index and r is right index of the sub-array
  of arr to be sorted */
long int mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        long int inversions = 0;
        //~ cout << "a" <<inversions << "," << l <<"," <<m<<","<< r<< endl;
        inversions += mergeSort(arr, l, m);
        //~ cout <<"b" << inversions << endl;
        inversions += mergeSort(arr, m+1, r);
        //~ cout <<"c"<< inversions << endl;
        inversions += merge(arr, l, m, r);
        //~ cout <<"d"<< inversions << endl;
        
        return inversions;
    }
    
    return 0;
}

int main () {
	int sz = 0;
	int intArray[100000];
	int i = 0; //counter
	string line;
	ifstream myfile ("IntegerArray.txt");
	if (myfile.is_open()){
		while ( getline (myfile,line))
		{	sz+=1;
			intArray[i++] = stoi(line, nullptr);
			//~ cout << intArray[i-1] << endl;
		}
		myfile.close();
	}

	else {
		cout << "Unable to open file"; 
		return 0;
	}
	int arr[] = {1,3,5,2,4,6};
	
	cout << mergeSort(intArray,0, sz-1) << endl;
	cout << sizeof(int) <<endl;
}
