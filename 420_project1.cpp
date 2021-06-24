#include<bits/stdc++.h>
using namespace std;
int k;
double xmin,ymin,xmax,ymax,arr[100],m;
ifstream input("in-6.txt",ios::in);

void clip_left(double x1,double y1,double x2,double y2)
{
    if(x2-x1)
    {
        m=(y2-y1)/(x2-x1);
    }
    else
    {
        m=100000;
    }
    if(x1 >= xmin && x2 >= xmin)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(x1 < xmin && x2 >= xmin)
    {
        arr[k]=xmin;
        arr[k+1]=y1+m*(xmin-x1);
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(x1 >= xmin  && x2 < xmin)
    {
        arr[k]=xmin;
        arr[k+1]=y1+m*(xmin-x1);
        k+=2;
    }
    if(x1<xmin && x2< xmin)
    {
        arr[k]=xmin;
        arr[k+1]=ymin;
        arr[k+2]=xmin;
        arr[k+3]=ymax;
        k+=4;
    }
}
void clip_right(double x1,double y1,double x2,double y2)
{
    if(x2-x1)
    {
        m=(y2-y1)/(x2-x1);
    }
    else
    {
        m=100000;
    }
    if(x1 <= xmax && x2 <= xmax)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(x1 > xmax && x2 <= xmax)
    {
        arr[k]=xmax;
        arr[k+1]=y1+m*(xmax-x1);
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(x1 <= xmax  && x2 > xmax)
    {
        arr[k]=xmax;
        arr[k+1]=y1+m*(xmax-x1);
        k+=2;
    }
}

void clip_top(double x1,double y1,double x2,double y2)
{
    if(y2-y1)
    {
        m=(x2-x1)/(y2-y1);
    }
    else
    {
        m=100000;
    }
    if(y1 <= ymax && y2 <= ymax)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(y1 > ymax && y2 <= ymax)
    {
        arr[k]=x1+m*(ymax-y1);
        arr[k+1]=ymax;
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(y1 <= ymax  && y2 > ymax)
    {
        arr[k]=x1+m*(ymax-y1);
        arr[k+1]=ymax;
        k+=2;
    }
}

void clip_bottom(double x1,double y1,double x2,double y2)
{
    if(y2-y1)
    {
        m=(x2-x1)/(y2-y1);
    }
    else
    {
        m=100000;
    }
    if(y1 >= ymin && y2 >= ymin)
    {
        arr[k]=x2;
        arr[k+1]=y2;
        k+=2;
    }
    if(y1 < ymin && y2 >= ymin)
    {
        arr[k]=x1+m*(ymin-y1);
        arr[k+1]=ymin;
        arr[k+2]=x2;
        arr[k+3]=y2;
        k+=4;
    }
    if(y1 >= ymin  && y2 < ymin)
    {
        arr[k]=x1+m*(ymin-y1);
        arr[k+1]=ymin;
        k+=2;
    }
}


int main()
{
    double xi,yi,xf,yf,poly[100];
    int n,i;
    if(!input)  //If file is not open
    {
        cout<<endl<< "File could not be opened"<<endl;
        exit(EXIT_FAILURE);    //indication of program failure is returned to the operating system.
    }
    string seq[4];
    cout<< "Xmin = ";
    input>>xmin;
    cout<<xmin<<endl;;
    cout<< "Xmax = ";
    input>>xmax;
    cout<<xmax<<endl;;
    cout<< "Ymin = ";
    input>>ymin;
    cout<<ymin<<endl;
    cout<< "Ymax = ";
    input>>ymax;
    cout<<ymax<<endl;;
    cout<< "Clipping edge sequence: ";
    for(i=0; i<4; i++)
    {
        input>>seq[i];
    }
    for(i=0;i<4;i++)
    {
        cout<<seq[i]<< " ";
    }
    cout<< "\nNo. of vertices in the polygon = ";
    input>>n;
    cout<<n<<endl;
    cout<<endl;
    k=0;
    for(i=0; i<n*2; i++)
    {
        input>>poly[i];
    }
    int d=1,g=0;
    while(g<n*2)
    {
        cout<< "P"<<d<< " : ("<<poly[g]<< ", "<<poly[g+1]<< ")\n";
        g+=2;
        d++;
    }
    poly[i]=poly[0];
    poly[i+1]=poly[1];
    //k=0;
    cout<< "\n";
    for(int z=0; z<4; z++)
    {
        k=0;
        if(seq[z]=="L")
        {
            cout<< "Clipping with respect to LEFT edge...\n";
            for(i=0; i < 2*n; i+=2)
            {
                clip_left(poly[i],poly[i+1],poly[i+2],poly[i+3]);
            }
            n=k/2;
            cout<< "New Sequence : ";
            for(i=0; i < k; i++)
            {
                poly[i]=arr[i];
            }
            poly[i]=poly[0];
            poly[i+1]=poly[1];
            for(i=0;i<k;i++) //SPECIAL CASE
            {
                for(int j=i+2;j<k;j++)
                {
                    if(i%2==0&&j%2==0&&poly[i]==poly[j]&&poly[i+1]==poly[j+1])
                    {
                        for(int c=j;c<k;c+=2)
                        {
                            poly[c]=poly[c+2];
                            poly[c+1]=poly[c+3];
                        }
                        k-=2;
                    }
                }
            }
            i=0;
            while(i<k)
            {
                cout<< "("<<poly[i]<< ", "<<poly[i+1]<< ") ";
                i+=2;
            }
            cout<< "\n\n";
        }
        k=0;
        if(seq[z]=="R")
        {
            cout<< "Clipping with respect to RIGHT edge...\n";
            for(i=0; i < 2*n; i+=2)
            {
                clip_right(poly[i],poly[i+1],poly[i+2],poly[i+3]);
            }
            n=k/2;
            cout<< "New Sequence : ";
            for(i=0; i < k; i++)
            {
                poly[i]=arr[i];
            }
            poly[i]=poly[0];
            poly[i+1]=poly[1];
            for(i=0;i<k;i++)
            {
                for(int j=i+2;j<k;j++)
                {
                    if(i%2==0&&j%2==0&&poly[i]==poly[j]&&poly[i+1]==poly[j+1])
                    {
                        for(int c=j;c<k;c+=2)
                        {
                            poly[c]=poly[c+2];
                            poly[c+1]=poly[c+3];
                        }
                        k-=2;
                    }
                }
            }
            i=0;
            while(i<k)
            {
                cout<< "("<<poly[i]<< ", "<<poly[i+1]<< ") ";
                i+=2;
            }
            cout<< "\n\n";
        }
        k=0;
        if(seq[z]=="T")
        {
            cout<< "Clipping with respect to TOP edge...\n";
            for(i=0; i < 2*n; i+=2)
            {
                clip_top(poly[i],poly[i+1],poly[i+2],poly[i+3]);
            }
            n=k/2;
            cout<< "New Sequence : ";
            for(i=0; i < k; i++)
            {
                poly[i]=arr[i];
            }
            poly[i]=poly[0];
            poly[i+1]=poly[1];
            for(i=0;i<k;i++)
            {
                for(int j=i+2;j<k;j++)
                {
                    if(i%2==0&&j%2==0&&poly[i]==poly[j]&&poly[i+1]==poly[j+1])
                    {
                        for(int c=j;c<k;c+=2)
                        {
                            poly[c]=poly[c+2];
                            poly[c+1]=poly[c+3];
                        }
                        k-=2;
                    }
                }
            }
            i=0;
            while(i<k)
            {
                cout<< "("<<poly[i]<< ", "<<poly[i+1]<< ") ";
                i+=2;
            }
            cout<< "\n\n";
        }
        k=0;
        if(seq[z]=="B")
        {
            cout<< "Clipping with respect to BOTTOM edge...\n";
            for(i=0; i < 2*n; i+=2)
            {
                clip_bottom(poly[i],poly[i+1],poly[i+2],poly[i+3]);
            }
            n=k/2;
            cout<< "New Sequence : ";
            for(i=0; i < k; i++)
            {
                poly[i]=arr[i];
            }
            poly[i]=poly[0];
            poly[i+1]=poly[1];
            for(i=0;i<k;i++)
            {
                for(int j=i+2;j<k;j++)
                {
                    if(i%2==0&&j%2==0&&poly[i]==poly[j]&&poly[i+1]==poly[j+1])
                    {
                        for(int c=j;c<k;c+=2)
                        {
                            poly[c]=poly[c+2];
                            poly[c+1]=poly[c+3];
                        }
                        k-=2;
                    }
                }
            }
            i=0;
            while(i<k)
            {
                cout<< "("<<poly[i]<< ", "<<poly[i+1]<< ") ";
                i+=2;
            }
            cout<< "\n\n";
        }
    }
    cout<< "\n\n\n";
    //cout<< "PRESS ANY KEY TO EXIT...";
    system("pause");
    system("cls");
}
