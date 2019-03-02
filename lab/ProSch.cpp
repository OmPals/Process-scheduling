//PROCESS SCHEDULING USING 
//1. FCFS - First Come First Serve algorithm (non Pre-emptive),
//2. SRTN - Shortest Remaining Time Next algorithm (Pre-emptive),
//3. PRIORITY (non Pre-emptive)
//4. HRRN - Highest Response Ratio Next algorithm (non Pre-emptive).
//WITH STRUCTURE 
//
//Author: Om Palsanawala
//Institute: DA-IICT
//Assigned by Prof. Jayprakash

#include<bits/stdc++.h>
#include<fstream>

using namespace std;

struct process{
	int pid, at, st, pri, iw, imw, ft, tat, rst, flag, flag2, pri1;
	float rr;
};

//1.FCFS Algorithm
int fcfs(process arr[], int n)
{
	FILE *fcfs;
	fcfs = fopen("fcfs.txt","w+");
    int t = 0, wt = 0, iwt = 0, mwt = 0, mtat = 0;
    fprintf(fcfs, "pid\tinit w\tint w\tft\ttat\n");
    for(int i = 0; i < n; i++)
    {
        wt = t - arr[i].at;
        mwt += wt;
        t += arr[i].st;
        mtat += t - arr[i].at;
        
        arr[i].iw = wt;
        arr[i].imw = iwt;
        arr[i].ft = t;
        arr[i].tat = t - arr[i].at;
		
		fprintf(fcfs, "%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].iw, arr[i].imw, arr[i].ft, arr[i].tat);
        
//        cout << "Process " << i+1 << " initial wait " << wt << " intermidiate wait " << iwt << " FT " << t << " TAT " << t - arr[i].at << endl;
    }
//    cout << " Mean wt: " << (float)mwt/n << "\nMean TAT: " << (float)mtat/n << endl;
	fprintf(fcfs, "mwt = %f\t mtat = %f\n", (float)mwt/n, (float)mtat/n);
	fclose(fcfs);
    return 0;
}

//2.SRTN Algorithm
int srtn(process arr[], int n)
{
	FILE *srtn;
	srtn = fopen("srtn.txt", "w+");
		
	int i1 = 0, ft = 0, sum = 0, t = 0, rs[n] = {0}, j = 0, min = 100, k1 = 0, mwt = 0, mtat = 0;
	
	for(int i = 0; i < n; i++)
		sum += arr[i].st;

//--->Gantt Chart
	std::vector<std::vector<int> > pt(n, std::vector<int>(sum));

	for(int k4 = 0; k4 < n; k4++)
	{
		arr[k4].rst = arr[k4].st;
		arr[k4].flag = 0;
		arr[k4].flag2 = 0;
		arr[k4].iw = 0;
		arr[k4].imw = 0;
	}
	
	while(t < sum)
	{
		min = 100;
//		---> Fetch processes before or at the time t
		for(j = 0; j < n; j++)
		{
			if(arr[j].at <= t)
			{
				rs[j] = arr[j].rst;
			}
			else
			{
				break;	
			}
		}
//		for(int p1 = 0; p1 < n; p1++)
//		{
//			cout << rs[p1] << " ";
//		}
//		cout << endl;
//		MIN of RST
		for(int k = 0; k < n; k++)
		{
			if(rs[k] > 0 && rs[k] < min)
			{
				k1 = k;
				min = rs[k];
			}
		}
//		cout << k1 << endl;
		
//		k1 gets cpu
		pt[k1][t] = 1;
//		cout << "here" << pt[k1][t] << endl;;
		arr[k1].rst--;
		t++;
	}
//	for(int k2 = 0; k2 > n; k2++)
//	{
//		for(int k3 = 0; k3 < sum; k3++)
//		{
//			fprintf(srtn, "%d\t", pt[k2][k3]);
//		}
//		fprintf(srtn, "\n");
//	}

//	for(int k2 = 0; k2 < n; k2++)
//	{
//		for(int k3 = 0; k3 < sum; k3++)
//		{
//			cout << pt[k2][k3] << " ";
//		}
//		cout << endl;
//	}
	for(int i = 0; i < sum; i++)
	{
		for(i1 = 0; i1 < n; i1++)
		{
			if(arr[i1].flag == 0 && pt[i1][i] == 0)
			{
				arr[i1].iw++;
			}
			else if(arr[i1].flag == 1 && pt[i1][i] == 0 && arr[i1].flag2 < arr[i1].st)
			{
				arr[i1].imw++;
			}
			else if(pt[i1][i] == 1)
			{
				arr[i1].flag = 1;
				arr[i1].flag2++;
				arr[i1].ft = i+1;
			}
		}
	}
	fprintf(srtn, "pid\tinit w\tint w\tft\ttat\n");
	for(int i = 0; i < n; i++)	
	{
		arr[i].tat = arr[i].ft - arr[i].at;
		mwt += arr[i].iw + arr[i].imw;
		mtat += arr[i].tat;
		fprintf(srtn, "%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].iw, arr[i].imw, arr[i].ft, arr[i].tat);
	}		
	fprintf(srtn, "mwt = %f\t mtat = %f\n", (float)mwt/n, (float)mtat/n);
	return 0;
}

//3.PRIORITY
int pri(process arr[], int n)
{
	FILE *prio;
	prio = fopen("prio.txt", "w+");
		
	int i1 = 0, ft = 0, sum = 0, t = 0, rs[n] = {-1}, j = 0, min = 100, k1 = 0, mwt = 0, mtat = 0;
	
	for(int i = 0; i < n; i++)
		sum += arr[i].st;

//--->Gantt Chart	
	std::vector<std::vector<int> > pt1(n, std::vector<int>(sum));

	for(int k4 = 0; k4 < n; k4++)
	{
//		arr[k4].rst = arr[k4].st;
		arr[k4].flag = 0;
		arr[k4].flag2 = 0;
		arr[k4].iw = 0;
		arr[k4].imw = 0;
	}
	
	while(t < sum)
	{
		min = 100;
//		---> Fetch processes before or at the time t
		for(j = 0; j < n; j++)
		{
			if(arr[j].at <= t && arr[j].pri != -1 && arr[j].pri < min)
			{
				rs[j] = arr[j].pri;
//				arr[j].flag2 = 1;	
				min = arr[j].pri;
				k1 = j;
			}
		}
//		--->PRIORITY
//		--->k1 gets CPU
//		arr[k1].flag = 1;
		arr[k1].pri = -1;
		for(int t1 = 0; t1 < arr[k1].st; t1++)
		{
			pt1[k1][t1+t] = 1;	
		}
		
		t += arr[k1].st;
	}
//	for(int k2 = 0; k2 < n; k2++)
//	{
//		for(int k3 = 0; k3 < sum; k3++)
//		{
//			cout << pt1[k2][k3] << " ";
//		}
//		cout << endl;
//	}	
	for(int i = 0; i < sum; i++)
	{
		for(i1 = 0; i1 < n; i1++)
		{
			if(arr[i1].flag == 0 && pt1[i1][i] == 0)
			{
				arr[i1].iw++;
			}
			else if(arr[i1].flag == 1 && pt1[i1][i] == 0 && arr[i1].flag2 < arr[i1].st)
			{
				arr[i1].imw++;
			}
			else if(pt1[i1][i] == 1)
			{
				arr[i1].flag = 1;
				arr[i1].flag2++;
				arr[i1].ft = i+1;
			}
		}
	}
	fprintf(prio, "pid\tinit w\tint w\tft\ttat\n");
	for(int i = 0; i < n; i++)	
	{
		arr[i].tat = arr[i].ft - arr[i].at;
		mwt += arr[i].iw + arr[i].imw;
		mtat += arr[i].tat;
		fprintf(prio, "%d\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].iw, arr[i].imw, arr[i].ft, arr[i].tat);
	}		
	fprintf(prio, "mwt = %f\t mtat = %f\n", (float)mwt/n, (float)mtat/n);
	return 0;
}
//4.HRRN
int hrrn(process ar[], int n)
{
	FILE *hrr;
	hrr = fopen("hrrn.txt", "w+");
		
	int i1 = 0, ft = 0, sum = 0, t = 0, rs[n] = {-1}, j = 0, k1 = 0, mwt = 0, mtat = 0;
	float min = 0;
	
	for(int i = 0; i < n; i++)
		sum += ar[i].st;
	
//	--->Gantt Chart
	std::vector<std::vector<int> > pt2(n, std::vector<int>(sum));

	for(int k4 = 0; k4 < n; k4++)
	{
		ar[k4].rr = 0;
		ar[k4].flag = 0;
		ar[k4].flag2 = 0;
		ar[k4].iw = 0;
		ar[k4].imw = 0;
	}
	
	while(t < sum)
	{
		min = 0;
//		---> Fetch processes before or at the time t
		for(j = 0; j < n; j++)
		{
			if(ar[j].at <= t && ar[j].pri1 > -1)
			{
				ar[j].rr = (float)(t - ar[j].at + ar[j].st)/ar[j].st;
//				arr[j].flag2 = 1;	
//				cout << "HERE" << arr[j].rr << endl;
				if(ar[j].rr > min)
				{
					min = ar[j].rr;
					k1 = j;
				}
			}
		}
//		--->PRIORITY
//		--->k1 gets CPU
//		arr[k1].flag = 1;
		ar[k1].pri1 = -1;
		for(int t1 = 0; t1 < ar[k1].st; t1++)
		{
			pt2[k1][t1+t] = 1;	
		}
		
		t += ar[k1].st;
	}
//	for(int k2 = 0; k2 < n; k2++)
//	{
//		for(int k3 = 0; k3 < sum; k3++)
//		{
//			cout << pt2[k2][k3] << " ";
//		}
//		cout << endl;
//	}	
	for(int i = 0; i < sum; i++)
	{
		for(i1 = 0; i1 < n; i1++)
		{
			if(ar[i1].flag == 0 && pt2[i1][i] == 0)
			{
				ar[i1].iw++;
			}
			else if(ar[i1].flag == 1 && pt2[i1][i] == 0 && ar[i1].flag2 < ar[i1].st)
			{
				ar[i1].imw++;
			}
			else if(pt2[i1][i] == 1)
			{
				ar[i1].flag = 1;
				ar[i1].flag2++;
				ar[i1].ft = i+1;
			}
		}
	}
	fprintf(hrr, "pid\tinit w\tint w\tft\ttat\n");
	for(int i = 0; i < n; i++)	
	{
		ar[i].tat = ar[i].ft - ar[i].at;
		mwt += ar[i].iw + ar[i].imw;
		mtat += ar[i].tat;
		fprintf(hrr, "%d\t%d\t%d\t%d\t%d\n", ar[i].pid, ar[i].iw, ar[i].imw, ar[i].ft, ar[i].tat);
	}		
	fprintf(hrr, "mwt = %f\t mtat = %f\n", (float)mwt/n, (float)mtat/n);
	return 0;
}


//*MAIN FUNCTION
int main()
{
// 1. Making processes from input.txt
	process p[50];
	int i = 0, num = 0, j = 0;
	std::ifstream file("input.txt");
	std::string str;
	std::getline(file, str,' ');
	while(std::getline(file, str,' '))
	{
		p[i].pid = i + 1;
		num = atoi( str.c_str() );
		p[i].at = num;	
		std::getline(file, str,' ');
		num = atoi( str.c_str() );
		p[i].st = num;
		std::getline(file, str,' ');
		num = atoi( str.c_str() );
		p[i].pri = num;
		p[i].pri1 = num;
		i++;
	}
	
// 2. ALGORITHMS: 
	
//	 1.FCFS
	fcfs(p, i);

//	2.SRTN
	srtn(p,i);

//	3.PRIORITY
	pri(p,i);

//	4.HRRN
	hrrn(p,i);

	cout << "Plz Check the output files fcfs.txt, srtn.txt, prio.txt and hrrn.txt in your current directory.\n Output shows initial waiting time, intermidiate waiting time, finish time and turn around time for each process in tabular form.\nmean waiting time and mean turn around time are calculated in next line.\nHave a nice day..." << endl;	
	return 0;
}
