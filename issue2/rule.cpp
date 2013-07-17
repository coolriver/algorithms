/*
 * Author:hanjiang
 * Usage: g++ -o rule.out rule.cpp
 *        ./rule.out RANGE CHARACTER
 */
#include <math.h>
#include <iostream> 
#include <time.h>
using namespace std; 

class Job
{
    private:
        long a;                         //integer range[0~a].
        long b;                         //count character b(b range from 0 to 9).
    public:
        Job(long a_,long b_);                          
        long Calculate(long integer);   //calculate count of "b" in "integer".
        void Traverse();                //calculate total count of "b" in [0~a] using method of traversing.
        void Rule();                    //calculate total count of "b" in [0~a] using method of finding rules.
        long Recursion(long integer,int step,bool zero); //recursion for function Rule().
};

Job::Job(long a_,long b_)
{
    a = a_;
    b = b_;
}

long Job::Calculate(long integer)
{
    long sum = 0;
    do{
        if ((integer % 10) == b){
            sum++;
        }
    }while((integer = integer / 10) > 0);
    return sum;
}

void Job::Traverse()
{
    long sum = 0;
    clock_t t_start,t_end;            //running time
    t_start = clock();
    for (long i = 0;i <=a;i++){       //calculate each integer in [0 ~ a] and get the summation of them.
        sum += Calculate(i);
    }
    t_end = clock();

    cout << "method:traverse  count:"<<sum<<"  time:"<<t_end - t_start<<endl;
}


/*
 * Parameters:
 *      integer : range of number
 *      step    : magnitude of integer
 *      zero    : if allow the head character is "0"
 *
 *  Return:
 *      the total count of character "b" in range of [0 ~ integer] 
 */

long Job::Recursion(long integer,int step,bool zero)
{
    if (step == 0){                    //recurse end point:"integer" only has one character
        return (integer >= b)? 1 : 0;
    }
    else{
        long tail_length = (long)pow(10,step);   //10e^step
        int head = integer / tail_length;        //max head character of "integer"
        long tail = integer % tail_length;       //chacacters of "integer" except of head character
        if (head > b){
           if (0 == b && !zero){                 //"b" is "0" and head character equals 0 is not allowed
                return (head - 1) * Recursion(tail_length - 1,step - 1,true) + //head character range [1~head-1]
                       Recursion(tail,step - 1,true) +                         //head character is "head"
                       Recursion(tail_length - 1,step - 1,false);              //head character is "0"
           }
           else{
                return head * Recursion(tail_length - 1,step - 1,true) +      //head character range[0~head-1]
                       tail_length +                                          //head character is "b"
                       Recursion(tail,step - 1,true);                         //head character is "head"
           }
        }
        else if (head == b){
           if (0 == b && !zero){
                return Recursion(tail,step - 1,false);                       //head character is "0"
           }
           return head * Recursion(tail_length,step - 1,true) +              //head character range[0~head-1]
                  (tail + 1) +                                               //head character is "b"
                  Recursion(tail,step - 1,true);                             //head character is "head"
        }
        else{
            return head * Recursion(tail_length,step - 1,true) +             //head character range[0~head-1]
                   Recursion(tail,step - 1,true);                            //head character is "head"
        }
    }
}

void Job::Rule()
{
    long sum = 0;
    clock_t t_start,t_end;            //running time
    t_start = clock();
    
    int atmp = a;
    int step  = 0;
    while ((atmp = atmp / 10) != 0){ // calculate step:the magnitude of "a"
        step++;
    }
    sum =  Recursion(a,step,false);  //start recursion

    t_end = clock();
    cout << "method:traverse  count:"<<sum<<"  time:"<<t_end - t_start<<endl;
}

int main(int argc,char ** argv)
{   
    int a,
    b,
    count; 
    if (argc < 3){
        cout <<"excute like this:./rule.out 2344 3"<<endl;
        exit(-1);
    } 
    Job job(atoi(argv[1]),atoi(argv[2]));
    job.Traverse();
    job.Rule();
    return 0;
}
