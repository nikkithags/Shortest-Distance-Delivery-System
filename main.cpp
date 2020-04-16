#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <limits.h>
#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
//DECLARING A STRUCTURE 'DRIVER' WITH FOUR DATA MEMBERS
struct driver
{
    int sno;
    char name[10];
    int node_number;
    char available;
};
//DECLARING A STRUCTURE 'NODE' WITH THREE DATA MEMBERS AND A POINTER OF TYPE NODE
struct node
{
	float priority;
	int previous;
	int number;
	struct node *next;
};

//FUNCTION TO INSERT A NODE INTO THE PRIORITY QUEUE
void insert(struct node **front,struct node **rear,int number,float priority=0,int previous=0)
{
    struct node *tmp;
    tmp=new node;
    tmp->priority=priority;
	tmp->previous=previous;
	tmp->number=number;
	if(*front==NULL)
    {
        tmp->next=NULL;
        *front=tmp;
        *rear=tmp;
    }
    else
    {
        (*rear)->next=tmp;
        tmp->next=NULL;
        (*rear)=tmp;
    }
}

//FUNCTION TO DISPLAY THE NODES
void display(struct node *front,string place[15])
{
    node *ptr;
    ptr = front;
    if (front == NULL)
        cout<<"Queue is empty\n";
    else
    {	cout<<"Queue is :\n";
        while(ptr != NULL)
        {
            cout<<place[ptr->number-1]<<"                 "<<ptr->priority<<"                 "<<ptr->previous<<"                 "<<ptr->number<<endl;
            ptr = ptr->next;
        }
    }
}

//FUNCTION TO ASSIGN 0 TO THE PRIORITY OF THE STARTING NODE
void assign_zero(struct node *front,int n)
{
    struct node *ptr;
    ptr=front;
    while(ptr!=NULL)
    {

        if(ptr->number==n)
        {
            ptr->priority=0;
        }
        ptr=ptr->next;
    }
}

//FUCNTION TO FIND THE LEAST DISTANCE OF ALL THE NODES FROM THE STARTING NODE
void least_distance(struct node **front,struct node *front_used,struct node *rear_used, float graph[15][15])
{
    int prev_traversed_node;
    struct node *p,*q,*pq;
    //PQ IS USED WHILE COMPARING AND CHANGING PRIORITY
    while(*front!=NULL)
    {
        p=*front;
        q=p->next;
        while(q!=NULL)
        {
            if(q->priority<p->priority)
            {
                p=q;
            }
            q=q->next;
        }
        //P POINTS AT THE NODE WITH THE SMALLEST PRIORITY
        prev_traversed_node=p->number;
        pq=*front;
        float p_pri,pq_pri;
        int p_num,pq_num;
        //P WHICH POINTS TO THE SMALLEST NODE IS COMPARED PRIORITY WISE WITH ALL THE OTHER NODES
        //PQ IS INITIALISED TO FRONT AND MOVED THROUGH ALL THE NODES TO BE COMPARED WITH P
        while(pq!=NULL)
        {
            p_pri=p->priority;
            p_num=p->number;
            pq_pri=pq->priority;
            pq_num=pq->number;
            //IF THERE IS A POSSIBILITY OF A SHORTER DISTANCE, THE PRIORITY OF THAT NODE ALONG WITH THE PREVIOSLY TRAVERSED NODE IS CHANGED
            if( (p_pri) + graph[(p_num)-1][(pq_num)-1] < pq_pri )
            {
                pq->previous= prev_traversed_node;
                pq->priority = (p_pri) + graph[(p_num)-1][(pq_num)-1];
            }

            pq=pq->next;
        }
        //DELINKING THE SHORTEST NODE
        if(p==*front)
        {
            *front=(*front)->next;
        }
        else
        {
            //Q IS REUSED AS PPREV HERE
            q=*front;
            while(q->next!=p)
            {
                q=q->next;
            }
            q->next=p->next;
        }
        p_num=p->number;
        p_pri=p->priority;
        int p_prev=p->previous;
        //INSERTING THE INFORMATION FROM THE SMALLEST NODE TO THE USED PRIORITY QUEUE
        insert(&front_used,&rear_used,p_num,p_pri,p_prev);
        delete p;
    }
}

//FUCNTION TO FOLLOW THE PREVIOUSLY VISITED NODE WITH THE LEAST PRIORITY FROM THE END PLACE TO THE START PLACE
void backtrack(struct node *front_used,struct node *rear_used, int num_end, string place[15],vector <int> &track,int &flag)
{
    vector <int> track_current;
    int track_extra=num_end;
    track_current.push_back(num_end);
    struct node *t;
    while(track_extra!=0)
    {
        t=front_used;
        while(t!=NULL && t->number!=track_extra)
        {
            t=t->next;
        }
        track_extra=t->previous;
        track_current.push_back(track_extra);
    }
    //TRACK_CURRENT NOW HAS THE PATH FROM THE END PLACE TO THE START PLACE
    if(flag!=0)
    {
        track_current.pop_back();
    }
    flag++;
    //FLAG TO DELETE INSERTING A PLACE TWICE
    track_current.pop_back();
    reverse(track_current.begin(),track_current.end());
    for(int i=0;i<track_current.size();i++)
    {
        track.push_back(track_current[i]);
    }
    //WE PUSH THE NODES FROM TRACK_CURRENT TO TRACK
}

//FUNCTION TO CALCULATE THE TOTAL DISTANCE TO TRAVERSE FROM THE START PLACE TO THE END PLACE
float distance(struct node *front_used, int num_end)
{
    float distance_end;
    struct node *p;
    p=front_used;
    while(p!=NULL)
    {
        if(p->number==num_end)
        {
            distance_end=p->priority;
        }
        p=p->next;
    }
    return distance_end;
}
//MAIN FUCNTION
int main()
{
    char ch;
    int number=1;
    do
    {

        int choice;
        system("cls");
        cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t1. New delivery\n\t\t\t\t\t\t\t\t\t\t\t\t2. Complete delivery\n\t\t\t\t\t\t\t\t\t\t\t\t3. Exit\n\t\t\t\t\t\t\t\t\t\t\t\tEnter your choice: ";
        cin>>choice;
        //SWITCH FOR EITHER ORDERING OR COMPLETION OF DELIVERY
        switch(choice)
        {
            case 1:
                {
                if(number<=0)
                {
                    system("cls");
                    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
                    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\tNo driver available";
                    cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t   Continue? ";
                    cin>>ch;
                    continue;
                }
                int order_places;
                float final_distance;
                vector <int> track_driver;
                vector <int> track_delivery;
                vector <int> order;
                string place[15]={"Anna Nagar","Nungambakkam","T Nagar","Porur","Mylapore","Ramapuram","Guindy","Adyar","Meenambakkam","Velachery","Besant Nagar","Chrompet","Palavakkam","Thoraipakkam","Sholinganallur"};
                driver ob;
                int driver_beginning[15];
                int driver_number[number];
                int driver_count;
                int dmax=9999;
                float graph[15][15]={
                                 {0,6.4,dmax,11.8,dmax,9.2,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax}
                                ,{6.4,0,3.7,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax}
                                ,{dmax,3.7,0,dmax,5.8,dmax,8.8,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax}
                                ,{11.8,dmax,dmax,0,dmax,3.2,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax}
                                ,{dmax,dmax,5.8,dmax,0,dmax,dmax,4.6,dmax,dmax,dmax,dmax,dmax,dmax,dmax}
                                ,{9.2,dmax,dmax,3.2,dmax,0,10,dmax,12.4,dmax,dmax,dmax,dmax,dmax,dmax}
                                ,{dmax,dmax,8.8,dmax,dmax,10,0,5.5,dmax,3.3,dmax,dmax,dmax,dmax,dmax}
                                ,{dmax,dmax,dmax,dmax,4.6,dmax,5.5,0,dmax,dmax,2.3,dmax,dmax,dmax,dmax}
                                ,{dmax,dmax,dmax,dmax,dmax,12.4,dmax,dmax,0,5,dmax,6.9,dmax,dmax,dmax}
                                ,{dmax,dmax,dmax,dmax,dmax,dmax,3.3,dmax,5,0,dmax,dmax,8.2,dmax,13.3}
                                ,{dmax,dmax,dmax,dmax,dmax,dmax,dmax,2.3,dmax,dmax,0,dmax,5.6,dmax,dmax}
                                ,{dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,6.9,dmax,dmax,0,dmax,14.7,dmax}
                                ,{dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,8.2,5.6,dmax,0,6,dmax}
                                ,{dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,14.7,6,0,5.2}
                                ,{dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,dmax,13.3,dmax,dmax,dmax,5.2,0}
                                };
                float driver_distance[number];
                int num_start,num_end;
                int count_n;
                int flag;
                float priority;
                int previous;
                struct node *front,*rear;
                struct node *front_used,*rear_used;
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
                //PRINTING THE LIST OF ALL THE PLACES AVAILABLE ON THE MAP
                cout<<"\n\n\n\n\n\n\n\n\n";
                cout<<"\t\t\t\t\t\t\t\t\t\t\t\t   PLACES "<<endl;
                for(int i=0;i<15;i++)
                {
                    cout<<"\t\t\t\t\t\t\t\t\t\t\t\t"<<i+1<<".\t"<<place[i]<<endl;
                }
                do
                {
                    //ACCEPTING THE ORDER OF PLACES TO BE VISITED
                    do
                    {
                        cout<<"\t\t\t\t\t\t\t\t\t  Enter the place number from the above list (Enter 0 to stop):";
                        cin>>order_places;
                    }while(order_places<0 || order_places>15);
                    order.push_back(order_places);
                }while(order_places!=0);
                order.pop_back();

                ifstream filed;
                filed.open("driverInformation.txt");
                driver_count=0;
                int i=0;
                //READING THE FILE AND STORING AVAILABLE DRIVER INFORMATION
                while(!filed.eof() && driver_count<number)
                {
                    filed >> ob.sno >> ob.name >> ob.node_number >> ob.available;
                    if(ob.available=='a')
                    {
                        driver_beginning[i]=ob.node_number;
                        driver_number[driver_count]=ob.sno;
                        driver_count++;
                    }
                    i++;
                }
                filed.close();

                //FOR FINDING THE DRIVER DISTANCES
                for(int i=0;i<number;i++)
                {
                    count_n=0;
                    priority=INT_MAX;
                    previous=0;
                    front=NULL;
                    rear=NULL;
                    front_used=NULL;
                    rear_used=NULL;
                    num_start=driver_beginning[driver_number[i]-1];
                    num_end=order[0];
                    for(int i=0;i<15;i++)
                    {
                        count_n++;
                        insert(&front,&rear,count_n,priority,previous);
                    }
                    insert(&front_used,&rear_used,1,priority,previous);
                    assign_zero(front,num_start);
                    least_distance(&front,front_used,rear_used,graph);
                    front_used=front_used->next;
                    driver_distance[i]=distance(front_used,num_end);
                }
                //FINDING THE SHORTEST DRIVER DISTANCE
                int num;
                int pos=0;
                float mini=driver_distance[0];
                for(i=0;i<number;i++)
                {
                    if(driver_distance[i]<mini)
                    {
                        mini=driver_distance[i];
                        pos=i;
                    }
                    num=driver_number[pos];
                }
                num_start=driver_beginning[num-1];

                filed.open("driverInformation.txt");
                char driver_name[10];
                int driver_num;
                driver_count=0;
                while(!filed.eof() && driver_count<15)
                {
                    filed >> ob.sno >> ob.name >> ob.node_number >> ob.available;
                    if(ob.sno==num)
                    {
                        strcpy(driver_name,ob.name);
                        driver_num=ob.sno;
                    }
                    driver_count++;
                }
                filed.close();
                //TO FIND THE DISTANCE BETWEEN SHORTEST DRIVER AND FIRST NODE
                final_distance=0;
                count_n=0;
                priority=INT_MAX;
                previous=0;
                front=NULL;
                rear=NULL;
                front_used=NULL;
                rear_used=NULL;
                flag=0;
                //INSERTING ALL THE NODES INTO THE UNUSED PRIORITY QUEUE
                for(int i=0;i<15;i++)
                {
                    count_n++;
                    insert(&front,&rear,count_n,priority,previous);
                }
                insert(&front_used,&rear_used,1,priority,previous);
                assign_zero(front,num_start);
                least_distance(&front,front_used,rear_used,graph);
                front_used=front_used->next;
                final_distance+=distance(front_used,num_end);
                backtrack(front_used,rear_used,num_end,place,track_driver,flag);
                //PRINTING THE FINAL OUTCOME OF SHORTEST DRIVER TO BEGINNING NODE
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tYour Swiggy driver, "<<driver_name<<" will arrive at the restaurant to pick up your order through ";
                for(int i=0;i<track_driver.size();i++)
                {
                    cout<<place[track_driver[i]-1]<<" -> ";
                }
                cout<<"\b\b\b\b   ";
                cout<<"\bwith a distance of "<<final_distance<<" kms."<<endl;
                //ACTUAL SHORTEST DISTANCE FROM START NODE TO END NODE
                final_distance=0;
                for(int i=0;i<order.size()-1;i++)
                {
                    count_n=0;
                    priority=INT_MAX;
                    previous=0;
                    front=NULL;
                    rear=NULL;
                    front_used=NULL;
                    rear_used=NULL;
                    flag=0;
                    num_start=order[i];
                    num_end=order[i+1];
                    //INSERTING ALL THE NODES INTO THE UNUSED PRIORITY QUEUE
                    for(int i=0;i<15;i++)
                    {
                        count_n++;
                        insert(&front,&rear,count_n,priority,previous);
                    }
                    insert(&front_used,&rear_used,1,priority,previous);
                    assign_zero(front,num_start);
                    least_distance(&front,front_used,rear_used,graph);
                    front_used=front_used->next;
                    final_distance+=distance(front_used,num_end);
                    backtrack(front_used,rear_used,num_end,place,track_delivery,flag);
                }
                //PRINTING THE FINAL OUTCOME
                cout<<"\n\t\t\t\tYour Swiggy driver, "<<driver_name<<" has picked up your order and will arrive at your location through ";
                for(int i=0;i<track_delivery.size();i++)
                {
                    cout<<place[track_delivery[i]-1]<<" -> ";
                }
                cout<<"\b\b\b\b   ";
                cout<<"\bwith a distance of "<<final_distance<<" kms."<<endl;
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t    ######################";
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t    # DRIVER NUMBER : "<<driver_num<<" #";
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t    ######################";
                driver_count=0;
                //REWRITING THE FILE WITH CHANGED NODE NUMBER AND AVAILABILITY
                filed.open("driverInformation.txt");
                ofstream fileptr;
                fileptr.open("copy.txt");
                while(!filed.eof() && driver_count<15)
                {
                    driver_count++;
                    filed >> ob.sno >> ob.name >> ob.node_number >> ob.available;
                    if(ob.sno==num)
                    {
                        ob.node_number=num_end;
                        ob.available='n';
                    }
                    fileptr << ob.sno <<" "<< ob.name <<" "<< ob.node_number <<" "<< ob.available<<" \n";
                }
                filed.close();
                fileptr.close();
                remove("driverInformation.txt");
                rename("copy.txt","driverInformation.txt");
                number--;
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t   Continue? ";
                cin>>ch;
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
                break;
                }
            case 2:
                {
                driver ob;
                int driver_n;
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tEnter driver number of completed delivery: ";
                cin>>driver_n;
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
                ifstream filed;
                filed.open("driverInformation.txt");
                ofstream fileptr;
                fileptr.open("copy.txt");
                int driver_count=0;
                //REWRITING THE NODE WITH AVAILABILITY
                while(!filed.eof() && driver_count<15)
                {
                    driver_count++;
                    filed >> ob.sno >> ob.name >> ob.node_number >> ob.available;
                    if(ob.sno==driver_n)
                        ob.available='a';
                    fileptr << ob.sno <<" "<< ob.name <<" "<< ob.node_number <<" "<< ob.available<<" \n";
                }
                filed.close();
                fileptr.close();
                remove("driverInformation.txt");
                rename("copy.txt","driverInformation.txt");
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\tDriver "<<driver_n<<" is now available for delivery"<<endl;
                number++;
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\t   Continue? ";
                cin>>ch;
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
                break;
                }
            case 3:
                exit(0);
            default:
                cout<<"Invalid input"<<endl;
                cout<<"Continue? "<<endl;
                cin>>ch;
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t\t\tSHORTEST DISTANCE";
        }
    }while(ch=='y' || ch=='Y');
    return 0;
}
