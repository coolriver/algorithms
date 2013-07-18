/*
 * Author:hanjiang
 * Usage: g++ -o rule.out rule.cpp
 *        ./rule.out RANGE CHARACTER
 */
#include <math.h>
#include <iostream> 
#include <sys/time.h>
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
        void RuleRecursion();           //calculate total count of "b" in [0~a] using method of finding rules in recursion.
        void RuleCirculation();           //calculate total count of "b" in [0~a] using method of finding rules in circulation.      
        long Recursion(long integer,int step,bool zero); //recursion for function RuleRecursion().
        long Circulation();                              //circulation for function RuleCirculation().
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
    timeval t_start,t_end;            //running time
    gettimeofday(&t_start,0);
    for (long i = 0;i <=a;i++){       //calculate each integer in [0 ~ a] and get the summation of them.
        sum += Calculate(i);
    }
    gettimeofday(&t_end,0);
    double timeuse = 1000000 * (t_end.tv_sec - t_start.tv_sec) +
                     t_end.tv_usec - t_start.tv_usec;
    cout << "method:Traverse         count:"<<sum<<"  time:"<<timeuse<<"us"<<endl;
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
        long tail_length = (long)pow(10,step);   //10e(step)
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

void Job::RuleRecursion()
{
    long sum = 0;
    timeval t_start,t_end;            //running time
    gettimeofday(&t_start,0);
    
    int atmp = a;
    int step  = 0;
    while ((atmp = atmp / 10) != 0){ // calculate step:the magnitude of "a"
        step++;
    }
    sum =  Recursion(a,step,false);  //start recursion

    gettimeofday(&t_end,0);
    double timeuse = 1000000 * (t_end.tv_sec - t_start.tv_sec) +                                                                        
                     t_end.tv_usec - t_start.tv_usec;
    cout << "method:RuleRecursion    count:"<<sum<<"  time:"<<timeuse<<"us"<<endl;
}

long Job::Circulation()
{
    long tmp = a;             //copy of a
    long count = 0;           //total count of "b"
    int character = 0;        //current character
    long tail_count = 0;      //count of "b" in range["tail_length"-1] and head character can be "0"
    long tail_length = 0;     //10e(STEP)
    long tail_count_zero = 0; //count of "b" in range["tail_length"-1] and head character can not be "0"
    do{
        character = tmp % 10;//get current character,from right to left
        if (tmp == a){       //if it is the first character(the lowest order character )
            count = (character >= b)? 1 : 0;
            tail_count = 1;
            tail_length = 10;
            tail_count_zero = 1;
        }
        else{
            if (character > b){
                if (0 == b && tmp / 10 == 0){//if it is the last character(the highest order character) and "b" is "0"
                    count = (character - 1) * tail_count + //head character range [1~character-1]
                            tail_count_zero +              //head character is "0"
                            count;                         //head character is "character"
                }
                else{
                    count = character * tail_count +       //head character range[0~character-1]
                            tail_length +                  //head character is "b"
                            count;                         //head character is "character"
                }
            }
            else if (character == b){
                    count = character * tail_count +       //head character range[0~character-1]
                            (a % tail_length + 1) +        //head character is "b"
                            count;                         //head character is "character"
                }
            else{
                count = character * tail_count +           //head character range[0~character-1] 
                        count;                             //head character is "character"
            }
        
            tail_length *= 10;
            if (0 == b){
                tail_count_zero  = 9 * tail_count +        //head character range[1~9]
                                   tail_count_zero;        //head character is "0"
            }
            tail_count = 10 * tail_count  +                //head character range[0~9]
                         tail_length / 10;                 //head character is "b"
            
        }
    }while((tmp = tmp / 10) > 0);

    return count;
}

void Job::RuleCirculation()
{
    long sum = 0;
    timeval t_start,t_end;            //running time
    gettimeofday(&t_start,0);

    sum =  Circulation();  //start recursion

    gettimeofday(&t_end,0);
    double timeuse = 1000000 * (t_end.tv_sec - t_start.tv_sec) +                                                                        
                     t_end.tv_usec - t_start.tv_usec;
    cout << "method:RuleCirculation  count:"<<sum<<"  time:"<<timeuse<<"us"<<endl;
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
    job.RuleRecursion();
    job.RuleCirculation();
    return 0;
}


