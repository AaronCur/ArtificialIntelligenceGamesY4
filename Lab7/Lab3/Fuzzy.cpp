#include "Fuzzy.h"

double Fuzzy::FuzzyGrade(double value, double x0, double x1)
{
	double result = 0;

	double x = value;

	if (x <= x0) {
		result = 0;
	}
	else if (x > x1) {
		result = 1;
	}
	else {
		result = ((x - x0) / (x1 - x0));
	}

	return result;
}

double Fuzzy::FuzzyTriangle(double value, double x0, double x1, double x2)
{
	double result = 0;

	double x = value;

	if ((x <= x0) || (x >= x2) ) {
		result = 0;
	}
	else if (x == x1) {
		result = 1;
	}
	else if ((x > x0) && (x < x1)) {
		result = ((x - x0) / (x1 - x0));
	}
	else {
		result = ((x2 - x) / (x2 - x1));
	}

	return result;
}

double Fuzzy::FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3)
{
	double result = 0;

	double x = value;

	if ((x <= x0) || (x >= x3)) {
		result = 0;
	}
	else if ((x >= x1) && ( x <= x2 )) {
		result = 1;
	}
	else if ((x > x0) && (x < x1)) {
		result = ((x - x0) / (x1 - x0));
	}
	else {
		result = ((x3 - x) / (x3 - x2));
	}

	return result;

}
double Fuzzy::FuzzyAND(double A, double B)
{
	
	return std::min(A, B);

}
double Fuzzy::FuzzyOR(double A, double B)
{
	return std::max(A, B);

}
double Fuzzy::FuzzyNOT(double A)
{
	return 1.0 - A;
}

void Fuzzy::update(float range) {

	mTiny = FuzzyTriangle(6, -100, 0, 100);
	mSmall = FuzzyTrapezoid(6, 25, 100, 150, 200);
	mModerate = FuzzyTrapezoid(6, 150, 200, 250, 300);
	mLarge = FuzzyGrade(6, 250, 300);

	mClose = FuzzyTriangle(range, -300, 0, 300);
	mMedium = FuzzyTrapezoid(range, 100, 300, 500, 700);
	mFar = FuzzyGrade(range, 500, 700);


	mLow = FuzzyOR(FuzzyAND(mMedium, mTiny), FuzzyAND(mMedium, mSmall));
	mMed = FuzzyAND(mClose, mTiny);
	mHigh = FuzzyAND(mClose, FuzzyNOT(mMedium));

	std::cout << "Low : " << mLow<< std::endl;
	std::cout << "Med : " << mMed << std::endl;
	std::cout << "High : " << mHigh << std::endl;

	int nDeploy = (mLow * 10 + mMed * 30 + mHigh * 50) /
		(mLow + mMed + mHigh);

	if (nDeploy < 0) {
		nDeploy = 0;
	}

	std::cout << "Deploy : " << nDeploy << std::endl;
	std::cout << std::endl;


	//if (mLow > mMedium)
	//{
	//	std::cout << "Low Threat" << std::endl;
	//}
	//else if (mMed > mLow && mMed > mHigh)
	//{
	//	std::cout << "Medium Threat" << std::endl;
	//}
	//else if (mHigh > mMed)
	//{
	//	std::cout << "High Threat" << std::endl;
	////}
	//
}