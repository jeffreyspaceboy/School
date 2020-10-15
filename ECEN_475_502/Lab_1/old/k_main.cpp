#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	// asking for file name in command line
	printf("Opening File: %s\n\n", argv[1]);
    ifstream inputFile(argv[1]);
    
	// Reading first two numbers of files to determine nodes and edges
    const int ARRAY_SIZE = 2; // Array size
    int numbers[ARRAY_SIZE];   // Array number with 10 elements
    int count = 0;             // Loop counter variable


    // Read the numbers from the file into the array.
    while (count < ARRAY_SIZE && inputFile >> numbers[count]){
       	//printf("%d\n",numbers[count]);
		count++;
    }
    	// Separating nodes and edges
	int num_nodes  = numbers[0]	;
	int num_edges = numbers[1];
	
	// make array from 1 to n/2
	int setA[num_nodes];
	int sizeof_setA = num_nodes/2;
	for (int i = 0; i < sizeof_setA; i++){
		setA[i] = i+1;
		printf("%d",setA[i]);
	}
	cout << endl;
	
	// make array from n/2 to n
	int setB[num_nodes];
	int sizeof_setB = num_nodes - (num_nodes/2);
	for (int i = num_nodes/2; i < num_nodes; i++){
		setB[i] = i+1;
		printf("%d",setB[i]);
	}
	cout << endl;
	
	// defining total variables
	int total_size = num_edges *2;
    int total_nums[num_edges][2]; 
 
	// separating rows into arrays
	printf("The nodes are: \n");
	int val;

    for(count = 0; count < num_edges; count++){
    	// putting connections into rows
		inputFile >> total_nums[count][0];
    	inputFile >> total_nums[count][1];
       	printf("%d %d\n",total_nums[count][0],total_nums[count][1]);
		
	}

	// determining amount of cuts
	int d[num_nodes+1];
	// making d all zeros
	for (int i=0; i < (num_nodes+1); i++) {
		d[i]= 0;
	}
	// running through total_nums
	for(int k = 0; k < num_edges; k++) {
		int in_setA = 0;
		int in_setB = 0;
		int a_index = 0;
		int b_index = 0;
		// scanning set A
		for(int i = 0; i < sizeof_setA; i++) {
			// scaning set B
			for(int j = 0; j < sizeof_setB; j++){
				// see if left setA values are in setA or setB
				if ((total_nums[k][0] == setA[i] || total_nums[k][1] == setA[i]) && in_setA != 1){
					in_setA = 1;
					a_index = setA[i];
					break;
				}
				if ((total_nums[k][0] == setB[j] || total_nums[k][1] == setB[j]) && in_setB != 1){
					in_setB = 1;
					b_index = setB[j];
					break;
				}
			}
			if(in_setA && in_setB){
				break;
			}
		}
		// add to d if cut
		if(in_setA && in_setB){
			//total_nums[k] is cut
			d[a_index]++;
			d[b_index]++;
		} else { // subtract from d if not cut
			//total_nums[k] is not cut
			d[a_index]--;
			d[b_index]--;
		}	
	}
	
	// printing d values
	for (int i = 1; i < (num_nodes + 1); i++){
		printf("d(%d) = %d\n", i, d[i]);
	}
	printf("\n");
	
	// finding delta g		
	
    // Close the file.
	inputFile.close();
		
    return 0;
}
