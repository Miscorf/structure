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

    hsize_t dims[RANK] = {0, 0};
    hsize_t maxdims[RANK] = {H5S_UNLIMITED, H5S_UNLIMITED};
    herr_t status;
    // hsize_t chunk_dims[2] = {1, 3};
    hsize_t chunk_dims[RANK]; // 块 维度

public:
    HF5();

    /// @brief 创建hf5类
    /// @param file_name
    /// @param dataset_name
    /// @param _chunk_dims 块维度大小

    HF5(char *file_name, char *dataset_name, hsize_t _chunk_dims[]);

    /// @brief 获取块维度参数
    /// @param  chunk_dims 存放位置
    void get_dims(hsize_t *chunk_dims);

    /// @brief 按块写入
    /// @param dimsext 块大小
    /// @param dataext 数据
    /// @return
    herr_t extend_write_chunk(hsize_t dimsext[], void *dataext);
    herr_t close();
    ~HF5();
};

#endif