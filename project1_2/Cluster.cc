/*
 * Cluster.cc
 *
 * Author: Viet Dinh
 * Date: 11/17/2016
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <iterator>
#include <cstddef>
#include "Cluster.h"

using namespace std;

void Cluster::merge(Cluster &arg){
	indices.merge(arg.indices);
	arg.distances.clear();
}

size_t Cluster::size() const {
	return indices.size();
}

const vector<double> &Cluster::operator[](size_t index){
	list<size_t>::iterator it0 = indices.begin();
	advance(it0, index);
	auto it = vec_arr.begin();
	advance(it, *it0);
	return *it;
}

void Cluster::add_vector(size_t vec_index){
	indices.push_back(vec_index);
}

double Cluster::distance(const Cluster &arg){
	double distance = 0;
	auto dist_arr_it = dist_arr.begin();
	auto it1 = indices.begin();
	size_t num_of_all_vec = vec_arr.size();
	size_t size1 = indices.size();
	size_t size2 = arg.indices.size();
	for (size_t i = 0; i < size1; ++i){
		auto it2 = arg.indices.begin();
		for (size_t j = 0; j < size2; ++j){	
			size_t x = *it1, y = *it2;
			if (x > y){
				x = *it2, y = *it1;
			}
			advance(dist_arr_it, x*(2 * num_of_all_vec - x - 3) / 2 + y - 1);
			distance += *dist_arr_it;
			dist_arr_it = dist_arr.begin();
			++it2;
		}
		++it1;
	}
	distance = distance / size1 / size2;
	return distance;
}

void Cluster::add_distance(double d){
	distances.push_front(d);
}

void Cluster::insert_distance(size_t index, double d){
	auto it = distances.begin();
	advance(it, index);
	distances.insert(it, d);
}

void Cluster::remove_distance(size_t index){
	auto it = distances.begin();
	advance(it, index);
	distances.erase(it);
}

size_t Cluster::min_distance_cluster_index(){
	if (distances.size() == 0) return -1;
	auto it = distances.begin();
	double min_dist = *it;
	++it;
	size_t index = 0, index_of_min = 0;
	for (it; it != distances.end(); ++it){
		++index;
		if (*it < min_dist){
			min_dist = *it;
			index_of_min = index;
		}
	}
	return index_of_min;
}

double Cluster::distance_by_index(size_t index){
	auto it = distances.begin();
	advance(it, index);
	return *it;
}

void Cluster::clear_all_distances(){
	distances.clear();
}