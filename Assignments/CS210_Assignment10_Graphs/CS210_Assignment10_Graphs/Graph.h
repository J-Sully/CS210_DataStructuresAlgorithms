/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  GRAPH.H
//  CS210_Assignment10_Graphs
//
//  Created by Jessie Sully on 4/22/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <float.h>
using namespace std;

#include "DynamicArray.h"

// Edge
class Graph;
static int sNumEdgeObjects = 0;
struct Edge {
  // update sNumEdgeObjects for bookkeeping.
  Edge() { sNumEdgeObjects++; }
  // update sNumEdgeObjects for bookkeeping.
  Edge(const Edge &edge) : mWeight(edge.mWeight), mVertexIdx1(edge.mVertexIdx1), mVertexIdx2(edge.mVertexIdx2), mEdgeIdx(edge.mEdgeIdx), mGraph(edge.mGraph)  { sNumEdgeObjects++; }
  // update sNumEdgeObjects for bookkeeping.
  Edge(const double weight, int vertexIdx1, int vertexIdx2, int edgeIdx, const Graph* graph) : mWeight(weight), mVertexIdx1(vertexIdx1), mVertexIdx2(vertexIdx2), mEdgeIdx(edgeIdx), mGraph(graph)  { sNumEdgeObjects++; }
  // update sNumEdgeObjects for bookkeeping.
  ~Edge() { sNumEdgeObjects--; mGraph = nullptr;};

  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const Edge *edge);
  friend ostream& operator<<(ostream& ostr, const Edge &edge);
  
  double mWeight = 0;
  // indexes correspond to the index of Vertex/Edge in mGraph
  int mVertexIdx1 = -1;
  int mVertexIdx2 = -1;
  int mEdgeIdx = -1;
  const Graph* mGraph = nullptr;
};

// Vertex
static int sNumVertexObjects = 0;
struct Vertex {
  Vertex() { sNumVertexObjects++; }
  Vertex(const string &name, int index, Graph* graph) : mName(name), mIndex(index), mGraph(graph) { sNumVertexObjects++; }
  ~Vertex() { sNumVertexObjects--; mGraph = nullptr; }
  
  const string& getName() const { return mName; }
  void addEdgeIdx(int edgeIdx) { mEdgeIdxs.addObject(edgeIdx); }
  int getEdgeIdx(int index) const { return mEdgeIdxs[index]; }
  int getNumEdges() const { return mEdgeIdxs.getSize(); }
  const DynamicArray<int>& getEdges() { return mEdgeIdxs; }
  
  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const Vertex *vertex);
  
  string mName;
  // indexes correspond to the index of Vertex/Edge in mGraph
  int mIndex = 0;
  DynamicArray<int> mEdgeIdxs;
  Graph* mGraph = nullptr;
};

class Graph {
public:
  Graph() {}
  // does not handle holes, skips vertices with index mismatches, will not add edge if indices are out of range
  Graph(const string &inputFile);
  ~Graph() {}
  
  const Vertex* getVertex(int index) const { return &mVertices[index]; }
  const Edge* getEdge(int index) const { return &mEdges[index]; }
  int getNumVertices() const { return mVertices.getSize(); }
  int getNumEdges() const { return mEdges.getSize(); }
  // throw exception if indices are out of range
  void addEdge(int index1, int index2, double weight);
  // does not handle errors in indexing - it only adds to the end of mVertices
  void addVertex(const string &name)
    { mVertices.addObject(Vertex(name, mVertices.getSize(), this)); }
  bool validateVertexIdx(int index) { return index >= 0 && index < mVertices.getSize(); }
  
  // uses Dijkstra's Algorithm to find minimum path between two verices and tracks path in ostr
  double getMinPath(int startIndex, int endIndex, ostream &ostr) const;
  
  friend ostream& operator<<(ostream& ostr, const Graph &graph);
  
private:
  DynamicArray<Vertex> mVertices;
  DynamicArray<Edge> mEdges;
};

Graph::Graph(const string &inputFile) {
  string input, name;
  int index1 = 0, index2 = 0;
  double weight = 0;
  ifstream fopenInput(inputFile);
  stringstream ss;
  
  if (fopenInput) {
    do {
      getline(fopenInput, input);
      if (input == "-1") break;
      ss.str(input);
      ss >> index1 >> name;
      while (ss >> input) { // handles names with whitespace
        name += ' ';
        name += input;
      }
      if (index1 == mVertices.getSize()) { // enforcing no holes
        addVertex(name);
      }
      ss.clear();
      name.clear();
    } while (index1 != -1);

    do {
      getline(fopenInput, input);
      if (input == "-1") break;
      ss.str(input);
      ss >> index1 >> index2 >> weight;
      // validate input
      if (mVertices.validateIndex(index1) && mVertices.validateIndex(index2) && weight > 0)
        addEdge(index1, index2, weight);
      ss.clear();
    } while (index1 != -1);
    
    fopenInput.close();
  }
}

void Graph::addEdge(int index1, int index2, double weight) {
  if (mVertices.validateIndex(index1) && mVertices.validateIndex(index2)) {
    mEdges.addObject(Edge(weight, index1, index2, mEdges.getSize(), this));
    mVertices[index1].addEdgeIdx(mEdges.getSize() - 1); // add new edgeIdx to vertex1
    mVertices[index2].addEdgeIdx(mEdges.getSize() - 1); // add new edgeIdx to vertex2
    return;
  }
  throw out_of_range("invalid index");
}

double Graph::getMinPath(int startIndex, int endIndex, ostream &ostr) const {
  const Vertex* curVertex = getVertex(startIndex);
  const Edge* curEdge = nullptr;
  double curPath = 0;
  int curVertexIdx = startIndex;
  int otherVertexIdx = -1; // connected to curVertex through curEdge
  int numVertices = mVertices.getSize();
  double minPathAvailable = DBL_MAX;
  
  bool settledVertices[numVertices];
  double minPath[numVertices];
  string minPathS[numVertices];
  
  ostr << "Shortest Path From " << getVertex(startIndex)->mName << " to " << getVertex(endIndex)->mName << ':' << endl;
  
  // fill arrays with start values
  for (int i = 0; i < numVertices; i++) {
    settledVertices[i] = false;
    minPath[i] = DBL_MAX;
    minPathS[i].empty();
  }
  minPath[startIndex] = 0; // path to itself = 0
  settledVertices[startIndex] = true; // 0 will always be minimum value, allows for skipping while loop if startIndex = endIndex
  
  while(!settledVertices[endIndex]) { // stop when end reached
    // reset loop
    curVertex = getVertex(curVertexIdx);
    settledVertices[curVertexIdx] = true;
    minPathAvailable = DBL_MAX;
    
    for (int i = 0; i < curVertex->getNumEdges(); i++) {
      curEdge = getEdge(curVertex->getEdgeIdx(i));
      // order can be mixed
      otherVertexIdx = (curEdge->mVertexIdx1 == curVertexIdx ?
                        curEdge->mVertexIdx2 : curEdge->mVertexIdx1);
      
      if (!settledVertices[otherVertexIdx]) { // if other vertex is not settled
        // from startVertex, all edges are minimum paths
        curPath = (curVertexIdx == startIndex ? curEdge->mWeight :  minPath[curVertexIdx] + curEdge->mWeight);
        if (minPath[otherVertexIdx] >= curPath) {
          minPath[otherVertexIdx] = curPath;
          // keep track of path in string format
          stringstream ss;
          ss << minPathS[curVertexIdx];
          ss << curEdge;
          minPathS[otherVertexIdx] = ss.str();
        }
      }
    }
    // find next vertex
    for (int i = 0; i < numVertices; i++) {
      if (!settledVertices[i] && (minPathAvailable > minPath[i])) {
        curVertexIdx = i;
        minPathAvailable = minPath[i];
      }
    }
  }
  ostr << minPathS[endIndex];
  ostr << "Total Distance: " << minPath[endIndex] << endl << endl;
  return minPath[endIndex];
}

ostream& operator<<(ostream& ostr, const Edge &edge) {
  ostr << edge.mWeight << ' ' << edge.mGraph->getVertex(edge.mVertexIdx1)->getName()
       << " <-> " << edge.mGraph->getVertex(edge.mVertexIdx2)->getName() << endl;
  return ostr;
}

ostream& operator<<(ostream& ostr, const Edge *edge) {
  ostr << edge->mWeight << ' ' << edge->mGraph->getVertex(edge->mVertexIdx1)->getName()
  << " <-> " << edge->mGraph->getVertex(edge->mVertexIdx2)->getName() << endl;
  return ostr;
}

ostream& operator<<(ostream& ostr, const Vertex &vertex) {
  ostr << vertex.mName << endl;
  for (int i = 0; i < vertex.mEdgeIdxs.getSize(); i++) {
    ostr << vertex.mGraph->getEdge(vertex.mEdgeIdxs[i]) << endl;
  }
  return ostr;
}

ostream& operator<<(ostream& ostr, const Graph &graph) {
  for (int i = 0; i < graph.mVertices.getSize(); i++) {
    ostr << graph.mVertices[i] << endl;
  }
  return ostr;
}

#endif /* GRAPH_H */
