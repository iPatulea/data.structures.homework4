/*Patulea Ionut
CA313*/


#include<fstream>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include "treap.h"
ifstream f("date.in");
ofstream g("date.out");
class Trie{

public:

	bool sem;
	Treap<pair<int,string> > *treap;
	Trie *ram[10];
	
	Trie(){
		sem = false;
		treap = new Treap<pair<int,string> >();
		memset( ram, 0, sizeof( ram ) );
	}

};

Trie *T = new Trie;
int r,b;
string cuv;
pair<int,string> foo;

void ins(Trie *nod,char *num,int nr)
{
	/*Intru in trie pana cand se termina sirul de numere*/
	b=*num-48;
	if( strlen(num) == 0 )
	{
		/*r este prioritatea */
		r = rand()%1000;
		nod->sem = true;
		foo = make_pair(nr,cuv);
		nod->treap->insert(nod->treap,foo,r);
		return;
	}
	/*creez ramura daca nu exista*/
	if( nod->ram[b]==0 )
		nod->ram[b] = new Trie;
	
	ins( nod->ram[b],num+1,nr);
}
void found(Trie *nod,char *num)
{ 
	/*la fel ca insertul intru in trie pe fiecare ramura indicata*/
	if (*num == '*')
	{
		num++;
		/*calculez ce cuvant caut*/
		b = atoi(num)+1;
		b = b%(nod->treap->nr_nodes);

		if (b == 0)
			b = nod->treap->nr_nodes;

		foo = nod->treap->findKD(b);
		g<<foo.second<<'\n';
		/*sterg perechea mea de aparitii si cuvant*/
		nod->treap->erase(nod->treap,foo);
		foo.first++;
		/*o inserez din nou cu numarul de aparitii crescut cu unu*/
		nod->treap->insert(nod->treap,foo,r);
		return;
	}

	if (strlen(num)==0)
	{
		/*doar il caut pe cel mai folosit si ii cresc numarul de aparitii*/
		foo = nod->treap->findKD(1);
		g<<foo.second<<'\n';
		nod->treap->erase(nod->treap,foo);
		foo.first++;
		nod->treap->insert(nod->treap,foo,r);
		return;
	}

	b=*num-48;
	if ( nod->ram[b] )
		found(nod->ram[b],num+1);
}
int main()
{
	int n,m,nr,lun;
	char num[100];
	f>>n;
	for (int j=1;j<=n;j++)
	{
		f>>cuv;
		f>>nr;
		lun = cuv.size();

		for(int i=0;i<lun;i++)
		{
			if (cuv[i]=='a' || cuv[i]=='b' || cuv[i]=='c'){
				num[i]='2';
				continue;
			}
			if (cuv[i]=='d' || cuv[i]=='e' || cuv[i]=='f'){
				num[i]='3';
				continue;
			}
			if (cuv[i]=='g' || cuv[i]=='h' || cuv[i]=='i'){
				num[i]='4';
				continue;
			}
			if (cuv[i]=='j' || cuv[i]=='k' || cuv[i]=='l'){
				num[i]='5';
				continue;
			}
			if (cuv[i]=='m' || cuv[i]=='n' || cuv[i]=='o'){
				num[i]='6';
				continue;
			}
			if (cuv[i]=='p' || cuv[i]=='q' || cuv[i]=='r' || cuv[i]=='s'){
				num[i]='7';
				continue;
			}
			if (cuv[i]=='t' || cuv[i]=='u' || cuv[i]=='v'){
				num[i]='8';
				continue;
			}
			if (cuv[i]=='w' || cuv[i]=='x' || cuv[i]=='y' || cuv[i]=='z'){
				num[i]='9';
				continue;
			}
		}

		num[lun]=NULL;
		ins(T,num,nr);

	}
	f>>m;
	for (int i=0;i<m;i++)
	{
		f>>num;
		/*Pun caracterul "sfarsit de sir" */
		num[strlen(num)]=NULL;
		found(T,num);
	}
	return 0;
}
