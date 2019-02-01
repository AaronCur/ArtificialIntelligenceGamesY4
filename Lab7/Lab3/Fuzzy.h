#pragma once
#include <algorithm>
#include <iostream>

class Fuzzy {
public:

	double FuzzyGrade(double value, double x0, double x1);
	double FuzzyTriangle(double value, double x0, double x1, double x2);
	double FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);

	double FuzzyAND(double A, double B);
	double FuzzyOR(double A, double B);
	double FuzzyNOT(double A);
	void update(float range);

	double mClose = 0, mMedium = 0, mFar = 0;
	double mTiny = 0, mSmall = 0, mModerate = 0, mLarge = 0;
	double mLow = 0;
	double mMed = 0;
	double mHigh = 0;;

	double nDeploy;

};
