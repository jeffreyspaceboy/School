#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
        std::vector<dim_t> D;//{(W,H),(H,W)}
        Block(std::vector<dim_t> new_D){
            D = new_D;
        }
        Block(int new_id, int new_x_size, int new_y_size, int orientation){
            id = new_id;
            dim_t dim(new_x_size, new_y_size);
            if(dim.size[0] <= dim.size[1] && orientation == V){
                D.push_back(dim);
                D.push_back(dim.reverse());
            }else{
                D.push_back(dim.reverse());
                D.push_back(dim);
            }
        }
        void print(){
            printf("%d: (%d %d),",id, D[0].size[0], D[0].size[1]);
            printf("(%d %d)\n", D[1].size[0], D[1].size[1]);
        }
        void print_all(){
            for(int i=0; i<D.size(); i++){
                printf("{%d %d} ", D[i].size[0], D[i].size[1]);
            }
            printf("\n");
        }
        // void flip_orientation(){
        //     for(int i=0; i<D.size(); i++){
        //         D[i] = D[i].reverse;
        //     }
        // }
};

std::vector<dim_t> v_stack(Block L, Block R){
    L.print_all();
    R.print_all();
    int l=0;
    int r=0;
    int max=0;
    std::vector<dim_t> results;
    while(l < L.D.size() && r < R.D.size()){
        if(L.D[l].size[1] > R.D[r].size[1]){
            max = L.D[l].size[1];
        }else{
            max = R.D[r].size[1];
        }
        dim_t new_dim(L.D[l].size[0]+R.D[r].size[0], max);
        bool push_en = true;
        for(int i=0; i<results.size(); i++){
            if(new_dim.same_as(results[i])){
                push_en = false;
            }
        }
        if(push_en){
            results.push_back(new_dim);
            //printf("%d %d\n",new_dim.size[0], new_dim.size[1]);
        }
        if(max == L.D[l].size[1]){
            l++;
        }
        if(max == R.D[r].size[1]){
            r++;
        }
    }
    return results;
}

std::vector<dim_t> h_stack(Block L, Block R){
    //L.flip_orientation();
    //R.flip_orientation();
    L.print_all();
    R.print_all();
    int l=0;
    int r=0;
    int max=0;
    std::vector<dim_t> results;
    while(l < L.D.size() && r < R.D.size()){
        if(L.D[l].size[0] > R.D[r].size[0]){
            max = L.D[l].size[0];
        }else{
            max = R.D[r].size[0];
        }
        dim_t new_dim(max, L.D[l].size[1]+R.D[r].size[1]);
        bool push_en = true;
        for(int i=0; i<results.size(); i++){
            if(new_dim.same_as(results[i])){
                push_en = false;
            }
        }
        if(push_en){
            results.push_back(new_dim);
            //printf("%d %d\n",new_dim.size[0], new_dim.size[1]);
        }
        
        if(max == L.D[l].size[0]){
            l++;
        }
        if(max == R.D[r].size[0]){
            r++;
        }
    }
    return results;
}



int main(){ // Main function int argc, char *argv[]
    std::fstream file("case.txt");//argv[1]);
    std::string tree_str;
    file >> tree_str;
    printf("%s\n",tree_str.c_str());
    int orientation[] = {V,H,H,V,V,V,H,H};
    int x_size, y_size;
    std::vector<Block> blocks;
    int i=0;
    while(!file.eof()){
        file >> x_size;
        file >> y_size;
        blocks.push_back(Block(blocks.size()+1, x_size, y_size, orientation[i]));
        blocks[blocks.size()-1].print();
        i++;
        //printf("%d %d\n",x_size, y_size);
    } 

    file.close();

    printf("\nA:\n");
    std::vector<dim_t> a = v_stack(blocks[0], blocks[4]);
    for(int i=0; i<a.size(); i++){
        a[i].print();
    }
    
    printf("\nB:\n");
    std::vector<dim_t> b = h_stack(blocks[1], blocks[7]);
    for(int i=0; i<b.size(); i++){
        b[i].print();
    }

    printf("\nC:\n");
    std::vector<dim_t> c = v_stack(Block(a), Block(b));
    for(int i=0; i<c.size(); i++){
        c[i].print();
    }

    printf("\nD:\n");
    std::vector<dim_t> d = v_stack(Block(c), blocks[3]);
    for(int i=0; i<d.size(); i++){
        d[i].print();
    }

    printf("\nF:\n");
    std::vector<dim_t> f = v_stack(Block(d), blocks[5]);
    for(int i=0; i<f.size(); i++){
        f[i].print();
    }
    
    printf("\nE:\n");
    std::vector<dim_t> e = h_stack(blocks[2], blocks[6]);
    for(int i=0; i<e.size(); i++){
        e[i].print();
    }

    printf("\nG:\n");
    std::vector<dim_t> g = h_stack(Block(e), Block(f));
    for(int i=0; i<g.size(); i++){
        g[i].print();
    }


    // printf("\n");
    // std::vector<dim_t> _L;
    // _L.push_back(dim_t(3,4));

    // std::vector<dim_t> _R;
    // _R.push_back(dim_t(20,3));
    // _R.push_back(dim_t(18,4));
    // _R.push_back(dim_t(13,5));
    // _R.push_back(dim_t(12,7));

    // Block L(_L);
    // Block R(_R);
    // std::vector<dim_t> test3 = h_stack(L, R);
    // for(int i=0; i<test3.size(); i++){
    //     test3[i].print();
    // }



    printf("--------------------------------------------------\n");

    return 0;
}

