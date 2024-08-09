/*-------------------------------------------
Program 5: Open mapping of UIC campus with template class graph and Dijkstra's algorithm
Course: CS 251, Fall 2023, UIC
System: VS Code
Name: Abrar Makki
------------------------------------------- */
//
// Adam T Koehler, PhD
// University of Illinois Chicago
// CS 251, Fall 2023
//
// Project Original Variartion By:
// Joe Hummel, PhD
// University of Illinois at Chicago
//

#pragma once

#include <iostream>
#include <utility>
#include <map>
#include <stdexcept>
#include <vector>
#include <set>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
	private:
	map<VertexT, map<VertexT, WeightT>> adjList; // map in map to represent an adjacency list
	public:
	graph() {} // default constructor

	graph(const graph& other) {
		this->adjList = other.adjList;
	}
	//make an assignment operator
	graph& operator=(const graph& other) {
		this->adjList = other.adjList;
		return *this;
	}
	//
	// NumVertices
	//
	// Returns the # of vertices currently in the graph.
	//
	int NumVertices() const {
		return this->adjList.size();
	}

	//
	// NumEdges
	//
	// Returns the # of edges currently in the graph.
	//
	int NumEdges() const {
		int numEdges = 0;
		for (const auto& element : this->adjList) { // iterate through the map
			numEdges += element.second.size();
		}
		return numEdges;
	}

	//
	// addVertex
	//
	// Adds the vertex v to the graph if there's room, and if so
	// returns true.  If the graph is full, or the vertex already
	// exists in the graph, then false is returned.
	//
	bool addVertex(VertexT v) {
		if (this->adjList.count(v) == 0) {
			this->adjList.insert({v, map<VertexT, WeightT>()});
			return true;
		}
		return false;
	}

	//
	// addEdge
	//
	// Adds the edge (from, to, weight) to the graph, and returns
	// true.  If the vertices do not exist or for some reason the
	// graph is full, false is returned.
	//
	// NOTE: if the edge already exists, the existing edge weight
	// is overwritten with the new edge weight.
	//
	bool addEdge(VertexT from, VertexT to, WeightT weight) {
		if (this->adjList.count(from) == 0 || this->adjList.count(to) == 0) { //check if the vertices exist
			return false;
		}
		if (this->adjList.at(from).count(to) == 0) { //check if the edge exists
			this->adjList.at(from).insert({to, weight});
		} else { //if the edge exists, overwrite the weight
			this->adjList.at(from).at(to) = weight;
		}
		return true;
	}

	//
	// getWeight
	//
	// Returns the weight associated with a given edge.  If
	// the edge exists, the weight is returned via the reference
	// parameter and true is returned.  If the edge does not
	// exist, the weight parameter is unchanged and false is
	// returned.
	//
	bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
		if (this->adjList.count(from) == 0 || this->adjList.count(to) == 0) {//check if the vertices exist
			return false;
		}
		if (this->adjList.at(from).count(to) == 0) {//check if the edge exists
			return false;
		}
		weight = this->adjList.at(from).at(to);//if the edge exists, return the weight
		return true;
	}

	//
	// neighbors
	//
	// Returns a set containing the neighbors of v, i.e. all
	// vertices that can be reached from v along one edge.
	// Since a set is returned, the neighbors are returned in
	// sorted order; use foreach to iterate through the set.
	//
	set<VertexT> neighbors(VertexT v) const {
		set<VertexT>  N;
		if (this->adjList.count(v) == 0) {//check if the vertex exists
			return N;
		}
		for (const auto& element : this->adjList.at(v)) {//iterate through the map
			N.insert(element.first);
		}
		return N;
	}

	//
	// getVertices
	//
	// Returns a vector containing all the vertices currently in
	// the graph.
	//
	vector<VertexT> getVertices() const {
		vector<VertexT>  V;
		for (const auto& element : this->adjList) { //iterate through the map
			V.push_back(element.first);
		}
		return V;
	}

	//
	// dump
	//
	// Dumps the internal state of the graph for debugging purposes.
	void dump(ostream& output) const {
		output << "***************************************************" << endl;
		output << "********************* GRAPH ***********************" << endl;

		output << "**Num vertices: " << this->NumVertices() << endl;
		output << "**Num edges: " << this->NumEdges() << endl;

		output << endl;
		output << "**Vertices:" << endl;
		int i = 0;
		for (const auto& element : this->adjList) { //loop through the map to print the vertices
			output << " " << i << ". " << element.first << endl;
			i++;
		}
		output << endl;
		output << "**Edges:" << endl;
		for (const auto& element : this->adjList) { // loop through the map keys, then loop through the map values which is another map
			output << " row " << element.first << ": "; //to print the edges
			for (const auto& element2 : this->adjList) {
				if (this->adjList.at(element.first).count(element2.first) == 0) {
					output << "F ";
				} else {
					output << "(T," << this->adjList.at(element.first).at(element2.first) << ") ";
				}
			}
			output << endl;
		}
		output << "**************************************************" << endl;
	}
};
