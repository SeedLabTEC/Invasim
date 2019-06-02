/**
* @file Utils.h
* @brief Header with global includes and declarations
* @author Dennis Porras Barrantes
* @date 09/02/19
**/

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

/**
 * @brief Include output and assert/test libraries
 * */
#include <stdio.h>
#include <cassert>
#include <iostream>

/**
 * @brief Verify if NDEBUG flag is set, to use debug funtions
 * */
#ifndef NDEBUG
#define dprintf(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define dprintf(fmt, ...) ((void)0)
#endif

//Global Structs

/**
 * @brief Struct that represents a coordinate in the matrix of processors.
 * 
 */
struct coordinate
{
	int x;
	int y;
};

/**
 * @brief Enum to define that differents states that a processing unit can have in invasive computing.
 * 
 */
enum Invasive_States
{
	INVADED,
	INFECTED,
	FREE
};

/**
 * @brief Array asociated to Invasive_States enum.
 * 
 */
static const std::string STRING_STATES[] = 
{
	"Invaded",
	"Infected",
	"Free"
};

#endif