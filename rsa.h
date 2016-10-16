long int p,q,n,t,flag,e[1000],d[100],temp[100],j,m[100],en[100],i;
long long int    ta;
int count=0;
char msg[100000];
int prime(long int);
void ce(long long int);
long int cd(long int);
void encrypt();
void decrypt();
void rsa()
{
	//printf("\nENTER FIRST PRIME NUMBER\n");
	//scanf("%ld",&p); //3
	//flag=prime(p);
	//if(flag==0)
	//{
	//	printf("\nWRONG INPUT\n");
	//	exit(1);
	//}
	//printf("\nENTER ANOTHER PRIME NUMBER\n"); //5
	//scanf("%ld",&q);
	//flag=prime(q); //check for primality
	//if(flag==0||p==q)
	//{
	//	printf("\nWRONG INPUT\n");
	//	exit(1);
	//}
	printf("\nENTER MESSAGE\n");
	fflush(stdin);// discards input buffer
	scanf("%s",&msg);
	for(i=0;msg[i]!='\0';i++) // null or /0 needs to be researched
		m[i]=msg[i]; //copying msg[i] to m[i] char by char


		//n=p*q; //3*5//15
		//t=(p-1)*(q-1); //2*4//8 //this is fi function

	//	printf("Value of t is:%ld",t);
	int l=strlen(msg);
		printf("The length is =%d\n",l);
		printf("\n");
		//ce();

	//encrypt();
	//decrypt();

}

//Function to check whether the number entered is prime or not
int prime(long int ta)
{
	int i;
	j=sqrt(ta); // we can also use here pr/2 ,Based on compilation time we'll choose one.
	for(i=2;i<=j;i++)
	{
		if(ta%i==0)
			return 0;
	}
	return 1;
}

void ce(long long int t) //This function is used to calculate e, we choose e in such a way that e(with p,q) does not have any factor in common i.e primality is relative
{	//global	int e[100];
	//printf("Value of ta is = %lld\n",t);
	int k;
	k=0;
	for(i=2;i<t;i++)
        {
        	//printf("Hello1\n");
            if(t%i==0)
               {
				 continue;
			}
                flag=prime(i);
      //          printf("Inside ce value of p and q=%lld\t %lld",p,q);
            if(flag==1&& i!=p&&i!=q)
            {	//printf("%d\n",i);
                e[k]=i;
				count++;
	//			printf("value of e[k] is %d",e[k]);//7
				flag=cd(e[k]);
				//printf("Hello3\n");
                if(flag>0)
		{
			d[k]=flag;
		//	printf("value  of dk : %d",d[k]);
			k++;
		}
		if(k==99)
			break;
		}
	}
	   printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
	for(i=0;i<count;i++)
		printf("\n%ld\t%ld\n",e[i],d[i]);
}

long int cd(long int x) // This function  is used to calculate the value of d//7 enters first
{
	long int k=1;
	while(1)
	{
		k=k+ta;
	//	printf("first Sum value:%ld",k);//9
		if(k%x==0) //here x is e // in order to get 1 it has to be one of the factor of x ie e[i];
		{
	//	printf("\ninside if Value of k is %d",k);
			//printf("The value of (k/x)is= %li\n",(k/x));
			return(k/x); }// we should divide to get 1 and corresponding value will give d
	}
}


//To encrypt a message m, we first convert it into a large integer. Then we calculate m^e \mod n.
void encrypt()
{ //	printf("1\n");
	long int pt,ct,key=e[0],k,len,ja;


	i=0;
	//printf("The first value of keys is= % li\n",key);
	len=strlen(msg);
	//printf("The length of msg is = %d\n",len); //hi//2
	while(i!=len)
	{ //	printf("2\n");
		pt=m[i];
	//	printf("%c\n",m[i]); //104 ASCII value of h is 104
		//printf("3\n");	//	printf("Value of pt before is %d",pt);
		pt=pt-96;
	//	printf("%d\n",pt); //8
	//	printf("Value of pt is %d",pt);
		k=1;
	//	printf("The value of ta is =%lld\n",ta);
		//printf("4\n");
		for(ja=0;ja<key;ja++) //key =7
		{ //printf("5\n");


			k=k*pt; //8

		//printf("k old:%d\n",k);//8
			k=k%n;
		//	printf("The value of ta is =%lld\n",ta);
		//	printf("k new:%d\n",k);//8%15=8 // final=9
		}
		temp[i]=k;
		ct=k+96;
		//printf("The value of ct is=%d\n",ct);
		//printf("value of ct is:%d",ct);
		en[i]=ct; //98 Ascii value of b is 98
		i++;
	}
	en[i]=-1; //-1??
	printf("\nEncrypted message:\n");
	for(i=0;en[i]!=-1;i++)
		printf("%c",en[i]);
}

void decrypt()
{
	long int pt,ct,key=d[0],k;
	i=0;
	while(en[i]!=-1)
	{
		ct=temp[i];
		k=1;
		for(j=0;j<key;j++)
		{
			k=k*ct;
			k=k%n;
		}
		pt=k+96;
		m[i]=pt;
		i++;
	}
	m[i]=-1;
	printf("\nDecrypted message:\n");
	for(i=0;m[i]!=-1;i++)
	{	printf("%c",m[i]);}
	printf("\n\n");
}
