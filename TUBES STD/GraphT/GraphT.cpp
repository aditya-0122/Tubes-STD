#include "GraphT.h"

const int MAX_VERTICES = 100; // Maksimal jumlah simpul dalam graph
const int INF = 1000000;      // Nilai besar untuk menggantikan infinity

// Inisialisasi graph
void initGraph(Graph& G) {
    firstVertex(G) = NULL;
}

// Membuat simpul baru
Vertex* createVertex(char id) {
    Vertex* newVertex = new Vertex;
    idVertex(newVertex) = id;
    firstEdge(newVertex) = NULL;
    nextVertex(newVertex) = NULL;
    return newVertex;
}

// Membuat edge baru
Edge* createEdge(char destVertexID, int weightTime, int weightCost) {
    Edge* newEdge = new Edge;
    destVertexID(newEdge) = destVertexID;
    weightTime(newEdge) = weightTime;
    weightCost(newEdge) = weightCost;
    nextEdge(newEdge) = NULL;
    return newEdge;
}

// Menambahkan simpul ke graph
void addVertex(Graph& G, Vertex* newVertex) {
    if (firstVertex(G) == NULL) {
        firstVertex(G) = newVertex;
    } else {
        Vertex* temp = firstVertex(G);
        while (nextVertex(temp) != NULL) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = newVertex;
    }
}

// Menambahkan edge ke simpul
void addEdge(Vertex* v, Edge* e) {
    if (firstEdge(v) == NULL) {
        firstEdge(v) = e;
    } else {
        Edge* temp = firstEdge(v);
        while (nextEdge(temp) != NULL) {
            temp = nextEdge(temp);
        }
        nextEdge(temp) = e;
    }
}

// Menghapus edge dari simpul
void deleteEdge(Vertex* v, char destVertexID) {
    Edge* prev = NULL;
    Edge* curr = firstEdge(v);

    while (curr != NULL && destVertexID(curr) != destVertexID) {
        prev = curr;
        curr = nextEdge(curr);
    }

    if (curr != NULL) {
        if (prev == NULL) {
            firstEdge(v) = nextEdge(curr);
        } else {
            nextEdge(prev) = nextEdge(curr);
        }
        delete curr;
    }
}

// Menghapus simpul dari graph
void deleteVertex(Graph& G, char vertexID) {
    Vertex* prev = NULL;
    Vertex* curr = firstVertex(G);

    while (curr != NULL && idVertex(curr) != vertexID) {
        prev = curr;
        curr = nextVertex(curr);
    }

    if (curr != NULL) {
        if (prev == NULL) {
            firstVertex(G) = nextVertex(curr);
        } else {
            nextVertex(prev) = nextVertex(curr);
        }

        // Hapus semua edge dari simpul ini
        Edge* edge = firstEdge(curr);
        while (edge != NULL) {
            Edge* toDelete = edge;
            edge = nextEdge(edge);
            delete toDelete;
        }
        delete curr;

        // Hapus semua edge yang mengarah ke simpul ini
        Vertex* temp = firstVertex(G);
        while (temp != NULL) {
            deleteEdge(temp, vertexID);
            temp = nextVertex(temp);
        }
    }
}

// Membersihkan seluruh graph
void cleanGraph(Graph& G) {
    Vertex* curr = firstVertex(G);
    while (curr != NULL) {
        Vertex* toDelete = curr;
        curr = nextVertex(curr);

        // Hapus semua edge dari simpul ini
        Edge* edge = firstEdge(toDelete);
        while (edge != NULL) {
            Edge* edgeToDelete = edge;
            edge = nextEdge(edge);
            delete edgeToDelete;
        }
        delete toDelete;
    }
    firstVertex(G) = NULL;
}

// Menampilkan graph
void printGraph(Graph& G) {
    Vertex* v = firstVertex(G);
    while (v != NULL) {
        cout << idVertex(v) << ":";
        Edge* e = firstEdge(v);
        while (e != NULL) {
            cout << " -> [" << destVertexID(e) << ", Waktu: " << weightTime(e) << ", Biaya: " << weightCost(e) << "]";
            e = nextEdge(e);
        }
        cout << endl;
        v = nextVertex(v);
    }
}

// Fungsi tambahan untuk mencari simpul berdasarkan ID
Vertex* findVertex(Graph& G, char id) {
    Vertex* temp = firstVertex(G);
    while (temp != NULL) {
        if (idVertex(temp) == id)
            return temp;
        temp = nextVertex(temp);
    }
    return NULL;
}

// Fungsi untuk mencari indeks simpul dalam array
int getVertexIndex(char vertices[], int vertexCount, char id) {
    for (int i = 0; i < vertexCount; ++i) {
        if (vertices[i] == id)
            return i;
    }
    return -1;
}

// Fungsi untuk mencari rute terbaik
void findBestRoute(Graph& G, char start, char end) {
    char vertices[100];
    int dist[100];
    char prev[100];
    bool visited[100];
    int vertexCount = 0;

    // Inisialisasi simpul
    Vertex* current = firstVertex(G);
    while (current != NULL) {
        vertices[vertexCount] = idVertex(current);
        dist[vertexCount] = (vertices[vertexCount] == start) ? 0 : INT_MAX;
        prev[vertexCount] = '\0'; // Belum ada simpul sebelumnya
        visited[vertexCount] = false; // Belum dikunjungi
        vertexCount++;
        current = nextVertex(current);
    }

    // Fungsi pembantu untuk mendapatkan indeks simpul berdasarkan ID
    auto getIndex = [&](char id) -> int {
        for (int i = 0; i < vertexCount; i++) {
            if (vertices[i] == id) return i;
        }
        return -1;
    };

    // Algoritma Dijkstra
    for (int i = 0; i < vertexCount; i++) {
        // Cari simpul dengan jarak minimum yang belum dikunjungi
        int minDist = INT_MAX, uIndex = -1;
        for (int j = 0; j < vertexCount; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                uIndex = j;
            }
        }

        if (uIndex == -1) break; // Tidak ada simpul yang bisa dikunjungi
        visited[uIndex] = true;

        char u = vertices[uIndex];
        Vertex* uVertex = firstVertex(G);
        while (uVertex != NULL && idVertex(uVertex) != u) {
            uVertex = nextVertex(uVertex);
        }

        if (uVertex == NULL) continue;

        Edge* edge = firstEdge(uVertex);
        while (edge != NULL) {
            char v = destVertexID(edge);
            int weight = weightTime(edge);
            int vIndex = getIndex(v);

            if (vIndex != -1 && dist[uIndex] != INT_MAX && dist[uIndex] + weight < dist[vIndex]) {
                dist[vIndex] = dist[uIndex] + weight;
                prev[vIndex] = u;
            }
            edge = nextEdge(edge);
        }
    }

    // Rekonstruksi jalur
    int endIndex = getIndex(end);
    if (endIndex == -1 || dist[endIndex] == INT_MAX) {
        cout << "Tidak ada jalur dari " << start << " ke " << end << ".\n";
        return;
    }

    char path[100];
    int pathLength = 0;
    for (char at = end; at != '\0'; at = prev[getIndex(at)]) {
        path[pathLength++] = at;
    }

    // Tampilkan hasil
    cout << "Jalur terbaik dari " << start << " ke " << end << ":\n";
    for (int i = pathLength - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << "\nTotal waktu: " << dist[endIndex] << " menit\n";
}

