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
  
  // copies member variables
  const Edge& operator=(const Edge& edge);

  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const Edge *edge);
  friend ostream& operator<<(ostream& ostr, const Edge &edge);
  
  
  double mWeight = 0;
  int mVertexIdx1 = -1;
  int mVertexIdx2 = -1;
  int mEdgeIdx = -1;
  const Graph* mGraph = nullptr;
};

const Edge& Edge::operator=(const Edge &edge) {
  mWeight = edge.mWeight;
  mVertexIdx1 = edge.mVertexIdx1;
  mVertexIdx2 = edge.mVertexIdx2;
  mEdgeIdx = edge.mEdgeIdx;
  mGraph = edge.mGraph;
  return *this;
}

// Vertex
static int sNumVertexObjects = 0;
struct Vertex {
  Vertex() { sNumVertexObjects++; }
  Vertex(const string &name, int index, Graph* graph) : mName(name), mIndex(index), mGraph(graph) { sNumVertexObjects++; }
  ~Vertex() { sNumVertexObjects--; mGraph = nullptr; }
  
  // copies member variables
  const Vertex& operator=(const Vertex& vertex);
  
  const string& getName() { return mName; }
  void addEdgeIdx(int edgeIdx) { mEdgeIdxs.addObject(edgeIdx); }
  int getEdgeIdx(int index) { return mEdgeIdxs[index]; }
  int getNumEdges() { return mEdgeIdxs.getSize(); }
  int getIndex() { return mIndex; }
  const DynamicArray<int>& getEdges() { return mEdgeIdxs; }
  
  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const Vertex *vertex);
  
  string mName;
  int mIndex = 0;
  DynamicArray<int> mEdgeIdxs;
  Graph* mGraph = nullptr;
};

const Vertex& Vertex::operator=(const Vertex &vertex) {
  mName = vertex.mName;
  mIndex = vertex.mIndex; 
  mEdgeIdxs = vertex.mEdgeIdxs;
  mGraph = vertex.mGraph;
  return *this;
}

class Graph {
public:
  Graph() {}
  Graph(const string &inputFile);
  ~Graph() {}
  
  Vertex& getVertex(int index) const { return mVertices[index]; }
  Edge& getEdge(int index) const { return mEdges[index]; }
  int getNumVertices() const { return mVertices.getSize(); }
  int getNumEdges() const { return mEdges.getSize(); }
  void addEdge(int index1, int index2, double weight);
  void addVertex(const string &name)
    { mVertices.addObject(Vertex(name, mVertices.getSize(), this)); }
  double getMinPath(int startIndex, int endIndex, ostream &ostr);
  friend ostream& operator<<(ostream& ostr, const Graph &graph);
  
private:
  DynamicArray<Vertex> mVertices;
  DynamicArray<Edge> mEdges;
};

// should add error handling?
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
      while (ss >> input) {
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
    mVertices[index1].addEdgeIdx(mEdges.getSize() - 1);
    mVertices[index2].addEdgeIdx(mEdges.getSize() - 1);
    return;
  }
  throw out_of_range("invalid index");
}

double Graph::getMinPath(int startIndex, int endIndex, ostream &ostr) {
  int numVertices = mVertices.getSize();
  bool settledVertices[numVertices];
  double minPath[numVertices];
  string minPathS[numVertices];
  int otherVertexIdx = -1;
  int curVertexIdx = startIndex;
  double curPath = 0;
  double minPathAvailable = DBL_MAX;
  Edge curEdge;
  stringstream ss;
  
  for (int i = 0; i < numVertices; i++) {
    if (i != startIndex) {
      settledVertices[i] = false;
      minPath[i] = DBL_MAX;
    }
  }
  settledVertices[startIndex] = true;
  minPath[startIndex] = 0;
  while(!settledVertices[endIndex]) {
    Vertex curVertex = getVertex(curVertexIdx);
    for (int i = 0; i < curVertex.getNumEdges(); i++) {
      curEdge = getEdge(curVertex.getEdgeIdx(i));
      otherVertexIdx = (curEdge.mVertexIdx1 == curVertexIdx ?
                        curEdge.mVertexIdx2 : curEdge.mVertexIdx1);
      if (!settledVertices[otherVertexIdx]) {
        curPath = (minPath[curVertexIdx] == DBL_MAX ? curEdge.mWeight :  minPath[curVertexIdx] + curEdge.mWeight);
        if (minPath[otherVertexIdx] >= curPath) {
          minPath[otherVertexIdx] = curPath;
          ss << minPathS[curVertexIdx] << endl;
          ss << curEdge;
          minPathS[otherVertexIdx] = ss.str();
          ss.clear();
        }
      }
    }
    for (int i = 0; i < numVertices; i++) {
      if (!settledVertices[i] && minPathAvailable > minPath[i]) {
        curVertexIdx = i;
      }
    }
    settledVertices[curVertexIdx] = true;
    minPathAvailable = DBL_MAX;
  }
  return minPath[endIndex];
}

ostream& operator<<(ostream& ostr, const Edge &edge) {
  ostr << edge.mWeight << ' ' << edge.mGraph->getVertex(edge.mVertexIdx1).getName()
       << " <-> " << edge.mGraph->getVertex(edge.mVertexIdx2).getName() << endl;
  return ostr;
}

ostream& operator<<(ostream& ostr, const Edge *edge) {
  ostr << edge->mWeight << ' ' << edge->mGraph->getVertex(edge->mVertexIdx1).getName()
  << " <-> " << edge->mGraph->getVertex(edge->mVertexIdx2).getName() << endl;
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
