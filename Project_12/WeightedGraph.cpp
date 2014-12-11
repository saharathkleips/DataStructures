/** @file WeightedGraph.cpp
* @author Saharath Kleips
* @brief This program will implement a Weighted Graph.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 11. A Weighted Graph
* is a linear data structure in which data items are maintained in descending
* order based on priority. You can only access data at the front of the queue,
* examining this data item entails removing it from the queue.
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "WeightedGraph.h"
#include "show12.cpp"
using namespace std;

//
// WEIGHTED GRAPH FUNCTION IMPLEMENTATIONS /////////////////////////////////////
//

/** The parameterized constructor
* that creates an empty WeightedGraph that allocates enough memory for a graph
* containing maxNumber verticies.
* @post This WeightedGraph will be a valid empty WeightedGraph with enough
* memory for maxNumber verticies.
* @param maxNumber is how much memory to allocate for this WeightedGraph.
*/
WeightedGraph::WeightedGraph(int maxNumber)
{
    maxSize = maxNumber;
    size = 0;
    vertexList = new Vertex[maxNumber];
    adjMatrix = new int[maxNumber * maxNumber];
    pathMatrix = new int[maxNumber * maxNumber];
    for(int i = 0; i < maxSize; i++)
        for(int j = 0; j < maxSize; j++)
            setEdge(i, j, INFINITE_EDGE_WT);
}

/** The copy constructor
* that initializes this WeightedGraph to be equivalent to the other
* WeightedGraph parameter.
* @pre other is a valid WeightedGraph.
* @post This WeightedGraph will be a deep copy of the other WeightedGraph.
* @param other is the WeightedGraph that this WeightedGraph will be made
* equivalent to.
*/
WeightedGraph::WeightedGraph(const WeightedGraph& other)
{
    *this = other;
}

/** The overloaded assignment operator
* that sets this WeightedGraph to be equivalent to the other WeightedGraph
* object parameter.
* @pre other is a valid WeightedGraph.
* @post This WeightedGraph will be a deep copy of the other WeightedGraph.
* @param other is the WeightedGraph that this WeightedGraph will be made
* equivalent to.
* @return The reference to this WeightedGraph.
*/
WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
{
    if(this == &other)
        return *this;
    if(!isEmpty())
    {   
        //Used instead of clear(), the copied graph can have different sizes
        delete[] vertexList;
        delete[] adjMatrix;
        delete[] pathMatrix;
    }

    //Copy properties of the other graph
    maxSize = other.size;
    size = other.size;
    vertexList = new Vertex[maxSize];
    adjMatrix = new int[maxSize * maxSize];
    pathMatrix = new int[maxSize * maxSize];
    //Copy graph data
    for(int i = 0; i < maxSize; i++)
    {
        vertexList[i] = other.vertexList[i];
        for(int j = 0; j < maxSize; j++)
        {
            adjMatrix[(i * maxSize) + j] = other.adjMatrix[(i * maxSize) + j];
            pathMatrix[(i * maxSize) + j] = other.pathMatrix[(i * maxSize) + j];
        }
    }
    return *this;
}

/** The destructor
* that deallocates the memory used to store this WeightedGraph.
* @post This WeightedGraph will be an empty, deallocated, WeightedGraph.
*/
WeightedGraph::~WeightedGraph()
{
    delete[] vertexList;
    delete[] adjMatrix;
    delete[] pathMatrix;
}

/** Inserts newVertex
* into this WeightedGraph. If the Vertex already exists in graph, then updates
* it.
* @pre This WeightedGraph is not full.
* @post newVertex will be added into this WeightedGraph or updated.
* @param newVertex is the Vertex to be added to this WeightedGraph or updated.
* @throw The WeightedGraph is full.
*/
void WeightedGraph::insertVertex(const Vertex& newVertex) throw (logic_error)
{
    //Check to update the vertex
    for(int i = 0; i < size; i++)
    {
        //If the vertex exists
        if(vertexList[i].getLabel() == newVertex.getLabel())
        {
            //Update the edge
            vertexList[i] = newVertex;
            for(int j = 0; j < size; j++)
                setEdge(i, j, INFINITE_EDGE_WT);
            //Exit when found
            return;
        }
    }

    if(isFull())
        throw logic_error("The Graph is full");

    //Add the vertex to the graph
    vertexList[size] = newVertex;
    for(int i = 0; i <= size; i++)
        setEdge(size, i, INFINITE_EDGE_WT);

    size++;
}

/** Inserts an undirected edge
* containing vertices v1 and v2 into the graph. The weight of the edge is wt. If
* there is already an edge containing vertices, then updates the weight of the 
* edge.
* @pre The graph includes vertices v1 and v2.
* @post The undirected edge is inserted into the graph.
* @param v1 is a vertex already in the graph.
* @param v2 is a vertex (not equivalent to v1) already in the graph.
* @param wt is the weight of the edge.
* @throw The graph is full.
*/
void WeightedGraph::insertEdge(const string& v1, const string& v2, int wt) 
    throw (logic_error)
{
    int index1 = getIndex(v1), index2 = getIndex(v2);

    //Vertices are not in the graph
    if(index1 == -1 || index2 == -1)
        throw logic_error("Vertex not found");

    cout << "Size = " << size << ", idx_v1 = " << index1 << ", idx_v2 = " <<
        index2 << endl;

    setEdge(index1, index2, wt);
}

/** Searches graph for vertex v.
* If this vertex is found, then places the value of vertex's data in vData and
* returns true. Otherwise, returns false and vData is undefined.
* @post vData will either be value of the vertex's data or undefined.
* @param v is the vertex to search the graph for.
* @param vData is the vertex that the found vertex will be placed into.
* @return True if the vertex is found. False if the vertex is not found.
*/
bool WeightedGraph::retrieveVertex(const string& v, Vertex& vData) const
{
    //Iterate graph for the vertex
    for(int i = 0; i < size; i++)
    {
        if(vertexList[i].getLabel() == v)
        {
            vData = vertexList[i];
            return true;
        }
    }
    //Vertex not found
    return false;
}

/** Searches the graph for the edge
* connecting vertices v1 and v2. If this edge exists, then places the weight of
* the edge in wt and returns true. Otherwise, returns false with wt undefined.
* @pre The graph includes vertices v1 and v2.
* @post wt will either be the value of the edge's weight or undefined.
* @param v1 is a vertex already in the graph.
* @param v2 is a vertex (not equivalent to v1) already in the graph.
* @param wt is the weight of the found edge will be placed into.
* @return True if the edge is found. False if the edge is not found.
* @throw The graph does not include vertex v1 or v2.
*/
bool WeightedGraph::getEdgeWeight(const string& v1, const string& v2, int& wt)
    const throw (logic_error)
{
    int index1 = getIndex(v1), index2 = getIndex(v2);

    //Vertices are not in the graph
    if(index1 == -1 || index2 == -1)
        throw logic_error("Edge not found");

    //If the edge has a real weight, return it
    if(getEdge(index1, index2) != INFINITE_EDGE_WT)
    {
        wt = getEdge(index1, index2);
        return true;
    }
    else
        return false;
}

/** Removes vertex v
* from the graph and any edges connected to v.
* @pre The graph includes vertex v.
* @post The graph will no longer include vertex v or any edges connected to it.
* @param v is the vertex to be removed.
* @throw The graph does not include vertex v.
*/
void WeightedGraph::removeVertex(const string& v) throw (logic_error)
{
    //Iterate the graph for the vertex
    for(int i = 0; i < size; i++)
    {
        if(vertexList[i].getLabel() == v)
        {
            //Check edges after to remove
            for(int j = i; j < size - 1; j++)
                for(int k = 0; k < size; k++)
                    adjMatrix[k * maxSize + j] = 
                        adjMatrix[k * maxSize + (j + 1)];

            //Check edges before to rermove
            for(int j = 0; j < size - 1; j++)
                for(int k = i; k < size; k++)
                    adjMatrix[k * maxSize + j] = 
                        adjMatrix[(k + 1) * maxSize + j];

            //Remove the actual vertex
            for(int j = i; j < size; j++)
                vertexList[j] = vertexList[j+1];

            size--;
            return;
        }
    }

    //Vertex isn't in the graph
    throw logic_error("Vertex not found");
}

/** Removes the edge
* connecting vertices v1 and v2 frorm the graph.
* @pre Graph includes vertices v1 and v2.
* @post The edge connecting v1 and v2 will no longer be in the graph.
* @param v1 is a vertex already in the graph.
* @pararm v2 is a vertex (not equivalent to v1) already in the graph.
* @throw The graph does not include vertex v1 or v2.
*/
void WeightedGraph::removeEdge(const string& v1, const string& v2) 
    throw (logic_error)
{
    int index1 = getIndex(v1), index2 = getIndex(v2);

    //Remove the edge if the vertices are found
    if(index1 != -1 && index2 != -1)
        setEdge(index1, index2, INFINITE_EDGE_WT);
    else
        throw logic_error("Edge not Found");
}

/** Removes all
* the vertices and edges in the graph.
* @post The graph will be cleared of all vertices and edges.
*/
void WeightedGraph::clear()
{
    size = 0;
}

/** Returns true if the graph is empty
* (no vertices). Otherwise, returns false.
* @return True if the graph is empty. False if the graph is not empty.
*/
bool WeightedGraph::isEmpty() const
{
    return (size == 0);
}

/** Returns true if the graph is full
* (cannot add any more vertices). Otherwise returns false.
* @return True if the graph is full. False if the graph is not full.
*/
bool WeightedGraph::isFull() const
{
    return (size == maxSize);
}

/** Computes and display's the path matrix
* of the graph.
* @post Paths are changed to the shortest path and outputted to the console.
*/
void WeightedGraph::showShortestPaths() const
{
    //Initialize the path array
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
            setPath(i, j, getEdge(i, j));
        setPath(i, i, 0);
    }

    //Iterate paths
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            for(int k = 0; k < size; k++)
            {
                //If there is a path between j & i and a path between i & k
                if(getPath(j, i) != INFINITE_EDGE_WT && 
                    getPath(i, k) != INFINITE_EDGE_WT)
                {
                    //If the sum of j & i and i & k is less than j & k
                    if(getPath(j, i) + getPath(i, k) < getPath(j, k) ||
                        getPath(j, k) == INFINITE_EDGE_WT)
                    {
                        //Replace j & k with j & i + i & k
                        setPath(j, k, (getPath(j, i) + getPath(i, k)));
                    }
                }
            }

    //Print the path matrix
    cout << endl << "Path matrix : " << endl << '\t';
    for(int col = 0; col < size; col++)
        cout << col << '\t';
    cout << endl;

    for(int row = 0; row < size; row++)
    {
        cout << row << '\t';
        for(int col = 0; col < size; col++)
        {
            int wt = getPath(row,col);
            if(wt == INFINITE_EDGE_WT)
                cout << "- \t";
            else
                cout << wt << '\t';
        }
        cout << endl;
    }
}

/** If no vertex has the same color
* as an adjacent vertex in the graph, returns true. Otherwise, returns false.
* @pre All vertices have been assigned a color.
* @return True if no vertex has the same color as an adjacent vertex. False if a
* vertex has the same color as an adjacent vertex.
*/
bool WeightedGraph::hasProperColoring() const
{
    //Iterate graph
    for(int i = 0; i < size; i ++)
        //Iterate vertices
        for(int j = 0; j < size; j++)
            //If the edge is properly weighted and doesn't have the same color
            if(getEdge(i, j) != INFINITE_EDGE_WT && 
                vertexList[i].getColor() == vertexList[j].getColor() && i != j)
                return false;

    return true;
}

/** If every vertex is of even degree
* in the graph, returns true. Otherwise, returns false.
* @return True if every vertex is of even degree. False if every vertex is not
* of even degree.
*/
bool WeightedGraph::areAllEven() const
{
    int count = 0;
    //Iterate the graph
    for(int i = 0; i < size; i++)
    {
        //Iterate the vertices
        for(int j = 0; j < size; j++)
            if(getEdge(i, j) != INFINITE_EDGE_WT)
                count++;

        //The vertex is not even
        if(count % 2 != 0)
            return false;

        count = 0;
    }
    return true;
}

/** Returns an adjacency matrix index
* from a vertex label.
* @pre v is a valid vertex label.
* @param v is the vertex label to get the adjacency matrix index from.
* @return The index location in the adjacency matrix. -1 if not found.
*/
int WeightedGraph::getIndex(const string& v) const
{
    for(int i = 0; i < size; i++)
        if(vertexList[i].getLabel() == v)
            return i;
        
    //Index not found
    return -1;
}

/** Returns an edge weight
* from adjacency matrix indices.
* @pre row and col are valid indices.
* @param row is the row index of the adjacency matrix.
* @param col is the column index of the adjacency matrix.
* @return The edge weight corresponding to the index locations.
*/
int WeightedGraph::getEdge(int row, int col) const
{
    return adjMatrix[(row * maxSize) + col];
}

/** Returns the path weight
* from the path matrix indicies.
* @pre row and col are valid indices.
* @param row is the row index of the path matrix.
* @param col is the column index of the path matrix.
* @return The path weight corresponding to the index locations.
*/
int WeightedGraph::getPath(int row, int col) const
{
    return pathMatrix[(row * maxSize) + col];
}

/** Sets the edge weight
* from adjacency matrix indices.
* @pre row and col are valid indices and wt is a valid weight.
* @post The edge between the two indices will be set.
* @param row is the row index of the adjacency matrix.
* @param col is the column index of the adjacency matrix.
* @param wt is the weight of the new edge.
*/
void WeightedGraph::setEdge(int row, int col, int wt)
{
    adjMatrix[(row * maxSize) + col] = wt;
    adjMatrix[(col * maxSize) + row] = wt;
}

/** Sets the path weight
* from the path matrix indices.
* @pre row and col are valid indices and wt is a valid weight.
* @post The path between the two indices will be set.
* @param row is the row index of the path matrix.
* @param col is the column index of the path matrix.
* @param wt is the weight of the new path.
*/
void WeightedGraph::setPath(int row, int col, int wt) const
{
    pathMatrix[(row * maxSize) + col] = wt;
    pathMatrix[(col * maxSize) + row] = wt;
}