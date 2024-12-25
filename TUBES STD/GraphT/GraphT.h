#ifndef GRAPHT_H_INCLUDED
#define GRAPHT_H_INCLUDED

#include <iostream>

using namespace std;

#define firstVertex(G) (G.firstVertex)
#define nextVertex(v) (v->nextVertex)
#define firstEdge(v) (v->firstEdge)
#define idVertex(v) (v->idVertex)
#define destVertexID(e) (e->destVertexID)
#define weightTime(e) (e->weightTime)
#define weightCost(e) (e->weightCost)
#define nextEdge(e) (e->nextEdge)

struct Edge {
    char destVertexID;
    int weightTime;
    int weightCost;
    Edge* nextEdge;
};

struct Vertex {
    char idVertex;
    Edge* firstEdge;
    Vertex* nextVertex;
};

struct Graph {
    Vertex* firstVertex;
};

// Prototipe fungsi-fungsi
void initGraph(Graph& G);
Vertex* createVertex(char id);
Edge* createEdge(char destVertexID, int weightTime, int weightCost);
void addVertex(Graph& G, Vertex* newVertex);
void addEdge(Vertex* v, Edge* e);
void deleteEdge(Vertex* v, char destVertexID);
void deleteVertex(Graph& G, char vertexID);
void cleanGraph(Graph& G);
void printGraph(Graph& G);
void findBestRoute(Graph& G, char start, char end);
#endif // GRAPHT_H_INCLUDED
