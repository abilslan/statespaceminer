#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#define maxv 25
#define THEFILE "C:\\Documents and Settings\\statespace.net"
#define FILE2 "C:\\Documents and Settings\\EcellModel.em"
#define FILE3 "C:\\Documents and Settings\\Topology.net"
#define REP "C:\\Documents and Settings\\Report.txt"
#define SREP "C:\\Documents and Settings\\ShortReport.txt"
typedef struct vert vertex[];
typedef struct rules RuleTables[];

struct vert {
   char vertex_type;
   int partition_cluster;
   int vertex_i;
   int rand_i;
   int k_in;
   int k_out;
   int threshold;
   int weighting;
   long rulesNumber;
   char cytoscape_id[30];
   char name[100];
   };

typedef struct node *link;
struct node {long v; link nextlink;};

link New(long v, link nextlink) {
    link x = malloc(sizeof *x);
    x->v = v; x->nextlink=nextlink;
    return x;
    }




/*Declare input validation function*/
int mygeti(int *result) {
   char *end, buff [ 13 ];
   fgets(buff, sizeof buff, stdin);
   *result = strtol(buff, &end, 10);
   return !isspace(*buff) && end != buff && (*end == '\n' || *end == '\0');
   }

int mygetc(char c) {
   char buff;
   scanf(" %c", &c);
   fflush(stdin);
   }

/*Declare initArray function*/
void initArray(int size_i, int size_j, int array[size_i][size_j]) {
     int i, j;
     for(i=0; i<size_i; i++) {
     for(j=0; j<size_j; j++) {
     array[i][j]=0;
     }
     }
     }

/*Declare initShortArray function*/
void initShortArray(int size_i, int size_j, short array[size_i][size_j]) {
     int i, j;
     for(i=0; i<size_i; i++) {
     for(j=0; j<size_j; j++) {
     array[i][j]=0;
     }
     }
     }

short** initShortDynArray(int size_i, long size_j) {
     int i;
     short **SDarray;
     SDarray = malloc(size_i*sizeof(short*));
     for(i = 0; i < size_i; i++) {
     SDarray[i] = malloc(size_j*sizeof(short));
     }
     return SDarray;
     }

void zeroShortDynArray(int size_i, long size_j, short **array) {
     int i;
     long j;
     for(i = 0; i < size_i; i++) {
     for(j = 0; j < size_j; j++) {
     array[i][j] = 0;
     }
     }
     }

void initLongArray(int size_i, long size_j, int array[size_i][size_j]) {
     int i;
     long j;
     for(i=0; i<size_i; i++) {
     for(j=0; j<size_j; j++) {
     array[i][j]=0;
     }
     }
     }

void initDynArray(int size_i, long size_j, int **array) {
     int i;
     long j;
     for(i=0; i<size_i; i++) {
     for(j=0; j<size_j; j++) {
     array[i][j]=0;
     }
     }
     }

void initLong1dDynArray(long size, long *array) {
     long i;
     for(i=0; i<size; i++) {
     array[i]=0;
     }
     }

void initArcs(int j, int size, int x, int y, short array[size][size]){
     int i;
     srand((unsigned)time(NULL));
     for (i=1; i<=j; i++) {
     x=rand()%size;
     y=rand()%size;
     if (array[x][y]==0){
     array[x][y]=1;
     } else {
     i--;
     }
     }
     }

/*Declare printArray function*/

void printArray(int size_i, int size_j, int array[size_i][size_j]) {
     int i, j;
     for(i=0; i<size_i; i++) {
     for(j=0; j<size_j; j++) {
     printf("%4d", array[i][j]);
     }
     printf("\n");
     }
     }

/*Declare printShortArray function*/

void printShortArray(int size_i, int size_j, short array[size_i][size_j]) {
     int i, j;
     for(i=0; i<size_i; i++) {
     for(j=0; j<size_j; j++) {
     printf("%4d", array[i][j]);
     }
     printf("\n");
     }
     }

short** printShortDynArray(int size) {
     int i, j;
     short **SDarray;
     for(i=0; i<size; i++) {
     for(j=0; j<size; j++) {
     printf("%4d", SDarray[i][j]);
     }
     printf("\n");
     }
     }

/*Declare printArray_j_i function*/

void printLongArray_j_i(int size_i, long size_j, int array[size_i][size_j]) {
     int i;
     long j;
     for(j=0; j<size_j; j++) {
     for(i=0; i<size_i; i++) {
     printf("%4d", array[i][j]);
     }
     printf("\n");
     }
     }

short** printShortDynArray_j_i(int size_i, long size_j, short **array) {
     int i;
     long j;
     for(j=0; j<size_j; j++) {
     for(i=0; i<size_i; i++) {
     printf("%4d", array[i][j]);
     }
     printf("\n");
     }
     }

void printDynArray_j_i(int size_i, long size_j, int **array) {
     int i;
     long j;
     for(j=0; j<size_j; j++) {
     for(i=0; i<size_i; i++) {
     printf("%4d", array[i][j]);
     }
     printf("\n");
     }
     }

/*Declare init_vertices function*/

void initVertexName(struct vert vertex[], int size_i){
     int i;
     char blank[]="";
     for(i=0; i<size_i; i++){
     strcpy(vertex[i].name,blank);
     }
     }

void init_vertices(struct vert vertex[], int size_i, int size_j, short array[size_i][size_j]) {
       int i,j, count=0;
       for(j=0;j<size_j;j++){
       vertex[j].threshold=0;
       vertex[j].weighting=1;
       vertex[j].vertex_i = j+1;
       int sum = 0;
       for(i=0;i<size_i;i++){
       sum = sum + abs(array[i][j]);
       vertex[j].k_in = sum;
       }
       vertex[j].rulesNumber = pow(2, vertex[j].k_in);
       }
       for(i=0;i<size_i;i++){
       int sum = 0;
       for(j=0;j<size_j;j++){
       sum = sum + abs(array[i][j]);
       vertex[i].k_out = sum;
       }
       }
       }

void initThresholdsAndWeights(struct vert vertex[], int size_i){
     int i;
     for (i=0; i<size_i; i++){
         vertex[i].threshold=0;
         vertex[i].weighting=1;
         }
         }

void showThresholdsAndWeights(struct vert vertex[], int size_i){
     int i;
     for (i=0; i<size_i; i++){
         printf("\nVertex %2d, threshold %2d, weight %2d", i+1, vertex[i].threshold, vertex[i].weighting);
         }
         }



void useThreshold(char response, struct vert vertex[], int size_i){
   int i, Tval;
   int count=0, count2=0;
   do {
   printf("\nUse threshold values (default 0)? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;

           do {
           printf("\nIndividual vertex or Global threshold? (I/G)_");
           scanf(" %c", &response);
           fflush(stdin);
           if (response=='i'||response=='I'){
           count2=1;
           for(i=0;i<size_i;i++){
           do {
           printf("\nEnter vertex %d threshold (max %d)_", i+1, size_i);
           fputs("", stdout);
           fflush(stdout);
           } while (!mygeti(&Tval)||(size_i<Tval)||(0>Tval) );
           vertex[i].threshold=Tval;
           }
           } else if (response=='g'||response=='G'){
           do {
           printf("\nEnter global threshold (max %d)_", size_i);
           fputs("", stdout);
           fflush(stdout);
           } while (!mygeti(&Tval)||(size_i<Tval)||(0>Tval) );
           for(i=0;i<size_i;i++){
           vertex[i].threshold=Tval;
           count2=1;
           }
           } else {
           count2=0;
           }
           } while (count2<1);

   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count=0;
   }
   }  while (count<1);
    }

void useWeighting(char response, struct vert vertex[], int size_i){
   int i, Wval;
   int count=0, count2=0;
   do {
   printf("\nUse weighting values (default 1)? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;

           do {
           printf("\nIndividual vertex or Global weights? (I/G)_");
           scanf(" %c", &response);
           fflush(stdin);
           if (response=='i'||response=='I'){
           count2=1;
           for(i=0;i<size_i;i++){
           do {
           printf("\nEnter vertex %d weight (max %d)_", i+1, size_i);
           fputs("", stdout);
           fflush(stdout);
           } while (!mygeti(&Wval)||(size_i<Wval)||(0>Wval) );
           vertex[i].weighting=Wval;
           }
           } else if (response=='g'||response=='G'){
           do {
           printf("\nEnter global weight (max %d)_", size_i);
           fputs("", stdout);
           fflush(stdout);
           } while (!mygeti(&Wval)||(size_i<Wval)||(0>Wval) );
           for(i=0;i<size_i;i++){
           vertex[i].weighting=Wval;
           count2=1;
           }
           } else {
           count2=0;
           }
           } while (count2<1);

   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count=0;
   }
   }  while (count<1);
    }

void getRuleNumber(struct vert vertex[], int size_i, long *number){
     int i;
     long temp=0;
     for(i=0;i<size_i;i++){
     if (vertex[i].rulesNumber>temp){
     temp=vertex[i].rulesNumber;
     }
     *number=temp;
     }
     }

void init_vertexType(struct vert vertex[], int size_i, int probability) {
       int i;
       for(i=0;i<size_i;i++){
       if (probability>vertex[i].rand_i){
       vertex[i].vertex_type = 'R';
       } else {
       vertex[i].vertex_type = 'A';
       }
       }
       }

void findTopology (struct vert vertex[], int size, short array1[size][size], short array2[size][size]){
      int i,j;
      for (i=0; i<size; i++) {
      if (vertex[i].vertex_type== 'R') {
      for (j=0; j<size; j++) {
      switch (array1[i][j]) {
      case 1:
      array2[i][j]=-1;
      break;
      case 0:
      array2[i][j]=0;
      break;
      }
      }
      } else {
      for (j=0; j<size; j++) {
      switch (array1[i][j]) {
      case 1:
      array2[i][j]=1;
      break;
      case 0:
      array2[i][j]=0;
      break;
      }
      }
      }
      }
      }


void rand_vertexType(struct vert vertex[], int size_i) {
      int i;
      srand((unsigned)time(NULL));
      for(i=0;i<size_i;i++){
      vertex[i].rand_i=rand()%100;
      }
      }


void checkForSources(struct vert vertex[], int *counter, int size){
     int i;
     int temp=0;
     for(i=0; i<size; i++) {
     if (vertex[i].k_in>0) {
     temp++;
     }
     }
     *counter=temp;
     }

 /*Initialise array using k_in field*/

void initArray_vertex(struct vert vertex[], int size_i, int size_j, int array[size_i][size_j]) {
       int i,j;
       for(i=0;i<size_i;i++){
       for(j=0;j<vertex[i].k_in;j++){
       array[i][j]=0;
       }
       }
       }

void init1dAray(int size, int array[size]){
     int i;
     for(i=0;i<size;i++)  {
     array[i]=0;
     }
     }

void initLong1dAray(long size, long array[size]){
     long i;
     for(i=0;i<size;i++)  {
     array[i]=0;
     }
     }

void intInitLong1dAray(int size, long array[size]){
     int i;
     for(i=0;i<size;i++)  {
     array[i]=0;
     }
     }

void longInitInt1dAray(long size, short array[size]){
     long i;
     for(i=0;i<size;i++)  {
     array[i]=0;
     }
     }

void initFloat1dAray(int size, float array[size]){
     int i;
     for(i=0;i<size;i++)  {
     array[i]=0;
     }
     }

void intInitFloat1dAray(long size, float array[size]){
     long i;
     for(i=0;i<size;i++)  {
     array[i]=0;
     }
     }

void findNeighbours(int size, short array1[size][size], int array2[size][size], int array3[size][size]) {
          int i,j,k;
          for(j=0;j<size;j++)  {
          k=0;
            for (i=0; i<size; i++) {
                  switch (array1[i][j]) {
                        case 0:
                        break;
                        case 1:
                        array2[j][k]=1;
                        array3[j][k]=i+1;
                        k=k+1;
                        break;
                       case -1:
                        array2[j][k]=-1;
                        array3[j][k]=i+1;
                        k=k+1;
                        break;
                         }
                         }
                         }
                         }


void initDFS(long size, link list[size], short array[size]){
    int i;
    for (i=0; i<size; i++) {
        list[i]=NULL;
        array[i]=0;
        }
        }

void initList(long size, link list[size], long array[size]){
    int i, q;
    for (i=0; i<size; i++) {
        q=array[i];
        list[q]=New(i, list[q]);
        list[i]=New(q, list[i]);
        }
        }

void traverse(int k, int marker, long size, short array[size], link list[size]) {

    link t;
    array[k]=marker;
    for (t=list[k]; t!=NULL; t=t->nextlink) {
        if (!array[t->v]) traverse((t->v), marker, size, array, list);
        }
        }

void assignRules(struct vert vertex[], int size_i, long size_j, short **array){
    int i;
    long j;
    for(i=0;i<size_i;i++)  {
          for (j=0; j<vertex[i].rulesNumber;j++)  {
           if (array[i][j]>=0) {
             array[i][j]=1;
             } else {
             array[i][j]=0;
             }
             }
             }
             }

void randomiseRules(struct vert vertex[], int size_i, long size_j, short **array){
    int i, pval;
    long j;
    do {
    fputs("\nEnter on probability_", stdout);
    fflush(stdout);
    } while (!mygeti(&pval)||(100<pval)||(0>pval) );
    srand((unsigned)time(NULL));
    for(i=0;i<size_i;i++)  {
          for (j=0; j<vertex[i].rulesNumber;j++)  {
           if ((rand()%100)<=pval) {
             array[i][j]=1;
             } else {
             array[i][j]=0;
             }
             }
             }
             }

 /*Print array using k_in field*/

void printArray_vertex(struct vert vertex[], int size_i, int size_j, int array[size_i][size_j]) {
       int i,j;
       for(i=0;i<size_i;i++){
       printf("\nVertex: %2d:", vertex[i].vertex_i);
       for(j=0;j<vertex[i].k_in;j++){
       printf("%4d", array[i][j]);
       }
       }
       }

void getBasinSize(long size1, int size2, short array1[size1], long array2[size2]) {
     long i;
     int j;
     for (i=0; i<size1; i++){
     j=array1[i]-1;
     array2[j]=array2[j]+1;
     }
     }

void decToBin(long dec, int size, int array[size]) {
     int remain, tracker;
     tracker=size-1;
     do {
     remain = dec % 2;
     array[tracker]=remain;
     dec = dec/2;
     tracker--;
     }
     while (dec > 0);
     do {
     array[tracker]=0;
     tracker--;
     } while (tracker>=0);
     }


void growTruthTables(struct vert vertex[], int size, int array1[size], int array2[size][size],short **array3, int array4[size][size]){
     int i,j,k,m, sum;
     printf("\n\nGrowing truthtables");
     for(i=0;i<size;i++)  {
     printf(".");
     for (j=0;j<vertex[i].rulesNumber;j++){
      sum=vertex[i].threshold;
      decToBin(j, size, array1);
      for(k=0; k<vertex[i].k_in;k++){
      m=(size-vertex[i].k_in)+k;
      sum=sum+((array2[i][k]*vertex[(array4[i][k])].weighting)*array1[m]);
      }
      array3[i][j]=sum;
      }
      }
      printf("\nDone\n");
      }

void checkRules(char response, int size_j, long size_i, int **array){
   int count=0;
   do {
   printf("\nShow rule table? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;
   printf("\n\nrulesSum array:\n\n");
   printDynArray_j_i(size_j, size_i, array);
   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count=0;
   }
   }  while (count<1);
   }

void DFS(long size, short array1[size], link list[size], int *componentCount){
    long i;
    *componentCount=0;
    for (i=0; i<size; i++) {
    if (array1[i]==0) {
    *componentCount = *componentCount+1;
    traverse(i, *componentCount, size, array1, list);
    }
    }
    }

void findHammingNeighbour(int vertex, int size, int array[size]){
     if (array[vertex]==1){
     array[vertex]=0;
     } else {
     array[vertex]=1;
     }
     }

void bin2dec(int size, int array[size], long *count){
     long z, temp=0;
     int i, l;
     for (i=1; i<=size; i++) {
     l=size-i;
     z = array[i-1]*pow(2, l);
     temp = temp + z; // sum it up
     }
     *count=temp;
     }

void compareBasins(long state, long neighbour, long size, short array1[size], float array2[size]){
     if (array1[state]==array1[neighbour]){
     array2[state]=array2[state]+1;
     }
     }

void getStateCoherence(long size, int N, float array1[size], float array2[size]){
     long i;
     for (i=0; i<size; i++){
     array2[i]=(array1[i]/N);
     }
     }

void getBasinCoherence(long size1, short array1[size1], float array2[size1], int size2, float array3[size2], long array4[size2]){
     long i;
     int count=1;
     do {
     for (i=0; i<size1; i++){
     if (array1[i]==count){
     array3[count-1]=array3[count-1]+array2[i];
     }
     }
     array3[count-1]=(array3[count-1]/array4[count-1]);
     count=count+1;
     } while  (count<=size2);
     }

void getRandCoherence(int size1, int N, long array1[size1], float array2[size1]){
     int i;
     for (i=0; i<size1; i++){
     array2[i]=((array1[i]-1)/(pow(2, N)-1));
     }
     }

void getMaxCoherence(int size1, int N, long array1[size1], float array2[size1]){
     int i;
     for (i=0; i<size1; i++){
     array2[i]=(log(array1[i])/log(2))/N;
     }
     }

void getStructCoherence(int size1, float array1[size1], float array2[size1], float array3[size1], float array4[size1]){
     int i;
     for (i=0; i<size1; i++){
     array4[i]=(array1[i]-array2[i])/(array3[i]-array2[i]);
     }
     }

void setAttractorStart(int size1, long size2, long array[size1], long array2[size2], short array3[size2], long array4[size1]){
     int i;
     long t, next;
     for (i=0; i<size1; i++){
     t=array[i];
     do {
     array3[t]=1;
     next=array2[t];
     t=next;
     } while (array3[t] != 1);
     array4[i]=t;
     }
     }

void findAttractorLength(int size1, long size2, long array[size1], long array2[size2], short array3[size2], long array4[size1]){
     int i;
     long t, next;
     for (i=0; i<size1; i++){
     t=array[i];
     do {
     array3[t]=1;
     array4[i]=array4[i]+1;
     next=array2[t];
     t=next;
     } while (array3[t] != 1);
     }
     }

void findAttractorStates(int size1, long size2, long array[size1], long array2[size2], long array4[size1], long **array5){
     int i;
     long j, t, next;
     for (i=0; i<size1; i++){
     t=array[i];
     for (j=0; j<array4[i]; j++) {
     array5[i][j]=t;
     next=array2[t];
     t=next;
     }
     }
     }

void showAttractorVector(int size, int size2, long array[size], long **array2, int array3[size2]){
     int i, j, k;
     long AttState;
     for (i=0; i<size; i++){
     printf("\nBasin %d: Attactor states:\n", i+1);
     for (j=0; j<array[i]; j++){
     AttState=array2[i][j];
     decToBin(AttState, size2, array3);
     for (k=0; k<size2; k++){
     printf("%4d", array3[k]);
     }
     printf("\n");
     }
     }
     }

void makePartitionFromAttractorVector(char filename[200], char discard, FILE *fp, char response, int size, int size2, long array[size], long **array2, int array3[size2]){
   int i,j,k,count=0, flag=0;
   long AttState;
   char suffix[9]="____.clu";
   char filepatharray[size][10][200];
   do {
   printf("\nSave attractors as partitions? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;
    do {
    printf("\nSave parent filename for series as (do not include extension) ... (C:\\blah\\stuff):\n");
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    printf("\nPartition series saved as:");
    for (i=0; i<size; i++){
    suffix[1]=(65+i);
     for (j=0; j<array[i]; j++){
    suffix[3]=(65+j);
    strcpy(filepatharray[i][j], filename);
    strcat(filepatharray[i][j], suffix);
    printf("\n%s",filepatharray[i][j]);
    fp=fopen(filepatharray[i][j], "w");
    fprintf(fp, "*Vertices %d", size2);
     AttState=array2[i][j];
     decToBin(AttState, size2, array3);
     for (k=0; k<size2; k++){
     fprintf(fp, "\n%d", array3[k]);
     }
     fclose(fp);
    }
    }
    if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    printf("\n");
    fclose(fp);
    flag++;
    }
    }while (flag<1);
   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void  topologyNotFound(char response, int *flag){
    int count=0;
    do {
    printf("\nTopology not found!");
    printf("\nSearch again/Continue/Exit application (S/C/E)?_");
    scanf(" %c", &response);
    fflush(stdin);
    if (response=='S'||response=='s'){
    *flag=0;
    count=1;
    } else if (response=='E'||response=='e'){
    printf("\nPress any key to exit");
    getchar();
    exit(EXIT_SUCCESS);
    } else if (response=='C'||response=='c'){
    *flag=1;
    count=1;
    } else {
    count =0;
    }
    } while (count <1);
    }


void enterTargeting(char response) {
   int count=0;
   do {
   printf("\nTarget nodes? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;
   } else if (response=='n'||response=='N'){
   printf("\nSaved files - press any key to exit");
   getchar();
   exit(EXIT_SUCCESS);
   } else {
   count = 0;
   }
   } while (count <1);
   }

void getNodedegrees(char response, int N, struct vert vertex[]) {
   int i, count=0;
   do {
   printf("\nShow node degrees? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;
   for(i=0;i<N;i++)  {
   printf("Vertex: %2d  k_in: %d  k_out: %d\n", vertex[i].vertex_i, vertex[i].k_in, vertex[i].k_out);
   }
   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void getNumberTargetNodes(int size, int *N) {
    int temp;
    do {
    fputs("\nHow many target vertices?_", stdout);
    fflush(stdout);
    } while (!mygeti(&temp)||(1>temp)||(temp>size) );
    *N=temp;
   }

void getTargetNodes(char response, int size, int t, int N, int **array) {
    int i, j, count, temp, temp2, selectionflag;

    i=t;
    while ((i<N)||(t<N)) {
    selectionflag=0;
    do {
    printf("\nEnter target vertex %d_", i+1);
    fputs("", stdout);
    fflush(stdout);
    } while (!mygeti(&temp)||(1>temp)||(temp>size) );
    array[0][i]=temp;

    for (j=0;j<i;j++){
    if (array[0][j]==temp){
    selectionflag=1;
    }
    }
    if (selectionflag!=1){

    do {
    printf("\nSet constitutive state (0/1)_");
    fputs("", stdout);
    fflush(stdout);
    } while (!mygeti(&temp2)||(0>temp2)||(temp2>1) );
    array[1][i]=temp2;
    t++;
    i++;
    } else if(selectionflag==1){
   printf("\nTarget vertex previously selected!");
   do {
   printf("\nReset state (Continue) or change Vertex (C/V)?_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='c'||response=='C'){
   count=1;
   selectionflag=0;

    do {
    printf("\nSet constitutive state (0/1)_");
    fputs("", stdout);
    fflush(stdout);
    } while (!mygeti(&temp2)||(0>temp2)||(temp2>1) );
    array[1][i]=temp2;
    t++;
    i++;

   } else if (response=='v'||response=='V'){
   count=1;
   selectionflag=0;
   getTargetNodes(response, size, t, 0, array);
   } else {
   count = 0;
   }
   } while (count <1);
   }
}
}
void repeatTargeting(char response, int *flag) {
   int count=0;
   do {
   printf("\nTarget/Restore nodes, or exit? (T/R/E)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='t'||response=='T'){
   count=1;
   *flag=0;
   } else if (response=='r'||response=='R'){
   count=1;
   *flag=1;
   } else if (response=='e'||response=='E'){
   count=1;
   *flag=2;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void targetVertex(struct vert vertex[], int size_i, long size_j, short **array, int **array2, int N){
     int i;
     long j;

     for (i=0; i<N; i++){
     for (j=0; j<vertex[(array2[0][i])-1].rulesNumber; j++){
     array[(array2[0][i])-1][j]=array2[1][i];
     }
     }
     }

void restoreVertex(struct vert vertex[], int size_i, long size_j, int **array, int N, int array2[size_i], int array3[size_i][size_i], int **array4){
     int i, k, m;
     long j;
     int Sum;

     for (i=0; i<N; i++){
     for (j=0;j<vertex[(array4[0][i])-1].rulesNumber;j++){
     Sum=0;
     decToBin(j, size_i, array2);
     for(k=0; k<vertex[(array4[0][i])-1].k_in;k++){
     m=(size_i-vertex[(array4[0][i])-1].k_in)+k;
     Sum=Sum+(array3[(array4[0][i])-1][k]*array2[m]);
     }
     if (Sum>=0) {
     array[(array4[0][i])-1][j]=1;
     } else {
     array[(array4[0][i])-1][j]=0;
     }
     }
     }
     }

void restoreVertex2(struct vert vertex[], int size_i, long size_j, short **array, int array2[size_i], int array3[size_i][size_i], int array4[size_i][size_i]){
    zeroShortDynArray(size_i, size_j, array);
    init1dAray(size_i, array2);
    /*grow state vector matrix*/
    growTruthTables(vertex, size_i, array2, array3, array, array4);
    /*Assign rules*/
    assignRules(vertex, size_i, size_j, array);
    }

void nameVertice (char discard, struct vert vertex[], int size, char response) {
   int i,j, count=0, uniqueflag;
   do {
   printf("\nName vertices? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;
   for (i=0; i<size; i++){
    do {
    uniqueflag=0;
    printf("\nVertex %d name_", i+1);
    scanf("%99[^\t\n]", vertex[i].name);
    discard =getchar();
    if (strlen(vertex[i].name)==0){
        printf("\nNo name selected!");
        }
    for (j=0; j<i; j++){
        if (strcmp(vertex[i].name, vertex[j].name)==0){
        printf("\n%s already selected! Please change name.", vertex[i].name);
        uniqueflag=1;
        }
        }
    } while ((discard!='\n')||(strlen(vertex[i].name)==0)||(uniqueflag==1));
    }

   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void nameVertices2 (char discard, struct vert vertex[], int size) {
   int i,j, count=0, uniqueflag;
   for (i=0; i<size; i++){
    do {
    uniqueflag=0;
    printf("\nVertex %d name_", i+1);
    scanf("%99[^\t\n]", vertex[i].name);
    discard =getchar();
    if (strlen(vertex[i].name)==0){
        printf("\nNo name selected!");
        }
    for (j=0; j<i; j++){
        if (strcmp(vertex[i].name, vertex[j].name)==0){
        printf("\n%s already selected! Please change name.", vertex[i].name);
        uniqueflag=1;
        }
        }
    } while ((discard!='\n')||(strlen(vertex[i].name)==0)||(uniqueflag==1));
   }
   }

void saveMatrixtoPajekAs (char filename[200], char discard, FILE *fp, int size, short array[size][size], char response) {
   int i,j,count=0;
   int flag=0;
   do {
   printf("\nSave topology to Pajek? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;

    do {
    printf("\nSave as... (C:\\blah\\stuff.thingy):\n");
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    fp=fopen(filename, "w");
     fprintf(fp, "*Vertices %d\n", size);
     fprintf(fp, "*Matrix\n");
     for (i=0; i<size; i++){
     for (j=0; j<size; j++) {
     fprintf(fp, "%4d", array[i][j]);
     }
     fprintf(fp, "\n");
     }
    if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    printf("File saved\n");
    fclose(fp);
    flag++;
    }
    }while (flag<1);

   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void writeMatrixToPajek(int size, short array[size][size], FILE *fp){
     int i,j;
     fp = fopen(FILE3, "w");
     fprintf(fp, "*Vertices %d\n", size);
     fprintf(fp, "*Matrix\n");
     for (i=0; i<size; i++){
     for (j=0; j<size; j++) {
     fprintf(fp, "%4d", array[i][j]);
     }
     fprintf(fp, "\n");
     }
     fclose(fp);
     }

void askForPartition(char response, int *pflag) {
   int count=0;
   do {
   printf("\nMake network partition? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;
   *pflag=1;
   } else if (response=='n'||response=='N'){
   count=1;
   *pflag=0;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void getPartitionType(char response, int *typeflag) {
   int count=0;
   printf("\nAvailable partition types:");
   printf("\nManual (M)");
   printf("\nRandom (R)");
   printf("\nNodeX-input sign (N)");
   do {
   printf("\n\nChoose partition type (M/R/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='m'||response=='M'){
   count=1;
   *typeflag=0;
   } else if (response=='r'||response=='R'){
   count=1;
   *typeflag=1;
   } else if (response=='n'||response=='N'){
   count=1;
   *typeflag=2;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void assignPartition(struct vert vertex[], int size, int csize, int child, short array[size][size], int typeflag, int *validationarray) {
    int i,j,k,x, randcheck;
    if (typeflag==0){
    printf("\nEnter vertex clusters (Max %d)_:", size);
    for (i=0; i<size; i++){
    do {
    printf("\nVertex %d):_", i+1);
    fputs("", stdout);
    fflush(stdout);
    } while (!mygeti(&vertex[i].partition_cluster)||(1>vertex[i].partition_cluster)||(vertex[i].partition_cluster>size) );
    }
    } else if (typeflag==1){
    do {
    printf("\nEnter number of clusters (Max %d)_:", size);
    fputs("", stdout);
    fflush(stdout);
    } while (!mygeti(&csize)||(1>csize)||(csize>size) );
    printf("clusters = %d\n", csize);

do {
    randcheck=0;
    validationarray=malloc(csize*sizeof(int));
    for(i=0; i<csize; i++){
    validationarray[i]=1;
    }
    for(i=0; i<size; i++){
    x=rand()%csize;
    validationarray[x]=0;
    vertex[i].partition_cluster=x+1;
    }
    for(i=0; i<csize; i++){
    randcheck=randcheck+validationarray[i];
    }
    free (validationarray);
    validationarray=NULL;
    } while (randcheck!=0);
    } else if (typeflag==2){
    do {
    fputs("\nEnter child node_:",stdout);
    fflush(stdout);
    } while (!mygeti(&child)||(1>child)||(child>size) );
    printf("selected child = %d\n", child);
    for (j=0; j<size; j++) {
    if (j+1==child){
    vertex[j].partition_cluster=3;
    } else if (array[j][child-1]==-1){
    vertex[j].partition_cluster=1;
    } else if (array[j][child-1]==1){
    vertex[j].partition_cluster=2;
    } else if (array[j][child-1]==0){
    vertex[j].partition_cluster=4;
    }
    }
    }
    for(i=0; i<size; i++){
    printf("\nVertex: %2d, Cluster: %2d", i+1, vertex[i].partition_cluster);
    }
    }

void savePartitiontoPajekAs (char filename[200], char discard, FILE *fp, int size, struct vert vertex[], char response) {
   int i,j,count=0;
   int flag=0;
   do {
   printf("\nSave partition to Pajek? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;

    do {
    printf("\nSave as... (C:\\blah\\stuff.thingy):\n");
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    fp=fopen(filename, "w");
     fprintf(fp, "*Vertices %d\n", size);
     for (i=0; i<size; i++){
     fprintf(fp, "%d\n", vertex[i].partition_cluster);
     }

    if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    printf("File saved\n");
    fclose(fp);
    flag++;
    }
    }while (flag<1);

   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void showPartition(struct vert vertex[], int size){
     int i;
     for (i=0;i<size;i++){
     printf("\nVertex: %d, Cluster: %d", i+1, vertex[i].partition_cluster);
     }
     }

void dismissPartition(struct vert vertex[], int size){
     int i;
     for (i=0;i<size;i++){
     vertex[i].partition_cluster=0;
     }
     }

void printFullReport(struct vert vertex[], int prob, int size1, int size2, int size3, int array1[size1][size1], int array2[size1][size3],FILE *fp){
    int i,j;
    fp = fopen(REP, "w");
    fprintf(fp, "StateSpaceMiner Network Report:\n\n");
    fprintf(fp, "Vertices:%4d, Arcs:%4d\n\n", size1, size2);
    for (i=0; i<size1; i++) {
    fprintf(fp, "Vertex:%2d Indegree:%2d Type:", vertex[i].vertex_i, vertex[i].k_in);
    if (prob>vertex[i].rand_i){
    fprintf(fp, "R");
    } else {
    fprintf(fp, "A");
    }
    fprintf(fp, "\n");
    }
    fprintf(fp, "\nTopology:\n");
    for (i=0; i<size1; i++) {
    for (j=0; j<size1; j++) {
    fprintf(fp, "%4d", array1[i][j]);
    }
    fprintf(fp, "\n");
    }
    fprintf(fp, "\nRules:\n");
    for (j=0; j<size3; j++) {
    for (i=0; i<size1; i++) {
    fprintf(fp, "%4d", array2[i][j]);
    }
    fprintf(fp, "\n");
    }
    fclose(fp);
    }

void printShortReport(char strg[], int comp, long AttL[comp], long **AttS, FILE *fp){
    int i,j;
    fprintf(fp, "\n\nStateSpaceMiner Network Report:\n");
    fprintf(fp, "Network: %s", strg);
    fprintf(fp, "\n");
    fprintf(fp, "Components: %4d", comp);

    for(i=0; i<comp; i++){
    fprintf(fp, "\nBasin %d: Attactor states:", i+1);
    for (j=0; j<AttL[i]; j++){
    fprintf(fp, " %8d", AttS[i][j]);
    }
    }
    }

void saveArcsListtoPajekAs (char filename[200], char discard, FILE *fp, long size, long array[size], char response) {
   int count=0;
   long i;
   int flag=0;
   do {
   printf("\nSave Statespace to Pajek? (Y/N)_");
   scanf(" %c", &response);
   fflush(stdin);
   if (response=='y'||response=='Y'){
   count=1;

    do {
    printf("\nSave as... (C:\\blah\\stuff.thingy):\n");
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    fp=fopen(filename, "w");
    fprintf(fp, "*Vertices %d\n", size);
    for(i=0; i<size; i++) {
    fprintf(fp, "%d \"state %d\"",i+1,i);
    fprintf(fp, "\n");
    }
    fprintf(fp, "*Arcs\n");
    for(i=0; i<size; i++) {
    fprintf(fp, "%10d   %10d",i+1, array[i]+1);
    fprintf(fp, "\n");
     }
    if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    printf("File saved\n");
    fclose(fp);
    flag++;
    }
    }while (flag<1);

   } else if (response=='n'||response=='N'){
   count=1;
   } else {
   count = 0;
   }
   } while (count <1);
   }

void saveArcsListtoPajekAsShort (char filename[200], struct vert vertex[], char discard, FILE *fp, int size, short array[size][size], char response) {
   int i,j;
   int flag=0;
   char blank[]="";
    do {
    printf("\nSave as... (C:\\blah\\stuff.thingy):\n");
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    fp=fopen(filename, "w");
    fprintf(fp, "*Vertices %d\n", size);
    for(i=0; i<size; i++) {
      if (strcmp(vertex[i].name, blank)!=0){
      fprintf(fp, "%d \"%s\"",i+1,vertex[i].name);
      fprintf(fp, "\n");
      } else {
      fprintf(fp, "%d \"v%d\"",i+1,i+1);
      fprintf(fp, "\n");
      }
      }
    fprintf(fp, "*Arcs\n");
    for(i=0; i<size; i++) {
    for(j=0; j<size; j++) {
      if (array[i][j]!=0){
      fprintf(fp, "%2d   %2d   %d",i+1, j+1, array[i][j]);
      fprintf(fp, "\n");
     }
     }
     }

    if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    printf("File saved\n");
    fclose(fp);
    flag++;
    }
    }while (flag<1);
   }

void writeArcsListToPajek(long size, long array[size], FILE *fp, char strg[]){
    long i;
    fp = fopen(strg, "w");
    fprintf(fp, "*Vertices %d\n", size);
    for(i=0; i<size; i++) {
    fprintf(fp, "%d \"state %d\"",i+1,i);
    fprintf(fp, "\n");
    }
    fprintf(fp, "*Arcs\n");
    for(i=0; i<size; i++) {
    fprintf(fp, "%10d   %10d",i+1, array[i]+1);
    fprintf(fp, "\n");
    }
    fclose(fp);
    }

void writeArcsListToPajek2(long size, long array[size], FILE *fp, char strg[], char strg2[]){
    long i;
    fp = fopen(strcat(strg,strg2), "w");
    fprintf(fp, "*Vertices %d\n", size);
    for(i=0; i<size; i++) {
    fprintf(fp, "%d \"state %d\"",i+1,i);
    fprintf(fp, "\n");
    }
    fprintf(fp, "*Arcs\n");
    for(i=0; i<size; i++) {
    fprintf(fp, "%10d   %10d",i+1, array[i]+1);
    fprintf(fp, "\n");
    }
    fclose(fp);
    }

  /*write E-cell model*/
void writeEcellModel(struct vert vertex[], int size_i, int array[size_i][size_i], int array2[size_i][size_i], FILE *fp){
    int i, j;
    fp = fopen(FILE2, "w");
    fprintf(fp, "Stepper ODEStepper(Default_Stepper)\n{\n# no property\n}\n\n");
    fprintf(fp, "System System(/)\n{\nStepperID	Default_Stepper;\n\n");
    for(i=0; i<size_i; i++) {
    fprintf(fp, "Variable Variable(RNA_V%d)\n{\nValue	0.0;\n}\n\n", i+1);
    fprintf(fp, "Variable Variable(Prot_V%d)\n{\nValue	0.0;\n}\n\n", i+1);
    }
    fprintf(fp, "Variable Variable(SIZE)\n{\nValue	1.0;\n}\n\n");
    for(i=0; i<size_i; i++) {
    fprintf(fp, "Process ExpressionFluxProcess(TransL_V%d)\n{\n", i+1);
    fprintf(fp, "kTL	1;\n");
    fprintf(fp, "VariableReferenceList	[TL1 Variable:.:RNA_V%d 0] [TL2 Variable:.:Prot_V%d 1];\n",i+1,i+1);
    fprintf(fp, "Expression	\"kTL*TL1.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(BaseTransC_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[TB Variable:.:RNA_V%d 1];\n", i+1);
    fprintf(fp, "Expression	0.001;\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(RNAdeg_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[Rdeg Variable:.:RNA_V%d -1];\n",i+1);
    fprintf(fp, "Expression	\"Rdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(Protdeg_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[Pdeg Variable:.:Prot_V%d -1];\n",i+1);
    fprintf(fp, "Expression	\"Pdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(TransC_V%d)\n{\n", i+1);
    fprintf(fp, "Kmax_V%d 5;\n", i+1);
    for (j=0; j<vertex[i].k_in; j++) {
    fprintf(fp, "kd_V%d 1;\n", array[i][j]);
    }
    fprintf(fp, "VariableReferenceList	[TransC Variable:.:RNA_V%d 1]", i+1);
    for (j=0; j<vertex[i].k_in; j++) {
    fprintf(fp, " [Prot_%d Variable:.:Prot_V%d 0]", array[i][j], array[i][j]);
    }
    fprintf(fp, ";\n");
    fprintf(fp, "Expression   \"Kmax_V%d*((", i+1);
    for (j=0; j<vertex[i].k_in; j++) {
    switch (array2[i][j]) {
    case 1:
    fprintf(fp, "(Prot_%d.Value/(Prot_%d.Value+kd_V%d))",array[i][j], array[i][j],array[i][j], array[i][j]);
    break;
    case -1:
    fprintf(fp, "(kd_V%d/(Prot_%d.Value+kd_V%d))",array[i][j], array[i][j],array[i][j], array[i][j]);
    break;
    }
    if (j<vertex[i].k_in-1) {
    fprintf(fp, "+");
    }
    }
    fprintf(fp, ")/%d)\";\n}\n\n", vertex[i].k_in);
    }
    fprintf(fp, "\n}");
    fclose(fp);
    }


  /*write E-cell model*/
void saveEcellModelAs(char filename[200], char discard, struct vert vertex[], int size_i, int array[size_i][size_i], int array2[size_i][size_i], FILE *fp){
    int i, j, count=0;

    do {
    printf("\nSave model as... (C:\\blah\\stuff.thingy):\n");
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    fp=fopen(filename, "w");
      if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    fprintf(fp, "Stepper ODEStepper(Default_Stepper)\n{\n# no property\n}\n\n");
    fprintf(fp, "System System(/)\n{\nStepperID	Default_Stepper;\n\n");
    for(i=0; i<size_i; i++) {
    fprintf(fp, "Variable Variable(RNA_V%d)\n{\nValue	0.0;\n}\n\n", i+1);
    fprintf(fp, "Variable Variable(Prot_V%d)\n{\nValue	0.0;\n}\n\n", i+1);
    }
    fprintf(fp, "Variable Variable(SIZE)\n{\nValue	1.0;\n}\n\n");
    for(i=0; i<size_i; i++) {
    fprintf(fp, "Process ExpressionFluxProcess(TransL_V%d)\n{\n", i+1);
    fprintf(fp, "kTL	1;\n");
    fprintf(fp, "VariableReferenceList	[TL1 Variable:.:RNA_V%d 0] [TL2 Variable:.:Prot_V%d 1];\n",i+1,i+1);
    fprintf(fp, "Expression	\"kTL*TL1.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(BaseTransC_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[TB Variable:.:RNA_V%d 1];\n", i+1);
    fprintf(fp, "Expression	0.001;\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(RNAdeg_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[Rdeg Variable:.:RNA_V%d -1];\n",i+1);
    fprintf(fp, "Expression	\"Rdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(Protdeg_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[Pdeg Variable:.:Prot_V%d -1];\n",i+1);
    fprintf(fp, "Expression	\"Pdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(TransC_V%d)\n{\n", i+1);
    fprintf(fp, "Kmax_V%d 5;\n", i+1);
    for (j=0; j<vertex[i].k_in; j++) {
    fprintf(fp, "kd_V%d 1;\n", array[i][j]);
    }
    fprintf(fp, "VariableReferenceList	[TransC Variable:.:RNA_V%d 1]", i+1);
    for (j=0; j<vertex[i].k_in; j++) {
    fprintf(fp, " [Prot_%d Variable:.:Prot_V%d 0]", array[i][j], array[i][j]);
    }
    fprintf(fp, ";\n");
    fprintf(fp, "Expression   \"Kmax_V%d*((", i+1);
    for (j=0; j<vertex[i].k_in; j++) {
    switch (array2[i][j]) {
    case 1:
    fprintf(fp, "(Prot_%d.Value/(Prot_%d.Value+kd_V%d))",array[i][j], array[i][j],array[i][j], array[i][j]);
    break;
    case -1:
    fprintf(fp, "(kd_V%d/(Prot_%d.Value+kd_V%d))",array[i][j], array[i][j],array[i][j], array[i][j]);
    break;
    }
    if (j<vertex[i].k_in-1) {
    fprintf(fp, "+");
    }
    }
    fprintf(fp, ")/%d)\";\n}\n\n", vertex[i].k_in);
    }
    fprintf(fp, "\n}");
    fclose(fp);
    count++;
    }
    } while (count<1);
    }

void saveEcellModelAs2(char filename[200], char discard, struct vert vertex[], int size_i, int array[size_i][size_i], int array2[size_i][size_i], FILE *fp){
    int i, j, count=0;
    char blank[]="";
    do {
    printf("\nSave model as... (C:\\blah\\stuff.thingy):\n");
    scanf("%199[^\t\n]", filename);
    do {
    discard =getchar();
    } while (discard!='\n');
    fp=fopen(filename, "w");
      if (fp==NULL) {
    printf("Filepath error\n");
    } else {
    fprintf(fp, "Stepper ODEStepper(Default_Stepper)\n{\n# no property\n}\n\n");
    fprintf(fp, "System System(/)\n{\nStepperID	Default_Stepper;\n\n");
    for(i=0; i<size_i; i++) {
      if (strcmp(vertex[i].name, blank)!=0){
    fprintf(fp, "Variable Variable(RNA_%s)\n{\nValue	0.0;\n}\n\n", vertex[i].name);
    fprintf(fp, "Variable Variable(Prot_%s)\n{\nValue	0.0;\n}\n\n", vertex[i].name);
      } else {
    fprintf(fp, "Variable Variable(RNA_V%d)\n{\nValue	0.0;\n}\n\n", i+1);
    fprintf(fp, "Variable Variable(Prot_V%d)\n{\nValue	0.0;\n}\n\n", i+1);
    }
    }
    fprintf(fp, "Variable Variable(SIZE)\n{\nValue	1.0;\n}\n\n");
    for(i=0; i<size_i; i++) {
      if (strcmp(vertex[i].name, blank)!=0){
    fprintf(fp, "Process ExpressionFluxProcess(TransL_%s)\n{\n", vertex[i].name);
    fprintf(fp, "kTL	1;\n");
    fprintf(fp, "VariableReferenceList	[TL1 Variable:.:RNA_%s 0] [TL2 Variable:.:Prot_%s 1];\n",vertex[i].name,vertex[i].name);
    fprintf(fp, "Expression	\"kTL*TL1.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(BaseTransC_%s)\n{\n", vertex[i].name);
    fprintf(fp, "VariableReferenceList	[TB Variable:.:RNA_%s 1];\n", vertex[i].name);
    fprintf(fp, "Expression	0.001;\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(RNAdeg_%s)\n{\n", vertex[i].name);
    fprintf(fp, "VariableReferenceList	[Rdeg Variable:.:RNA_%s -1];\n",vertex[i].name);
    fprintf(fp, "Expression	\"Rdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(Protdeg_%s)\n{\n", vertex[i].name);
    fprintf(fp, "VariableReferenceList	[Pdeg Variable:.:Prot_%s -1];\n",vertex[i].name);
    fprintf(fp, "Expression	\"Pdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(TransC_%s)\n{\n", vertex[i].name);
    fprintf(fp, "Kmax_%s 5;\n", vertex[i].name);
      } else {
    fprintf(fp, "Process ExpressionFluxProcess(TransL_V%d)\n{\n", i+1);
    fprintf(fp, "kTL	1;\n");
    fprintf(fp, "VariableReferenceList	[TL1 Variable:.:RNA_V%d 0] [TL2 Variable:.:Prot_V%d 1];\n",i+1,i+1);
    fprintf(fp, "Expression	\"kTL*TL1.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(BaseTransC_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[TB Variable:.:RNA_V%d 1];\n", i+1);
    fprintf(fp, "Expression	0.001;\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(RNAdeg_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[Rdeg Variable:.:RNA_V%d -1];\n",i+1);
    fprintf(fp, "Expression	\"Rdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(Protdeg_V%d)\n{\n", i+1);
    fprintf(fp, "VariableReferenceList	[Pdeg Variable:.:Prot_V%d -1];\n",i+1);
    fprintf(fp, "Expression	\"Pdeg.Value\";\n}\n\n");
    fprintf(fp, "Process ExpressionFluxProcess(TransC_V%d)\n{\n", i+1);
    fprintf(fp, "Kmax_V%d 5;\n", i+1);
    }
    for (j=0; j<vertex[i].k_in; j++) {
      if (strcmp(vertex[((array[i][j])-1)].name, blank)!=0){
    fprintf(fp, "kd_%s 1;\n", vertex[((array[i][j])-1)].name);
    }else {
    fprintf(fp, "kd_V%d 1;\n", array[i][j]);
    }
    }
      if (strcmp(vertex[i].name, blank)!=0){
    fprintf(fp, "VariableReferenceList	[TransC Variable:.:RNA_%s 1]", vertex[i].name);
    } else {
    fprintf(fp, "VariableReferenceList	[TransC Variable:.:RNA_V%d 1]", i+1);
    }
    for (j=0; j<vertex[i].k_in; j++) {
    if (strcmp(vertex[((array[i][j])-1)].name, blank)!=0){
    fprintf(fp, " [Prot_%s Variable:.:Prot_%s 0]", vertex[((array[i][j])-1)].name, vertex[((array[i][j])-1)].name);
    } else {
    fprintf(fp, " [Prot_%d Variable:.:Prot_V%d 0]", array[i][j], array[i][j]);
    }
    }
    fprintf(fp, ";\n");
      if (strcmp(vertex[i].name, blank)!=0){
    fprintf(fp, "Expression   \"Kmax_%s*((", vertex[i].name);
    } else {
    fprintf(fp, "Expression   \"Kmax_V%d*((", i+1);
    }
    for (j=0; j<vertex[i].k_in; j++) {
    switch (array2[i][j]) {
    case 1:
    if (strcmp(vertex[((array[i][j])-1)].name, blank)!=0){
    fprintf(fp, "(Prot_%s.Value/(Prot_%s.Value+kd_%s))",vertex[((array[i][j])-1)].name, vertex[((array[i][j])-1)].name,vertex[((array[i][j])-1)].name);
    break;
    } else {
    fprintf(fp, "(Prot_%d.Value/(Prot_%d.Value+kd_V%d))",array[i][j], array[i][j],array[i][j], array[i][j]);
    break;
    }
    case -1:
    if (strcmp(vertex[((array[i][j])-1)].name, blank)!=0){
    fprintf(fp, "(kd_%s/(Prot_%s.Value+kd_%s))",vertex[((array[i][j])-1)].name, vertex[((array[i][j])-1)].name,vertex[((array[i][j])-1)].name);
    break;
    } else {
    fprintf(fp, "(kd_V%d/(Prot_%d.Value+kd_V%d))",array[i][j], array[i][j],array[i][j], array[i][j]);
    break;
    }
    }
    if (j<vertex[i].k_in-1) {
    fprintf(fp, "+");
    }
    }
    fprintf(fp, ")/%d)\";\n}\n\n", vertex[i].k_in);
    }
    fprintf(fp, "\n}");
    fclose(fp);
    count++;
    }
    } while (count<1);
    }
