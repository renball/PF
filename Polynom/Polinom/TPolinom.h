#include "TList.h"
class TPolinom : public THeadList<TMonom>
{
protected:
	void Print(std::ostream& os) const;
public:
	TPolinom();
	TPolinom(TPolinom& pol);

	TPolinom& operator=(TPolinom& pol);

	void AddMonom(TMonom mon);

	bool operator==(TPolinom& pol);
	bool operator!=(TPolinom& pol);

	TPolinom operator+(TPolinom& pol);
	TPolinom operator-(TPolinom& pol);

	TPolinom operator*(TPolinom& pol);
	TPolinom operator*(TMonom& pol);
	TPolinom operator*(double a);

	friend TPolinom operator*(TMonom& m, TPolinom& pol)
	{
		return pol * m;
	}

	friend TPolinom operator*(double a, TPolinom& pol)
	{
		return pol * a;
	}

	friend std::ostream& operator<<(std::ostream& os, TPolinom& pol)
	{
		pol.Print(os);
		return os;
	}
};

//вывод полинома
void TPolinom::Print(std::ostream& os) const
{
	TNode<TMonom>* _pCurr = pFirst;

	if (_pCurr == pStop)
	{
		os << "0";
		return;
	}

	TMonom m = _pCurr->val;
	double absCoeff = fabs(m.coeff);

	if (m.coeff < 0) os << "- ";


	if (m.IsConst())
	{
		os << absCoeff;
	}

	else
	{
		if (absCoeff != 1) os << absCoeff << "*";
		os << m;
	}

	_pCurr = _pCurr->pNext;

	for (; _pCurr != pStop; _pCurr = _pCurr->pNext)
	{
		TMonom m = _pCurr->val;
		double absCoeff = fabs(m.coeff);

		if (m.coeff < 0) os << " - ";
		else os << " + ";

		if (m.IsConst())
		{
			os << absCoeff;
		}
		else
		{
			if (absCoeff != 1)
				os << absCoeff << "*";
			os << m;
		}
	}
}
//конструктор
TPolinom::TPolinom()
{
	TMonom m(0, 0, -1);
	pHead->val = m;
}
TPolinom::TPolinom(TPolinom& pol)
{
	TMonom m(0, 0, -1);
	pHead->val = m;
	for (pol.Reset(); !pol.IsEnd(); pol.GoNext())
	{
		InsLast(pol.GetCurr());
	}
}
TPolinom& TPolinom::operator=(TPolinom& pol)
{
	while (pFirst != pStop)
	{
		DelFirst();
	}

	pFirst = pLast = pPrev = pCurr = pStop = pHead;
	len = 0;

	pol.Reset();
	while (!pol.IsEnd())
	{
		InsLast(pol.GetCurr());
		pol.GoNext();
	}
	return *this;
}
void TPolinom::AddMonom(TMonom mon)
{
	if (mon.coeff == 0)
		return;

	Reset();

	while (mon < pCurr->val)
	{
		GoNext();
	}

	if (pCurr->val == mon)
	{
		pCurr->val.coeff += mon.coeff;
		if (pCurr->val.coeff == 0)
		{
			DelCurr();
		}
	}

	else
	{
		InsCurr(mon);
	}
}

bool TPolinom::operator==(TPolinom& pol)
{
	TPolinom rtp(pol);
	rtp.Reset();
	Reset();
	while (!IsEnd())
	{
		if (!(pCurr->val == rtp.pCurr->val))
		{
			return false;
		}
		else
		{
			GoNext();
			rtp.GoNext();
		}
	}

	return true;
}
bool TPolinom::operator!=(TPolinom& pol)
{
	return !(this == &pol);
}
TPolinom TPolinom::operator+(TPolinom& pol)
{
	TPolinom res(pol);
	Reset();
	res.Reset();

	while (!IsEnd())
	{
		if (res.pCurr->val > pCurr->val)
		{
			res.GoNext();
		}
		else if (res.pCurr->val < pCurr->val)
		{
			res.InsCurr(pCurr->val);
			GoNext();
		}
		else
		{
			res.pCurr->val.coeff += pCurr->val.coeff;
			if (res.pCurr->val.coeff == 0)
			{
				res.DelCurr();
				GoNext();
			}
			else
			{
				res.GoNext();
				GoNext();
			}
		}
	}
	return res;

}
TPolinom TPolinom::operator*(TPolinom& pol)
{
	TPolinom res;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		TPolinom temp = m * pol;
		res = res + temp;
	}

	return res;
}
TPolinom TPolinom::operator*(TMonom& mon)
{
	TPolinom res;

	if (mon.coeff == 0) return res;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		res.InsLast(m * mon);
	}

	return res;
}
TPolinom TPolinom::operator*(double a)
{
	TPolinom res;

	if (a == 0) return res;

	for (Reset(); !IsEnd(); GoNext())
	{
		TMonom m = GetCurr();
		m.coeff *= a;

		res.InsLast(m);
	}
	return res;
}
TPolinom TPolinom::operator-(TPolinom& pol)
{
	return operator+(pol.operator*(-1));
}