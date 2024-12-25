#include "GraphT.h"

int main() {
    Graph G;
    initGraph(G);

    // Hardcoded untuk simpul
    Vertex* v1 = createVertex('A');
    Vertex* v2 = createVertex('B');
    Vertex* v3 = createVertex('C');
    Vertex* v4 = createVertex('D');
    Vertex* v5 = createVertex('E');
    addVertex(G, v1);
    addVertex(G, v2);
    addVertex(G, v3);
    addVertex(G, v4);
    addVertex(G, v5);

    // Hardcoded untuk edge bidirectional
    addEdge(v1, createEdge('B', 10, 5));
    addEdge(v2, createEdge('A', 10, 5));

    addEdge(v1, createEdge('C', 15, 8));
    addEdge(v3, createEdge('A', 15, 8));

    addEdge(v2, createEdge('D', 20, 12));
    addEdge(v4, createEdge('B', 20, 12));

    addEdge(v3, createEdge('D', 25, 18));
    addEdge(v4, createEdge('C', 25, 18));

    addEdge(v4, createEdge('E', 5, 2));
    addEdge(v5, createEdge('D', 5, 2));

    int choice;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tampilkan graph\n";
        cout << "2. Tambah simpul\n";
        cout << "3. Tambah edge\n";
        cout << "4. Hapus simpul\n";
        cout << "5. Hapus edge\n";
        cout << "6. Cari rute terbaik\n";
        cout << "7. Bersihkan graph\n";
        cout << "8. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n=== JARINGAN TRANSPORTASI ===\n";
                printGraph(G);
                break;

            case 2: {
                cout << "Masukkan id simpul baru (A-Z): ";
                char id;
                cin >> id;
                addVertex(G, createVertex(id));
                cout << "Simpul " << id << " berhasil ditambahkan.\n";
                break;
            }

            case 3: {
                cout << "Masukkan id simpul asal, tujuan, waktu (menit), dan biaya (Rp):\n";
                char from, to;
                int weightTime, weightCost;
                cout << "Asal: ";
                cin >> from;
                cout << "Tujuan: ";
                cin >> to;
                cout << "Waktu: ";
                cin >> weightTime;
                cout << "Biaya: ";
                cin >> weightCost;

                Vertex* source = firstVertex(G);
                while (source != NULL && idVertex(source) != from) {
                    source = nextVertex(source);
                }
                if (source != NULL) {
                    addEdge(source, createEdge(to, weightTime, weightCost));
                    // Tambahkan edge dua arah
                    Vertex* dest = firstVertex(G);
                    while (dest != NULL && idVertex(dest) != to) {
                        dest = nextVertex(dest);
                    }
                    if (dest != NULL) {
                        addEdge(dest, createEdge(from, weightTime, weightCost));
                    }
                    cout << "Edge dari " << from << " ke " << to << " berhasil ditambahkan.\n";
                } else {
                    cout << "Simpul asal tidak ditemukan.\n";
                }
                break;
            }

            case 4: {
                cout << "Masukkan id simpul yang ingin dihapus: ";
                char id;
                cin >> id;
                deleteVertex(G, id);
                cout << "Simpul " << id << " berhasil dihapus.\n";
                break;
            }

            case 5: {
                cout << "Masukkan id simpul asal dan tujuan untuk edge yang ingin dihapus:\n";
                char from, to;
                cout << "Asal: ";
                cin >> from;
                cout << "Tujuan: ";
                cin >> to;

                Vertex* source = firstVertex(G);
                while (source != NULL && idVertex(source) != from) {
                    source = nextVertex(source);
                }
                if (source != NULL) {
                    deleteEdge(source, to);
                    // Hapus edge dua arah
                    Vertex* dest = firstVertex(G);
                    while (dest != NULL && idVertex(dest) != to) {
                        dest = nextVertex(dest);
                    }
                    if (dest != NULL) {
                        deleteEdge(dest, from);
                    }
                    cout << "Edge dari " << from << " ke " << to << " berhasil dihapus.\n";
                } else {
                    cout << "Simpul asal tidak ditemukan.\n";
                }
                break;
            }

            case 6: {
                cout << "Masukkan simpul asal: ";
                char from, to;
                cin >> from;
                cout << "Masukkan simpul tujuan: ";
                cin >> to;
                findBestRoute(G, from, to);
                break;
            }

            case 7:
                cleanGraph(G);
                cout << "Graph telah dibersihkan.\n";
                break;

            case 8:
                cout << "Keluar dari program. Semua resource akan dibersihkan.\n";
                cleanGraph(G);
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 8);

    return 0;
}
