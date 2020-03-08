// Projekt - Bjoern Oke Maas

#include "KnightMove.h"

KnightMove::KnightMove(Field*  srcField, Field* dstField) : Edge(*srcField, *dstField)
{
	this->srcField = srcField;
	this->dstField = dstField;
}

KnightMove::~KnightMove()
{
}