// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <iostream>

TBitField::TBitField(int len)
{
	MemLen = 0;
	BitLen = len;
	if (len >= 0) {
		MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw 1;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}

}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= 0)
		return(n / (sizeof(TELEM) * 8));
	else
		throw 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << (n - GetMemIndex(n) * sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < BitLen) && (n >= 0))
		pMem[this->GetMemIndex(n)] = pMem[this->GetMemIndex(n)] | this->GetMemMask(n);
	else
		throw 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < BitLen)
		pMem[this->GetMemIndex(n)] = pMem[this->GetMemIndex(n)] & ~this->GetMemMask(n);
	else
		throw 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < BitLen)
		if (pMem[this->GetMemIndex(n)] & this->GetMemMask(n))
			return 1;
		else
			return 0;
	else throw 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen) {
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen) {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i])
				return false;
		}
		return true;
	}
	else
		return false;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return false;
	else
		return true;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int n;
	TBitField output(0);
	if (BitLen < bf.BitLen) {
		n = MemLen;
		output = bf;
	}
	else {
		n = bf.MemLen;
		output = *this;
	}
	for (int i = 0; i < n; i++) {
		output.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return output;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n;
	TBitField out(0);
	if (BitLen < bf.BitLen) {
		n = MemLen;
		out = bf;
	}
	else {
		n = bf.MemLen;
		out = *this;
	}
	for (int i = 0; i < n; i++) {
		out.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return out;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a = *this;
	for (int i = 0; i < BitLen; i++) {
		if (a.GetBit(i))
			a.ClrBit(i);
		else
			a.SetBit(i);
	}
	return a;

	TBitField temp(*this);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод 
{
	int temp;

	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> temp;

		if (temp == 1)
		{
			bf.SetBit(i);
		}
		else
		{
			bf.ClrBit(i);
		}
	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод 
{
	ostr << "( ";
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i) << " ";
	}
	ostr << ")"<<endl;

	return ostr;
}
