#include <hdf5.h>
#include <iostream>
#include <string>

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
    HF5(char *file_name, char *dataset_name, hsize_t _chunk_dims[], int time_flag);
    void get_dims(hsize_t *buf);
    herr_t extend_write_chunk(hsize_t dimsext[], void *dataext);

public:
    ~HF5();
};

HF5::HF5(char *file_name, char *dataset_name, hsize_t _chunk_dims[], int time_flag)
{
    hsize_t size[2];
    dataspace = H5Screate_simple(RANK, dims, maxdims);
    file = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    size[0] = 0;
    size[1] = _chunk_dims[1];
    chunk_dims[0] = _chunk_dims[0];
    chunk_dims[1] = _chunk_dims[1];
    prop = H5Pcreate(H5P_DATASET_CREATE);
    status = H5Pset_chunk(prop, RANK, chunk_dims);
    dataset = H5Dcreate2(this->file, dataset_name, H5T_NATIVE_INT, dataspace,
                         H5P_DEFAULT, prop, H5P_DEFAULT);
    status = H5Dset_extent(dataset, size);
}
void HF5::get_dims(hsize_t *buf)
{
    herr_t sta;
    hsize_t now_dims[2];

    filespace = H5Dget_space(dataset);
    sta = H5Sget_simple_extent_dims(filespace, now_dims, NULL);
    buf[0] = now_dims[0];
    buf[1] = now_dims[1];
    // std::cout << "buf:" << buf[0] << " " << buf[1] << std::endl;
    // status = H5Dclose(filespace);
}
herr_t HF5::extend_write_chunk(hsize_t dimsext[], void *dataext)
{
    hsize_t size[2];
    hsize_t offset[2];
    // 获取维度信息
    filespace = H5Dget_space(dataset);
    status = H5Sget_simple_extent_dims(filespace, dims, NULL);
    // Extend the dataset.
    size[0] = dims[0] + dimsext[0];
    size[1] = dims[1];
    status = H5Dset_extent(dataset, size);
    // Select a hyperslab.
    // std::cout << "dims:" << dims[0] << std::endl;
    filespace = H5Dget_space(dataset);
    offset[0] = dims[0];
    offset[1] = 0;
    status = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL,
                                 dimsext, NULL);
    // std::cout << "exten size:" << size[0] << size[1] << std::endl;
    // std::cout << "dims:" << dims[0] << std::endl;

    // Define memory space.
    memspace = H5Screate_simple(RANK, dimsext, NULL);

    // Write the data to the hyperslab.
    status = H5Dwrite(dataset, H5T_NATIVE_INT, memspace, filespace,
                      H5P_DEFAULT, dataext);
    return status;
}

HF5::~HF5()
{
    try
    {
        status = H5Dclose(dataset);
        status = H5Pclose(prop);
        status = H5Sclose(dataspace);
        status = H5Sclose(memspace);
        status = H5Sclose(filespace);
        status = H5Fclose(file);
    }
    catch (const std::exception &e)
    {
        std::cerr << "析构函数出现错误！" << e.what() << '\n';
    }
}
