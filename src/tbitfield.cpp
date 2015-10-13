// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len>=0)
	{
		BitLen=len;
		MemLen=(BitLen+31)/32;
		pMem=new TELEM[MemLen];
		for(int i=0; i<MemLen; i++)
		{
			pMem[i]=0;
		}
	}else
		throw new exception();
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=(BitLen+31)/32;
	pMem=new TELEM[MemLen];
	for(int i=0; i<MemLen; i++)
	{
		pMem[i]=bf.pMem[i];
	}

}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n/32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1<<(n%32));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n>=0) && (n<BitLen))
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
	else
		throw new exception();
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n>=0) && (n<BitLen))
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}else
		throw new exception();
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n>=0) && (n<BitLen))
	{
		return ((pMem[GetMemIndex(n)] & GetMemMask(n))>0);
	}else
		throw new exception();
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen=bf.BitLen;
	MemLen=(BitLen+31)/32;
	delete[] pMem;
	pMem=new TELEM[MemLen];
	for(int i=0; i<MemLen; i++)
	{
		pMem[i]=bf.pMem[i];
	}

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int sum=0;
	if(BitLen==bf.BitLen)
	{
		for(int i=0; i<MemLen-1; i++)
		{
			sum+=(pMem[i]!=bf.pMem[i]);
		}
		for(int i=32*(MemLen-1); i<BitLen; i++)
		{
			sum+=(GetBit(i)!=bf.GetBit(i));
		}

		return (sum==0);


	}else
		return false;


}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(this->operator==(bf));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if(BitLen>bf.BitLen) {
		TBitField t(*this);
		for(int i=0; i<bf.MemLen; i++)
		{
			t.pMem[i] |=bf.pMem[i];
		}
		return t;
	}else{	
		TBitField t(bf);
		for(int i=0; i<MemLen; i++)
		{
			t.pMem[i] |=pMem[i];
		}	
		return t;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if(BitLen>bf.BitLen) {
		TBitField t(BitLen);
		for(int i=0; i<bf.MemLen; i++)
		{
			t.pMem[i] =pMem[i] & bf.pMem[i];
		}
		return t;
	}else{	
		TBitField t(bf.BitLen);
		for(int i=0; i<MemLen; i++)
		{
			t.pMem[i] =pMem[i] & bf.pMem[i];
		}	
		return t;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField t(BitLen);
	for(int i=0; i<MemLen; i++)
	{
		t.pMem[i]= ~ pMem[i];
	}

	return t;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char c;
	for(int i=0; i<bf.BitLen; i++)
	{
		istr>> c;
		if (c=='1') bf.SetBit(i);

	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

	for(int i=0; i<bf.BitLen; i++)
	{
		ostr << bf.GetBit(i) << ' ';
	}
	return ostr;
}
