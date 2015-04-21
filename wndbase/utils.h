/********************************************************************************
*filename     :utils.h
*synopsis     :utilities
*created      :lanshh 2012-03-12
*last modified:lanshh 2015-04-21
********************************************************************************/
#ifndef __UTILS_H
#define __UTILS_H
#include "list.h"
#include "config.h"
#include "debug.h"
#include "CommonFuns.h"
/*****************************************************************************************
* generate an entry that converts the #define'd value into string  
******************************************************************************************/
#define LSH_ENTRY(value)                { value, L#value }
/****************** Returns Number Of Elements *********************/
#define dim(x) (sizeof(x) / sizeof(x[0]))
void CalculateCRC(unsigned char* buffer, unsigned long size, unsigned short* crc);
#endif