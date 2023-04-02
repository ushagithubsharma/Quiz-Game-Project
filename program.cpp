#include<iostream>
#include<Ctime>
#include<conio.h>
#include<windows.h>
#include<graphics.h>
#include<string.h>
#include<unistd.h>
#include<cstdlib>
#include "MMSystem.h"
using namespace std;
string player_name;
bool pay_half_skip=true;
bool skip=true;
long cash=0;
long question_price=100;
int consective=0;
int right_answer=0;
int wrong_answer=0;
int question_no=1;
void createpassword1();
int ask_random_question();
void checkpassword(string password);
void loadingbar();
void results();
void game_rules();
void logo();
void start();
void settime();
void front();
void sound();
void setquestionins();
int setquestiontime(int number);
int check_answer(char answer,char correct_answer);
struct Question{
    string question;
    string option_a;
    string option_b;
    string option_c;
    string option_d;
    char answer;
    bool availability;
};
Question question[10];
int main()
{
    system("cls");
    question[0]={"which programming structure makesa comparison?\n","relation","decision","sequence","repetition",'b',true};
    question[1]={"A loop within a loop is called?\n","nested loop","complex loop","infinite loop","none",'a',true};
    question[2]={"which statement causes a loop to terminate early?\n","continue"," break","sleep"," default",'b',true};
    question[3]={"variable that holds a large group of similar type of data is called?\n"," constant"," scalar value","array","multiple variable",'c',true};
    question[4]={"A two dimensional array can be viewed as?\n","arguments,parameters","rows,columns","increment,decrement","none",'b',true};
    question[5]={"The index of first element of array is always?\n","0"," 1"," -1"," 2",'a',true};
    question[6]={"The name of the structure is referred to as its?\n","paramet","argument"," return type","data type",'d',true};
    question[7]={"which of the following allows you to access structure members ?\n","dot operator"," loop","this->","*",'a',true};
    question[8]={"The process of sending argument to the function is called ?\n","sending","bdelivering"," giving","passing",'d',true};
    question[9]={"The statement that avtivates a function is called?\n","declaration","implementation"," function output","function output",'c',true};
    //logo();
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,4);
    front();
    loadingbar();
    createpassword1();
    return 0;
    //checkpassword(password);
}
void start()
{
    system("cls");
    cout<<"\n\n\n================================================================================================================================"<<endl;
    cout<<"====================================================WELCOME TO THE=============================================================="<<endl;
    cout<<"==========================================KAUN BANEGA CRORAPATI SIMULATION======================================================"<<endl;
    cout<<"================================================================================================================================"<<endl;
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,6);
    cout<<"\n\n\n\n\n\n\t\t\t\t\t\tEnter your name:";
    SetConsoleTextAttribute(h,1);
    getline(cin,player_name);
    system("cls");
    game_rules();
    while(true)
    {
        static int c=2;
        if(question_no>10)
        break;
        else if(c==0)
        {
            break;
        }
        else
        c=ask_random_question();
    }
    results();
}

int ask_random_question()
{
    
    srand(time(0));
    while(true)
    {
        int number=rand()%10;
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        
        SetConsoleTextAttribute(h,13);
        if(question[number].availability)
        {
            question[number].availability=false;
           
            cout<<endl<<endl;
            SetConsoleTextAttribute(h,6);
            //system("cls");
            int s=setquestiontime(number);
            if(s==1)
            {
                results();
                return 0;
            }
            else
            {
            SetConsoleTextAttribute(h,6);
            char answer= _getch();
            answer=tolower(answer);
            SetConsoleTextAttribute(h,2);
            cout<<"\n\nyour choosen option is:"<<answer<<"\n";
            cout<<endl;
            question_no++;
            int a=check_answer(answer,question[number].answer);
            return a;
            break;
            }
        }
    }
}
int check_answer(char answer,char correct_answer)
{
        
    if(answer==correct_answer)
    {
         HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,3);
        cout<<"The correct option is:"<<correct_answer<<"\n";
        SetConsoleTextAttribute(h,6);
        cout<<"Congrulations...! Your answer is right"<<endl;
        SetConsoleTextAttribute(h,1);
        cout<<"you earned $"<<question_price<<endl;
        SetConsoleTextAttribute(h,12);
        cout<<"\t\t\tpress any key to continue...."<<endl;
        _getch();
        right_answer++;
        consective++;
        cash=cash+question_price;
    }
    else if((answer=='h')&&(pay_half_skip))
    {
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,1);
        cout<<"you choose the life line 'PAY HALF AND SKIP'"<<endl;
        SetConsoleTextAttribute(h,12);
        cout<<"you lose $"<<question_price/4<<endl;
        SetConsoleTextAttribute(h,6);
        cout<<"\t\t\tPress any key to continue....."<<endl;
        _getch();
        cash=cash-(question_price/4);
        pay_half_skip=false;

    }
    else if((answer=='l')&&(skip))
    {
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,1);
        cout<<"you choose the life line 'LEAVE QUESTION'"<<endl;
        SetConsoleTextAttribute(h,12);
        cout<<"you lose $0"<<question_price/4<<endl;
        SetConsoleTextAttribute(h,6);
        cout<<"\t\t\tPress any key to continue....."<<endl;
        _getch();
        skip=false;

    }
    else
    {
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,2);
        cout<<"The correct option is:"<<correct_answer<<"\n";
        SetConsoleTextAttribute(h,6);
        cout<<"Sorry...!your answer is wrong..."<<endl;
        SetConsoleTextAttribute(h,1);
        cout<<"you lose $"<<question_price/2<<endl;
        SetConsoleTextAttribute(h,3);
        cout<<"\t\t\t\t\tpress any key to end......"<<endl;
        _getch();
           wrong_answer++;
            consective=0;
        cash=cash-(question_price*2);
    }
    question_price=question_price*2;
    if(consective==3)
    pay_half_skip=true;
    if(consective==5)
    skip=true;
    if(answer==correct_answer||answer=='h'||answer=='l')
    return 1;
    else 
    return 0;
}
void checkpassword(string password)
{
    string password1;
    static  int i=3;
     HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,1);
    cout<<"Enter the password for verification\n\n";
    
    SetConsoleTextAttribute(h,6);
    cout<<"NOTE:\n\n";
   
    SetConsoleTextAttribute(h,3);
    if(i==3)
    {
    cout<<"********************************************************************************************************************************"<<endl;
    cout<<"you have only three chances to enter the password \n\nIf you are not able to fill the correct password within these choice then you are not able to play game"<<endl;
    cout<<"********************************************************************************************************************************"<<endl<<endl;
    }
     SetConsoleTextAttribute(h,2);
      //cout<<"password is"<<password;
    cout<<"\t\t\t\t\t\tPASSWORD:";
    getline(cin,password1);
   
    if(password1==password)
    {
        SetConsoleTextAttribute(h,6);
        cout<<"\n\n--------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"VALID PASSWORD!\n";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
        SetConsoleTextAttribute(h,2);
        cout<<"\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE\n";
        _getch();
        system("cls");
        settime();
    }
    else
    {
        SetConsoleTextAttribute(h,6);
        //cout<<"********************************************************************************************************************************"<<endl;
        cout<<"\n\n--------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"INVALID PASSWORD\n";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
       SetConsoleTextAttribute(h,2);
        cout<<"\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE\n";
        _getch();
        system("cls");
        if(i>1)
        {   
            i--;
            SetConsoleTextAttribute(h,1);
            cout<<"***********************************************************************************************************************"<<endl;
            cout<<"ALERT! YOU HAVE ONLY "<<i<<" chances left\n";
            cout<<"***********************************************************************************************************************"<<endl<<endl;
            checkpassword(password);
        }
        else 
        {
        SetConsoleTextAttribute(h,6);
        cout<<"--------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"SORRY! YOU LOSE YOUR ALL THREE CHANCES"<<endl;
        cout<<"--------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
        }  

    }

}
void setquestionins()
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,2);
     cout<<"IMPORTANT INSTRUCTION:"<<endl;
    SetConsoleTextAttribute(h,6);
     cout<<"\n\n***********************************YOU HAVE TO GIVE THE ANSWER OF TAHT QUESTION WITHIN 30 SECONDS*******************************"<<endl<<endl;
     cout<<"********************IF YOU FAIL TO GIVE ANSWER OF THAT QUESTION WITHIN 30 SECOND THEN YOU OUT FROM THE GAME**********************"<<endl<<endl;
     SetConsoleTextAttribute(h,12);
     cout<<"\n\n\n\n\t\t\t\t\tPRESS ANY KEY TO START THE QUIZ";
     _getch();
     system("cls");
}
int setquestiontime(int number)
{
    //system("cls");
     int s=30;
     HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(h,12);
     while(!_kbhit())
     {
          sleep(1);
          s--;
          if(s<0)
          {
               cout<<"\n\n\n\t\t\t\t\tTIME OUT!";
               break;
          }
          
          system("cls");
              SetConsoleTextAttribute(h,13);
            cout<<"================================================================================================="<<endl;
            cout<<"================================KAUN BANEGA CROREPATI============================================"<<endl;
            cout<<endl;
            SetConsoleTextAttribute(h,6);
            cout<<"\n\nThis Question No: "<<question_no<<" Is For $" <<question_price<<"\t\t\tBalance Is $"<<cash<<endl<<endl;
            SetConsoleTextAttribute(h,15);
            cout<<"Life Lines Available:";
            if(pay_half_skip)
            {
            SetConsoleTextAttribute(h,10);
            cout<<"\th=>PAY HALF AND SKIP";
            }
            if(skip)
            {
            SetConsoleTextAttribute(h,12);
            cout<<"\tl=>LEAVE QUESTION";
            }
           cout<<endl<<endl;
           SetConsoleTextAttribute(h,15);
           cout<<endl<<endl<<question[number].question<<endl<<endl;
           HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h,6);
            cout<<"a) " <<question[number].option_a<<endl<<"b) "<<question[number].option_b<<endl;
            cout<<"c) " <<question[number].option_c<<endl<<"d) "<<question[number].option_d<<endl<<endl;
          
     cout<<"\n\n\t\t\t\t\t\t"<<s<<endl<<endl<<endl<<endl;
      cout<<"\n\nENTER YOUR OUTPUT:";
     //cout<<"\n\t\t"<<s;
    // cout<<"\n\n\n\t\t\t\t\tPress any key to stop";
     }
     if(s==-1)
     {
        cout<<"\n\n\t\t\t\t\tTIME OUT \n SORRY YOU LOOSE CHANCE TO PLAY MORE";
        return 1;
     }
     
    
    
    // _getch();
    
}
    void createpassword1()
    {
        string password;
        string guess;
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,1);
        cout<<"Please create your own password\n\n\n\n";
        SetConsoleTextAttribute(h,6);
        cout<<"NOTE:\n\n";
        SetConsoleTextAttribute(h,2);
        //cout<<"********************************************************************************************************************************"<<endl<<endl;
        cout<<"********************************************************************************************************************************"<<endl<<endl;
        cout<<"The password must be equal to or greater than eight character"<<endl<<endl;
        cout<<"********************************************************************************************************************************"<<endl<<endl;
        SetConsoleTextAttribute(h,12);
        cout<<"\n\n\t\t\t\t\t\tCREATE PASSWORD:";
        SetConsoleTextAttribute(h,13);
        getline(cin,guess);
        if(guess.length()<8)
        {
            SetConsoleTextAttribute(h,12);
            cout<<"\n\n********************************************************************************************************************************"<<endl;
            cout<<"Non acceptable password\n"<<endl;
            cout<<"you have entered password less than eight character\n"<<endl;
            cout<<"********************************************************************************************************************************"<<endl<<endl;
            //system("cls");
            SetConsoleTextAttribute(h,6);
            cout<<"\n\nplease enter password again!\n"<<endl<<endl;
             //cout<<"*****************************************************************************************"<<endl<<endl;
            SetConsoleTextAttribute(h,15);
            cout<<"\t\t\t\t\t\n\n\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE\n"<<endl<<endl;
            _getch();
            system("cls");
            //cout<<"press any key to continue";
            createpassword1();
        }
        else
        {
            SetConsoleTextAttribute(h,11);
            cout<<"\n\n********************************************************************************************************************************"<<endl<<endl;
            cout<<"Acceptable Password\n"<<endl;  
            //cout<<"********************************************************************************************************************************"<<endl<<endl;  
            cout<<"********************************************************************************************************************************"<<endl<<endl;
            SetConsoleTextAttribute(h,1);
            cout<<"\t\t\t\t\t\n\n\t\t\t\t\t\tPLEASE PRESS ANY KEY TO CONTINUE"<<endl<<endl;
            _getch();
            system("cls");
            //cout<<"guess is"<<guess;
            checkpassword(guess);

        }
        
    }
    void settime()
    {
    short minutes=0,seconds=20;
    int time;
    
    time=(minutes!=0)?minutes*60:0;
    time+=seconds;
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,12);
    cout<<"********************************************************************************************************************************"<<endl<<endl;
    cout<<"********************************************************************************************************************************"<<endl<<endl;
    cout<<"--------------------------------------------QUIZ WILL START WITHIN 20 SECONDS --------------------------------------------------"<<endl<<endl;
    cout<<"-------------------------------------------SO YOU HAVE TO WANT FOR 20 SECONDS --------------------------------------------------"<<endl<<endl;
    cout<<"********************************************************************************************************************************"<<endl<<endl;
    cout<<"********************************************************************************************************************************"<<endl<<endl;
    SetConsoleTextAttribute(h,6);
    cout<<"\n\n\n\n\t######################################PRESS ANY KEY TO START THE TIME#############################################"<<endl<<endl;
    _getch();
    for(int i=time;i>0;i--)
    { 
        system("cls");
        
        SetConsoleTextAttribute(h,6);
        cout<<"\n\n\t\t\t\t\t\tQUIZ WILL START AFTER 20 SECONDS";
        cout<<"\n\n\n\n\n\n";
         SetConsoleTextAttribute(h,12);
        cout<<"********************************************************************************************************************************"<<endl<<endl;
        cout<<"################################################################################################################################"<<endl<<endl;
        SetConsoleTextAttribute(h,6);
        cout<<"\t\t\t\tREMAINING TIME IS....\t\t\t\t"<<minutes<<":"<<seconds<<endl<<endl;
        SetConsoleTextAttribute(h,12);
        cout<<"################################################################################################################################"<<endl<<endl;
        cout<<"********************************************************************************************************************************"<<endl<<endl;
        minutes=(i%60==0)?--minutes:minutes;
        seconds=(seconds==0)?59:--seconds;
        sleep(1);
    }
    system("cls");
    cout<<"\n\n\n\n\n\n";
    SetConsoleTextAttribute(h,1);
    cout<<"***********************************************************Time ENDED***********************************************************\n******************************************************Lasted for "<<time<<" seconds*****************************************************"<<"\n"<<endl;
    SetConsoleTextAttribute(h,13);
    cout<<"\n\n******************************************PRESS ANY KEY TO START THE QUIZ*******************************************************"<<endl<<endl;
    _getch();
    start();
    }
    void loadingbar()
    {
        //system("COLOR Oe");
        system("cls");
        cout<<"\e[?251";
        SetConsoleCP(437);
        SetConsoleOutputCP(437);
        int bar1=117,bar2=219;
        cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t";
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,12);
        cout<<"LLOADING....................";
        cout<<"\n\n\n\t\t\t\t\t\t";
        //HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,6);
        for(int i=0;i<25;i++)
        {
            cout<<(char)bar1;
        }
        cout<<"\r";
        cout<<"\t\t\t\t\t\t";
        for(int i=0;i<25;i++)
        {
            cout<<(char)bar2;
            Sleep(150);

        }
        cout<<"\n\t\t\t\t\t\t"<<(char)1<<"!";
        system("pause");
        //_getch();
        system("cls");
    }
    void results()
    {
        double percentage;
        percentage=right_answer*10;
        system("cls");
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,12);
        cout<<"============================================================================================================================="<<endl;
        cout<<"=============================================CHOOSE YOUR OPTION=============================================================="<<endl;
        cout<<"============================================================================================================================="<<endl;
        cout<<"Player Name:\t\t\t"<<player_name<<endl<<endl;
        //HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,2);
        cout<<"-----------------------------------------------------------------------------------------------------------------------------"<<endl;
        //HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,6);
        cout<<"Right Answer:\t\t\t"<<right_answer<<endl<<endl;
        //HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,2);
        cout<<"-----------------------------------------------------------------------------------------------------------------------------"<<endl;
       // HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,6);
        cout<<"Wrong Answer:\t\t\t"<<wrong_answer<<endl<<endl;
       // HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,2);
        cout<<"-----------------------------------------------------------------------------------------------------------------------------"<<endl;
       // HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,6);
        cout<<"Average:\t\t\t"<<percentage<<"%"<<endl<<endl;
        //HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,2);
        cout<<"-----------------------------------------------------------------------------------------------------------------------------"<<endl;
        if(cash>=0)
        {
        SetConsoleTextAttribute(h,1);
            cout<<"Winning Amount:\t\t\t$"<<cash<<endl<<endl;
        }
        else
        {
        SetConsoleTextAttribute(h,1);
            cout<<"Loosing Amount:\t\t\t$"<<cash<<endl<<endl;
        }
        //HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,13);
        cout<<"============================================================================================================================="<<endl;
        cout<<"======================================THANKS FOR PLAYING THIS GAME==========================================================="<<endl;
        cout<<"=======================================TUTORIAL BY ALFA TECHNOLOLOGY========================================================="<<endl;
        cout<<"============================================================================================================================="<<endl;
        cout<<"=======================================PRESS ANY KEY TO END============================================================="<<endl;
        cout<<"============================================================================================================================="<<endl;
        _getch();
        //cout<<"\n\n\n\n\t\t\t\t\t\t"<<"PRESS ANY KEY TO CONTINUE";
    }
    void game_rules()
    {
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,6);
        //cout<<"********************************************************************************************************************************"<<endl;
        cout<<"================================================================================================================================"<<endl;
        cout<<"========================================RULES AND REGULATION===================================================================="<<endl;
        cout<<"01. There Are Total Ten Question In This Game."<<endl<<endl;
        cout<<"02. There Onl Two Life Lines Which You Can At Any Stage Of Th Game."<<endl<<endl;
        cout<<"03. Pay Half & Skip Means You Have To Pay 1/4 5 Of Current Question."<<endl<<endl;
        cout<<"04. Leave Question Means You Can Leave A Question Without Any Detection."<<endl<<endl;
        cout<<"05. If You  Attempt 3 Consecutive Right Answer Pay Half & Skip Will Rescued."<<endl<<endl;
        cout<<"06. If You Attempts 5 Consecutive Right Answer Leave Question Will Rescued."<<endl<<endl;
        cout<<"07. After Every  Question The Amount Of Question Will Be Double."<<endl<<endl;
        cout<<"08. If The Answer Is Wrong Then Half Of The Amount Will Be Deducts From Your Balnce."<<endl<<endl;
        cout<<"09. Press H For Pay Half & Skip Help Line And L For Leave Question Help Line."<<endl<<endl;
        cout<<"10. Press A,B,C Or D To Answer Any Question."<<endl;
        cout<<"================================================================================================================================"<<endl;
        cout<<"============================================PRESS ANY KEY TO GET START=========================================================="<<endl;
        cout<<"================================================================================================================================"<<endl;
        _getch();
    system("cls");
     setquestionins();
    }
    void front()
    {
    	
        cout<<"********************************************************************************************************************************"<<endl<<endl;
        cout<<"********************************************************************************************************************************"<<endl<<endl;
        HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,6);
        cout<<"\n\n\t\t\t  *********************By Usha Sharma*********************";
		char a[33]="QUIZ GAME PROJECT";
        for(int i=0;i<33;i++)
        {
            if(i==0)
            {
            cout<<"\t\t\t\t\t\t"<<a[i];
            Sleep(200);
            }
            else if(i<22)
            {
            cout<<a[i];
            Sleep(200);
            }
            else if(i==22) 
            {
            cout<<"\n\n\t\t\t\t\t\t    "<<a[i];
            Sleep(200);
            }
            else
            {
            //SetConsoleTextAttribute(h,11);
            cout<<a[i];
            Sleep(200);
            }
        }
        SetConsoleTextAttribute(h,4);
        cout<<"\n\n********************************************************************************************************************************"<<endl<<endl;
        cout<<"********************************************************************************************************************************"<<endl<<endl;
        cout<<"\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE";
        _getch();
        

    }

