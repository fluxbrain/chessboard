#pragma once

// Projekt - Bjoern Oke Maas

#include "Field.h"
#include "Edge.h"

class KnightMove : public Edge
{
public:
	KnightMove(Field*  srcField, Field* dstField);
	~KnightMove();

private:

	Field*  srcField;
	Field* dstField;
};