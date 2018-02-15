#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
//08
int main()
{
	std::fstream ulaz("input.txt", std::ios::in);
	std::fstream izlaz("output.txt", std::ios::out);
	//1 nacin

	std::vector<char> vektor;
	char c;
	while ((c = ulaz.get()) != EOF)
		vektor.push_back(c);

	std::sort(vektor.begin(), vektor.end(), [](char a, char b) { return a < b; });
	while (!vektor.empty())
	{
		izlaz << vektor.back();
		vektor.pop_back();
	}
	ulaz.close();
	izlaz.close();

	return 0;

	//ovo mozda nije dobar nacin, pitajte asistenta
	/*std::priority_queue<char> prioritetni_red; //sam sortira clanove dok ih trpa u prioritetni red.
	char c;
	while (c = ulaz.get()) //treba usporedba da je != eof
	{
	prioritetni_red.push(c);
	}
	while (!prioritetni_red.empty())
	{
	izlaz << prioritetni_red.top();
	prioritetni_red.pop();
	}
	ulaz.close();
	izlaz.close();*/
}

/*
svaki paran karakter u fajlu, ali u sortiranom redoslijedu
std::priority_queue<char> prioritetni_red; //sam ga sortira
char c;
bool paran;
while (c = ulaz.get()) //treba usporedba da je != eof
{
if(paran)
{
prioritetni_red.push(c);
paran = false;
}
else
paran = true;
}
while (!prioritetni_red.empty())
{
izlaz << prioritetni_red.top();
prioritetni_red.pop();
}
*/

//primjer lambda funkcije, caputre - lambda funkcija ili anonimni funkcijski objekt (funkcijski objekt, eng. "functor", google it) 
/*
{
int i = 5;
std::cout << i;
int niz[] = {3,5,7};
std::for_each(niz, niz+3, [&i](int broj){i+=broj;});
std::cout << i;
}
// lambda funkcija primjer
//[sta hvata, kako hvata](tip argument, tip argument, koliko ti treba....){ sta funkcija radi, sta hoces mozes, koliko hoces linija };
*/