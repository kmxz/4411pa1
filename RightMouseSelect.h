////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#pragma once
#include "impressionistDoc.h"
#include "impressionistUI.h"

void MouseBegin(const Point source, const Point target, ImpressionistDoc* pDoc);
void MouseMove(const Point source, const Point target, ImpressionistDoc* pDoc);
void MouseEnd(const Point source, const Point target, ImpressionistDoc* pDoc);

