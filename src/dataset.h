#ifndef DATASET_H
#define DATASET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <gsl/gsl_sf_gamma.h>
#include <inttypes.h>
#include "utils.h"
#include "detector.h"
#ifdef WITH_HDF5
#include <hdf5.h>
#endif // WITH_HDF5

struct dataset {
	// Data set type (0=sparse, 1=dense integer, 2=dense double)
	int type ;
	int num_data, num_pix, num_data_prev ;
	double mean_count ;
	char filename[1024] ;
	
	// Sparse dataset
	long ones_total, multi_total ;
	int *ones, *multi, *place_ones, *place_multi, *count_multi ;
	long *ones_accum, *multi_accum ;
	
	// Dense dataset
	double *frames ;
	int *int_frames ;
	
	// Pointer to next dataset
	struct dataset *next ;
	
	// Need only be defined for head dataset
	int tot_num_data, num_blacklist ;
	double tot_mean_count ;
	int *count ;
	double *sum_fact ;
	uint8_t *blacklist ;
} ;

int data_from_config(char*, char*, char*, struct detector*, struct dataset*) ;
void calc_sum_fact(struct detector*, struct dataset*) ;
int parse_dataset(char*, struct detector*, struct dataset*) ;
int parse_dataset_list(char*, struct detector*, struct dataset*) ;
void blacklist_from_config(char*, char*, struct dataset*) ;
void make_blacklist(char*, int, struct dataset*) ;
int write_dataset(struct dataset*) ;
void calc_powder(struct detector*, struct dataset*) ;
void free_data(int, struct dataset*) ;

#endif //DATASET_H
