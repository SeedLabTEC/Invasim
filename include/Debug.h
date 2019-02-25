/**
* @file Debug.h
* @brief Description
* @author Dennis Porras Barrantes
* @date 09/02/19
**/

#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

/**
 * @brief Include output and assert/test libraries
 * */
#include <stdio.h>
#include <cassert>

/**
 * @brief Verify if NDEBUG flag is set, to use debug funtions
 * */ 
#ifndef NDEBUG
#define dprintf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define dprintf(fmt, ...) ((void)0)
#endif

#endif