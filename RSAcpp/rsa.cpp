
#include <bits/stdc++.h>
using namespace std;

int binary[1000];
int euclidArray[3];

int p=0;
int q=0;

int e=0,d=0,n=0;


int convertToBinary(int x);
int modularExponentiation(int a, int b, int n);
void extendedEuclid(int a,int b);
int multiplicativeInverse(int a,int n);
bool primeTest(int a);
void makePrime();
void createKeys();
void printPublicKey();
void printPrivateKey();
int encryptWithPublicKey(int ch);
int decryptWithPrivateKey(int ch);
void methodOne();
void methodTwo();
void testMethod();

int main(){
	//freopen("input.txt","rb",stdin);
	//methodTwo();
	testMethod();
}
void testMethod(){
	int count=9;
	while(count<10){
		createKeys();
		printPublicKey();
		printPrivateKey();
		count++;
	}
}
/*
void methodOne(){
	createKeys();
	char msg[1000];
	for(int test=1;test<=test;test++){
		cout<<"Write message: ";
		cin>>msg;
		for(int i=0;i<strlen(msg);i++)
			msg[i]=encryptWithPrivateKey(msg[i]);
		cout<<msg<<endl;

		for(int i=0;i<strlen(msg);i++)
			msg[i]=decryptWithPublicKey(msg[i]);
		cout<<msg<<endl;
	}
}
*/
void methodTwo(){
	createKeys();
	int x;
	cin>>x; 

	int y=encryptWithPublicKey(x);
	int z=decryptWithPrivateKey(y);
	cout<<x<<" "<<z<<endl;
	if(x==z) cout<<"Test passed on methodTwo";
	else cout<<"Test failed on methodTwo";
	cout<<endl;
	methodTwo();
}
int convertToBinary(int x){		//method needed for modular exponentiation
	int len=0;
	int i=0;
	while(x>0){
		binary[i]=x%2;
		x=x/2;
		len++;
		i++;
	}
	return len;
}
int modularExponentiation(int a, int b, int n){		//method need for message transformation
	int c=0;
	int d=1;

	int digits=convertToBinary(b);
	for(int i=digits-1;i>=0;i--){
		c=c*2;
		d=(d*d)%n;
		if(binary[i]==1){
			c=c+1;
			d=(d*a)%n;
		}
	}
	return d;
}
void extendedEuclid(int a,int b){		//recursive extended euclid algorithm
	if(b==0){
		euclidArray[0]=a;
		euclidArray[1]=1;
		euclidArray[2]=0;

	}
	else{
		extendedEuclid(b,a%b);
		int d_=euclidArray[0];
		int x_=euclidArray[1];
		int y_=euclidArray[2];
		euclidArray[0]=d_;
		euclidArray[1]=y_;
		euclidArray[2]=x_-floor(a/b)*y_;
	}
}
int multiplicativeInverse(int a,int n){		//special case of modular linear equation solver whrere b==1
	extendedEuclid(a,n);
	int d=euclidArray[0];
	int x_=euclidArray[1];
	int y_=euclidArray[2];
	if(d==1){
		int x0=x_%n;
		return x0%n;
	}
	else return 0;
}
void makePrime(){
	cout<<"Generating prime..."<<endl;
	FILE* fp=fopen("primeList.txt","rb");		//opening file containing prime number list 
	srand(time(NULL));
	int rn=rand()%300;		//select the rangeEnd
	int x;
	for(int i=0;i<rn/2;i++){		//select the first half
		fscanf(fp,"%d",&x);
		p=x;
	}
	for(int i=rn/2;i<=rn;i++){		//select the second half
		fscanf(fp,"%d",&x);
		q=x;
	}
	fclose(fp);
	if(primeTest(p) && primeTest(q)) cout<<"Primes found"<<endl;
}
void createKeys(){
	cout<<"Creating keys..."<<endl;
	makePrime();
	n=p*q;		//multiplying two prime numbers to get n
	int phiN=(p-1)*(q-1);		//calculating phi(n)=(p-1)(q-1) because p and q are primes
	int primes[]={3,5,7,11,13,17,19,23,29,31,37,41,
		43,47,53,61,67,71,73,79,83,89,97};
	int random=rand();
	//cout<<"random= "<<random<<endl;
	int index=random%30;
	//cout<<"index= "<<index<<endl;
	e=primes[index];		//calculating e realtively prime to phi(n)
	d=multiplicativeInverse(e,phiN);	//getting multiplicative inverse of e(mod phi(n))
}
void printPublicKey(){
	cout<<"Public Key: ";
	printf("e=%d,n=%d\n",e,n);
}
void printPrivateKey(){
	cout<<"Private Key: ";
	printf("d=%d,n=%d\n",d,n);
}
int encryptWithPublicKey(int ch){
	return modularExponentiation(ch,e,n);
}
int decryptWithPrivateKey(int ch){
	return modularExponentiation(ch,d,n);
}
bool primeTest(int n){
	for(int i=2;i<n;i++){
		if(n%i==0) {
			cout<<i<<endl;
			return false;
		}
	}
	return true;
}