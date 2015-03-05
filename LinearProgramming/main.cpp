#include <stdio.h>

#include "LPSolver.h"

void main() {
	LPSolver lp(4);

	// 制約
	{
		std::vector<int> colno(4);
		std::vector<double> row(4);
		colno[0] = 1; row[0] = 2.0;
		colno[1] = 2; row[1] = 3.0;
		colno[2] = 3; row[2] = 5.0;
		colno[3] = 4; row[3] = 6.0;
		lp.addConstraint(LE, row, colno, 9.0);
	}

	// objective関数
	{
		std::vector<double> row(4);
		row[0] = 4.0;
		row[1] = 5.0;
		row[2] = 12.0;
		row[3] = 14.0;
		lp.setObjective(row);
	}

	// upper bound
	{
		std::vector<double> vals(4, 1.0);
		lp.setUpperBound(vals);
	}

	lp.maximize();
	lp.displaySolution();
}