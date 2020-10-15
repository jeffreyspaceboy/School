
#include <iostream>
#include <fstream>
#include <string>

typedef int node_t;

typedef struct {
    node_t a;
    node_t b;
    bool cut;
} edge_t;

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


int main(){ //int argc, char *argv[]
    std::fstream file("case0.txt");

    int num_nodes;
    int num_edges;
    file >> num_nodes;
    file >> num_edges;
    printf("Nodes: %d, Edges: %d\n",num_nodes, num_edges);

    node_t *A = (node_t*)malloc((num_nodes/2) * sizeof(node_t));
    node_t *B = (node_t*)malloc((num_nodes/2) * sizeof(node_t));
    int i;
    for(i=0; i<(num_nodes/2); i++){
        A[i] = i+1;
        B[i] = (num_nodes/2)+(i+1);
        printf("%d,%d\n",A[i],B[i]);
    }
    printf("\n");

    edge_t *edges = (edge_t*)malloc((num_edges) * sizeof(edge_t));
    int *D = (int*)malloc((num_nodes+1) * sizeof(int));
    for(i=1; i<=(num_nodes+1); i++){
        D[i] = 0;
    }

    int value;
    i=0;
    while(i < num_edges){
        file >> edges[i].a;
        printf("%d,",edges[i].a);
        file >> edges[i].b;
        printf("%d\n",edges[i].b);
        edges[i].cut = is_cut(edges[i], A, B, num_nodes);
        if(edges[i].cut){
            D[(edges[i].a)] += 1;  
            D[(edges[i].b)] += 1;
        }else{
            D[(edges[i].a)] -= 1;  
            D[(edges[i].b)] -= 1;
        }
        i++;
    }
    file.close();
    printf("\n");

    for(i=1; i<(num_nodes+1); i++){
        printf("%d\n",D[i]);
    }

    

    free(A);
    free(B);
    free(edges);
    free(D);
}

dGi = D(ai)+D(bi)-2*c(ai*bi)



// void kernighan_lin(node_t *nodes, edge_t *edges){
//$     determine a balanced initial partition of the nodes into sets A and B
    
//     while(g_max > 0){
//         compute D values for all a in A and b in B

//         let gv, av, and bv be empty lists
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