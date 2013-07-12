#include <stdio.h>
#include <iostream>
#include <ctime>
#include <math.h>
#define MAXNUM 20
#define GROUPSIZE 20
#define EVONUM 1000
#define RANDOMRANGE 10000
#define SEXP 0.8
#define VARIAP 0.3

using namespace std;

typedef struct {
	int ability;
	double sumP;
	int gene[MAXNUM];
}One;

void initAB();
void getRandomUnit(One * guy);
void initGroup();
int getAbility(int *gene,int option);
void exchange(int *ac,int *bc);
void getNB();
void haveSex();
void variation();
void select();
void evaluate();
void setNB();
void Xover(int father,int mother);
void doVaria(int guy);

int a[MAXNUM];//= {21,33,32,4,165,6,7,833,9,1800};
int b[MAXNUM];// = {12,435,12,546,12,31,145,67,23,98};
int indexs[MAXNUM + 1];
int maxGap = 0;


One group[GROUPSIZE + 1];
One groupEvo[GROUPSIZE + 1];

int main(int argc, char* argv[])
{
	srand(unsigned(time(0)));
	initAB();
	initGroup();
	getNB();
	for (int i = 0;i < GROUPSIZE;i++){
		printf("i%d:",i);
		for (int j = 0;j < MAXNUM;j++){
			printf("%d ",group[i].gene[j]);
		}
		printf("\n");
	}

	int it = 0;
	while (group[GROUPSIZE].ability != (maxGap + 1 - maxGap % 2) && it < EVONUM){
		select();
		haveSex();
		variation();
		evaluate();
		setNB();
		it ++;
		printf("\n it:%d  ability:%d  gap:%d",it,group[GROUPSIZE].ability,maxGap - group[GROUPSIZE].ability + 1);
	}
	//printf("\n%d\t%d",group[GROUPSIZE].ability,maxGap + 1);
	getAbility(group[GROUPSIZE].gene,1);
	//printf("\n\nmaxgap:%d\n",maxGap);
	//getchar();
	return 0;
}

void initAB()
{
	for (int i = 0;i < MAXNUM;i++){
		a[i] = rand() % RANDOMRANGE;
		b[i] = rand() % RANDOMRANGE;
	}
	for (int i = 0;i < MAXNUM + 1;i++){
		indexs[i] = i - 1;
	}


	for (int i = 0;i < MAXNUM;i++){
		maxGap += abs(a[i]) + abs(b[i]);
	}
}

void initGroup()
{
	
	for (int i = 0;i < GROUPSIZE;i++){
		getRandomUnit(group + i);
		group[i].sumP = 0.0;
	}
	evaluate();
}

void getRandomUnit(One * guy)
{
	
	for (int i = 0;i < MAXNUM;i++){
		int ranIndex = rand()%(MAXNUM + 1);
		guy->gene[i] = indexs[ranIndex];
	}
	//guy->ability = getAbility(guy->gene);
}

void evaluate()
{
	for (int i = 0;i < GROUPSIZE;i++){
		group[i].ability = getAbility(group[i].gene,0);
	}
}

int getAbility(int *gene,int option)
{
	int ac[MAXNUM],bc[MAXNUM];
	int suma,sumb;
	suma = sumb = 0;
	for (int i = 0;i < MAXNUM;i++){
		ac[i] = a[i];
		bc[i] = b[i];
	}
	for (int i = 0;i < MAXNUM;i++){
		if (gene[i] > 0){
			exchange(ac+i,bc+gene[i]);
		}
	}
	for (int i = 0;i < MAXNUM;i++){
		suma += ac[i];
		sumb += bc[i];
	}
	if (option){
		printf("\nac:");
		for (int i = 0;i < MAXNUM;i++){
			printf("%d ",ac[i]);
		}
		printf("\nbc:");
		for (int i = 0;i < MAXNUM;i++){
			printf("%d ",bc[i]);
		}
	printf("\nsuma:%d  sumb:%d\n",suma,sumb);
	//printf("\tability:%d\n",abs(maxGap - abs(suma-sumb)) + 1);
	}
	return abs(maxGap - abs(suma-sumb)) + 1;
}

void exchange(int *ac,int *bc)
{
	int middle = *ac;
	*ac = *bc;
	*bc = middle;
}

void getNB(){
	int j = 0;
	for (int i = 0;i < GROUPSIZE;i++){
		if (group[i].ability > group[j].ability)
		{
			j = i;
		}
	}
	group[GROUPSIZE] = group[j];
	//printf("j:%d\n",j);
}

void select()
{
	double sumAbility = 0.0;
	double selectP;
	for (int i = 0;i < GROUPSIZE;i++){
		sumAbility += group[i].ability;
	}

	group[0].sumP = double(group[0].ability)/sumAbility;
	for (int i = 1;i < GROUPSIZE;i++){
		group[i].sumP += group[i-1].sumP + double(group[i].ability)/sumAbility;
	}

	for (int i = 0;i < GROUPSIZE;i++){
		selectP = rand() % 1001 / 1000.0;
		if (selectP < group[0].sumP){
			groupEvo[i] = group[0];
		}
		else{
			for (int j = 1;j < GROUPSIZE;j++){
				if (selectP >= group[j-1].sumP && selectP <= group[j].sumP){
					groupEvo[i] = group[j];
				}
			}
		}
	}

	for (int i = 0;i < GROUPSIZE;i++){
		group[i] = groupEvo[i];
	}
}

void haveSex()
{
	double sexp;
	int first = 0;
	int female,male;
	for (int i = 0;i < GROUPSIZE;i++){
		sexp = (double)(rand() % 1000) / 1000.0;
		if (sexp <= SEXP){
			first ++;
			if (first % 2){
				female = i;
			}
			else{
				male = i;
				Xover(male,female);
			}
		}
	}
}

void Xover(int father,int mother)
{
	int crusor1,crusor2,bigger,smaller,tmp;
	crusor1 = rand() % (MAXNUM - 2) + 1;
	crusor2 = rand() % (MAXNUM - 2) + 1;
	bigger = (crusor1 > crusor2) ? crusor1 : crusor2;
	smaller = (crusor1 < crusor2) ? crusor1 : crusor2;

	for (int i = smaller;i <= bigger;i++){
		tmp = group[father].gene[i];
		group[father].gene[i] = group[mother].gene[i];
		group[mother].gene[i] = tmp;
	}

}

void variation()
{
	double variaP;
	for (int i = 0;i < GROUPSIZE;i++){
		variaP = (double)(rand() % 1000) / 1000.0;
		if (variaP <= VARIAP){
			doVaria(i);
		}
	}
}

void doVaria(int guy)
{
	int crusor,tmp;
	int maxlentgh = MAXNUM / 2;
	int length = rand() % maxlentgh + 1;
	crusor = rand() % (MAXNUM - length) + 1;
	
	for (int i = 0;i < length && i + crusor < MAXNUM;i++){
		group[guy].gene[i + crusor] = indexs[rand()%(MAXNUM + 1)];
	}
}

void setNB()
{
	int big = 0;
	int small = 0;

	for (int i = 0;i < GROUPSIZE;i++){
		if (group[big].ability < group[i].ability){
			big = i;
		}
		if (group[small].ability > group[i].ability){
			small = i;
		}
	}

	if (group[big].ability > group[GROUPSIZE].ability){
		group[GROUPSIZE] = group[big];
	}
	else{
		group[small] = group[GROUPSIZE];
	}
}
