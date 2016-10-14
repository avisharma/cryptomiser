long int p,q,n,t,flag,e[100000],d[100000],temp[100000],j,m[100000],en[100000],i;
char msg[100000];
 /*
long might be better if you write portable code and you need integer of at least 32-bits.
long is guaranteed to be not less than 32-bits by C standard whereas int is not guaranteed (it may be 16-bits).
*/


// Here ,e is our public key which is used for encryption and d is our private key which is used for decryption.
// e and should always be coprime
//{Pub} = (e,t)
//{Priv} = (d,t)
//function declaration
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();
void rsa()
{
	printf("\nENTER FIRST PRIME NUMBER\n");
	scanf("%ld",&p); //3
	flag=prime(p);
	if(flag==0)
	{
		printf("\nWRONG INPUT\n");
		exit(1);
	}
	printf("\nENTER ANOTHER PRIME NUMBER\n"); //5
	scanf("%ld",&q);
	flag=prime(q); //check for primality
	if(flag==0||p==q)
	{
		printf("\nWRONG INPUT\n");
		exit(1);
	}
	printf("\nENTER MESSAGE\n");
	fflush(stdin);// discards input buffer
	scanf("%s",&msg);
	for(i=0;msg[i]!='\0';i++) // null or /0 needs to be researched
		m[i]=msg[i]; //copying msg[i] to m[i] char by char


		n=p*q; //3*5//15
		t=(p-1)*(q-1); //2*4//8 //this is fi function
		printf("Value of t is:%ld",t);
		printf("\n");
		ce();
		printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
	for(i=0;i<j-1;i++)
	printf("\n%ld\t%ld",e[i],d[i]);
	encrypt();
	decrypt();
	return 0;
}
//Function to check whether the number entered is prime or not
int prime(long int pr)
{
	long int i;
	j=sqrt(pr); // we can also use here pr/2 ,Based on compilation time we'll choose one.
	for(i=2;i<=j;i++)
	{
		if(pr%i==0)
			return 0;
	}
	return 1;
}

void ce() //This function is used to calculate e, we choose e in such a way that e(with p,q) does not have any factor in common i.e primality is relative
{
	long int k;
	k=0;
	for(i=2;i<t;i++)
        {
            if(t%i==0)
               {
				 continue;
			}
                flag=prime(i);
            if(flag==1&&i!=p&&i!=q)
            {
                e[k]=i;
			//	printf("value of e[k] is %d",e[k]);//7
				flag=cd(e[k]);
                if(flag>0)
		{
			d[k]=flag;
		//	printf("value  of dk : %d",d[k]);
			k++;
		}
		if(k==999)
			break;
		}
	}
}

long int cd(long int x) // This function  is used to calculate the value of d//7 enters first
{
	long int k=1;
	while(1)
	{
		k=k+t;
		//printf("first Sum value:%ld",k);//9
		if(k%x==0) //here x is e // in order to get 1 it has to be one of the factor of x ie e[i];
		{
		//printf("\ninside if Value of k is %d",k);

			return(k/x); }// we should divide to get 1 and corresponding value will give d
	}
}


//To encrypt a message m, we first convert it into a large integer. Then we calculate m^e \mod n.
void encrypt(
)
{
	long int pt,ct,key=e[0],k,len;
	i=0;
	len=strlen(msg); //hi//2
	while(i!=len)
	{
		pt=m[i]; //104 ASCII value of h is 104
		//	printf("Value of pt before is %d",pt);
		pt=pt-96; //8
	//	printf("Value of pt is %d",pt);
		k=1;
		for(j=0;j<key;j++) //key =7
		{
			k=k*pt; //8
		//	printf("k old:%d",k);//8
			k=k%n;
		//	printf("k new:%d",k);//8%15=8 // final=9
		}
		temp[i]=k;
		ct=k+96;
		//printf("value of ct is:%d",ct);
		en[i]=ct; //98 Ascii value of b is 98
		i++;
	}
	en[i]=-1; //-1??
	printf("\nTHE ENCRYPTED MESSAGE IS\n");
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
	printf("\nTHE DECRYPTED MESSAGE IS\n");
	for(i=0;m[i]!=-1;i++)
		printf("%c",m[i]);
}
