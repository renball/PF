#include "gtest.h"
#include <iostream>
#include "..\Polinom\TList.h"
#include "..\Polinom\TPolinom.h"

//Для списка
TEST(TList, CAN_CREATE_LIST)
{
	ASSERT_NO_THROW(TList<int> t);
}

TEST(TList, NEW_LIST_IS_EMPTY)
{
	TList<int> t;
	ASSERT_TRUE(t.IsEmpty());
}

TEST(TList, LIST_WITH_ELEMENTS_IS_NOT_EMPTY)
{
	TList<int> t;
	t.InsFirst(1);
	ASSERT_TRUE(!t.IsEmpty());
}

TEST(TList, CAN_INSERT_FIRST)
{
	TList<int> t;
	ASSERT_NO_THROW(t.InsFirst(1));
}

TEST(TList, CAN_DELETE_FIRST)
{
	TList<int> t;
	t.InsLast(1);
	t.InsLast(2);
	t.InsLast(3); 
	t.InsLast(4);
	ASSERT_NO_THROW(t.DelFirst());

}

TEST(TList, CAN_INSERT_LAST)
{
	TList<int> t;
	t.InsFirst(1);
	ASSERT_NO_THROW(t.InsLast(2));

}

TEST(TList, CAN_INSERT_WHEN_ELEMENT_FIRST)
{
	TList<int> t;
	t.InsFirst(1);
	t.InsFirst(2);
	t.InsFirst(3); 
	t.InsFirst(4);

	t.Reset();
	ASSERT_NO_THROW(t.InsCurr(100));

}

TEST(TList, CAN_INSERT_ELEMENT_WHEN_SECOND)
{
	TList<int> t;
	t.InsFirst(1);
	t.InsFirst(2);
	t.InsFirst(3);
	t.InsFirst(4);

	t.Reset();
	t.GoNext();
	ASSERT_NO_THROW(t.InsCurr(100));

}

TEST(TList, CAN_DELETE_ELEMENT_WHEN_SECOND)
{
	TList<int> t;
	t.InsLast(1);
	t.InsLast(2);
	t.InsLast(3);
	t.InsLast(4);

	t.Reset();
	t.GoNext();
	ASSERT_NO_THROW(t.DelCurr());
}

TEST(TList, CAN_INSERT_ELEMENT_WHEN_LAST)
{
	TList<int> t;
	t.InsLast(1);
	t.InsLast(2);
	t.InsLast(3);
	t.InsLast(4);

	t.Reset();
	t.GoNext();
	t.GoNext();
	t.GoNext();
	t.GoNext();
	ASSERT_NO_THROW(t.InsCurr(100));
}

TEST(TList, TList_CAN_DELETE_ELEMENT_WHEN_LAST)
{
	TList<int> t;
	t.InsLast(1);
	t.InsLast(2);
	t.InsLast(3);
	t.InsLast(4);

	t.Reset();
	t.GoNext();
	t.GoNext();
	t.GoNext();
	ASSERT_NO_THROW(t.DelCurr());
}


//для полиномов 


TEST(TMonom, CAN_CREATE_MONOM)
{
	ASSERT_NO_THROW(TMonom m);
}


TEST(TPolinom, CAN_CREATE_POLINOM)
{
	ASSERT_NO_THROW(TPolinom tp);
}
TEST(TPolinom, CAN_COPY_POLINOM)
{
	TPolinom tp;
	tp.AddMonom(TMonom(1, 1, 1, 1));
	TPolinom tp_new(tp);
	EXPECT_TRUE(tp == tp_new);
}
TEST(TPolinom, CORRECT_COEFF_MULTIPLY)
{
	TPolinom tp1;
	TMonom tm(1, 1, 1, 1);
	TMonom tm1(2, 2, 2, 2);
	tp1.AddMonom(tm);
	tp1.AddMonom(tm1);
	TPolinom tp2;
	TMonom tm2(2, 1, 1, 1);
	TMonom tm3(4, 2, 2, 2);
	tp2.AddMonom(tm2);
	tp2.AddMonom(tm3);
	EXPECT_TRUE((tp1 * 2) == tp2);
}
TEST(TPolinom, CAN_ASSIGN_POLINOM)
{
	TPolinom t1;
	TMonom tm(1, 1, 1, 1);
	t1.AddMonom(tm);
	TPolinom t2 = t1;
	EXPECT_TRUE(t1 == t2);
}

TEST(TPolinom, CAN_ASSIGN_POLINOM_TO_ITSELF)
{
	TPolinom t;
	TMonom tm(1, 1, 1, 1);
	t.AddMonom(tm);
	ASSERT_NO_THROW(t = t);
	EXPECT_TRUE(t == t);
}
TEST(TPolinom, ASSIGNEP_POLINOM_IS_EQUAL)
{
	bool result = true;
	TPolinom tp1;
	TMonom tm(1, 1, 1, 1);
	TMonom tm1(2, 2, 2, 2);
	tp1.AddMonom(tm);
	tp1.AddMonom(tm1);
	TPolinom tp2;
	tp2 = tp1;
	EXPECT_TRUE(tp1 == tp2);
}
TEST(TPolinom, CAN_ADD_MONOM_TO_POLINOM)
{
	TPolinom t;
	TMonom tm(1, 1, 1, 1);
	ASSERT_NO_THROW(t.AddMonom(tm));
}
TEST(TPolinom, CORRECT_ADD_POLINOM_TO_POLINOM)
{
	TPolinom t1;
	TMonom tm(2, 1, 1, 1);

	TMonom tm1(1, 1, 1, 1);
	TMonom tm2(1, 2, 2, 2);


	t1.AddMonom(tm1);
	t1.AddMonom(tm2);

	TPolinom t2;

	t2.AddMonom(tm);
	t2.AddMonom(tm2);

	TPolinom res;
	TMonom tm3(3, 1, 1, 1);
	TMonom tm4(2, 2, 2, 2);
	res.AddMonom(tm4);
	res.AddMonom(tm3);

	EXPECT_TRUE((t1 + t2) == res);
}
TEST(TPolinom, CORRECT_ADD_POLINOM_TO_POLINOM_2)
{
	TPolinom t1;
	TMonom tm(2, 1, 1, 1);
	TMonom tm1(1, 1, 1, 1);

	TMonom tm2(1, 2, 2, 2);
	TMonom tm22(5, 2, 2, 2);

	TMonom tm3(3, 3, 3, 3);
	TMonom tm33(-3, 3, 3, 3);

	t1.AddMonom(tm1);
	t1.AddMonom(tm2);
	t1.AddMonom(tm3);

	TPolinom t2;

	t2.AddMonom(tm1);
	t2.AddMonom(tm22);
	t2.AddMonom(tm33);

	TPolinom res;

	TMonom tm4(6, 2, 2, 2);

	res.AddMonom(tm);
	res.AddMonom(tm4);


	EXPECT_TRUE((t1 + t2) == res);
}
TEST(TPolinom, CORRECT_ADD_POLINOM_TO_POLINOM_3)
{
	TPolinom t1;
	TMonom tm(-1, 1, 1, 1);

	TMonom tm1(1, 1, 1, 1);
	TMonom tm2(1, 2, 2, 2);
	TMonom tm22(5, 2, 2, 2);
	TMonom tm3(3, 3, 3, 3);
	TMonom tm33(2, 3, 3, 3);


	t1.AddMonom(tm);
	t1.AddMonom(tm2);
	t1.AddMonom(tm3);

	TPolinom t2;

	t2.AddMonom(tm1);
	t2.AddMonom(tm22);
	t2.AddMonom(tm33);

	TPolinom res;

	TMonom tm4(6, 2, 2, 2);
	TMonom tm5(5, 3, 3, 3);

	res.AddMonom(tm4);
	res.AddMonom(tm5);


	EXPECT_TRUE((t1 + t2) == res);
}
TEST(TPolinom, CORRECT_ADD_POLINOM_TO_POLINOM_4)
{
	TPolinom t1;
	TMonom tm(2, 1, 1, 1);

	TMonom tm1(1, 1, 1, 1);
	TMonom tm2(-5, 2, 2, 2);
	TMonom tm22(5, 2, 2, 2);
	TMonom tm3(3, 3, 3, 3);
	TMonom tm33(2, 3, 3, 3);

	TMonom tm4(6, 2, 2, 2);
	TMonom tm5(5, 3, 3, 3);


	t1.AddMonom(tm);
	t1.AddMonom(tm2);
	t1.AddMonom(tm3);

	TPolinom t2;

	t2.AddMonom(tm1);
	t2.AddMonom(tm22);
	t2.AddMonom(tm33);

	TPolinom res;

	res.AddMonom(tm);
	res.AddMonom(tm5);


	EXPECT_TRUE((t1 + t2) == res);
}
TEST(TPolinom, CAN_MULTIPLY_MONOM_BY_POLINOM)
{
	TPolinom tp;

	TMonom tm(4, 3, 2, 1);

	TMonom tm1(1, 1, 1, 1);
	TMonom tm2(2, 2, 2, 2);
	tp.AddMonom(tm1);
	tp.AddMonom(tm2);


	TPolinom res;
	TMonom tm3(8, 5, 4, 3);
	TMonom tm4(4, 4, 3, 2);
	res.AddMonom(tm3);
	res.AddMonom(tm4);

	EXPECT_TRUE(tp * tm == res);
}
TEST(TPolinom, CAN_MULTIPLY_POLINOMS)
{
	TPolinom tp;
	TMonom tm1(2, 2, 3, 3);
	TMonom tm2(4, 4, 4, 4);
	tp.AddMonom(tm1);
	tp.AddMonom(tm2);

	TMonom tm3(4, 1, 2, 2);
	TMonom tm4(1, 3, 2, 5);
	TPolinom tp1, res;
	tp1.AddMonom(tm3);
	tp1.AddMonom(tm4);
	TMonom tm(4, 7, 6, 9);
	TMonom tmm(2, 5, 5, 8);
	TMonom tmmm(8, 3, 5, 5);
	res.AddMonom(tm);
	res.AddMonom(tmm);
	res.AddMonom(tmmm);


	EXPECT_TRUE(tp * tp1 == res);
}