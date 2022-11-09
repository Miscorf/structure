#ifndef _HF5_FILE
#define _HF5_FILE

#include <hdf5.h>
#define RANK 2
class HF5
{
private:
    hid_t file; /* handles */
    hid_t dataspace, dataset;
    hid_t filespace, memspace;
    hid_t prop;

    hsize_t dims[2] = {0, 0}; // = {0, 3}; // group 维度
    hsize_t maxdims[2] = {H5S_UNLIMITED, H5S_UNLIMITED};
    herr_t status;
    // hsize_t chunk_dims[2] = {1, 3};
    hsize_t chunk_dims[2];        // 块 维度
    int data[1][3] = {{1, 1, 1}}; /* data to write */

public:
    HF5();
    HF5(char *file_name, char *dataset_name, hsize_t _chunk_dims[]);
    void get_dims(hsize_t *buf);
    herr_t extend_write_chunk(hsize_t dimsext[], void *dataext);
    herr_t close();

public:
    ~HF5();
};

#endif