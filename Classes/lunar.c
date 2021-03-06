#include "sdncal.h"

/*
 * Start day for lunar conversion
 * Solar 1/1/1800 = Lunar 12/7/1799, 0(평달) 
 *
 * 음력달 데이터
 * 
 * 1 : 29 평달 / 작은달
 * 2 : 30 평달 / 큰달
 * 3 : 58 = 29 + 29 윤달일 있는 달 / 평달이 작고 윤달도 작다
 * 4 : 59 = 29 + 30 윤달일 있는 달 / 평달이 작고 윤달이 크다
 * 5 : 59 = 30 + 29 윤달일 있는 달 / 평달이 크고 윤달이 작다
 * 6 : 60 = 30 + 30 윤달일 있는 달 / 평달과 윤달이 모두 크다
 * 
 */

int luna_month_table[][12] = {
	{1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2},	/* 1799 */
	{2, 1, 2, 5, 2, 1, 2, 1, 2, 1, 2, 1},
	{1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2},	/* 1801 */ 
	{1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1},
	{2, 3, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2, 2},
	{1, 2, 1, 2, 1, 3, 2, 1, 2, 2, 2, 1},
	{2, 2, 1, 2, 1, 1, 1, 2, 1, 2, 2, 1},
	{2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2},
	{1, 2, 2, 1, 5, 2, 1, 2, 1, 1, 2, 1},
	{2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2},
	{1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 2},
	{1, 1, 5, 2, 1, 2, 2, 1, 2, 2, 1, 2},	/* 1811 */
	{1, 1, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1},
	{2, 5, 2, 1, 1, 1, 2, 1, 2, 2, 1, 2},
	{2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 2, 1, 2, 1, 5, 1, 2, 1, 2, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1},
	{2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 1, 2},
	{1, 2, 1, 5, 2, 2, 1, 2, 2, 1, 2, 1},
	{1, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2},
	{1, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1, 2},	/* 1821 */
	{2, 1, 5, 1, 1, 2, 1, 2, 2, 1, 2, 2},
	{2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 4, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 1, 2, 2, 4, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 1, 2, 3, 2, 1, 2, 2, 1, 2, 2, 2},
	{1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2},	/* 1831 */
	{1, 2, 1, 2, 1, 1, 2, 1, 5, 2, 2, 2},
	{1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 5, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2},
	{1, 2, 1, 5, 1, 2, 2, 1, 2, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 4, 1, 1, 2, 1, 2, 1, 2, 2, 1},	/* 1841 */
	{2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 1},
	{2, 2, 2, 1, 2, 1, 4, 1, 2, 1, 2, 1},
	{2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 5, 2, 1, 2, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 2, 1, 1, 2, 3, 2, 1, 2, 2},	/* 1851 */
	{2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 5, 2, 1, 2, 1, 2},
	{1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2},
	{1, 2, 1, 1, 5, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2},
	{2, 1, 6, 1, 1, 2, 1, 1, 2, 1, 2, 2},
	{1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2},	/* 1861 */
	{2, 1, 2, 1, 2, 2, 1, 5, 2, 1, 1, 2},
	{1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2},
	{1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 1, 2, 4, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 2},
	{1, 2, 2, 3, 2, 1, 1, 2, 1, 2, 2, 1},
	{2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 2, 2, 1, 2, 1, 2, 1, 1, 5, 2, 1},
	{2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2},	/* 1871 */
	{1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2},
	{1, 1, 2, 1, 2, 4, 2, 1, 2, 2, 1, 2},
	{1, 1, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1},
	{2, 2, 1, 1, 5, 1, 2, 1, 2, 2, 1, 2},
	{2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 2, 4, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 1, 2},
	{1, 2, 1, 2, 1, 2, 5, 2, 2, 1, 2, 1},	/* 1881 */
	{1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1, 2},
	{2, 1, 1, 2, 3, 2, 1, 2, 2, 1, 2, 2},
	{2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 2, 1, 5, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2},
	{1, 5, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2},	/* 1891 */
	{1, 1, 2, 1, 1, 5, 2, 2, 1, 2, 2, 2},
	{1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 5, 1, 2, 1, 2, 1, 2, 1},
	{2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 5, 2, 2, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 5, 2, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1},	/* 1901 */
	{2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 2, 3, 2, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1},
	{2, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2},
	{1, 2, 2, 4, 1, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1},
	{2, 1, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2},
	{1, 5, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 1, 1, 5, 1, 2, 2, 1, 2, 2},	/* 1911 */
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2},
	{2, 2, 1, 2, 5, 1, 2, 1, 2, 1, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1},
	{2, 3, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 2, 1, 1, 2, 1, 5, 2, 1, 2, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2},	/* 1921 */
	{2, 1, 2, 2, 3, 2, 1, 1, 2, 1, 2, 2},
	{1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2},
	{2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1},
	{2, 1, 2, 5, 2, 1, 2, 2, 1, 2, 1, 2},
	{1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 5, 1, 2, 1, 1, 2, 2, 1, 2, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 2},
	{1, 2, 2, 1, 1, 5, 1, 2, 1, 2, 2, 1},
	{2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1},	/* 1931 */
	{2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2},
	{1, 2, 2, 1, 6, 1, 2, 1, 2, 1, 1, 2},
	{1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2},
	{1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 4, 1, 1, 2, 2, 1, 2, 2, 2, 1},
	{2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1},
	{2, 2, 1, 1, 2, 1, 4, 1, 2, 2, 1, 2},
	{2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 2, 1, 2, 2, 4, 1, 1, 2, 1, 2, 1},	/* 1941 */
	{2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 4, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1, 2},
	{2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2},
	{2, 5, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 1, 2, 2, 1, 2, 3, 2, 1, 2, 1, 2},
	{1, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2},	/* 1951 */
	{1, 2, 1, 2, 4, 1, 2, 2, 1, 2, 1, 2},
	{1, 2, 1, 1, 2, 2, 1, 2, 2, 1, 2, 2},
	{1, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2},
	{2, 1, 4, 1, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 1, 5, 2, 1, 2, 2},
	{1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 5, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2},   /* 1961 */
	{1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 2, 3, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2},
	{1, 2, 5, 2, 1, 1, 2, 1, 1, 2, 2, 1},
	{2, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 2, 1, 5, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2},
	{1, 2, 1, 1, 5, 2, 1, 2, 2, 2, 1, 2},   /* 1971 */
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 5, 1, 2, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2},
	{2, 2, 1, 2, 1, 2, 1, 5, 1, 2, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1},
	{2, 1, 2, 2, 1, 2, 2, 1, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 6, 1, 2, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2},   /* 1981 */
	{2, 1, 2, 3, 2, 1, 1, 2, 1, 2, 2, 2},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2},
	{2, 1, 2, 2, 1, 1, 2, 1, 1, 5, 2, 2},
	{1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 1},
	{2, 1, 2, 1, 2, 5, 2, 2, 1, 2, 1, 2},
	{1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 1, 2, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 1, 5, 1, 2, 2, 1, 2, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 2},   /* 1991 */
	{1, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2},
	{1, 2, 5, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 1, 2, 5, 2, 1, 1, 2},
	{1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 1},
	{2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 1, 2, 3, 2, 2, 1, 2, 2, 2, 1},
	{2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1},
	{2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 1},
	{2, 2, 1, 5, 2, 1, 1, 2, 1, 2, 1, 2},   /* 2001 */
	{2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2},
	{1, 5, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 1, 5, 2, 2, 1, 2, 2},
	{1, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1, 2},
	{2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2},
	{2, 2, 1, 1, 5, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1},   /* 2011 */
	{2, 1, 2, 5, 2, 2, 1, 1, 2, 1, 2, 1},
	{2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 1, 2, 5, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 2, 2, 1, 2, 1},
	{2, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 2, 1, 2, 1, 4, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2},
	{2, 1, 2, 5, 2, 1, 1, 2, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},   /* 2021 */
	{2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2},
	{1, 5, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 2, 1, 1, 5, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1},
	{2, 2, 2, 1, 5, 1, 2, 1, 1, 2, 2, 1},
	{2, 2, 1, 2, 2, 1, 1, 2, 1, 1, 2, 2},
	{1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 5, 2, 1, 2, 2, 1, 2, 1, 2, 1},   /* 2031 */
	{2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 5, 2},
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 2, 1, 4, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2},
	{2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1},
	{2, 2, 1, 2, 5, 2, 1, 2, 1, 2, 1, 1},
	{2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2},   /* 2041 */
	{1, 5, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2},
	{2, 1, 2, 1, 1, 2, 3, 2, 1, 2, 2, 2},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2},
	{2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2},
	{2, 1, 2, 2, 4, 1, 2, 1, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 2, 1, 2, 1, 1, 2, 1},
	{2, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2, 1},
	{1, 2, 4, 1, 2, 1, 2, 2, 1, 2, 2, 1}, 
	{2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2, 2},   /* 2051 */
	{1, 2, 1, 1, 2, 1, 1, 5, 2, 2, 2, 2},
	{1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 2},
	{1, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2},
	{1, 2, 2, 1, 2, 4, 1, 1, 2, 1, 2, 1},
	{2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2},
	{1, 2, 2, 1, 2, 1, 2, 2, 1, 1, 2, 1},
	{2, 1, 2, 4, 2, 1, 2, 1, 2, 2, 1, 1},
	{2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 1, 2, 1, 1, 2, 2, 1, 2, 2, 1},
	{2, 2, 3, 2, 1, 1, 2, 1, 2, 2, 2, 1},   /* 2061 */
	{2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 1},
	{2, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2},
	{2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2},
	{1, 2, 1, 2, 5, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 1, 2, 2, 1, 2, 2, 1, 2},
	{1, 2, 1, 5, 1, 2, 1, 2, 2, 2, 1, 2},
	{2, 1, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2},
	{2, 1, 2, 1, 2, 1, 1, 5, 2, 1, 2, 2},   /* 2071 */
	{2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2},
	{2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1},
	{2, 1, 2, 2, 1, 5, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1},
	{2, 1, 2, 3, 2, 1, 2, 2, 2, 1, 2, 1},
	{2, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2},
	{1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{2, 1, 5, 2, 1, 1, 2, 1, 2, 1, 2, 2},
	{1, 2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2},   /* 2081 */
	{1, 2, 2, 2, 1, 2, 3, 2, 1, 1, 2, 2},
	{1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
	{2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2},
	{1, 2, 1, 1, 6, 1, 2, 2, 1, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1},
	{2, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2},
	{1, 2, 1, 5, 1, 2, 1, 1, 2, 2, 2, 1},
	{2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1},
	{2, 2, 2, 1, 2, 1, 1, 5, 1, 2, 2, 1},
	{2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1},   /* 2091 */
	{2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1},
	{1, 2, 2, 1, 2, 4, 2, 1, 2, 1, 2, 1},
	{2, 1, 1, 2, 1, 2, 2, 1, 2, 2, 1, 2},
	{1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1},
	{2, 1, 2, 3, 2, 1, 1, 2, 2, 2, 1, 2},
	{2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 1, 2},
	{2, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2},
	{2, 5, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2},
	{2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1},
	{2, 2, 1, 2, 2, 1, 5, 2, 1, 1, 2, 1}	/* 2101 */
};

void sdnToLunar(long int sdn, int *pYear, int *pMonth, int *pDay, int *intercalary) {
	int year = 0;
	int month = 0;
	int day = 0;
	long int dn = sdn - FIRST_YEAR_SDN;
	int daysInYear = LUNAR_DAYS_IN_1799;
	
	if (dn <= daysInYear) {
		*pYear = LUNAR_START_YEAR;
		*pMonth = LUNAR_START_MONTH;
		*pDay = LUNAR_START_DAY + dn;
	} else {
		int i;
		while (dn > daysInYear) {
			year++;
			dn -= daysInYear;
			daysInYear = 0;
			for (i = 0; i < 12; i++) {
				switch (luna_month_table[year][i]) {
					case 1:
						daysInYear += 29;
						break;
					case 2:
						daysInYear += 30;
						break;
					case 3:
						daysInYear += 58;
						break;
					case 4:
						daysInYear += 59;
						break;
					case 5:
						daysInYear += 59;
						break;
					case 6:
						daysInYear += 60;
						break;
					default:
						break;
				}
			}
		}
		
		int daysInMonth = 0;
		int monthType = 0;
		do {
			dn -= daysInMonth;
			monthType = luna_month_table[year][month];
			switch (monthType) {
				case 1:
					daysInMonth = 29;
					break;
				case 2:
					daysInMonth = 30;
					break;
				case 3:
					daysInMonth = 58;
					break;
				case 4:
					daysInMonth = 59;
					break;
				case 5:
					daysInMonth = 59;
					break;
				case 6:
					daysInMonth = 60;
					break;
				default:
					break;
			}
			month++;
		} while (dn > daysInMonth);
		
		if (dn < 30 || (dn == 30 && monthType == 2)) {
			*intercalary = 0;
			day = dn;
		} else {
			*intercalary = 1;
			switch (monthType) {
				case 3:
					day = dn - 29;
					break;
				case 4:
					day = dn - 29;
					break;
				case 5:
					day = dn - 30;
					break;
				case 6:
					day = dn - 30;
					break;
				default:
					break;
			}
		}
		
		*pYear = year + LUNAR_START_YEAR;
		*pMonth = month;
		*pDay = day;
	}
}

long int LunarToSdn(int year, int month, int day, int intercalary) {
	int i;
	long int sdn = 0L;
	
	int yearIndex = year - LUNAR_START_YEAR;
	int currentYearIndex = yearIndex  - 1;
	while (currentYearIndex > 0) {
		for (i = 0; i < 12; i++) {
			switch (luna_month_table[currentYearIndex][i]) {
				case 1:
					sdn += 29;
					break;
				case 2:
					sdn += 30;
					break;
				case 3:
					sdn += 58;
					break;
				case 4:
					sdn += 59;
					break;
				case 5:
					sdn += 59;
					break;
				case 6:
					sdn += 60;
					break;
				default:
					break;
			}
		}
		currentYearIndex--;
	}
	
	int currentMonthIndex = 0;
	while (currentMonthIndex < month - 1) {
		switch (luna_month_table[yearIndex][currentMonthIndex]) {
			case 1:
				sdn += 29;
				break;
			case 2:
				sdn += 30;
				break;
			case 3:
				sdn += 58;
				break;
			case 4:
				sdn += 59;
				break;
			case 5:
				sdn += 59;
				break;
			case 6:
				sdn += 60;
				break;
			default:
				break;
		}
		currentMonthIndex++;
	}
	
	if (intercalary) {
		switch (luna_month_table[yearIndex][currentMonthIndex]) {
			case 3:
				sdn += 29;
				break;
			case 4:
				sdn += 29;
				break;
			case 5:
				sdn += 30;
				break;
			case 6:
				sdn += 30;
				break;
			default:
				break;
		}
	}
	
	return sdn + day + FIRST_YEAR_SDN + LUNAR_DAYS_IN_1799;
}

int intercalaryMonth(int year, int month) {
	int yearIndex = year - LUNAR_START_YEAR;
	return (luna_month_table[yearIndex][month - 1] >= INTERCALARY_FIRST_CONSTANT);
}