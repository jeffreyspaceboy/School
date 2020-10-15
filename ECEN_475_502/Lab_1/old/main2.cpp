
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define MAX_SIZE 1000

class edge_t{
    public:
        int a_id;
        int b_id;
        int weight;
        bool cut;
    
        edge_t(int aID, int bID){
            a_id = aID;
            b_id = bID;
        }
        bool is_cut();
};

class node_t{
    public:
        int id;
        std::vector<edge_t> edges;
        int D;
        bool fixed;
    
        node_t(int new_id){
            id = new_id;
            fixed = false;
        }
        void set_id(int new_id){
            id = new_id;
        }
        void find_d();
        void add_edge(node_t b){
            edges.push_back(edge_t(id, b.id));
        }
};

class set_t{
    public:
        int num_nodes;
        int num_edges;
        std::vector<node_t> nodes;

        set_t(std::string filename){  
            std::fstream file(filename);
            file >> num_nodes;
            file >> num_edges;
            int i;
            for(i=0; i<num_nodes; i++){
                nodes.push_back(node_t(i));
            }
            int value[2];
            for(i=0; i<num_edges; i++){
                file >> value[0];
                file >> value[1];
                value[0] = find_node_index(value[0]);
                value[1] = find_node_index(value[1]);
                nodes[value[0]].add_edge(value[1]);
                nodes[value[1]].add_edge(value[0]);
                printf("%d,",nodes[value[0]].edges);
                printf("%d\n",edges[i].b);
            }
        }
        int find_node_index(int id){
            for(int i=0; i<nodes.size(); i++){
                if(id == nodes[i].id){
                    return i;
                }
            }
        }
};








//Given a graph, divide the vertices into two subsets of...
//...equal or nearly equal size.

//Cost = number of edges between the two subsets

bool is_cut(edge_t edge, node_t *A, node_t *B, int num_nodes){
    bool in_a = false;
    bool in_b = false;
    for(int i=0; i<(num_nodes/2); i++){
        for(int j=0; j<(num_nodes/2); j++){
            if(edge.a == A[i] || edge.b == A[i]){
                in_a = true;
            }
            if(edge.a == B[i] || edge.b == B[i]){
                in_b = true;
            }
        }
    }
    if(in_b && in_a){
        return  true;
    }
    return false;
}

bool has_edge(edge_t *edges, node_t a, node_t b, int num_edges){
    for(int i=0; i<num_edges; i++){
        if(edges->a == a && edges->b == b){
            return true;
        }else if(edges->a == b && edges->b == a){
            return true;
        }
    }
    return false;
}


int main(){ //int argc, char *argv[]
    // std::fstream file("case0.txt");

    // int num_nodes;
    // int num_edges;
    // file >> num_nodes;
    // file >> num_edges;
    // printf("Nodes: %d, Edges: %d\n",num_nodes, num_edges);

    node_t A[num_nodes/2];
    node_t B[num_nodes/2];
    edge_t edges[num_edges];
    int D[num_nodes+1];

    int i;
    for(i=0; i<(num_nodes/2); i++){
        A[i] = i+1;
        B[i] = (num_nodes/2)+(i+1);
        printf("%d,%d\n",A[i],B[i]);
        D[i+1] = 0;
        D[(num_nodes/2)+(i+1)] = 0;
    }
    printf("\n");
    int value[2];
    for(i=0; i<num_edges; i++){
        file >> value[0];
        file >> value[1];
        edges[i].a = value[0];
        edges[i].b = value[1];
        printf("%d,",edges[i].a);
        printf("%d\n",edges[i].b);
    }
    //     edges[i].cut = is_cut(edges[i], A, B, num_nodes);
    //     if(edges[i].cut){
    //         D[(edges[i].a)] += 1;  
    //         D[(edges[i].b)] += 1;
    //     }else{
    //         D[(edges[i].a)] -= 1;  
    //         D[(edges[i].b)] -= 1;
    //     }
    // }

    // int gv[num_nodes+1];
    // int av[num_nodes+1];
    // int bv[num_nodes+1];
    // for(int n=1; n <= (num_nodes/2); n++){
    //     if(has_edge(edges, a, b, num_edges)){
    //         return D[a] + D[b] - (2*1); 
    //     }else{
    //         return D[a] + D[b] - (2*0); 
    //     }
    // }

    

    // file.close();
    // printf("\n");

    // for(i=1; i<(num_nodes+1); i++){
    //     printf("%d\n",D[i]);
    // }

}

//dGi = D(ai)+D(bi)-2*c(ai*bi)




// void kernighan_lin(node_t *nodes, edge_t *edges){
//     //Split set into A and B
//     while(g_max > 0){
//         //Compute D values for all a in A and b in B

        
//         int gv[];//let gv, av, and bv be empty lists
//         int av[];
//         int bv[];
//         for(int n=1; n <= |V|/2; n++){
//             find a from A and b from B, such that g = D[a] + D[b] − 2×c(a, b) is maximal

//             remove a and b from further consideration in this pass

//             add g to gv, a to av, and b to bv

//             update D values for the elements of A = A \ a and B = B \ b
//         }
//         find k which maximizes g_max, the sum of gv[1], ..., gv[k]
//         if(g_max > 0){
//             Exchange av[1], av[2], ..., av[k] with bv[1], bv[2], ..., bv[k]
//         }
//     }

//     return G(V, E);
// }