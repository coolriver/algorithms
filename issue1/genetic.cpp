/*
 *   Author:Hanjiang
 */
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <math.h>
#define MAXNUM 20           //Size of each array.
#define GROUPSIZE 20        //Size of population.
#define EVONUM 1000         //Generation number that the population evolves.
#define RANDOMRANGE 10000   //Range of the ramdom integers in each array.
#define SEXP 0.8            //Probability of successfully mate.
#define VARIAP 0.3          //Probability of variation.

using namespace std;

typedef struct {           //Struct of individual.
	int ability;           //Ability to live(viability).
	double sumP;           //Accumulative select probability.
	int gene[MAXNUM];      //Gene of indivudual.
			       //gent[i] = j means that a[i] exchange with b[j].
}One;

void initAB();                          //Initialize the two arrays.
void getRandomUnit(One * guy);          //Initialize an individual.
void initGroup();                       //Initialize the population.
int getAbility(int *gene,int option);   //Calculate the vialibity of an individual.
void exchange(int *ac,int *bc);         //Exchange the value of two integers.
void getNB();                           //Get the individual that has the strongest viability.
void haveSex();                         //Mate  #_#.
void variation();                       //Variation config.
void select();                          //Natural selection.
void evaluate();                        //Get viability of each individual in population.
void setNB();                           //Set the individual that has the strongest viability.
void Xover(int father,int mother);      //Exchange part of genes of two individuals.
void doVaria(int guy);                  //Do variation.

int a[MAXNUM];               //Array a.
int b[MAXNUM];               //Array b.
int indexs[MAXNUM + 1];      //Gene available range.
int maxGap = 0;              //Summation of all integers both in array a and array b.


One group[GROUPSIZE + 1];   //Population:an array of individuals.
                            //The last element in array is used to store the best individual in a population
One groupEvo[GROUPSIZE + 1];//A temporary array used for natural selection.

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
