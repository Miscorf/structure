/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the COPYING file, which can be found at the root of the source code       *
 * distribution tree, or in https://support.hdfgroup.org/ftp/HDF5/releases.  *
 * If you do not have access to either file, you may request a copy from     *
 * help@hdfgroup.org.                                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 *  This example how to work with extendible datasets. The dataset
 *  must be chunked in order to be extendible.
 *
 *  It is used in the HDF5 Tutorial.
 */

#include <stdint.h>
#include <hdf5.h>
#include <H5Cpp.h>
#include <iostream>

#define FILENAME "extbyrow.h5"
#define DATASETNAME "ExtendibleArray"
#define RANK 2

using namespace std;

int main(void)
{
    hid_t file; /* handles */
    hid_t dataspace, dataset;
    hid_t filespace, memspace;
    hid_t prop;

    hsize_t dims[2] = {3, 3}; /* dataset dimensions at creation time */
    hsize_t maxdims[2] = {H5S_UNLIMITED, H5S_UNLIMITED};
    herr_t status;
    hsize_t chunk_dims[2] = {1, 3};
    int data[3][3] = {{1, 1, 1}, /* data to write */
                      {1, 1, 1},
                      {1, 1, 1}};

    /* Variables used in extending and writing to the extended portion of dataset */
    hsize_t size[2];
    hsize_t offset[2];
    hsize_t dimsext[2] = {1, 3}; /* extend dimensions */
    int dataext[1][3] = {{5, 5, 5}};

    /* Variables used in reading data back */
    hsize_t chunk_dimsr[2];
    hsize_t dimsr[2];
    hsize_t i, j;
    int rdata[6][3];
    herr_t status_n;
    int rank, rank_chunk;

    /* Create the data space with unlimited dimensions. */
    dataspace = H5Screate_simple(RANK, dims, maxdims);

    /* Create a new file. If file exists its contents will be overwritten. */
    file = H5Fcreate(FILENAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /* Modify dataset creation properties, i.e. enable chunking  */
    prop = H5Pcreate(H5P_DATASET_CREATE);
    status = H5Pset_chunk(prop, RANK, chunk_dims);

    /* Create a new dataset within the file using chunk
       creation properties.  */
    dataset = H5Dcreate2(file, DATASETNAME, H5T_NATIVE_INT, dataspace,
                         H5P_DEFAULT, prop, H5P_DEFAULT);

    /* Write data to dataset */
    status = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL,
                      H5P_DEFAULT, data);

    /* Extend the dataset. Dataset becomes 4 x 3  */
    hsize_t dim_new[2];
    int tag = 0;
    for (size_t i = 0; i < 3; i++)
    {
        filespace = H5Dget_space(dataset);
        status_n = H5Sget_simple_extent_dims(filespace, dim_new, NULL);
        size[0] = dim_new[0] + dimsext[0];
        size[1] = dim_new[1];
        cout << size[0] << size[1] << endl;
        status = H5Dset_extent(dataset, size);

        /* Select a hyperslab in extended portion of dataset  */

        offset[0] = i + 2;
        offset[1] = 0;
        status = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL,
                                     dimsext, NULL);

        /* Define memory space */
        memspace = H5Screate_simple(RANK, dimsext, NULL);

        /* Write the data to the extended portion of dataset  */
        status = H5Dwrite(dataset, H5T_NATIVE_INT, memspace, filespace,
                          H5P_DEFAULT, dataext);
    }

    tag++;

    /* Close resources */
    status = H5Dclose(dataset);
    status = H5Pclose(prop);
    status = H5Sclose(dataspace);
    status = H5Sclose(memspace);
    status = H5Sclose(filespace);
    status = H5Fclose(file);

    /********************************************
     * Re-open the file and read the data back. *
     ********************************************/

    file = H5Fopen(FILENAME, H5F_ACC_RDONLY, H5P_DEFAULT);
    dataset = H5Dopen2(file, DATASETNAME, H5P_DEFAULT);

    filespace = H5Dget_space(dataset);
    rank = H5Sget_simple_extent_ndims(filespace);
    status_n = H5Sget_simple_extent_dims(filespace, dimsr, NULL);

    prop = H5Dget_create_plist(dataset);

    if (H5D_CHUNKED == H5Pget_layout(prop))
        rank_chunk = H5Pget_chunk(prop, rank, chunk_dimsr);

    memspace = H5Screate_simple(rank, dimsr, NULL);
    cout << "dimsr:" << dimsr[0] << dimsr[1] << endl;
    status = H5Dread(dataset, H5T_NATIVE_INT, memspace, filespace,
                     H5P_DEFAULT, rdata);

    printf("\n");
    printf("Dataset: \n");
    for (j = 0; j < dimsr[0]; j++)
    {
        for (i = 0; i < dimsr[1]; i++)
            printf("%d ", rdata[j][i]);
        printf("\n");
    }

    status = H5Pclose(prop);
    status = H5Dclose(dataset);
    status = H5Sclose(filespace);
    status = H5Sclose(memspace);
    status = H5Fclose(file);
}