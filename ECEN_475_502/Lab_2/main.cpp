#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

/*
Title: Lab 2 - Stockmeyer Algorithm
Author: Jeffrey Fisher II 
Class: ECEN-457-502
Due Date: 10/13/2020
*/

#define H 0
#define V 1

class dim_t{ //Class used to store a set of dimentions.
    public:
        int size[2]; //(Width, Height)
        dim_t(){ //Default Constructor.
            size[0] = 0;
            size[1] = 0;
        }
        dim_t(int w, int h){ //Standard Constructor.
            size[0] = w;
            size[1] = h;
        }
        dim_t reverse(){ //Return reversed dimentions.
            dim_t new_dim(size[1], size[0]);
            return new_dim;
        }
        int area(){ //Returns area of dim
            return size[0]*size[1];
        }
        void print(){ //Print out the dimentions.
            printf("(%d %d)\n", size[0], size[1]);
        }
};

class Block{ //Class used to store the information pertaining to a Node.
    public:
        int id; //Identification number.
        std::vector<dim_t> D; //A vector of multiple potential dimentions. 
        Block(){} //Default Constructor.
        Block(std::vector<dim_t> new_D){ //Constructor with vector.
            D = new_D;
        }
        Block(int new_id, int new_x_size, int new_y_size){ //Constructor with default size.
            id = new_id;
            dim_t dim(new_x_size, new_y_size);
            D.push_back(dim); //Add original dim...
            D.push_back(dim.reverse()); //...and reversed dim.
        }
        dim_t find_min(){
            int area = 1000;
            dim_t result;
            for(int i=0; i<D.size(); i++){
                if(D[i].area() < area){
                    area = D[i].area();
                    result = D[i];
                }
            }
            return result;
        }
        void print(){ //Print Default dims
            printf("%d: (%d %d),(%d %d)\n",id, D[0].size[0], D[0].size[1], D[1].size[0], D[1].size[1]);
        }
        void print_all(std::string name){ //Print all dims
            printf(" %s:",name.c_str());
            for(int i=0; i<D.size(); i++){
                printf("{%d %d} ", D[i].size[0], D[i].size[1]);
            }
            printf("\n");
        }
};

bool v_compare(dim_t A, dim_t B){ //Compare two dims for vertical
    return (A.size[0] < B.size[0]);
}

bool h_compare(dim_t A, dim_t B){ //Compare two dims for vertical
    return (A.size[0] > B.size[0]);
}

Block v_stack(Block L, Block R){ //Algorithm for v_stacks
    sort(L.D.begin(), L.D.end(), v_compare); //Sort for vertical stacks
    sort(R.D.begin(), R.D.end(), v_compare);
    L.print_all("L");
    R.print_all("R");
    int l=0;
    int r=0;
    std::vector<dim_t> results; //Vector of dims
    while(l < L.D.size() && r < R.D.size()){ //While not out of dims
        dim_t new_dim(L.D[l].size[0]+R.D[r].size[0], std::max(L.D[l].size[1], R.D[r].size[1]));
        results.push_back(new_dim); //Calculate and add new potential dim
        if(L.D[l].size[1] > R.D[r].size[1]){ l++; }else{ r++; } //Increment r or l based on max
    }
    return Block(results);
}

Block h_stack(Block L, Block R){ //Algorithm for h_stacks
    sort(L.D.begin(), L.D.end(), h_compare); //Sort for horizontal stacks
    sort(R.D.begin(), R.D.end(), h_compare);
    L.print_all("L");
    R.print_all("R");
    int l=0;
    int r=0;
    std::vector<dim_t> results; //Vector of dims
    while(l < L.D.size() && r < R.D.size()){ //While not out of dims
        dim_t new_dim(std::max(L.D[l].size[0], R.D[r].size[0]), L.D[l].size[1]+R.D[r].size[1]);
        results.push_back(new_dim); //Calculate and add new potential dim
        if(L.D[l].size[0] > R.D[r].size[0]){ l++; }else{ r++; } //Increment r or l based on max
    }
    return Block(results);
}

int main(int argc, char *argv[]){ // Main function 
    std::fstream file(argv[1]);
    std::string tree_str;
    file >> tree_str;
    printf("%s\n",tree_str.c_str());

    int x_size, y_size;
    std::vector<Block> blocks;
    while(!file.eof()){
        file >> x_size;
        file >> y_size;
        blocks.push_back(Block(blocks.size()+1, x_size, y_size));
        blocks[blocks.size()-1].print();
    } 
    file.close();

    //TODO: USE POLISH EXPRESSION INSTEAD \/
    printf("\nA:\n");
    Block a = v_stack(blocks[0], blocks[4]);
    a.print_all("D");
    
    printf("\nB:\n");
    Block b = h_stack(blocks[1], blocks[7]);
    b.print_all("D");

    printf("\nC:\n");
    Block c = v_stack(a,b);
    c.print_all("D");

    printf("\nD:\n");
    Block d = v_stack(c, blocks[3]);
    d.print_all("D");

    printf("\nF:\n");
    Block f = v_stack(d, blocks[5]);
    f.print_all("D");
    
    printf("\nE:\n");
    Block e = h_stack(blocks[2], blocks[6]);
    e.print_all("D");

    printf("\nG:\n");
    Block g = h_stack(e,f);
    g.print_all("D");

    printf("\nFinal Area:\n");
    dim_t final = g.find_min();
    final.print();

    printf("\n--------------------------------------------------\n");
    return 0;
}

