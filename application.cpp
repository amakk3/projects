/*-------------------------------------------
Program 5: Open mapping of UIC campus with template class graph and Dijkstra's algorithm
Course: CS 251, Fall 2023, UIC
System: VS Code
Name: Abrar Makki
------------------------------------------- */
//
//
// Adam T Koehler, PhD
// University of Illinois Chicago
// CS 251, Fall 2023
//
// Project Original Variartion By:
// Joe Hummel, PhD
// University of Illinois at Chicago
//
// 
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <queue>

#include "tinyxml2.h"
#include "dist.h"
#include "graph.h"
#include "osm.h"


using namespace std;
using namespace tinyxml2;

const double INF = numeric_limits<double>::max();

//class to compare a pair of vertices and their distance in the priority queue
class prioritize {
	public:
	bool operator()(const pair<long long, double>& p1, pair<long long, double>& p2) const {
		return p1.second > p2.second;
	}
};
//function to find the nearest node to a given node, and return the coordinates to that node
Coordinates findNearestNode(BuildingInfo& building, vector<FootwayInfo>& Footways, map<long long, Coordinates>& Nodes) {
	//given building, find nearest footway node
	double minDist = INF;
	Coordinates nearestNode;
	for (const auto& FootwayInfo : Footways) { //go through footways and then go through nodes in each footway, and find the nearest node to the building
		for (const auto& node : FootwayInfo.Nodes) {
			if (distBetween2Points(building.Coords.Lat, building.Coords.Lon, Nodes.at(node).Lat, Nodes.at(node).Lon) < minDist) {
				minDist = distBetween2Points(building.Coords.Lat, building.Coords.Lon, Nodes.at(node).Lat, Nodes.at(node).Lon);
				nearestNode = Nodes.at(node);
			}
		}
	}
	return nearestNode;
}

// dijkstra's algorithm to return the shortest path between two nodes, a path vector, and a boolean to check if path exists
pair<pair<vector<long long>, double>, bool> dijkstra(graph<long long, double>& G, long long start, long long dest) {
	pair<vector<long long>, double> path; // path vector and distance
	map<long long, double> dist; 
	map<long long, long long> pred; 
	double weight;
	priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> pq;
	for (const auto& vertex : G.getVertices()) { // for each vertex in the graph, set distance to infinity and predecessor to 0
		dist[vertex] = INF;
		pred[vertex] = 0;
		pq.push(make_pair(vertex, INF));//push each vertex into the priority queue
	}
	dist[start] = 0; // set start distance to 0
	pq.push(make_pair(start, 0));//push start into the priority queue
	while (!pq.empty()) { // while the priority queue is not empty, pop the top element
		auto currV = pq.top().first;
		if (dist[currV] == INF) { // if currV has not been visited
			break;
		} else if (currV == dest) { //else if currV is the destination
			break;
		} else { // else pop the top element and continue path from that element
			pq.pop();
		}
		auto neighbors = G.neighbors(currV);
		for (const auto& adj : neighbors) { //loop through neighbors of currV to find the shortest path
			G.getWeight(adj, currV, weight);
			auto alt = dist[currV] + weight;//calculate the distance from currV to adj
			if (alt < dist[adj]) { //compare the distance from currV to adj to the distance from start to adj to pick the shortest path
				dist[adj] = alt;
				pred[adj] = currV;
				pq.push(make_pair(adj, alt));//push the new distance into the priority queue
			}
		}
	}
	vector<long long> pathList;//vector to store the path
	long long currV = dest;
	//check if path exists
	if (pred[currV] == 0 && currV != start) { //build path vector, if path does not exist, return false, else return true
		path.first = pathList;
		path.second = -1;
		pair<pair<vector<long long>, double>, bool> pathAndPred;
		pathAndPred.first = path;
		pathAndPred.second = false;
		return pathAndPred;
	}
	while (pred[currV] != 0) { //build path vector based on predecessor
		pathList.push_back(currV);
		currV = pred[currV];
	}
	pathList.push_back(currV);//start with the start node then reverse the vector to get the correct path order from start to dest
	reverse(pathList.begin(), pathList.end());
	path.first = pathList;
	path.second = dist[dest];
	pair<pair<vector<long long>, double>, bool> pathAndPred;//store the path vector, distance, and boolean in a triple
	pathAndPred.first = path;
	pathAndPred.second = true;
	return pathAndPred;
}
//function to run the main application search engine
void application(
	map<long long, Coordinates>& Nodes, vector<FootwayInfo>& Footways,
	vector<BuildingInfo>& Buildings, graph<long long, double>& G) {
	string person1Building, person2Building;

	cout << endl;
	cout << "Enter person 1's building (partial name or abbreviation), or #> ";
	getline(cin, person1Building);

	while (person1Building != "#") {
		cout << "Enter person 2's building (partial name or abbreviation)> ";
		getline(cin, person2Building);
	    // search for buildings 1 & 2 given partial name or abbreviation
		bool found1 = false;
		bool found2 = false;
		// pathfound = false;
		BuildingInfo p1building, p2building, destBuilding;
		for (const auto& building : Buildings) { // for each building
			if ((building.Abbrev == person1Building || building.Fullname.find(person1Building) != string::npos) && (!found1)) { // if building 1 is found
				p1building = building;
				found1 = true;
			}
			if ((building.Abbrev == person2Building || building.Fullname.find(person2Building) != string::npos) && (!found2)) { // if building 2 is found
				p2building = building;
				found2 = true;
			}
		}
		if (!found1) {
			cout << "Person 1's building not found" << endl;
			cout << "Enter person 1's building (partial name or abbreviation), or #> ";
			getline(cin, person1Building);
			continue;
		} else if (!found2) {
			cout << "Person 2's building not found" << endl;
			cout << "Enter person 1's building (partial name or abbreviation), or #> ";
			getline(cin, person1Building);
			continue;
		}
		//find the nearest building to the center of the two buildings given
		double minDist1 = INF;
		cout << "\nPerson 1's point:\n " << p1building.Fullname << endl;
		cout << " (" << p1building.Coords.Lat << ", " << p1building.Coords.Lon << ")" << endl;
		cout << "Person 2's point:\n " << p2building.Fullname << endl;
		cout << " (" << p2building.Coords.Lat << ", " << p2building.Coords.Lon << ")" << endl;
		Coordinates center = centerBetween2Points(p1building.Coords.Lat, p1building.Coords.Lon, p2building.Coords.Lat, p2building.Coords.Lon);
		for (const auto& building : Buildings) { // for each building calculate the distance and find min distance to center
			if (distBetween2Points(building.Coords.Lat, building.Coords.Lon, center.Lat, center.Lon) < minDist1) {
				minDist1 = distBetween2Points(building.Coords.Lat, building.Coords.Lon, center.Lat, center.Lon);
				destBuilding = building;
			}
		}
		cout << "Destination Building:" << endl;
		cout << " " << destBuilding.Fullname << endl;
		cout << " (" << destBuilding.Coords.Lat << ", " << destBuilding.Coords.Lon << ")" << endl;
		// find the nearest nodes of the buildings and the destination building
		auto p1node = findNearestNode(p1building, Footways, Nodes);
		auto p2node = findNearestNode(p2building, Footways, Nodes);
		auto destnode = findNearestNode(destBuilding, Footways, Nodes);
		cout << "\nNearest P1 node:\n " << p1node.ID << endl;
		cout << " (" << p1node.Lat << ", " << p1node.Lon << ")" << endl;
		cout << "Nearest P2 node:\n " << p2node.ID << endl;
		cout << " (" << p2node.Lat << ", " << p2node.Lon << ")" << endl;
		cout << "Nearest destination node:\n " << destnode.ID << endl;
		cout << " (" << destnode.Lat << ", " << destnode.Lon << ")" << endl;
		//create paths from each person to the destination building and to one another if valid
		auto path1 = dijkstra(G, p1node.ID, destnode.ID);
		auto path2 = dijkstra(G, p2node.ID, destnode.ID);
		auto path3 = dijkstra(G, p1node.ID, p2node.ID);
		//calculate the distance from each node to the next in the path1 list
		if (path1.second == false && (p1building.Abbrev != p2building.Abbrev)) { //if path1 does not exist and the buildings are not the same
			cout << "Sorry, destination unreachable." << endl;
		} else if (path3.second == false) { //if the there isnt a valid path from p1 to p2 at all
			cout << "Sorry, destination unreachable." << endl;
		}else {
			cout << "\nPerson 1's distance to dest: " << path1.first.second <<  " miles" << endl;
			cout << "Path: ";
			for (const auto& node : path1.first.first) { //print the path from p1 to dest
				cout << node;
				if (node != path1.first.first[path1.first.first.size() - 1]) {
					cout << "->";
				}
			}
			cout << endl;
			cout << "\nPerson 2's distance to dest: " << path2.first.second <<  " miles" << endl;
			cout << "Path: ";
			for (const auto& node : path2.first.first) { //print the path from p2 to dest
				cout << node;
				if (node != path2.first.first[path2.first.first.size() - 1]) {
					cout << "->";
				}
			}
		}
		cout << endl;
		cout << "Enter person 1's building (partial name or abbreviation), or #> ";
		getline(cin, person1Building);
	}
}

int main() {
	// maps a Node ID to it's coordinates (lat, lon)
	map<long long, Coordinates>  Nodes;
	// info about each footway, in no particular order
	vector<FootwayInfo>          Footways;
	// info about each building, in no particular order
	vector<BuildingInfo>         Buildings;
	XMLDocument                  xmldoc;

	cout << "** Navigating UIC open street map **" << endl;
	cout << endl;
	cout << std::setprecision(8);

	string def_filename = "map.osm";
	string filename;

	cout << "Enter map filename> ";
	getline(cin, filename);

	if (filename == "") {
		filename = def_filename;
	}

	//
	// Load XML-based map file
	//
	if (!LoadOpenStreetMap(filename, xmldoc)) {
		cout << "**Error: unable to load open street map." << endl;
		cout << endl;
		return 0;
	}

	//
	// Read the nodes, which are the various known positions on the map:
	//
	int nodeCount = ReadMapNodes(xmldoc, Nodes);

	//
	// Read the footways, which are the walking paths:
	//
	int footwayCount = ReadFootways(xmldoc, Footways);

	//
	// Read the university buildings:
	//
	int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

	//
	// Stats
	//
	assert(nodeCount == (int)Nodes.size());
	assert(footwayCount == (int)Footways.size());
	assert(buildingCount == (int)Buildings.size());

	cout << endl;
	cout << "# of nodes: " << Nodes.size() << endl;
	cout << "# of footways: " << Footways.size() << endl;
	cout << "# of buildings: " << Buildings.size() << endl;

	graph<long long, double> G;

	// add vertices to graph
	for (const auto& element : Nodes) {
		G.addVertex(element.first);
	}

	// add distance between nodes to graph
	for (const auto& FootwayInfo : Footways) {
		for (size_t i = 0; i < FootwayInfo.Nodes.size() - 1; i++) {
			auto node1 = FootwayInfo.Nodes.at(i);
			auto node2 = FootwayInfo.Nodes.at(i + 1);
			auto dist = distBetween2Points(Nodes.at(node1).Lat, Nodes.at(node1).Lon, Nodes.at(node2).Lat, Nodes.at(node2).Lon);
			G.addEdge(node1, node2, dist);
			G.addEdge(node2, node1, dist);
		}
	}
	cout << "# of vertices: " << G.NumVertices() << endl;
	cout << "# of edges: " << G.NumEdges() << endl;
	cout << endl;

	// Execute Application
	application(Nodes, Footways, Buildings, G);

	//
	// done:
	//
	cout << "** Done **" << endl;
	return 0;
}
