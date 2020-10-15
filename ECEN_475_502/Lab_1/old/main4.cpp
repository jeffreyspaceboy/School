#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
Title: Lab 1 - Kernighan-Lin (KL) Algorithm 
Author: Jeffrey Fisher II 
Class: ECEN-457-502
Due Date: 9/15/2020
*/

typedef int node_t; //Node Type

typedef struct { //Edge Type
    node_t a;
    node_t b;
    bool cut;
} edge_t;

edge_t create_edge(node_t new_a, node_t new_b);
bool is_cut(edge_t edge, std::vector<node_t> A, std::vector<node_t> B);
bool has_edge(std::vector<edge_t> edges, node_t a, node_t b);
bool has_node(std::vector<node_t> nodes, node_t node);

int main(int argc, char *argv[]){ // Main function
    printf("Opening File: %s\n\n", argv[1]);
    std::fstream file(argv[1]);
    int num_nodes;
    int num_edges;
    file >> num_nodes;//First line of file
    file >> num_edges;
    printf("Nodes: %d, Edges: %d\n",num_nodes, num_edges);
    printf("\n");
    std::vector<node_t> A;//Two subsets
    std::vector<node_t> B;
    printf("A,B:\n");
    for(int i=0; i<(num_nodes/2); i++){ //Generate the two subsets
        A.push_back(i+1);
        B.push_back((num_nodes/2)+(i+1));
        printf("%d,%d\n",A[i],B[i]);
    }
    printf("\n");

    std::vector<edge_t> edges; //Edge vector
    std::vector<int> D; //D vector
    for(int i=0; i<=num_nodes; i++){
        D.push_back(0); //Clearing D values
    }

    int value[2];
    printf("Edges:\n");
    for(int i=0; i < num_edges; i++){
        file >> value[0];//Fill edges vector
        file >> value[1];
        edges.push_back(create_edge(value[0], value[1]));
        printf("%d,%d\n",edges[i].a,edges[i].b);

        edges[i].cut = is_cut(edges[i], A, B); //Determine if vectors are cut
        if(edges[i].cut){ //Calculate D based on cut/uncut edges
            D[edges[i].a] += 1;  
            D[edges[i].b] += 1;
        }else{
            D[edges[i].a] -= 1;  
            D[edges[i].b] -= 1;
        }
    }
    file.close();
    printf("\n");

    for(int i = 0; i < D.size(); i++){ //Show D
        if(has_node(A, i) || has_node(B, i)){
            printf("D(%d): %d\n",i, D[i]);
        }
    }
    printf("\n");

    
    std::vector<int> gv; //Running gain list
    std::vector<node_t> av; //New Subsets
    std::vector<node_t> bv;
    
    int G = 0;
    int k = 0;
    bool start = true;
    while(G > 0 || start == true){ //Loop until result
        int ai, bi;
        int dg = 0;
        int test_g = 0;
        for(int a=0; a< A.size(); a++){
            for(int b=0; b< B.size(); b++){
                if(has_edge(edges, A[a], B[b])){ //Calculate G for all node combinations
                    test_g = D[A[a]] + D[B[b]] - (2*1);
                }else{
                    test_g = D[A[a]] + D[B[b]];
                }
                printf("A:%d  B:%d  g:%d\n",A[a],B[b],dg);
                if(test_g >= dg && (D[A[a]] >= D[B[b]])){ //Find highest g
                    ai = a;
                    bi = b;
                    dg = test_g;
                }
            }
        }
        printf("Selected: A:%d  B:%d  g:%d\n",A[ai], B[bi], dg);
        //printf("\n");
        
        gv.push_back(dg); //Add g to list
        av.push_back(A[ai]);//Add selected A and B to the new Subsets
        bv.push_back(B[bi]);

        if(G >= 0){ //If the loop is not complete:
            A.erase(A.begin()+ai); //Remove a and b from original subsets
            B.erase(B.begin()+bi);
            int previous_G = G;
            G += gv[gv.size()-1];
            start = false;
            if(G >= previous_G){
                previous_G = G;
                k = (gv.size()-1);
            }
            printf("G: %d\n",G);
        }
        
        for(int i=0; i < num_edges; i++){ //Re-calculate D's
            edges[i].cut = is_cut(edges[i], A, B);
            if(edges[i].cut){
                D[(edges[i].a)] += 1;  
                D[(edges[i].b)] += 1;
            }else{
                D[(edges[i].a)] -= 1;  
                D[(edges[i].b)] -= 1;
            }
        }   

        for(int i = 0; i < D.size(); i++){ //Print out D's
            if(has_node(A, i) || has_node(B, i)){
                printf("D(%d): %d\n",i, D[i]);
            }
        }
        printf("\n");
    }
    return 0;
}


edge_t create_edge(node_t new_a, node_t new_b){ //Create an edge
    edge_t new_edge;
    new_edge.a = new_a;
    new_edge.b = new_b;
    return new_edge;
}

bool is_cut(edge_t edge, std::vector<node_t> A, std::vector<node_t> B){ //check if an edge is cut
    bool in_a = false;
    bool in_b = false;
    for(int a=0; a< A.size(); a++){
        for(int b=0; b< B.size(); b++){
            if(edge.a == A[a] || edge.b == A[a]){
                in_a = true;
            }
            if(edge.a == B[b] || edge.b == B[b]){
                in_b = true;
            }
        }
    }
    if(in_b && in_a){
        return  true;
    }
    return false;
}

bool has_edge(std::vector<edge_t> edges, node_t a, node_t b){//Check if there is an edge between nodes
    for(int i=0; i<edges.size(); i++){
        if(edges[i].a == a && edges[i].b == b){
            return true;
        }else if(edges[i].a == b && edges[i].b == a){
            return true;
        }
    }
    return false;
}

bool has_node(std::vector<node_t> nodes, node_t node){//Check if a certain node exists in a list
    for(int i=0; i<nodes.size();i++){
        if(node == nodes[i]){
            return true;
        }
    }
    return false;
}