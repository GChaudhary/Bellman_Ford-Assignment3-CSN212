#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <climits>
#include <list>

using namespace std;
 

int bellmanFord( int vertices, int startVertex, vector< list< pair<int, int> > > adjList, vector< pair<int, int> > & leastDistances )
{
    int i, j, k;
    list< pair<int, int> >::iterator iter;
     
    // Initialisation
    for (i = 0; i <= vertices; ++i) {
        leastDistances[i].first = INT_MAX;
        leastDistances[i].second = -1;
    }
     
    // Initializing 'source' distance = 0
    leastDistances[startVertex].first = 0;
    leastDistances[startVertex].second = 0;
     
    
    for (i = 1; i <= vertices - 1; ++i) { // Iterating through |V|-1 vertices
        for (j = 1; j <= vertices; ++j) { // Iterating through all the edges     
            iter = adjList[j].begin();
             
            while (iter != adjList[j].end()) {
                if (leastDistances[j].first == INT_MAX) {
                    ++iter;
                    continue;
                }
                 
                // Relaxation Step
                if ((*iter).second + leastDistances[j].first < leastDistances[(*iter).first].first) {
                    leastDistances[(*iter).first].first = (*iter).second + leastDistances[j].first;
                    leastDistances[(*iter).first].second = j;
                }
                 
                ++iter;
            }
        }
    }
     
    // Negative Cycle Detection
    for (j = 1; j <= vertices; ++j) {
        iter = adjList[j].begin();
         
        while (iter != adjList[j].end()) {
            // Checking for further relaxation
            if ((*iter).second + leastDistances[j].first < leastDistances[(*iter).first].first) {
                return -1;
            }
             
            ++iter;
        }
    }
     
    return 1;
}
 
int main()
{
    int vertices, edges, v1, v2, weight;
     
    cout << "Enter the number of Vertices -" << endl;
    cin >> vertices;
     
    cout << "Enter the number of Edges -" << endl;
    cin >> edges;
     
    vector< list< pair<int, int> > > adjList(vertices + 1);
     
    cout << "Enter the Edges V1 to V2, with weight W -";
    for (int i = 1; i <= edges; ++i) {
        cin >> v1 >> v2 >> weight;
        adjList[v1].push_back(make_pair(v2, weight));
    }
        
    vector< pair<int, int> > leastDistances(vertices + 1);
    
    int startVertex;
    cout << "\nEnter the Start Vertex -\n";
    cin >> startVertex;
     
    int retValue = bellmanFord(vertices, startVertex, adjList, leastDistances);
    // Exit if 'negative cycles' exist in the graph 
    if (retValue == -1) {
        cout << "Negative Cycles exist in the Graph" << endl;
        return 0;
    }
     
    // Output 
    cout << "\n\nVertex    Shortest Distance to Vertex " << startVertex << "     Parent Vertex-\n";
    for (int i = 1; i <= vertices; ++i) {
        cout << "  " << i << "\t\t " << leastDistances[i].first << " \t\t\t\t " << leastDistances[i].second << endl;
    }
     
    return 0;
}
