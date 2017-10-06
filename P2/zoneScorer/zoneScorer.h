#ifndef ZONESCORER_H
#define ZONESCORER_H

#include "../dataStructures/zoneIndex/zoneIndex.h"

std::vector< tuple< int, float>> scoreQuery( zoneIndex Ind, std::string query, int k, float g);




#endif 