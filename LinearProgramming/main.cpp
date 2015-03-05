/**
 * 自作LPSolverのテストドライバ
 *
 * 0-1 Knapsack問題を解いてみよう。
 *  - 許容重さは、9。
 *  - 各アイテムの重さは、2, 3, 5, 6。
 *  - 各アイテムの価値は、4, 5, 12, 14。
 *  - 各アイテムは、高々1個しか入れられない。
 * 式で表すと、
 *    maximize    4.0 * x1 + 5.0 * x2 + 12.0 * x3 + 14.0 * x4
 *    subject to  2.0 * x1 + 3.0 * x2 +  4.0 * x3 +  6.0 * x4 <= 9.0
 *                x1, x2, x3, x4 <= 1.0
 * Integer Programmingで解くと、正解は、x2 = x3 = 1。価値は、19。
 * Linear Programmingで解くと、正解は、x3 = 1、x4 = 0.6666。価値は、21.333。
 */

#include <stdio.h>
#include "LPSolver.h"

int main() {
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

	return 0;
}