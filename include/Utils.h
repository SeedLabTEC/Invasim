/**
* @file Utils.h
* @brief Description
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
struct coordinate
{
	int x;
	int y;
};

enum Invasive_States
{
	INVADED,
	INFECTED,
	FREE
};

static const std::string STRING_STATES[] = 
{
	"Invaded",
	"Infected",
	"Free"
};

#endif