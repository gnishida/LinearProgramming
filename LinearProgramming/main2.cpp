#include <stdio.h>

#include <lp_lib.h>

void main() {
	lprec *lp;

	lp = make_lp(0, 4);

	{
		set_col_name(lp, 1, "x1");
		set_col_name(lp, 2, "x2");
		set_col_name(lp, 3, "x3");
		set_col_name(lp, 4, "x4");
	}

	// 制約
	{
		set_add_rowmode(lp, TRUE);

		int colno[4];
		double row[4];			// 変数の数+1
		colno[0] = 1; row[0] = 2.0;
		colno[1] = 2; row[1] = 3.0;
		colno[2] = 3; row[2] = 5.0;
		colno[3] = 4; row[3] = 6.0;
		add_constraintex(lp, 4, row, colno, LE, 9.0);

		set_add_rowmode(lp, FALSE);
	}

	// objective関数
	{
		double row[5];
		row[1] = 4.0;
		row[2] = 5.0;
		row[3] = 12.0;
		row[4] = 14.0;
		set_obj_fn(lp, row);
	}

	// upper bound
	{
		for (int i = 0; i < 4; ++i) {
			set_upbo(lp, i + 1, 1.0);
		}
	}

	// solve
	set_maxim(lp);
	int ret = solve(lp);
	switch (ret) {
	case -2:
		printf("NOMEMORY\n");
		break;
	case 0:
		printf("OPTIMAL\n");
		break;
	case 1:
		printf("SUBOPTIMAL\n");
		break;
	case 2:
		printf("INFEASIBLE\n");
		break;
	case 3:
		printf("UNBOUNDED\n");
		break;
	default:
		printf("UNKNOWN\n");
		break;
	}

	// display solution
	{
		double obj = get_objective(lp);
		printf("Obj: %lf\n", obj);

		double row[4];
		get_variables(lp, row);
		for (int i = 0; i < 4; ++i) {
			printf("%s: %lf\n", get_col_name(lp, i + 1), row[i]);
		}
	}

	delete_lp(lp);
}