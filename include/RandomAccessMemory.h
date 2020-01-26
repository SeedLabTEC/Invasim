#ifndef INCLUDE_RandomAccessMemory_H_
#define INCLUDE_RandomAccessMemory_H_

#define SIZE 256

/**
* @file RandomAccessMemory.h
* @brief Memory class declaration
* @author Jairo Ortega Calderon
* @date 20/09/19
**/
class RandomAccessMemory{
    private:
        int chunk[SIZE] = {};
        
    public:
        /**
         * @brief Construct a new Random Access Memory class
         */
        RandomAccessMemory();
        /**
         * @brief Read from memory and write it.
         * @param pRD Flag for read
         * @param pWR Flag for write
         * @param pdirection Address to read/write
         * @param pdata Data to write
         * @return int value of memory
         */
        int read_write_Mem(bool pRD, bool pWR, int pdirection, int pdata);
};

#endif