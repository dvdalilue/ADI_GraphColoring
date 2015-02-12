// CI-5651
// David Lilue, 09-10444

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <math.h>
#include <algorithm>

using namespace std;

class Node
{
public:

    Node () {}

    Node (int e)
    {
       valor = e;
       std::vector<int> adyacentes;
    }

    void addAd (int nd)
    {
       adyacentes.push_back(nd);
    }

    int getV() const { return valor; }

    void setV( int v) { valor = v; }

    int pop()
    {
        int aux = adyacentes.back();
        adyacentes.pop_back();
        return aux;
    }

    vector<int> ady()
    {
        return adyacentes;
    }

    int size()
    {
        return adyacentes.size();
    }

    bool empty()
    {
        return adyacentes.empty();
    }

private:
    int valor;
    std::vector<int> adyacentes;
};

void imprimirGrafo(Node g[], int n)
{
    int i = 0;

    while (i < n) {
        if (g[i].getV() != -1)
        {
            cout << (g[i].getV()) << " -- ";
            while (!g[i].empty()) {
                cout << g[i].pop() << ", ";
            }
        }
        cout << "\n";
        i++;
    }
}

void printvector(vector<int> li) {
    vector<int>::iterator i;
    for( i = li.begin(); i != li.end(); ++i)
        cout << *i << " ";
    cout << endl;
}

int getWGraph(Node g[], int n, int *delta, int *p)
{
    int i = 0,
        d = 0,
        m = 0;

    double r = 0.0;

    while (i < n)
    {
        if (g[i].getV() != -1) {
            d = g[i].size();
            m = max(d, m);
            if (m == d) *p = i;
            d = n - d;
            r += (1.0/((double) d));
        } else {
            m = max(0, m);
            r += (1.0/((double) n));
        }
        i++;
    }

    *delta = m;

    return int(r);
}

int getLowestV(Node g[], int r[], int p)
{
    Node aux = g[p];
    std::vector<int> colors, ady;

    int i = 0,
        j = 0,
        k;

    ady = aux.ady();

    for (std::vector<int>::iterator it = ady.begin() ; it != ady.end(); ++it) {
        if (r[*it] != 0) colors.push_back(r[*it]);
    }

    std::sort(colors.begin(), colors.end());

    k = colors.size();

    if (!colors.empty()) {
        j = colors.back();
        colors.pop_back();
    }
    
    while (!colors.empty())
    {
        i = colors.back();
        colors.pop_back();
        if ((j - i) > 1) {
            k = i;
        }
    }
    return k + 1;
}

bool allColored(int r[], int n)
{
    int i = 0;

    while (i < n)
    {
        if (r[i] == 0) return false;
        i++;
    }
    return true;
}

void graphColoring(Node g[], int n, int w, int d, int p)
{
    bool back = false;
    int k = w + 1,
        u = 0,
        i = 0,
        l = 0;

    int result[n],
        dsat[n];
    
    bool colorDisp[n];

    Node aux;

    for (u = 0; u < n; u++) {
        result[u] = 0;
        dsat[u] = 0;
        colorDisp[u] = true;
    }

    result[p] = 1;

    aux = g[p];

    while(!aux.empty()) { i = aux.pop(); dsat[i] = 1; }

    // Aumnetar el DSAT de los vertices adyacentes.

    while (!allColored(result, n))
    {
        i = 0;
        u = 0;
        l = 0;

        while (i < n)
        {
            if (result[i] == 0) {
                u = max(u, dsat[i]);
                if (u == dsat[i]) l = i;
            }
            i++;
        }

        aux = g[l];
        while(!aux.empty()) { u = aux.pop(); dsat[u] += 1; }

        result[l] = getLowestV(g, result, l);
        //cout << result[l] << "\n";

    }

    i = 0;
    u = 0;

    while (i < n)
    { 
        u = max(u,result[i++]);
    }

    cout << "X^(G): " << u;

    // u_k    = numero de colores usados en la actual
    //          solucion parcial de nivel k-1.

    // U(x_k) = conjunto de colores {1..min(u_k+1, q-1)}
    //          que no han sido usados en la actual solucion
    //          parcial de nivel k-1. Para un vecino de x_k.

    // c      = color actual de x_k, 

    // while true
    // {
    //     if !back {

    //     }
    // }
}

int main(int argc, char const *argv[])
{
    string line;
    std::ifstream file;

    Node nd;

    int i     = 0,
        org   = 0,
        dst   = 0,
        nodes = 0,
        edges = 0,
        w     = 0,
        delta = 0;

    file.open(argv[1]);

    if (!file.is_open())
    {
        cout << "No se pudo abrir el archivo";
        return 1;
    }   
    
    while (getline (file, line))
    {
        if (line[0] == 'p') break;
    }

    std::stringstream iss(line);
    std::istream_iterator<std::string> begin(iss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> tokens(begin, end);

    for(std::vector<std::string>::const_iterator i = tokens.begin(); i != tokens.end(); ++i) {
        if ((*i != "p") || (*i != "edge"))
        {
            istringstream buffer(*i);
            if (nodes == 0) buffer >> nodes;   
            else buffer >> edges;
        }
    }

    Node graph[nodes];
    nd = Node(-1);

    for (i = 0; i < nodes; i++)
    {
        graph[i] = nd;
    }

    while (getline (file, line))
    {
        std::stringstream iss(line);
        std::istream_iterator<std::string> begin(iss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> tokens(begin, end);

        for(std::vector<std::string>::const_iterator i = tokens.begin(); i != tokens.end(); ++i) {
            if (*i != "e")
            {
                istringstream buffer(*i);
                if (org == 0) {
                    buffer >> org;
                }
                else {
                    buffer >> dst;
                    if (graph[org-1].getV() == -1) { graph[org-1].setV(org); }
                    if (graph[dst-1].getV() == -1) { graph[dst-1].setV(dst); }
                    graph[org-1].addAd(dst-1);
                    graph[dst-1].addAd(org-1);
                    org = 0;
                }
            }
        }
    }

    file.close();

    w = getWGraph(graph, nodes, &delta, &i);// w = Cota inerior, delta = cota superior.

    graphColoring(graph, nodes, w, delta + 1, i);
    // imprimirGrafo(graph, nodes);
    
    return 0;
}