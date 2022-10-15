#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;

bool strlf(char a[], const char b[]) {
	int c = strlen(a);
	for (int i = 0; i < c; i++) {
		if (a[i] = b[0]) return true;
	}
	return false;
}
class MathException
{
public:
	MathException(const char (*name_op), long v1, long v2) : val1(v1), val2(v2) {
		strcpy_s(op_name, name_op);
	}
protected:
	char op_name[20]; 
	long val1; 
	long val2; 
public:
	virtual char* Message() {
		char c[] = "";
		return c;
	}
};

class OverflowException : public MathException 
{ 
public:
	OverflowException(const char(*name_op), long v1, long v2) : MathException(name_op, v1, v2) {
		try {
			double val;
			if (strlf(op_name, "+")) {
				val = static_cast<long long>(val1) + static_cast<long long>(val2);
				if (val > LONG_MAX) throw val;
			}
			if (strlf(op_name, "-")) {
				val = static_cast<long long>(val1) - static_cast<long long>(val2);
				if (val > LONG_MAX) throw val;
			}
			if (strlf(op_name, "/")) {
				val = static_cast<long long>(val1) / static_cast<long long>(val2);
				if (val > LONG_MAX) throw val;
			}
		}
		catch (double val) {
			Message();
			cout << "Результат вычесления: " << val << endl;
		}
	}
private:
	char* Message() { 
		char b[20] = "Переполнение сверху";
		cout << b << endl;
		return b;
	}
};

class UnderflowException : public MathException {
public:
	UnderflowException(const char(*name_op), long v1, long v2) : MathException(name_op, v1, v2) {
		try {
			double val;
			if (strlf(op_name, "+")) {
				val = static_cast<long long>(val1) + static_cast<long long>(val2);
				if (val < LONG_MIN) throw val;
			}
			if (strlf(op_name, "-")) {
				val = static_cast<long long>(val1) - static_cast<long long>(val2);
				if (val < LONG_MIN) throw val;
			}
			if (strlf(op_name, "/")) {
				val = static_cast<long long>(val1) / static_cast<long long>(val2);
				if (val < LONG_MIN) throw val;
			}
		}
		catch (double val) {
			Message();
			cout << "Результат вычесления: " << val << endl;
		}
	}
private:
	char* Message() {
		char b[] = "Переполнение снизу";
		cout << b << endl;
		return b;
	}
};

class ZdivideException : public MathException {
public:
	ZdivideException(const char(*name_op), long v1, long v2): MathException(name_op, v1,v2){
		try {
			if (strlf(op_name, "/")) {
				if (val2 == 0) throw val2;
			}
		}
		catch (long val2) {
			Message();
			cout << "Результат вычисления: " << "infinity" << endl;
		}
	}
private:
	char* Message() { 
		char b[] = "Деление на ноль";
		cout << b << endl;
		return b;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	ZdivideException* a = new ZdivideException("/", 1, 0);
	UnderflowException* b = new UnderflowException("+", LONG_MIN, -1000000000);
	OverflowException* c = new OverflowException("+", LONG_MAX, 100000000);
	return 0;
}
