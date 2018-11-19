/*
 * main.cc
 *
 * Author: Viet Dinh
 * Date: 11/17/2016
 */

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <cstddef>
#include "Cluster.h"

using namespace std;

list<vector<double>> readInput(istream &is);

int main(int argc, char** argv){
	//no more than 1 argument accepted
	if (argc > 2){
		cout << " Too many arguments." << endl;
		return -1;
	}
	
	//argument must be a positive integer and in range of type size_t
	size_t cluster_number = 1;
	if (argc != 1){
		string str(argv[1]);
		try{
			cluster_number = stoi(str);
		}
		catch (const invalid_argument &e){
			cout << "Invalid argument. Number of clusters must be a positive integer." << endl;
			return -1;
		}
		catch (const out_of_range &e){
			cout << "Out of range of integer type." << endl;
			return -1;
		}
	}
	if (cluster_number < 1){
		cout << "Invalid argument. Number of clusters must be a positive integer." << endl;
		return -1;
	}

	//reads input and create a list of vectors
	//created an empty list of cluster
	list<vector<double>> vectors = readInput(cin);
	list<Cluster> clusters;
	if (vectors.size() < cluster_number){
		cout << "Number of clusters cant be greater than number of vectors.";
		return -1;
	}
	
	//For each vector in vector list:
	//creates an empty cluster
	//adds the vector to cluster
	for (list<vector<double>>::iterator it = vectors.begin(); it != vectors.end(); ++it){
		Cluster cluster;
		cluster.add_vector(*it);
		clusters.push_back(cluster);
	}

	//for each cluster in cluster list
	//calculates distances from it to all clusters standing before it in cluster list
	//adds distances to the cluster's distance list in same order as all clusters stading before it
	list<Cluster>::iterator it1 = clusters.end();
	list<Cluster>::iterator it2;
	--it1;
	for (size_t i = clusters.size() - 1; i > 0; --i){
		it2 = clusters.begin();
		advance(it2, i - 1);
		for (size_t j = i; j > 0; --j){
			(*it1).add_distance((*it1).distance(*it2));
			--it2;
		}
		--it1;
	}

	//finds 2 clusters that the distance between them is smallest
	//merges cluster 2 to cluster 1 and remove cluster 2 from the list
	//repeats two above steps until number of clusters left in list equals to the argument user pass to command line
	while (clusters.size() != cluster_number){
		//assigns smallest distance in distance list of last cluster to variable min_distance
		it1 = clusters.end();
		--it1;
		size_t source_index = clusters.size() - 1;
		size_t source_index_of_min_distance = source_index;
		size_t dest_index = (*it1).min_distance_cluster_index();
		size_t dest_index_of_min_distance = dest_index;
		double min_distance = (*it1).distance_by_index(dest_index_of_min_distance);
		--it1;
		//iterates through all other clusters in the cluster list, except the first cluster
		//finds the smallest distance in distance list of each cluster
		//compares this distance to min_distance and updates min_distance if necessary
		for (; it1 != clusters.begin(); --it1){
			--source_index;
			dest_index = (*it1).min_distance_cluster_index();
			double temp = (*it1).distance_by_index(dest_index);
			if (temp < min_distance){
				min_distance = temp;
				source_index_of_min_distance = source_index;
				dest_index_of_min_distance = dest_index;
			}
		}
		//merges 2 clusters that the distance between them is smallest
		//2 clusters become only one cluster
		//updates distance list of each cluster in list
		it1 = clusters.begin();
		it2 = clusters.begin();
		advance(it1, source_index_of_min_distance);
		advance(it2, dest_index_of_min_distance);
		(*it1).merge(*it2);
		it2 = clusters.erase(it2);
		while (it2 != it1){
			(*it2).remove_distance(dest_index_of_min_distance);
			++it2;
		}
		(*it1).clear_all_distances();
		while (it2 != clusters.begin()){
			--it2;
			(*it1).add_distance((*it1).distance(*it2));
		}
		++it1;
		while (it1 != clusters.end()){
			(*it1).remove_distance(source_index_of_min_distance);
			(*it1).remove_distance(dest_index_of_min_distance);
			auto it3 = clusters.begin();
			advance(it3, source_index_of_min_distance - 1);
			double temp = (*it1).distance(*it3);
			(*it1).insert_distance(source_index_of_min_distance - 1, temp);
			++it1;
		}
	}

	//prints all clusters in list to output
	it1 = clusters.begin();
	for (size_t i = 0; i < clusters.size(); ++i){
		cout << "CLUSTER #" << i + 1 << endl;
		for (size_t j = 0; j < (*it1).size(); ++j){
			for (size_t k = 0; k < (*it1)[j].size(); ++k){
				cout << (*it1)[j][k] << "  ";
			}
			cout << "\n";
		}
		++it1;
		if (i != clusters.size() - 1){
			cout << "\n";
		}
	}

	return 0;
}

list<vector<double>> readInput(istream &is){
	string temp;//holds each line read from input
	list<vector<double>> tempList;
	size_t previous_vector_size = 0;
	while (getline(is, temp)){
		if (temp.find_first_not_of(" \t") != string::npos){
			size_t first_not_a_space = temp.find_first_not_of(" \t");
			size_t last_not_a_space = temp.find_last_not_of(" \t");
			temp = temp.substr(first_not_a_space, last_not_a_space - first_not_a_space + 1);
			stringstream ss(temp);
			string tok;
			vector<double> tempVec;
			while (std::getline(ss, tok, ' ')){
				try{
					tempVec.push_back(stod(tok));
				}
				catch (const invalid_argument &e){
					cout << "Invalid dimension's value found, must be double type." << endl;
					exit(-1);
				}
				catch (const out_of_range &e){
					cout << "Out of range of double type." << endl;
					exit(-1);
				}
			}

			if (previous_vector_size != 0){
				if (tempVec.size() != previous_vector_size){
					cout << "Vectors have different number of dimensions." << endl;
					exit(-1);
				}
			}
			else{
				previous_vector_size = tempVec.size();
			}

			tempList.push_back(tempVec);
		}
	}
	
	return tempList;
}