#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <getline.h>
#include <getline.c>
#include <getdelim.h>
#include <getdelim.c>

#ifndef SSMINER1_H
#define SSMINER1_H
#include <ssminer1.h>
#endif

void readOption(char response, int *flag) {
   int count=0;
   *flag=0;
   do {
   printf("\nLoad existing network or randomise topology? (L/R)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='l'||response=='L'){
   *flag=1;
   count=1;
   } else if (response=='r'||response=='R'){
   *flag=2;
   count=1;
   } else {
   *flag = 0;
   }
   } while (count <1);
   }
   
void getFilename (char filename[200], char discard, FILE *fp) {
    int flag=0;
    do { 
    printf("\nEnter network filepath and extension (C:\\blah\\stuff.thingy):\n");       
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    if (fopen(filename, "r")!=NULL){
    printf("Found file %s\n", filename);
    flag++;    
    } else if ((fp==NULL)||(fopen(filename, "r")==NULL)){      
    printf("Filepath error\n");
    }
    }while (flag<1);
    }
    
void getFileType(char response, int *flag) {
   int count=0;
   do {
   printf("\nPajek/Cytoscape? (P/C)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='p'||response=='P'){
   count=1;
   *flag=count;
   } else if (response=='c'||response=='C'){
   count=2;
   *flag=count;
   } else {
   count = 0;
   }
   } while (count <1);
   }  
    
void getBatchDumpFile (char filename[200], char discard, FILE *fp) {
    int flag=0;
    do { 
    printf("\nEnter filepath and extension of batchdump file (C:\\blah\\stuff.thingy):\n");       
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    fp=fopen(filename, "r");
    if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    flag++;
    } 
    }while (flag<1);
    printf("Found file %s\n", filename);    
    fclose(fp);
    }
    
void getFilesFromBatchDump (int N, FILE *fp, char strg[], char strg2[]) {
    int linesize=199;
    char line[199];
    int i;    
    char *ptr=(char *) malloc (linesize + 1);    
    char field1 [199];  
    fp=fopen(strg, "r");
    
    for(i=0;i<N;i++){
    getline(&ptr, &linesize, fp);
    }   
    
    getline(&ptr, &linesize, fp);      
    sscanf(ptr, "%s", &field1);    
    printf("Found file %s\n", field1);
    strcpy(strg2, field1);
    printf("filepath= %s\n", strg2);
    free(ptr);
    ptr=NULL;
    fclose(fp);     
    }
    
void getVerticesFromCytoscape(int *number, FILE *fp, char strg[], int *AttLines) {
    int linesize=199;    
    char *ptr= malloc ((linesize + 1)*sizeof(char));    
    char field1 [6];
    char nodeflag[]="<node";
    int count=0;
    int AttributeCounter;
    fseek(fp, 0, SEEK_SET);
    while ((getline(&ptr, &linesize, fp))!=-1){           
    sscanf(ptr, "%5s", &field1);
    if (strcmp(field1, nodeflag)==0){
    count++;
    AttributeCounter=0;  
    }
    if(count<2){
    AttributeCounter++;
    *AttLines=(AttributeCounter-1);
    }
    }
    *number=count;       
    free (ptr);
    ptr=NULL;
    }

int checkForMetaCore(FILE *fp, char strg[], int AttLines) {
    int linesize=199;
    int i,j,n;
    int count=0;
    int genegoCounter=0;   
    char *ptr=(char *) malloc (linesize + 1);
    char *ptr2;        
    char field1 [6];
    char field2[19];
    char field3[19];    
        
    char nodeflag[]="<node";
    char genegoflag[]="name=\"GENEGO_ID\"";
              
    fseek(fp, 0, SEEK_SET); 
    
    while ((getline(&ptr, &linesize, fp))!=-1){
    ptr2=ptr;
    sscanf(ptr, "%5s %n", &field1, &n);
    ptr2 +=(n+1);    
    if (strcmp(field1, nodeflag)==0){
    for(i=0;i<AttLines-1;i++){
    getline(&ptr, &linesize, fp);
    sscanf(ptr2, "%18[^ ] %18[^ ] %n", &field2, &field3, &n);
    if (strcmp(field3, genegoflag)==0){
    genegoCounter++;
    }
    }
    }
    }
    if (genegoCounter!=0){
    printf("\nFound GeneGo network\n"); 
    return 1;          
    }
    free(ptr);
    free(ptr2);
    ptr=NULL;
    ptr2=NULL;
    }
    
void FillCytoscapeIDs(struct vert vertex[], FILE *fp, char strg[]) {
    int linesize=199;
    int n;
    int count=0;    
    char *ptr=(char *) malloc (linesize + 1);
    char *ptr2;    
    char field1 [6];
    char field2[19];
    char field3[19];    
    char nodeflag[]="<node";
 
    fseek(fp, 0, SEEK_SET); 
    
    while ((getline(&ptr, &linesize, fp))!=-1){
    ptr2=ptr;
    sscanf(ptr, "%5s %18[^\"]%n", &field1, &field2, &n);
    if (strcmp(field1, nodeflag)==0){
    ptr2 +=(n+1);
    sscanf(ptr2, "%18[^\"]", &field3);
    strcpy(vertex[count].cytoscape_id, field3);
    count++;
    }
    }
    free (ptr);
    }

void FillCanonicalNames(struct vert vertex[], FILE *fp, char strg[]) {
    int linesize=199;
    char illegalflag[]="-";
    char legalflag[]="_";
    int i,j,n;
    int count=0;    
    char *ptr=(char *) malloc (linesize + 1);
    char *ptr2;
    char test;        
    char field1 [6];
    char field2[19];
    char field3[21];    
    char field4[19];
    char field5[100];
        
    char nodeflag[]="<node";
    char nameflag[]="name=\"canonicalName\"";
              
    fseek(fp, 0, SEEK_SET);  
    
    while ((getline(&ptr, &linesize, fp))!=-1){
    ptr2=ptr;
    sscanf(ptr, "%5s %n", &field1, &n);
    ptr2 +=(n+1);    
    if (strcmp(field1, nodeflag)==0){
    do{
    getline(&ptr, &linesize, fp);
    sscanf(ptr2, "%18[^ ] %20[^ ] %18[^\"] %n", &field2, &field3, &field4, &n);
    } while (strcmp(nameflag, field3)!=0);
    ptr2+=(n+1);
    sscanf(ptr2, "%99[^\"] %n", &field5, &n);          
    strcpy(vertex[count].name, field5);

    
    count++;
}
} 
    free (ptr);
    ptr=NULL;                             
    }


void cleanNames(struct vert vertex[], int size){
     int i, j;
     for (i=0; i<size; i++){
     for(j=0; j<100; j++){
     if (vertex[i].name[j]=='-'){
     strcpy(&vertex[i].name[j], "_");
     }
     }
     }
     }
     
     
         
void getEdgeNumberFromCytoscape(int *number, FILE *fp, char strg[]) {

    int linesize=199;    
    char *ptr=(char *) malloc (linesize + 1);    
    char field1 [6];
    char edgeflag[]="<edge";
    int count=0;
    
    fseek(fp, 0, SEEK_SET);
    
    while ((getline(&ptr, &linesize, fp))!=-1){           
    sscanf(ptr, "%5s", &field1);
    if (strcmp(field1, edgeflag)==0){
    count++;  
    }
    }
    *number=count;
    free (ptr);
    ptr=NULL;
    }

void dealWithUSLines(char response, int *Lflag, int *Prob){
   int count=0, temp;
   printf("\nNetwork may contain unspecified edge effects!\n");
   printf("\nUnspecified edge processing options:\n");
   printf("1. Ignore US edges\n");
   printf("2. Make US edges activating\n"); 
   printf("3. Make US edges repressive\n");
   printf("4. Randomise US edge weighting\n");       
   do {
   printf("\nSelect option (1-4)_");   
   fputs("", stdout);
   fflush(stdout);
   } while (!mygeti(&temp)||(1>temp)||(temp>4) );
   *Lflag=temp;
   if (*Lflag==4){
      do {
      printf("\nEnter repressor probability (0-100)_");   
      fputs("", stdout);
      fflush(stdout);
   } while (!mygeti(&temp)||(0>temp)||(temp>100) );
   *Prob=temp;     
   }   
   }
    
void getAdjacencyFromMetaCore(struct vert vertex[], int number, short array[number][number], FILE *fp, char strg[]) {
    int linesize=199;
    int i,j,n;
    int count=0;    
    char *ptr=(char *) malloc (linesize + 1);
    char *ptr2;        
    char field1 [6];
    char field2[19];
    char field3[19];    
    char field4[19];
    char field5[19];
        
    char arcflag[]="<edge";
    char repressorflag[]="AA0000";
    
    char **IDtemp = malloc (number*sizeof(char));
    for (i=0;i<number;i++){
    IDtemp[i] = malloc (20*sizeof(char));
    IDtemp[i]=vertex[i].cytoscape_id; 
    }

    fseek(fp, 0, SEEK_SET);
    while ((getline(&ptr, &linesize, fp))!=-1){
    ptr2=ptr;
    sscanf(ptr, "%5s %18[^\"]%n", &field1, &field2, &n);
    if (strcmp(field1, arcflag)==0){
    ptr2 +=(n+1);
    sscanf(ptr2, "%18[^ ] %18[^ ] %18[^\"]", &field3, &field4, &field5);
    }
    for (i=0; i<number; i++){
    for (j=0; j<number; j++){
    if ((strcmp (field3, vertex[i].cytoscape_id)==0)&&(strcmp (field5, IDtemp[j])==0)){                               
    array[i][j]=1;
    }
    }    
    }
    }
    free (ptr);
    ptr=NULL;
    for (i=0;i<number;i++){
    free(IDtemp[i]);
    }
    free(IDtemp);
    IDtemp=NULL;                 
    }
            
void getTopologyFromMetaCore(struct vert vertex[], int number, short array[number][number], FILE *fp, char strg[], int *US, int Lflag, int pval) {     
    int linesize=199;
    int i,j,n,r;
    int count=0;
    int USlines=0;   
    char *ptr=(char *) malloc (linesize + 1);
    char *ptr2;        
    char field1 [6];
    char field2[19];
    char field3[19];    
    char field4[19];
    char field5[19];   
    char arcflag[]="<edge";
    char interactionflag[]="name=\"EDGE_COLOR\"";
    char repressorflag[]="AA0000";
    char activatorflag[]="00AA00";
    char USflag[]="0000AA";
    char USflag2[]="000000";    
    char **IDtemp = malloc (number*sizeof(char));
    for (i=0;i<number;i++){
    IDtemp[i] = malloc (20*sizeof(char));
    IDtemp[i]=vertex[i].cytoscape_id; 
    }
               
    fseek(fp, 0, SEEK_SET);
    while ((getline(&ptr, &linesize, fp))!=-1){
    ptr2=ptr;
    sscanf(ptr, "%5s %18[^\"]%n", &field1, &field2, &n);
    if (strcmp(field1, arcflag)==0){
    ptr2 +=(n+1);
    sscanf(ptr2, "%18[^ ] %18[^ ] %18[^\"]", &field3, &field4, &field5);
    }
    for (i=0; i<number; i++){
    for (j=0; j<number; j++){
    if ((strcmp (field3, vertex[i].cytoscape_id)==0)&&(strcmp (field5, IDtemp[j])==0)){
    do{
    getline(&ptr, &linesize, fp);
    ptr2=ptr;
    sscanf(ptr, "%5s %18[^ ] %18[^ ] %18[^\"] %n", &field1, &field2, &field3, &field4, &n);
    ptr2+=(n+1);
    } while (strcmp (field3, interactionflag)!=0);
    sscanf(ptr2, "%18[^\"]", &field5);
    if (strcmp(field5, repressorflag)==0){
    array[i][j]=-1;
    } else if (strcmp(field5, activatorflag)==0){                                
    array[i][j]=1;
    } else if ((strcmp(field5, USflag)==0)||(strcmp(field5, USflag2)==0)){
    r=rand()%100;
    USlines++;                                
    *US=USlines;
          if (Lflag==1){
          array[i][j]=0;
          printf("\n%s -> %s US interaction ignored", vertex[i].name, vertex[j].name);
          } else if (Lflag==2){
          array[i][j]=1;
          printf("\n%s -> %s US interaction converted to activator", vertex[i].name, vertex[j].name);
          } else if (Lflag==3){
          array[i][j]=-1;
          printf("\n%s -> %s US interaction converted to repressor", vertex[i].name, vertex[j].name);
          } else if (Lflag==4){
                 if(r<pval){
                 array[i][j]=-1;
                 printf("\n%s -> %s US interaction converted to repressor", vertex[i].name, vertex[j].name);
                 } else {
                 array[i][j]=1;
                 printf("\n%s -> %s US interaction converted to activator", vertex[i].name, vertex[j].name);
                 }
    }                           
    }     
    }    
    }
    }
    }
    free (ptr);
    ptr=NULL;
    for (i=0;i<number;i++){
    free(IDtemp[i]);
    }
    free(IDtemp);
    IDtemp=NULL;                 
    }

void getVerticesFromPajek(int *number, FILE *fp, char strg[]) {
    int linesize=199;
    int temp;       
    char line[20];   
    char vertflag[10];               
    fseek(fp, 0, SEEK_SET); 
    fgets(line, sizeof(line), fp);
    sscanf(line, "%9s %3d", &vertflag, &temp);       
    *number=temp;         
    }

void getTopologyFromPajek(int size, FILE *fp, char strg[], short array[size][size]) {
    int linesize=199;
    int i,j,n,sum;  
    char line[199];                
    fseek(fp, 0, SEEK_SET);  
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    char *ptr=(char *) malloc (linesize + 1);
    char *ptr2;  
            
    for(i=0; i<size; i++){
    sum=0;
    getline(&ptr, &linesize, fp);
    ptr2=ptr;
    for(j=0; j<size; j++){
    sscanf(ptr2, "%2hd %n", &array[i][j], &n);
    ptr2+=n;    
    }
    }
    free (ptr);
    ptr=NULL;              
    }
