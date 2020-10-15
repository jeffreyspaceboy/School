#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

/*
Title: Lab 2 - Stockmeyer Algorithm
Author: Jeffrey Fisher II 
Class: ECEN-457-502
Due Date: 10/14/2020
*/

#define H 0
#define V 1

class dim_t{
    public:
        int size[2];
        dim_t(){
            size[0] = 0;
            size[1] = 0;
        }
        dim_t(int w, int h){
            size[0] = w;
            size[1] = h;
        }
        dim_t reverse(){
            dim_t new_dim(size[1], size[0]);
            return new_dim;
        }
        void print(){
            printf("(%d %d)\n", size[0], size[1]);
        }
        bool same_as(dim_t check){
            if(size[0] == check.size[0] && size[1] == check.size[1]){
                return true;
            }
            return false;
        }
};

class Block{
    public:
        int id;
        char name;
        std::vector<dim_t> D;//{(W,H),(H,W)}
        Block(){}
        Block(std::vector<dim_t> new_D){
            D = new_D;
        }
        Block(char new_name, std::vector<dim_t> new_D){
            name = new_name;
            D = new_D;
        }
        Block(int new_id, int new_x_size, int new_y_size){
            id = new_id;
            dim_t dim(new_x_size, new_y_size);
            D.push_back(dim);
            D.push_back(dim.reverse());
        }
        void print(){
            printf("%d: (%d %d),(%d %d)\n",id, D[0].size[0], D[0].size[1], D[1].size[0], D[1].size[1]);
        }
        void print_all(std::string name){
            printf(" %s:",name.c_str());
            for(int i=0; i<D.size(); i++){
                printf("{%d %d} ", D[i].size[0], D[i].size[1]);
            }
            printf("\n");
        }
};

bool v_compare(dim_t A, dim_t B){
    return (A.size[0] < B.size[0]);
}

bool h_compare(dim_t A, dim_t B){
    return (A.size[0] > B.size[0]);
}

Block v_stack(Block L, Block R){
    sort(L.D.begin(), L.D.end(), v_compare);
    sort(R.D.begin(), R.D.end(), v_compare);
    L.print_all("L");
    R.print_all("R");
    int l=0;
    int r=0;
    std::vector<dim_t> results;
    while(l < L.D.size() && r < R.D.size()){
        dim_t new_dim(L.D[l].size[0]+R.D[r].size[0], std::max(L.D[l].size[1], R.D[r].size[1]));
        results.push_back(new_dim); 
        if(L.D[l].size[1] > R.D[r].size[1]){ l++; }else{ r++; }
    }
    Block result(results);
    return result;
}

Block h_stack(Block L, Block R){
    sort(L.D.begin(), L.D.end(), h_compare);
    sort(R.D.begin(), R.D.end(), h_compare);
    L.print_all("L");
    R.print_all("R");
    int l=0;
    int r=0;
    std::vector<dim_t> results;
    while(l < L.D.size() && r < R.D.size()){
        dim_t new_dim(std::max(L.D[l].size[0], R.D[r].size[0]), L.D[l].size[1]+R.D[r].size[1]);
        results.push_back(new_dim);
        if(L.D[l].size[0] > R.D[r].size[0]){ l++; }else{ r++; }
    }
    Block result(results);
    return result;
}


Block full_block_replace(std::vector<Block> blocks, char block_name, std::string tree_str){
    if(block_name == 'V' || block_name == 'H'){
        printf("ERROR: Invalid block name");
    }
    int block_kind = -1;
    int i, a, b;
    for(i=0; i<tree_str.size(); i++){
        if(isdigit(tree_str[i]) && isdigit(tree_str[i+2])){
            printf("%c, %c, %c\n",tree_str[i], tree_str[i+2], tree_str[i+4]);
            a = i;
            b = i+2;
            if(tree_str[i+4] == 'V'){
                block_kind = V;
                break;
            }else if(tree_str[i+4] == 'H'){
                block_kind = H;
                break;
            }
            
        }
    }
    for(int j=0; j<4; j++){
        tree_str.erase(tree_str.begin()+i); 
    }
    tree_str[0] = block_name;
    printf("%s\n",tree_str.c_str());
    if(block_kind == V){
        Block L(blocks[a].D);
        Block R(blocks[b].D);
        Block new_block = v_stack(L, R);
        new_block.name = block_name;
        return new_block;
    }else if(block_kind == H){
        Block L(blocks[a].D);
        Block R(blocks[b].D);
        Block new_block = h_stack(L, R);
        new_block.name = block_name;
        return new_block;
    }

    Block new_block;
    return new_block;
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


    full_block_replace(blocks, 'A', tree_str);
    


    //TODO: USE POLISH EXPRESSION
    // for(int i=0; i < tree_str.size(); i++){
    //     if(isdigit(tree_str[i])){

    //     }
        
    //     // blocks[(tree_str[j]-'0')-1] 
    //     // blocks[(tree_str[j]-'0')-1]
    // } 

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

    printf("--------------------------------------------------\n");

    return 0;
}

