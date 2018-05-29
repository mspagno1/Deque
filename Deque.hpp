#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <random>
#include <unistd.h>
#include <typeinfo>

//CHANGE CODE FOR End to be +1 over 

using namespace std;

//DEQUE STRUCTURE
#define Deque_DEFINE(t)								\
	struct Deque_##t##_Iterator;						\
	struct Deque_##t{								\
		int deqSize;							\
		t *array;							\
		int numElements;						\
		t * start;							\
		t * ending;							\
		char type_name[strlen("Deque_"#t)+1]; 						\
		int startNum;							\
		int endNum;							\
		bool (*result)(const t &,const t &); 				\
		void (*dtor)(Deque_##t * deq);					\
		int (*size)(Deque_##t * deq);					\
		bool (*empty)(Deque_##t * deq);					\
		void (*push_back)(Deque_##t* deq, t element);			\
		void (*push_front)(Deque_##t * deq, t element);			\
		t& (*front)(Deque_##t *deq);					\
		t& (*back)(Deque_##t* deq);					\
		void (*pop_front)(Deque_##t * deq);				\
		void (*pop_back)(Deque_##t * deq);					\
		Deque_##t##_Iterator (*begin)(Deque_##t *deq);			\
		Deque_##t##_Iterator (*end)(Deque_##t *deq);			\
		t& (*at)(Deque_##t * deq, int pos);				\
		void (*clear)(Deque_##t * deq);					\
	};									\
										\
	/*Iterator*/								\
	struct Deque_##t##_Iterator{						\
		t* iter;							\
		Deque_##t * deq;						\
		/*Iterator functions*/						\
		void inc(Deque_##t##_Iterator *it){				\
			if(it->iter != &deq->array[(deq->deqSize - 1)]){	\
				it->iter = it->iter + 1;			\
			}							\
			else{							\
				it->iter =  &deq->array[0];			\
			}							\
		}								\
										\
		void dec(Deque_##t##_Iterator *it){						\
			if(it->iter != &deq->array[0]){				\
				it->iter = it->iter - 1;			\
			}							\
			else{							\
				it->iter = &deq->array[(deq->deqSize - 1)];	\
			}							\
		}								\
										\
		t& deref(Deque_##t##_Iterator *it){					\
			return * it->iter ;					\
		}								\
	};									\
	/*Deconstructor of some kind para: deque */				\
	void Deque_##t##_dtor(Deque_##t * deq){							\
		free (deq->array);						\
	}									\
										\
	/*size -returns size of deque para: deque object passed*/		\
	int Deque_##t##_size(Deque_##t * deq){							\
		return deq->numElements;					\
	}									\
										\
	/*empty - returns if deque is empty or not para : deque object*/	\
	bool Deque_##t##_empty(Deque_##t * deq){						\
		bool emptyCheck;						\
		if(deq->numElements == 0){					\
			emptyCheck = true;					\
		}								\
		else{								\
			emptyCheck = false;					\
		}								\
		return emptyCheck;						\
	} 									\
										\
										\
	/*push_back - adds element to the end of the deque para: deque object , object added*/	\
	void Deque_##t##_push_back(Deque_##t* deq, t element){		\
		if(deq->numElements == deq->deqSize){		\
			t * temp;	\
			temp = (t *) malloc((deq->deqSize*sizeof(t)));			\
			int i = 0;		\
			int pos = deq->startNum;	\
			while(pos != deq->endNum +1){	\
				if(pos == deq->deqSize){	\
					pos = 0;	\
				}	\
				temp[i] = deq->array[pos];	\
				if(pos == deq->endNum){		\
					break;	\
				}	\
				pos++;	\
				i++;	\
			}	\
			deq->array = (t*) realloc (deq->array, (deq->deqSize * 2) * sizeof(t));	\
			for(int p = 0; p < deq->deqSize; p++){	\
				deq->array[p] = temp[p];	\
			}	\
			deq->start = &deq->array[0];	\
			deq->ending = &deq->array[(deq->deqSize - 1)];	\
			deq->startNum = 0;	\
			deq->endNum = deq->deqSize - 1;	\
			deq->deqSize = deq->deqSize*2;	\
			free (temp);			\
		}	\
		if(deq->numElements == 0){	\
			*deq->ending = element;	\
		}	\
		else{	\
			if(deq->endNum == (deq->deqSize - 1)){	\
				deq->ending =  &deq->array[0];	\
				*deq->ending = element;	\
				deq->endNum = 0;	\
			}	\
			else{	\
				deq->ending = deq->ending + 1;	\
				deq->endNum = deq->endNum + 1;	\
				*deq->ending = element;	\
			}	\
		}	\
		deq->numElements = deq->numElements + 1;	\
	}	\
	\
	/*push_front - adds element to the start of the deque para: deque object , object added*/	\
	void Deque_##t##_push_front(Deque_##t * deq, t element){	\
		if(deq->numElements == deq->deqSize){	\
			t * temp;	\
			temp = (t *) malloc((deq->deqSize*sizeof(t)));		\
			int i = 0;		\
			int pos = deq->startNum;	\
			while(pos != deq->endNum +1){	\
				if(pos == deq->deqSize){	\
					pos = 0;	\
				}	\
				temp[i] = deq->array[pos];	\
				if(pos == deq->endNum){		\
					break;			\
				}		\
				pos++;		\
				i++;		\
			}			\
			deq->array = (t*) realloc (deq->array, (deq->deqSize * 2) * sizeof(t));	\
			for(int p = 0; p < deq->deqSize; p++){	\
				deq->array[p] = temp[p];	\
			}	\
			deq->start = &deq->array[0];	\
			deq->ending = &deq->array[(deq->deqSize - 1)];	\
			deq->startNum = 0;	\
			deq->endNum = deq->deqSize - 1;	\
			deq->deqSize = deq->deqSize*2;	\
			free (temp);			\
		}	\
		if(deq->numElements == 0){	\
			*deq->start = element;	\
		}	\
		else{	\
			if(deq->startNum == 0){	\
				deq->start = &deq->array[(deq->deqSize - 1)];	\
				*deq->start = element;	\
				deq->startNum = deq->deqSize -1;	\
			}	\
			else{	\
				deq->start = deq->start - 1;	\
				deq->startNum = deq->startNum - 1;	\
				*deq->start = element;		\
			}	\
		}		\
		deq->numElements = deq->numElements + 1;	\
	}							\
	/*front - accesses first element para: deque object*/	\
	t& Deque_##t##_front(Deque_##t *deq){					\
		return *deq->start;				\
	}						\
			\
	/*back - accesses last element para: deque object*/	\
	t& Deque_##t##_back(Deque_##t* deq){					\
		return *deq->ending;				\
	}							\
								\
	/*pop_front - deletes first element para: deque object*/	\
	void Deque_##t##_pop_front(Deque_##t * deq){				\
		if(deq->startNum != (deq->deqSize -1)){		\
			deq->start = deq->start + 1;		\
			deq->startNum = deq->startNum + 1;	\
		}						\
		else{						\
			deq->start = &deq->array[0];		\
			deq->startNum = 0;			\
		}						\
		deq->numElements = deq->numElements - 1;	\
	}							\
								\
	/*pop_back - deletes last element para: deque object*/	\
	void Deque_##t##_pop_back(Deque_##t * deq){				\
		if(deq->endNum != 0){				\
			deq->ending = deq->ending - 1;		\
			deq->endNum = deq->endNum - 1;		\
		}						\
		else{						\
			deq->ending = &deq->array[(deq->deqSize - 1)];	\
			deq->endNum = deq->deqSize - 1;		\
		}						\
		deq->numElements = deq->numElements - 1;	\
	}							\
								\
	/*begin - returns the position of first element iterator para: deque obj*/	\
	Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *deq){					\
		Deque_##t##_Iterator it;								\
		it.iter = deq->start;							\
		it.deq = deq;							\
		return it;						\
	}							\
											\
	/*end - returns the position of first element iterator para: deque obj*/	\
	Deque_##t##_Iterator Deque_##t##_end(Deque_##t *deq){				\
		Deque_##t##_Iterator it;					\
		it.iter = deq->ending +1;				\
		it.deq = deq;					\
		return it;					\
	}							\
										\
	/*at -returns element at a certain location para: deque obj, position*/	\
	t& Deque_##t##_at(Deque_##t * deq, int pos){		\
		return deq->array[((deq->startNum+pos)%(deq->deqSize ))];		\
	}					\
										\
	/*clear- clears out the elements of a deque para : deque obj*/		\
	void Deque_##t##_clear(Deque_##t * deq){				\
		deq->start = &deq->array[0];			\
		deq->ending = &deq->array[0];			\
		deq->numElements  = 0;				\
		deq->startNum = 0;				\
		deq->endNum = 0;				\
	}							\
	/*Iterator_equal checks if the iterator is at the end of our deque para: iterator struct and ending pos*/		\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it1, Deque_##t##_Iterator it2){		\
		if(it1.iter == (it2.iter)){				\
			return true;					\
		}							\
	else{								\
			return false;					\
		}							\
	}								\
											\
	/*equal checks if two deques are equal*/					\
	bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2){				\
		bool sameStruct = true;							\
		if(deq1.numElements == deq2.numElements){				\
			if(deq1.startNum == deq2.startNum){				\
				int pos = deq1.startNum;				\
				while( pos != (deq1.endNum +1)){				\
					bool deq1Front = (*deq1.result)(deq1.array[pos],deq2.array[pos]);	\
					bool deq1Back = (*deq1.result)(deq2.array[pos],deq1.array[pos]);	\
					if(deq1Front == false){					\
						if(deq1Back == true){ 					\
							sameStruct = false;		\
						}					\
					}						\
					else{						\
						sameStruct = false;			\
					}						\
					if(pos == deq1.deqSize){			\
						pos = 0;				\
						if(pos == deq1.endNum){			\
							break;				\
						}					\
					}						\
					pos++;						\
				}							\
			}								\
			else{								\
				sameStruct = false;					\
			}							\
		}							\
		else{							\
			sameStruct = false;				\
		}							\
		return sameStruct;					\
									\
	}								\
/*c_tor  comp IS A FUNCTION POINTER (WERE PASSING A FUNCTION TO USE IN OUR COMPARSION*/								\
	void Deque_##t##_ctor(Deque_##t *deq,bool (*comp)(const t &,const t &)){		\
		deq->array = (t *) malloc(10*sizeof(t));			\
		deq->deqSize = 10;						\
		deq->start = &deq->array[0];					\
		deq->ending = &deq->array[0];					\
		deq->numElements  = 0;						\
		deq->startNum = 0;						\
		deq->endNum = 0;						\
		deq->result = (comp);						\
		strcpy(deq->type_name,"Deque_"#t);				\
		deq->dtor = (Deque_##t##_dtor);					\
		deq->size  = (Deque_##t##_size);				\
		deq->empty = (Deque_##t##_empty);				\
		deq->push_back = (Deque_##t##_push_back);			\
		deq->push_front = (Deque_##t##_push_front);			\
		deq->front = (Deque_##t##_front);				\
		deq->back =  (Deque_##t##_back);				\
		deq->pop_front = (Deque_##t##_pop_front);			\
		deq->pop_back =  (Deque_##t##_pop_back);			\
		deq->begin = (Deque_##t##_begin);				\
		deq->end = (Deque_##t##_end);					\
		deq->at =  (Deque_##t##_at);					\
		deq->clear = (Deque_##t##_clear);						\
	}									\
										

#endif
