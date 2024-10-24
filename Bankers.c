#include <stdio.h>
#define inf 100
int main(){
int nump, numr,i,j;
printf("Enter number of Processes: ");
scanf("%d", &nump);
printf("Enter number of Resources: ");
scanf("%d", &numr);
int allocated[nump][numr], need[nump][numr], max[nump][numr], instances[numr], available[numr], sequence[nump];
printf("Enter number of instances of Resource ");
for (i=0;i<numr;i++){
printf("R %d : ",i+1);
scanf("%d", &instances[i]);
available[i]= instances[i];}
printf("Enter max matrix : ");
for (i=0;i<nump;i++){
printf ("Process %d \n", i+1);
for (j=0;j<numr;j++){
printf("Resource %d: ",i+1);
scanf("%d", &max[i][j]);}}
printf("Enter allocated matrix : ");
for (i=0;i<nump;i++){
printf ("Process %d \n", i+1);
for (j=0;j<numr;j++){
printf("Resource %d: ",i+1);
scanf("%d", &allocated[i][j]);
need[i][j]= max[i][j]-allocated[i][j];
available[j]-=allocated[i][j];}}
for (i=0;i<nump;i++){
for (j=0;j<numr;j++){
need[i][j]= max[i][j]-allocated[i][j];
available[j]-=allocated[i][j];}}
int pending=nump, flag, current, count,k=0;
while(pending>0){
flag=0;
for (i=0;i<nump;i++){
count=0;
for(j=0;j<numr;j++){
if (need[i][j]<=available[j]){
count++;}} 
if (count==numr){
current=i;
flag=1;
break;}}
if (flag==0){
break;}
sequence[k]=current;
k++;
pending--;
for (i=0;i<numr;i++){
available[i]+=allocated[current][i];
need[current][i]= inf;}}
if (pending==0){
printf("Safe sequence: ");
for (i=0;i<nump;i++){
printf("%d \t", sequence[i]);}}
else {
printf("Unsafe");}}