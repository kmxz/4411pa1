////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#pragma once
#include "impressionistDoc.h"
#include "impressionistUI.h"

void MouseBegin(const ImpPoint source, const ImpPoint target, ImpressionistDoc* pDoc);
void MouseMove(const ImpPoint source, const ImpPoint target, ImpressionistDoc* pDoc);
void MouseEnd(const ImpPoint source, const ImpPoint target, ImpressionistDoc* pDoc);

