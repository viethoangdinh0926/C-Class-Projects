/*
 * Cluster.h
 *
 * Author: Viet Dinh
 * Date: 11/17/2016
 */

#ifndef H_CLUSTER
#define H_CLUSTER

class Cluster{
	//contains indices of vectors in vec_arr, which belong to the cluster
	std::list<std::size_t> indices;
	//the array contains all vectors need to devide into clusters
	const std::list<std::vector<double>> &vec_arr;
	//list of all distances between 2 vectors for all vectors in vec_arr
	//order of elements in list will follow the rule: 
	//vec0-vec1, vec0-vec2,...vec0-vecN,vec1-vec2,vec1-vec3,...,vec1-vecN,...,vec(N-1)-vecN
	//N+1 is size of vec_arr
	const std::list<double> &dist_arr;
	//distances form this cluster to other clusters
	//distances saved and removed when necessary
	//so no need to recalculate every distance everytime mergeing clusters happens
	std::list<double> distances;
public:
	//constructor
	Cluster(const std::list<std::vector<double>> &arg, const std::list<double> &arg1):vec_arr(arg), dist_arr(arg1) {};
	//merges add all vectors of "arg" to this cluster, remove all vectors of "arg"
	//clears centroid vector of "arg" and recalculate centroid vector of this cluster.
	void merge(Cluster &arg);
	//returns number of vectors of this cluster
	std::size_t size() const;
	//overloading subscript operator
	//returns indexed vector from list of vectors of this cluster
	const std::vector<double> &operator[](std::size_t index);
	//adds a vector to vector list of this cluster, recalculates centroid of this cluster
	void add_vector(std::size_t vec_index);
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