/*
 * Cluster.h
 *
 * Author: Viet Dinh
 * Date: 11/17/2016
 */

#ifndef H_CLUSTER
#define H_CLUSTER

class Cluster{
	//all vectors of this cluster
	std::list<std::vector<double>> vectors;
	//distances form this cluster to other clusters
	//distances saved and removed when necessary
	//so no need to recalculate every distance everytime mergeing clusters happens
	std::list<double> distances;
	//"center" vector of the cluster
	std::vector<double> centroid;
public:
	//this class only needs default constructor

	//merges add all vectors of "arg" to this cluster, remove all vectors of "arg"
	//clears centroid vector of "arg" and recalculate centroid vector of this cluster.
	void merge(Cluster &arg);
	//returns number of vectors of this cluster
	std::size_t size() const;
	//overloading subscript operator
	//returns indexed vector from list of vectors of this cluster
	const std::vector<double> &operator[](std::size_t index);
	//adds a vector to vector list of this cluster, recalculates centroid of this cluster
	void add_vector(std::vector<double> v);
	//returns distance between two centroids of this cluster and cluster "arg"
	double distance(const Cluster &arg);
	//adds a distance to the head of distance list
	void add_distance(double d);
	//inserts a distance at specfific position in list
	void insert_distance(std::size_t index, double d);
	//removes a distance at specific position in list
	void remove_distance(std::size_t index);
	//returns index of the cluster in list to which the distance from this cluster is minimum
	std::size_t min_distance_cluster_index();
	//returns distance from this cluster to the indexed cluster
	//returns -1 when index is negative
	double distance_by_index(std::size_t index);
	//empty distance list
	void clear_all_distances();

};

#endif