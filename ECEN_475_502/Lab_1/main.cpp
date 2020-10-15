#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
Title: Lab 1 - Kernighan-Lin (KL) Algorithm 
Author: Jeffrey Fisher II 
Class: ECEN-457-502
Due Date: 9/16/2020
*/

class Edge{ 
    public:
        int node1_id;
        int node2_id;
        bool cut;
        int delt_g;
        Edge(int id_1, int id_2, bool is_cut){
            node1_id = id_1;
            node2_id = id_2;
            cut = is_cut;
        }

        void print_edge(){
            printf("%d %d\n",node1_id,node2_id);
        }
}; //Edge

class Node{
    public:
        int id;
        int D;
        bool fixed;
        std::vector<Edge> edges;
        Node(int new_id){
            id = new_id;
            D = 0;
            fixed = false;
        }
        Node(const Node &obj){
            id = obj.id;
            D = obj.D;
            fixed = obj.fixed;
            edges = obj.edges;
        }

        int find_d(){
            int num_cut = 0;
            D = 0;
            for(int i=0; i<edges.size(); i++){
                if(edges[i].cut){ 
                    D++; 
                    num_cut++;
                } else{ 
                    D--; 
                }
            }
            
            return D;
        }
        int has_edge(int id_1, int id_2){
            for(int i=0; i<edges.size(); i++){
                if(edges[i].node1_id == id_1 && edges[i].node2_id == id_2){
                    return 1;
                }else if(edges[i].node1_id == id_2 && edges[i].node2_id == id_1){
                    return 1;
                }
            }
            return 0;
        }
        int get_edge(int id_1, int id_2){
            for(int i=0; i<edges.size(); i++){
                if(edges[i].node1_id == id_1 && edges[i].node2_id == id_2){
                    return i;
                }else if(edges[i].node1_id == id_2 && edges[i].node2_id == id_1){
                    return i;
                }
            }
            return -1;
        }

        void print_id(){
            printf("%d\n",id);
        }
        void print_d(){
            printf("%d",D);
        }
}; //Node

class Set{
    public:
        std::vector<Node> nodes;
        Set(){}
        void push_back(int new_id){
            Node new_node(new_id);
            nodes.push_back(new_node);
        }
        bool is_cut(int id_1, int id_2){
            int has_id[2] = {0,0};
            for(int i=0; i<nodes.size(); i++){
                if(nodes[i].id == id_1){ has_id[0] = 1; }
                if(nodes[i].id == id_2){ has_id[1] = 1; }
            }
            if(has_id[0] && has_id[1]){ return false; }
            return true;
        }
        void refresh_edges(){
            for(int i=0; i<nodes.size(); i++){ 
                for(int j=0; j<nodes[i].edges.size(); j++){
                    nodes[i].edges[j].cut = is_cut(nodes[i].edges[j].node1_id, nodes[i].edges[j].node2_id);
                } 
            }
        }
        void push_edge(int id_1, int id_2){
            Edge new_edge(id_1, id_2, is_cut(id_1, id_2));
            for(int i=0; i<nodes.size(); i++){
                if(nodes[i].id == id_1){ 
                    nodes[i].edges.push_back(new_edge); 
                }
                if(nodes[i].id == id_2){ 
                    nodes[i].edges.push_back(new_edge); 
                }
            }  
        }
        void find_d(){
            for(int i=0; i<nodes.size(); i++){
                //if(!nodes[i].fixed){
                nodes[i].find_d();
                //}
            }
        }
        void print_d(){
            for(int i=0; i<nodes.size(); i++){
                if(!nodes[i].fixed){
                    printf("D(%d): %d\n",nodes[i].id,nodes[i].D);
                }
            }
        }
}; //Set

bool is_in_cut_edges(Edge edge_to_test, std::vector<Edge> cut_edges){
    for(int k=0; k<cut_edges.size(); k++){
        if(edge_to_test.node1_id == cut_edges[k].node1_id && edge_to_test.node2_id == cut_edges[k].node2_id){
            return true;
        }
        if(edge_to_test.node1_id == cut_edges[k].node2_id && edge_to_test.node2_id == cut_edges[k].node1_id){
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]){ // Main function
    std::fstream file(argv[1]);
    int num_nodes, num_edges;
    file >> num_nodes;//First line of file
    file >> num_edges;
    Set A;//Two subsets
    Set B;

    for(int i=0; i<(num_nodes/2); i++){ //Generate the two subsets
        A.push_back(i+1);
        B.push_back((num_nodes/2)+(i+1));
    }


    int value[2];
    for(int i=0; i < num_edges; i++){
        file >> value[0];//Fill edges vector
        file >> value[1];
        A.push_edge(value[0], value[1]);
        B.push_edge(value[0], value[1]);
    }
    file.close();

    //Calculating D
    A.find_d();
    B.find_d();
    std::vector<Set> As;
    std::vector<Set> Bs;

    int g = 0;
    int max_gain = 0;
    int key_node_idx[2] = {0,0};

    int G = 1;//max_gain;
    std::vector<int> Gs;
    
    bool all_fixed = false;

    while(G > 0 || all_fixed){
        A.find_d();
        B.find_d();
        g = 0;
        max_gain = 0;
        for(int i=0; i<A.nodes.size(); i++){
            for(int j=0; j<B.nodes.size(); j++){
                if(!A.nodes[i].fixed && !B.nodes[j].fixed ){
                    g = A.nodes[i].D + B.nodes[j].D - 2*A.nodes[i].has_edge(A.nodes[i].id, B.nodes[j].id);
                    if(abs(g)>abs(max_gain)){
                        max_gain = g;
                        key_node_idx[0] = i;
                        key_node_idx[1] = j;
                    }
                }
            }
        }
        Node temp = A.nodes[key_node_idx[0]]; 
        A.nodes[key_node_idx[0]] = B.nodes[key_node_idx[1]]; 
        B.nodes[key_node_idx[1]] = temp;
        A.nodes[key_node_idx[0]].fixed = true;
        B.nodes[key_node_idx[1]].fixed = true;
        A.refresh_edges();
        B.refresh_edges();
        
        
        
        if(Gs.size()>0){
            G = Gs[Gs.size()-1] + max_gain;
        }else{
            G = max_gain;
        }
        Gs.push_back(G);
        As.push_back(A);
        Bs.push_back(B);
        
        int fixed_sum = 0;
        for(int i=0; i<A.nodes.size(); i++){
            if(A.nodes[i].fixed){
                fixed_sum++; 
            } 
        }
        for(int i=0; i<B.nodes.size(); i++){
            if(B.nodes[i].fixed){
                fixed_sum++; 
            } 
        }
        if(fixed_sum == num_nodes){
            fixed_sum = true;
        }
    }
    int max = 0;
    int idx = 0;
    for(int i=0; i<Gs.size(); i++){
        if(Gs[i]>max){
            max = Gs[i];
            idx = i;
        }
    }
    printf("\nFinal Partitioned Sets:\n");
    for(int i=0; i<As[idx].nodes.size(); i++){ //Generate the two subsets
        printf("A:%d  B:%d\n",As[idx].nodes[i].id, Bs[idx].nodes[i].id);
    }
    std::vector<Edge> cut_edges;
    for(int i=0; i<As[idx].nodes.size(); i++){
        for(int k=0; k<As[idx].nodes[i].edges.size(); k++){
            if(!is_in_cut_edges(As[idx].nodes[i].edges[k], cut_edges) && As[idx].nodes[i].edges[k].cut == true){
                cut_edges.push_back(As[idx].nodes[i].edges[k]);
            }
        }
    }
    for(int j=0; j<Bs[idx].nodes.size(); j++){
        for(int k=0; k<Bs[idx].nodes[j].edges.size(); k++){
            if(!is_in_cut_edges(Bs[idx].nodes[j].edges[k], cut_edges) && Bs[idx].nodes[j].edges[k].cut == true){
                cut_edges.push_back(Bs[idx].nodes[j].edges[k]);
            }
        }
    }
    printf("\nFinal Cut Edges: \n");
    for(int k=0; k<cut_edges.size(); k++){
        cut_edges[k].print_edge();
    }
    printf("\n");

    return 0;
}

