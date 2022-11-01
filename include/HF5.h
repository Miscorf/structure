// #include <hdf5.h>
// #include <iostream>
// #include <string>

// using namespace std;
// class HF5
// {
// private:
//     hid_t hf5_file; /* handles */
//     hid_t dataspace, dataset;
//     hid_t filespace, memspace;
//     hid_t prop;

//     hsize_t dims[2]; // 维度
//     hsize_t maxdims[2] = {H5S_UNLIMITED, H5S_UNLIMITED};
//     herr_t status;
//     // hsize_t chunk_dims[2] = {1, 3};
//     hsize_t chunk_dims[2];       // 块维度
//     int data[3][3] = {{1, 1, 1}, /* data to write */
//                       {1, 1, 1},
//                       {1, 1, 1}};

// public:
//     HF5();
//     HF5(const string &_name);
//     HF5(const string &_name, const int &_age);

// public:
//     ~HF5();
// };
