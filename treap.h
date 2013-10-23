/*Patulea Ionut
CA313*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
using namespace std;

template <typename T> struct Treap {
  T key;
  int priority, nr_nodes;
  Treap<T> *left, *right;
  bool nil;
  
 
  Treap() : priority(-1), left(NULL), right(NULL), nil(true), nr_nodes(0) {}

  
  void addData(T key, int priority) {
    this->nil = false;
    this->key = key;
    this->priority = priority;
    this->nr_nodes = 1;
    this->left = new Treap();
    this->right = new Treap();
  }

 
  void delData() {
    this->nil = true;
    this->priority = -1;
    delete this->left;
    delete this->right;
    this->left = NULL;
    this->right = NULL;
    this->nr_nodes = 0;
  }

  bool isNil() {
    return this->nil;
  }

  void rotateRight(Treap<T> *&nod) {
   Treap<T> *aux = nod->left;
	nod->left = aux->right;
    aux->right = nod;
	aux->nr_nodes = nod->nr_nodes;
	nod->nr_nodes = nod->left->nr_nodes + nod->right->nr_nodes +1;
    nod = aux;
  }

  void rotateLeft(Treap<T> *&nod) {
    Treap<T> *aux = nod->right;
	nod->right=aux->left;
	aux->left = nod;
	aux->nr_nodes = nod->nr_nodes;
	nod->nr_nodes = nod->left->nr_nodes + nod->right->nr_nodes +1;
	nod = aux;
  }

  void insert(Treap<T> *&fatherPointer, T key, int priority) {
    if (this->isNil()) 
	{
      this->addData(key, priority);
      return ;
    }
    if (key.first < this->key.first)
	{
		fatherPointer->nr_nodes++;
		left->insert(fatherPointer->left, key, priority);
	}
    else if (key.first > this->key.first)
	{
		fatherPointer->nr_nodes++;
		right->insert(fatherPointer->right, key, priority);
	}
	else if (key.second < this->key.second)
	{
		fatherPointer->nr_nodes++;
		right->insert(fatherPointer->right, key, priority);
	}
	else if (key.second > this->key.second)
	{
		fatherPointer->nr_nodes++;
		left->insert(fatherPointer->left, key, priority);
	}

    if (this->left->priority >= this->priority) 
	{
		rotateRight(fatherPointer);
    } 
	else if (this->right->priority > this->priority) 
	{
      rotateLeft(fatherPointer);
    }
  }

  void erase(Treap<T> *&fatherPointer, T key) {
    if (this->nil) 
	{
      return ;
    }
    if (key.first < this->key.first)
	{
		fatherPointer->nr_nodes--;
		left->erase(fatherPointer->left, key);
	}
    else if (key.first > this->key.first)
	{
		fatherPointer->nr_nodes--;
		right->erase(fatherPointer->right, key);
	}
	else if (key.second < this->key.second)
	{
		fatherPointer->nr_nodes--;
		right->erase(fatherPointer->right, key);
	}
	else if (key.second > this->key.second)
	{
		fatherPointer->nr_nodes--;
		left->erase(fatherPointer->left, key);
	}
    else if (this->left->isNil() && this->right->isNil()) 
	{
		this->delData();
    } 
	else if (this->left->priority > this->right->priority) 
	{
		fatherPointer->nr_nodes--;
      	rotateRight(fatherPointer);
      	erase(fatherPointer->right, key);
    }
	else 
	{
		fatherPointer->nr_nodes--;
       	rotateLeft(fatherPointer);
        erase(fatherPointer->left, key);
    }
  }

   T findKD(int k) {
   
	if(right->nr_nodes+1 > k) 
	{
      return right->findKD(k);
    }
    if (right->nr_nodes+1 == k) 
		return key;
    if(right->nr_nodes+1 < k) 
	{
      return left->findKD(k - right->nr_nodes-1);
    }
	//in caz de eroare
	T x;
	return x;
  }
};
