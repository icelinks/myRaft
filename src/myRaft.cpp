//
//Authors:icelinks(719597520@qq.com)
//
//Date:2017/11/22
//Last Change:2017/11/22
//
#define DEBUG
#define MULTITHREAD
#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#ifdef MULTITHREAD
    #include<pthread.h>
    pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
#endif
using namespace std;

//Timer for myRaft(multithread allowed)
class myTimer{
private:
    int count = 0;
    bool stopFlag = false;

public:
    void initTimer(){
        #ifdef MULTITHREAD
            pthread_mutex_lock(&myMutex);
        #endif

            count = 0;

        #ifdef MULTITHREAD
            pthread_mutex_unlock(&myMutex);
        #endif
    }

    void setTimer(int time){
        while(1){
            if(stopFlag==true)return;
            sleep(1);

        #ifdef MULTITHREAD
            pthread_mutex_lock(&myMutex);
        #endif

            count+=1;

        #ifdef MULTITHREAD
            pthread_mutex_unlock(&myMutex);
        #endif

            if(count==time)break;
        }
        callbackFunc();
    }

    virtual void callbackFunc(){}

    void stopTimer(){
        stopFlag = true;
    }
};

#ifdef DEBUG
    class Pt:public myTimer{
    public:
        int a = 0;

        virtual void callbackFunc(){
            cout<<"Timer!!!"<<endl;
            a = 1;
        }
    };

    Pt pt;

    void* threadFunc(void *arg){
        pt.setTimer(3);
    }

    int main(){
        pthread_t myThread;
        pthread_create(&myThread,NULL,threadFunc,NULL);
        while(1){
            pt.initTimer();
            sleep(2);
        }
        return 0;
    }
#endif