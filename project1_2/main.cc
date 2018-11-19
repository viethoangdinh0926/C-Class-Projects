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
#include <cmath>
#include "Cluster.h"

using namespace std;

//reads input
//returns a list of double vector
list<vector<double>> readInput(istream &is);
//merges clusters in cluster list
//leave c_num clusters in cluster list after merging
void merge_clusters(list<Cluster> &clusters, const size_t c_num);

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

	//calculate all distances between each 2 vectors for all vectors and put in a list
	list<double> distances;
	auto it0 = vectors.begin();
	size_t vec_num = vectors.size();
	size_t vector_size = (*it0).size();
	for (size_t i = 0; i < vec_num - 1; ++i){
		auto it2 = vectors.begin();
		advance(it2, i + 1);
		for (size_t j = i + 1; j < vec_num; ++j){
			double dist = 0;
			for (size_t k = 0; k < vector_size; ++k){
				dist += ((*it2)[k] - (*it0)[k]) * ((*it2)[k] - (*it0)[k]);
			}
			dist = sqrt(dist);
			distances.push_back(dist);
			++it2;
		}
		++it0;
	}

	//For each vector in vector list
	//creates an empty cluster
	//adds the vector to cluster
	size_t index = 0;
	for (list<vector<double>>::iterator it = vectors.begin(); it != vectors.end(); ++it){
		Cluster cluster(vectors, distances);
		cluster.add_vector(index);
		clusters.push_back(cluster);
		++index;
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
	

	merge_clusters(clusters, cluster_number);
	
	//prints all clusters in list to output
	cout << "\n\nResulting clusters:" << endl;
	it1 = clusters.begin();
	size_t size1 = clusters.size();
	for (size_t i = 0; i < size1; ++i){
		cout << "cluster: [";
		size_t size2 = (*it1).size();
		for (size_t j = 0; j < size2; ++j){
			cout << "[";
			size_t size3 = (*it1)[j].size();
			for (size_t k = 0; k < size3; ++k){
				cout << (*it1)[j][k];
				if (k != size3 - 1){
					cout << " ";
				}
				else{
					cout << "]";
				}
			}
			if (j != size2 - 1){
				cout << ", ";
			}
			else{
				cout << "]" << endl;
			}
		}
		++it1;
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

void merge_clusters(list<Cluster> &clusters, const size_t c_num){
	//finds 2 clusters that the distance between them is smallest
	//merges cluster 2 to cluster 1 and remove cluster 2 from the list
	//repeats two above steps until number of clusters left in list equals to the argument user pass to command line
	while (clusters.size() != c_num){
		auto it1 = clusters.end();
		--it1;
		size_t source_index = clusters.size() - 1;
		size_t source_index_of_min_distance = source_index;
		size_t dest_index = (*it1).min_distance_cluster_index();
		size_t dest_index_of_min_distance = dest_index;
		double min_distance = (*it1).distance_by_index(dest_index_of_min_distance);
		--it1;

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

		it1 = clusters.begin();
		auto it2 = clusters.begin();
		advance(it1, source_index_of_min_distance);
		advance(it2, dest_index_of_min_distance);

		//print merging process
		cout << "Merging: cluster: [";
		size_t size1 = (*it1).size();
		for (size_t i = 0; i < size1; ++i){
			cout << "[";
			size_t size2 = (*it1)[i].size();
			for (size_t j = 0; j < size2; ++j){
				if (j != size2 - 1){
					cout << (*it1)[i][j] << " ";
				}
				else{
					cout << (*it1)[i][j] << "]";
					if (i != size1 - 1){
						cout << ", ";
					}
					else{
						cout << "]" << endl;
					}
				}
			}
		}
		cout << "         cluster: [";
		size1 = (*it2).size();
		for (size_t i = 0; i < size1; ++i){
			cout << "[";
			size_t size2 = (*it2)[i].size();
			for (size_t j = 0; j < size2; ++j){
				if (j != size2 - 1){
					cout << (*it2)[i][j] << " ";
				}
				else{
					cout << (*it2)[i][j] << "]";
					if (i != size1 - 1){
						cout << ", ";
					}
					else{
						cout << "]" << endl;
					}
				}
			}
		}

		//merge and remove
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
}