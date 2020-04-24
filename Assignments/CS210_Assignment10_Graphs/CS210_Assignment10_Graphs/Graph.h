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
using namespace std;

#include "DynamicArray.h"

// Edge
struct Vertex;
static int sNumEdgeObjects = 0;
struct Edge {
  // update sNumEdgeObjects for bookkeeping.
  Edge() { sNumEdgeObjects++; }
  // update sNumEdgeObjects for bookkeeping.
  Edge(const double weight, Vertex* vertex1, Vertex* vertex2) : mWeight(weight), mVertex1(vertex1), mVertex2(vertex2) { sNumEdgeObjects++; }
  // update sNumEdgeObjects for bookkeeping.
  ~Edge();
  
  // copies member variables
  Edge& operator=(const Edge& edge);
  
  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const Edge *edge);
  friend ostream& operator<<(ostream& ostr, const Edge *edge);
  
  double mWeight = 0;
  Vertex* mVertex1 = nullptr;
  Vertex* mVertex2 = nullptr;
};

Edge::~Edge() {
  mVertex1 = nullptr;
  mVertex2 = nullptr;
  sNumEdgeObjects--; // update sNumEdgeObjects for bookkeeping.
}

Edge& Edge::operator=(const Edge &edge) {
  mWeight = edge.mWeight;
  mVertex1 = edge.mVertex1;
  mVertex2 = edge.mVertex2;
  return *this;
}

// Vertex
static int sNumVertexObjects = 0;
struct Vertex {
  Vertex() { sNumVertexObjects++; }
  Vertex(const string &name) : mName(name) { sNumVertexObjects++; }
  ~Vertex() { sNumVertexObjects--; }
  
  // copies member variables
  Vertex& operator=(const Vertex& vertex);
  
  void addEdge(Edge &edge) { mEdges.addObject(&edge); }
  
  // makes streaming easier
  friend ostream& operator<<(ostream& ostr, const Vertex *vertex);
  
  string mName;
  DynamicArray<Edge*> mEdges;
};

Vertex& Vertex::operator=(const Vertex &vertex) {
  mName = vertex.mName;
  mEdges = vertex.mEdges;
  return *this;
}

ostream& operator<<(ostream& ostr, const Vertex &vertex) {
  ostr << vertex.mName << endl;
  for (int i = 0; i < vertex.mEdges.getSize(); i++) {
    ostr << vertex.mEdges[i] << endl;
  }
  return ostr;
}

ostream& operator<<(ostream& ostr, const Edge &edge) {
  ostr << edge.mWeight << ' ' << edge.mVertex1->mName << " <-> " << edge.mVertex2->mName;
  return ostr;
}

ostream& operator<<(ostream& ostr, const Edge *edge) {
  ostr << edge->mWeight << ' ' << edge->mVertex1->mName << " <-> " << edge->mVertex2->mName;
  return ostr;
}

class Graph {
public:
  Graph() {}
  ~Graph() {}
  
  void addVertex(const string &name) { mVertices.addObject(Vertex(name)); }
  Vertex& getVertex(int index) const { return mVertices[index]; }
  int getNumVertices() const { return mVertices.getSize(); }
  const DynamicArray<Edge*>& getEdges(const Vertex &vertex) const { return vertex.mEdges; }
  void addEdge(int index1, int index2, double weight);
  friend ostream& operator<<(ostream& ostr, const Graph &graph);
  
private:
  DynamicArray<Vertex> mVertices;
  DynamicArray<Edge> mEdges;
};

void Graph::addEdge(int index1, int index2, double weight) {
  Edge workingEdge;
  if (mVertices.validateIndex(index1) && mVertices.validateIndex(index2)) {
    workingEdge.mWeight = weight;
    workingEdge.mVertex1 = &mVertices[index1];
    workingEdge.mVertex2 = &mVertices[index2];
    mEdges.addObject(workingEdge);
    mVertices[index1].addEdge(mEdges[mEdges.getSize() - 1]);
    mVertices[index2].addEdge(mEdges[mEdges.getSize() - 1]);
    return;
  }
  throw out_of_range("invalid index");
}

ostream& operator<<(ostream& ostr, const Graph &graph) {
  for (int i = 0; i < graph.mVertices.getSize(); i++) {
    ostr << graph.mVertices[i] << endl;
  }
  return ostr;
}

#endif /* GRAPH_H */
