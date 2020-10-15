
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef int node_t;

typedef struct {
    node_t a;
    node_t b;
    bool cut;
} edge_t;

edge_t create_edge(node_t new_a, node_t new_b){
    edge_t new_edge;
    new_edge.a = new_a;
    new_edge.b = new_b;
    return new_edge;
}

bool is_cut(edge_t edge, std::vector<node_t> A, std::vector<node_t> B){
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

bool has_edge(std::vector<edge_t> edges, node_t a, node_t b){
    for(int i=0; i<edges.size(); i++){
        if(edges[i].a == a && edges[i].b == b){
            return true;
        }else if(edges[i].a == b && edges[i].b == a){
            return true;
        }
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

    std::vector<node_t> A;
    std::vector<node_t> B;

    for(int i=0; i<(num_nodes/2); i++){
        A.push_back(i+1);
        B.push_back((num_nodes/2)+(i+1));
        printf("%d,%d\n",A[i],B[i]);
    }
    printf("\n");

    std::vector<edge_t> edges;
    std::vector<int> D;
    for(int i=0; i<=num_nodes; i++){
        D.push_back(0);
    }

    int value[2];
    for(int i=0; i < num_edges; i++){
        file >> value[0];
        file >> value[1];
        edges.push_back(create_edge(value[0], value[1]));
        printf("%d,%d\n",edges[i].a,edges[i].b);

        edges[i].cut = is_cut(edges[i], A, B);
        if(edges[i].cut){
            D[(edges[i].a)] += 1;  
            D[(edges[i].b)] += 1;
        }else{
            D[(edges[i].a)] -= 1;  
            D[(edges[i].b)] -= 1;
        }
    }
    file.close();
    printf("\n");

    for(int i=1; i<D.size(); i++){
        printf("D: %d\n",D[i]);
    }
    printf("\n");
    int g = 0;
    int test_g = 0;
    int ai, bi;
    std::vector<int> gv;
    std::vector<node_t> av;
    std::vector<node_t> bv;
    int g_max = 0;
    int G = 0;
    int k = 0;
    bool start = true;
    while(G > 0 || start == true){
        for(int a=0; a< A.size(); a++){
            for(int b=0; b< B.size(); b++){
                if(has_edge(edges, A[a], B[b])){
                    test_g = D[A[a]] + D[B[b]] - (2*1);
                }else{
                    test_g = D[A[a]] + D[B[b]];
                }
                printf("A: %d B: %d g: %d\n",A[a],B[b],test_g);
                if(test_g >= g){
                    g = test_g;
                    ai = a;
                    bi = b;
                }
            }
        }
        //printf("\n");
        printf("Selected: A: %d B: %d g: %d\n",A[ai], B[bi], g);
        gv.push_back(g);
        av.push_back(A[ai]);
        bv.push_back(B[bi]);

        A.erase(A.begin()+ai); 
        B.erase(B.begin()+bi);

        for(int i=0; i < num_edges; i++){
            edges[i].cut = is_cut(edges[i], A, B);
            if(edges[i].cut){
                D[(edges[i].a)] += 1;  
                D[(edges[i].b)] += 1;
            }else{
                D[(edges[i].a)] -= 1;  
                D[(edges[i].b)] -= 1;
            }
        }   

        for(int i=1; i<D.size(); i++){
            printf("D: %d\n",D[i]);
        }

        int previous_G = G;
        for(int i=0; i < gv.size(); i++){
            G += gv[i];
            start = false;
            if(G >= previous_G){
                previous_G = G;
                k = i;
            }
        }
        printf("G: %d\n",G);
        printf("\n");
    }
    

    return 0;
}


// void kernighan_lin(node_t *nodes, edge_t *edges){
//     determine a balanced initial partition of the nodes into sets A and B
    
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