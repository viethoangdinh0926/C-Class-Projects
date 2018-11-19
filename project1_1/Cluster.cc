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
	if (centroid.size() == 0){
		for (size_t i = 0; i < arg.centroid.size(); ++i){
			centroid.push_back(arg.centroid.at(i));
		}
	}
	else{
		size_t size = vectors.size();
		size_t arg_size = arg.vectors.size();
		for (size_t i = 0; i < arg.centroid.size(); ++i){
			centroid[i] = (centroid[i] * size + arg.centroid[i] * arg_size)/(size + arg_size);
		}
	}
	
	vectors.merge(arg.vectors);
	arg.distances.clear();
	arg.centroid.clear();
}

size_t Cluster::size() const {
	return vectors.size();
}

const vector<double> &Cluster::operator[](size_t index){
	list<vector<double>>::iterator it = vectors.begin();
	advance(it, index);
	return *it;
}

void Cluster::add_vector(vector<double> v){
	if (centroid.size() == 0){
		for (size_t i = 0; i < v.size(); ++i){
			centroid.push_back(v[i]);
		}
	}
	else{
		for (size_t i = 0; i < v.size(); ++i){
			centroid[i] = (centroid[i]*vectors.size() + v[i])/(vectors.size() + 1);
		}
	}
	vectors.push_back(v);
}

double Cluster::distance(const Cluster &arg){
	double distance = 0;
	for (size_t i = 0; i < centroid.size(); ++i){
		distance += (centroid[i] - arg.centroid[i])*(centroid[i] - arg.centroid[i]);
	}
	distance = sqrt(distance);
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