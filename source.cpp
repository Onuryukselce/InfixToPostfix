#include <iostream>
#include <string>
#include <sstream>
#include <locale>
using namespace std;

#include <iostream>
using namespace std;


class Stack
{
	int top;
	int size;
	char* stackArr;
public:

	Stack() { top = -1; size = 5; }

	bool push(char x);
	char pop();
	char peek();
	bool isEmpty();
};

bool Stack::push(char item) // Stack'e item ekleme fonksiyonu
{
	if (top == -1) // Stack boşsa,
		stackArr = new char[size]; // stackArr adlı yeni dizi oluşturulur.
	if (top >= (size - 1)) { // Stack fullse
		char* d2;
		d2 = new char[size * 2]; // // d2 adlı bir array oluştur ve  boyutunu size*2 olarak ayarla
		for (int i = 0; i <= top; i++) // stackArr içinde gezin
			d2[i] = stackArr[i]; // stackArr elemanlarını d2'ye ekle
		stackArr = d2; // stackArr'yi d2'ye eşitle
		size = size * 2; // boyutu ikiye katla
	}
		stackArr[++top] = item; // stack'e elemanı ekle.
		return true;
}

char Stack::pop() // itemi stackten çıkaran fonksiyon
{
	if (top <= -1) { // Eğer top -1 ise uyarı ver
		return NULL;
	}
	else { // değilse stackten çıkarma işlemini yap
		char item = stackArr[top--];
		return item; // çıkarılan itemi döndür;
	}
}

char Stack::peek()
{
	if (top >= 0)
		return stackArr[top--]; // çıkarılan itemi döndür;
}
bool Stack::isEmpty() // Stack boşsa return et.
{
	if (top <= -1) {
		return true;
	}
	else {
		return false;
	}
}



/* Bu Kısım daha sonra hesap makinesinede cevrilirken kullanilabilir.
template <class T>
int s_toi(T ch) // string -> int donusumunu yapan fonksiyon, string, char karmasasi olmamasi icin template kullanildi.
{
	int i;
	std::istringstream(ch) >> i;
	return i;
}


int calculate(char oprtr, int x, int y) {
	if (oprtr == '+')
		return x + y;
	else if (oprtr == '-')
		return x - y;
	else if (oprtr == '*')
		return x * y;
	else if (oprtr == '/')
		return x / y;
}
*/


int priority(char ch) // işlem önceliği belirleyen fonksiyon
{
	if (ch == '+' || ch == '-') // + veya - ise öncelik 1
		return 1;
	else if (ch == '*' || ch == '//')// * veya / ise öncelik 2
		return 2;
	else if (ch == '^') // ^ ise öncelik 3
		return 3;
	else {
		return 0;
	}
}

string infixtToPostfix(Stack* st, string infix) //infix ifadeyi postfixe ceviren fonksiyon
{
	string postfix; //postfix, ifade postfix stringi icinde olusturulup return edilecek
	string::iterator it;

	for (it = infix.begin(); it != infix.end(); it++) //infix ifadenin icinde gezinmemize saglayacak for dongusu.
	{
			if (isalnum(*it)) //mevcut indisdeki char bir alnumerik karakterse
			{
				postfix += *it; // postfixe direk ekleme yap.
			}
		else // mevcut indisdeki char bir operatörse
		{
				if (*it == '(') // operatör parantez açma ise stack'e push et
				{
					st->push(*it);
				}
				else if (*it == '^') // operatör üs alma ise stack'e push et
				{
					st->push(*it);
				}
				else if (*it == ')') // operatör parantez kapama ise
				{
	
					while (st->isEmpty() == false && st->peek() != '(') { // parantez açmayi bulana kadar geriye gel
						postfix += st->peek();// postfixe ekle,

						cout << postfix << endl;
						st->pop(); // pop işlemi yap.

					}
					st->pop(); // parantez açma işaretini de stackten çıkarıyoruz.
				}
				else //Hiç biri değilse, yani " + - * /" ise 
				{ 
					if (priority(*it) > priority(st->peek())) // Operatör önceliği en üstteki operatörden büyük ise
					{

						st->push(*it);//stack'e push et.
					}
					else //operatör önceliği en üstteki operatörden küçük ise  
					{
						while ((!st->isEmpty()) && priority(*it) < priority(st->peek())) // Stack boş değilse, önceliği yüksek olana git.
						{
							postfix += st->peek(); // postfixe ekle, 
							st->pop(); // pop işlemi yap..
						}
					}
				st->push(*it); // Son operatörü stack'e push et.
				}
		}
	}
	while (!st->isEmpty()) // Stack boşalana kadar devam et
	{
		postfix += st->peek(); // postfix'e stackteki elemanı ekle.
		st->pop(); // stackten elemanı sil.
	}
	return postfix; // postfix ifadeyi döndür.
}





int main()
{
	Stack* post = new Stack();
	string in = "8+4*5";
	string postfix = infixtToPostfix(post, in);
	cout << in << " ifadesinin postfix hali : " << postfix << " seklinde" << endl;
}

