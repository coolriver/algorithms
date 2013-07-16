/*
 *Author:hanjiang
 */
#include <math.h>
#include <iostream> 
#include <time.h>
using namespace std; 

class Job
{
    private:
        long a;
        long b;
    public:
        Job(long a_,long b_);
        long Calculate(long integer);
        void Traverse();
        void Rule();
        long Recursion(long integer,int step,bool zero);
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
    clock_t t_start,t_end;
    t_start = clock();
    for (long i = 0;i <=a;i++){
        sum += Calculate(i);
    }
    t_end = clock();

    cout << "method:traverse  count:"<<sum<<"  time:"<<t_end - t_start<<endl;
}

long Job::Recursion(long integer,int step,bool zero)
{
    if (step == 0){
        return (integer >= b)? 1 : 0;
    }
    else{
        long tail_length = (long)pow(10,step);
        int head = integer / tail_length;
        long tail = integer % tail_length;
        if (head > b){
           if (0 == b && !zero){
                return (head - 1) * Recursion(tail_length - 1,step - 1,true) + Recursion(tail,step - 1,true) + Recursion(tail_length - 1,step - 1,false);
           }
           else{
                return head * Recursion(tail_length - 1,step - 1,true) + tail_length + Recursion(tail,step - 1,true); 
           }
        }
        else if (head == b){
           if (0 == b && !zero){
                return Recursion(tail,step - 1,false);
           }
           return head * Recursion(tail_length,step - 1,true) + (tail + 1) + Recursion(tail,step - 1,true);
        }
        else{
            return head * Recursion(tail_length,step - 1,true) + Recursion(tail,step - 1,true);
        }
    }
}

void Job::Rule()
{
    long sum = 0;
    clock_t t_start,t_end;
    t_start = clock();
    
    int atmp = a;
    int step  = 0;
    while ((atmp = atmp / 10) != 0){
        step++;
    }
    sum =  Recursion(a,step,false);

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
