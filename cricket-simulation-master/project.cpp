#include<iostream>
#include<fstream>
#include<string.h>
#include<math.h>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;

class team;
int arr[4][10]={{-1,-1,0,0,1,2,4,4,6,6},{-1,-1,1,2,2,4,4,6,6,6},{-1,-1,-1,0,0,1,2,2,4,4},{	-1,-1,0,0,1,1,1,2,2,2}},tn;

class bowl
{
	private:	
		int bwl_pts;
		char bwl_typ[30];
		
		int balls;
		int runs;
		float eco;
		int wkts;
		float spd;
		friend class team;
	public:
		bowl()
		{
			bwl_pts=0;
			runs=0;
			strcpy(bwl_typ,"");
			eco=0;
			balls=0;
			wkts=0;
			spd=0;
		}

		void get_bwl();
		void put_bwl();

		void bwl_cs(int ball,int speed)
		{
			if(ball==-1)
				wkts++;
			else
				runs+=ball;
			balls++;
			if(wkts!=0)
				eco=(balls/wkts);
			spd=speed;
		}
		int ret_bwlpts()
		{
			return bwl_pts;
		}
};

void bowl::get_bwl()
{
	cout<<"enter bwl_pts: "<<endl;
	cin>>bwl_pts;
	cout<<"enter bwl_typ: "<<endl;
	cin>>bwl_typ;
	cout<<"enter economy: "<<endl;
	cin>>eco;
	cout<<"enter wickets: "<<endl;
	cin>>wkts;
	cout<<"enter bowling speed: "<<endl;
	cin>>spd;
}

void bowl::put_bwl()
{
	cout<<"bowling points is: "<<bwl_pts<<endl;
	cout<<"bowling type is: "<<bwl_typ<<endl;
	cout<<"no of balls bowled: "<<balls<<endl;
	cout<<"runs given: "<<runs<<endl;
	cout<<"bowling economy is: "<<eco<<endl;
	cout<<"wickets taken: "<<wkts<<endl;
	cout<<"bowling speed: "<<spd<<endl<<endl;
}

class bat {
    //members:
	private:
		int bat_points;
		char bat_type[30];     
		int cent;     
		int half_cent;     
		
		int high_score;     
		float average;//str rate     
		int score;     
		int num_ball;    
		friend class team;
	//functions:     
	public:         
		bat()      //default constructor       
		{             
			bat_points=0;             
			high_score=0;             
			average=0.0;             
			cent=0;             
			half_cent=0;             
			score=0;             
			num_ball=0;             
			strcpy(bat_type,"");         
		}         

		void get_bat();
		void put_bat();

		void bat_cs(int scr)         
		{             
			num_ball++;             
			if(!(scr==-1))             
				score+=scr;
			high_score=score;
			average=score/num_ball;          
		}

		int ret_batpts()
		{
			return bat_points;
		}
}; 

void bat::get_bat()
{         
	cout<<"Enter batsman's points: "<<endl;         
	cin>>bat_points;         
	cout<<"Enter batting type: "<<endl;         
	cin>>bat_type;         
	cout<<"Enter batsman's high score: "<<endl;         
	cin>>high_score;         
	cout<<"Enter number of centuries and half-centuries: "<<endl;         
	cin>>cent>>half_cent;  
} 

void bat::put_bat()
{     
	cout<<"Number of Balls: "<<num_ball<<endl;     
	cout<<"Batsman's points: "<<bat_points<<endl;     
	cout<<"Batting type: "<<bat_type<<endl;     
	cout<<"High score: "<<high_score<<endl;     
	cout<<"Centuries: "<<cent<<endl;     
	cout<<"Half Centuries: "<<half_cent<<endl<<endl; 
}

class player:public bat,public bowl
{
	private:
		char nm[30];
		friend class team;
	public:
		player()
		{
			strcpy(nm,"");
		}
		void cpy_nm(char* str)
		{
			strcpy(nm,str);
		}
		void get_player();
		void put_player(int);
};
void player::get_player()
{
	cout<<"enter player name:"<<endl;
	cin>>nm;
	cout<<"enter batting data:"<<endl;
    get_bat();
	cout<<"enter bowling data:"<<endl;
	get_bwl();
}
void player::put_player(int x=3)
{
	cout<<"player name: "<<nm<<endl<<endl;
	
	if(x==3)
	{
		cout<<"batting data:"<<endl<<endl;
		put_bat();
		cout<<"bowling data:"<<endl<<endl;
		put_bwl();
	}
	
	if(x==0)
	{
		cout<<"batting data:"<<endl<<endl;
		put_bat();
	}
	else if(x==1)
	{
		cout<<"bowling data:"<<endl<<endl;
		put_bwl();
	}
}

class team
{
	private:
		static int tno;
		int teamno;
		char team_nm[30];
		int r;
		friend class player;
	public:         
		player p[11];
	
		team()//default constructor         
		{     
			r=0;
			strcpy(team_nm,"");
			tno++;
			teamno=tno;
		}
		char* retnm()
		{
			return team_nm;
		}
		void inc_run(int x)
		{
			r+=x;
		}
		int ret_run()
		{
			return r;
		}
		void read_playerinfo();
		friend istream& operator >> (istream& in, team &t);
		friend ostream& operator << (ostream& out, team &t);
};
int team::tno = 0;
ostream& operator << (ostream& out, team &t)
{             
	out<<"The team's name: "<<t.team_nm<<endl<<endl;
	for(int i=0;i<11;i++)
		t.p[i].put_player(tn);
	return out;
}
istream& operator >> (istream& in, team &t)
{             
		cout<<"Enter the team "<<t.teamno<<"'s name: "<<endl;
		in>>t.team_nm;
		t.read_playerinfo();
		return in;
}
void team::read_playerinfo()
{
	int i;
	player p1;
	fstream file("playerinfo.txt",ios::in);
	if(!file)
	{
		cout<<"Sorry, Match cancelled due to rain !!"<<endl;
		cout<<"(Check all files!!)"<<endl;
		char c = getchar();
		exit(0);
	}
	if(teamno==1)
		for(i=0;i<11;i++)
		{
			file>>p[i].nm;
			file>>p[i].bat_points;
			file>>p[i].bat_type;
			file>>p[i].cent;
			file>>p[i].half_cent;
			file>>p[i].bwl_pts;
			file>>p[i].bwl_typ;
		}
	else if(teamno==2)
	{
		for(i=0;i<11;i++)
		{
			file>>p1.nm;
			file>>p1.bat_points;
			file>>p1.bat_type;
			file>>p1.cent;
			file>>p1.half_cent;
			file>>p1.bwl_pts;
			file>>p1.bwl_typ;
		}
		for(i=0;i<11;i++)
		{
			file>>p[i].nm;
			file>>p[i].bat_points;
			file>>p[i].bat_type;
			file>>p[i].cent;
			file>>p[i].half_cent;
			file>>p[i].bwl_pts;
			file>>p[i].bwl_typ;
		}
	}
}
int randomize(int a=10)
{
		return(rand()%a);
}

void save_file(team &t1,team &t2)
{
	fstream file("matchdata.dat",ios::out);
	if(!file)
	{
		cout<<"Sorry, Match cancelled due to rain !!"<<endl;
		cout<<"(Check all files!!)"<<endl;
		char c = getchar();
		exit(0);
	}
	file.write((char*)&t1,sizeof(team));
	file.write((char*)&t2,sizeof(team));
	file.close();
}

void read_file(team &t1,team &t2)
{
	fstream file("matchdata.dat",ios::in);
	if(!file)
	{
		cout<<"Sorry, Match cancelled due to rain !!"<<endl;
		cout<<"(Check all files!!)"<<endl;
		char c = getchar();
		exit(0);
	}
	file.read((char*)&t1,sizeof(team));
	file.read((char*)&t2,sizeof(team));
	file.close();
}

int cmp_player(player tm1, player tm2)
{
    int temp0=tm1.ret_batpts();
    int temp1=tm2.ret_bwlpts();
    if((temp0>7)&&(temp1>7))
        return 0;
    else if((temp0>7)&&(temp1<=7))
        return 1;
    else if((temp0<=7)&&(temp1>7))
        return 2;
    else if((temp0<=7)&&(temp1<=7))
        return 3;
    else
		return -1;
}

int run(int no)
{
	int runs[10],i;
	for(i=0;i<10;i++)
		runs[i]=arr[no][i];
	return runs[randomize()];
}
int spd_rand()
{
	return 100+randomize(100);
}

int cointoss(char* tmnm1, char* tmnm2)
{
	int ran;

	cout<<"the coin is being tossed"<<endl;

	ran=randomize(2);

	if(ran==0)
	{
		cout<<endl<<tmnm1<<" wins the \"TOSS\" and choose to bat"<<endl;
		return 0;
	}
	else
	{
		cout<<endl<<tmnm2<<" wins the \"TOSS\" and choose to bat"<<endl;
		return 1;
	}
}
int swap(int tn)
{
	if(tn==0)
		return 1;
	else
		return 0;
}
int main()
{
	int i,j,k,wkt[2]={0,0},bt=0,bw=10,r,n,ba=0,f;
	char c;
	team t[2];

	srand(time(NULL));
	
	cin>>t[0];
	cin>>t[1];
	
	tn=cointoss(t[0].retnm(),t[1].retnm());
	c=getchar();
	
	fstream plt;

	plt.open("plot.txt",ios::out);
	if(!plt)
	{
		cout<<"Sorry, Match cancelled due to rain !!"<<endl;
		cout<<"(Check all files!!)"<<endl;
		char c = getchar();
		exit(0);
	}
	cout<<"Choose !! \n1.See Entire Match !!\n2.See the final results !!\n";
	cout<<"(any other option - you will see the enire match)"<<endl;
	cin>>f;
	if(f!=1&&f!=2)
		f=1;
	c=getchar();
	for(k=0;k<2;k++)
	{
		ba=1;
		cout<<"\n\n"<<t[tn].retnm()<<" is Batting !!"<<endl;
		for(i=0;i<4;i++)
		{
			for(j=0;j<6;j++)
			{
				
				if(tn==0)
					n=cmp_player(t[0].p[bt],t[1].p[bt]);
				else
					n=cmp_player(t[1].p[bt],t[0].p[bt]);
				r=run(n);
				if(r!=-1)
					cout<<"runs: "<<r<<endl<<5-j<<" balls left in this over !!"<<endl;
				if(tn==0)
				{	
					t[0].p[bt].bat_cs(r);
					t[1].p[bw].bwl_cs(r,spd_rand());
				}
				else
				{
					t[1].p[bt].bat_cs(r);
					t[0].p[bw].bwl_cs(r,spd_rand());
				}
				if(r==-1)
				{
					cout<<"OUT !!!!!"<<endl;
					t[tn].p[bt].put_player(0);
					bt++;
					wkt[tn]++;
				}
				else
					t[tn].inc_run(r);
				if(j<5)
					cout<<"the team score is: "<<t[tn].ret_run()<<"/"<<wkt[tn]<<" in "<<i<<"."<<j+1<<" overs"<<endl;
				else
					cout<<"the team score is: "<<t[tn].ret_run()<<"/"<<wkt[tn]<<" in "<<i+1<<"."<<0<<" overs"<<endl;

				if(r!=-1)
					plt<<ba<<" "<<t[tn].ret_run()<<endl;
				else
					plt<<ba<<" "<<t[tn].ret_run()<<endl;
				
				ba++;
				
				if(bt==12)
				{
					cout<<"ALL OUT !!!!!"<<endl;
					if(f==1)
						c=getchar();
					cout<<t[tn]<<endl;
					break;
				}
				if(f==1)
					c=getchar();
			}
			cout<<"OVER UP !!"<<endl;
		
			if(tn==0)
				t[1].p[bw].put_player(1);
			else
				t[0].p[bw].put_player(1);
			bw--;
			if(i==5)
				bw=10;
			if(f==1)
				c=getchar();
		}
		cout<<"\n\n"<<t[tn].retnm()<<"'s innings is up !!"<<endl;
		tn=swap(tn);
		plt<<"\n\n";
	}
	cout<<"\n\n\n";
	int a,b;
	a=t[tn].ret_run();
	cout<<a<<"/"<<wkt[tn]<<" is "<<t[tn].retnm()<<"'s score !!"<<endl;
	tn=swap(tn);
	b=t[tn].ret_run();
	cout<<b<<"/"<<wkt[tn]<<" is "<<t[tn].retnm()<<"'s score !!"<<endl;
	
	if(a>b)
	{
		tn=swap(tn);
		cout<<"\n\n\n"<<t[tn].retnm()<<" WON THE MATCH !!!!!"<<endl;
		cout<<"Do you want to see the team stats?(y/n)"<<endl;
		cin>>c;
		if(c=='y'||c=='Y')
		{
			cout<<t[tn]<<endl;
			c=getchar();
		}
	}
	else if(b>a)
	{
		cout<<"\n\n\n"<<t[tn].retnm()<<" WON THE MATCH !!!!!"<<endl;
		cout<<"Do you want to see the winning team's stats?(y/n)"<<endl;
		cin>>c;
		if(c=='y'||c=='Y')
		{
			cout<<t[tn]<<endl;
			c=getchar();
		}
	}
	else
		cout<<"\n\n\n"<<"TIE !!!!!!"<<endl;
	
	save_file(t[0],t[1]);
	
	cout<<"do you want to see the entire match stats??"<<endl;
	cin>>c;
	if(c=='y'||c=='Y')
	{
		read_file(t[0],t[1]);
		cout<<t[tn]<<endl;
		tn=swap(tn);
		cout<<t[tn]<<endl;
	}

	plt.close();
	return 0;
}
