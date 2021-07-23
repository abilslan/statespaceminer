#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <math.h>

#ifndef SSMINER1_H
#define SSMINER1_H
#include <ssminer1.h>
#endif

#define maxv 25
#define minv 3

void networkMenu(char response, char discard, char filename[200], int *Attcount, int *pval, int *lines, FILE *fp, int *Nflag, int *Nsubflag, int *NVflag, int*Fflag, int *verts, long *mrules, int *minA, int *maxA, int *Mflag) {
   int count=0, temp, Vcount;
   int i,j;
   
   printf("\nNetwork menu:\n");
   printf("1. Load network\n");
   printf("2. Randomise network\n"); 
   printf("3. Dismiss network\n");
   printf("4. Show network info\n");   
   printf("5. Name vertices\n");
   printf("6. Save network\n");   
   printf("7. Quit network menu\n");                     
   do {
   printf("\nSelect submenu (1-7)_");   
   fputs("", stdout);
   fflush(stdout);
   } while (!mygeti(&temp)||(1>temp)||(temp>7) );
   if (temp==1){
      if (*Nflag==1){
      printf("Please dismiss existing network!");
      } else {
      *Nsubflag=1;
      printf("Loading\n");

      *Nflag=1;
      *Mflag=0;

      }   
   } else if (temp==2){
      if (*Nflag==1){
      printf("Please dismiss existing network!");
      } else {
       *Nsubflag=2;
      printf("Randomising\n");
       do {
       printf("\nEnter number of vertices (Min %d, Max %d)_:", minv, maxv); 
       fputs("", stdout);
       fflush(stdout);
       } while (!mygeti(&Vcount)||(minv>Vcount)||(Vcount>maxv) );  
       *Nflag=1;
       *Mflag=0;
       *verts=Vcount;
       *mrules=pow(2, Vcount);
       *minA=Vcount;
       *maxA=Vcount*(Vcount-1); 
       do {
       fputs("\nEnter repressor probability (0-100)_: ", stdout);
       fflush(stdout);
       } while (!mygeti(&temp)||(0>temp)||(temp>100) ); 
       *pval=temp;
       do {
       printf("\nEnter number of arcs (min %d, max %d)", *minA, *maxA);
       fputs("_: ", stdout);
       fflush(stdout);
       } while (!mygeti(&temp)||(temp<*minA)||(temp>*maxA));
       *lines=temp;
       }                 
   } else if (temp==3){
       *Nsubflag=3;
       if (*Nflag!=1){
       printf("No network active! Please choose a network option.\n");
       } else {
       *Nflag=0;
       *Mflag=1;
       }
   } else if (temp==4){
       if (*Nflag!=1){
       printf("No network active! Please choose a network option.\n");
       } else {
       *NVflag=1;
       }         
       }  else if (temp==5){
       if (*Nflag!=1){
       printf("No network active! Please choose a network option.\n");
       } else {
       *Nflag=1;
       *Nsubflag=5;
       }         
   } else if (temp==6){
       if (*Nflag!=1){
       printf("No network active! Please choose a network option.\n");
       } else {
       *Nflag=1;
       *Nsubflag=6;
       }         
   } else if (temp==7){
       if(*Nflag!=1){
       *Nflag=1;
       *Mflag=1;
       *Nsubflag=7;
       }
       }  
   }
   
void partitionMenu(char response, int *Pflag, int *Psubflag) {
   int count=0, temp;
   printf("\nPartition menu:\n");
   printf("1. Load partition\n");
   printf("2. Create partition\n"); 
   printf("3. Save partition\n");
   printf("4. Show active partition\n");
   printf("5. Dismiss partition\n");  
   printf("6. Quit partition menu\n");           
   do {
   printf("\nSelect submenu (1-5)_");   
   fputs("", stdout);
   fflush(stdout);
   } while (!mygeti(&temp)||(1>temp)||(temp>6) );
   if (temp==2){
      if (*Pflag==1){
      do {
      printf("A partition is already active. Reassign? (Y/N)_");
      scanf(" %c", &response);
      fflush(stdin);
      if (response=='y'||response=='Y'){
      count=1;
      *Pflag=1;
      *Psubflag=2;      
      } else if (response=='n'||response=='N'){
      count=1;
      *Pflag=1;
      *Psubflag=0;
      } else {
      count = 0;
      }
      } while (count <1);
      } else {
   *Pflag=1;
   *Psubflag=2;
      }
   } else if (temp==3){
     if (*Pflag!=1){
     printf("No partition active! Assign a partition before saving.");
     *Psubflag=0;
     } else {     
     *Pflag=1;
     *Psubflag=3;
     }
   } else if (temp==4){
     if (*Pflag!=1){
     printf("No partition active! Assign a partition before saving.");
     *Psubflag=0;
     } else {     
     *Pflag=1;
     *Psubflag=4;
     }
     } else if (temp==5){
     if (*Pflag!=1){
     printf("No partition active to dismiss!");
     *Psubflag=0;
     } else {     
     *Pflag=1;
     *Psubflag=5;
     }  
     }   
   }

void ruleMenu(char response, int *Rflag, int *Rsubflag) {
   int count=0, temp;
   printf("\nRule menu:\n");
   printf("1. Activate threshold rules\n");
   printf("2. Change thresholds and weights\n");   
   printf("3. Show thresholds and weights\n");
   printf("4. Restore default thresholds and weights\n");       
   printf("5. Randomise rules\n"); 
   printf("6. Show rule table\n");
   printf("7. Quit rule menu\n");              
   do {
   printf("\nSelect submenu (1-7)_");   
   fputs("", stdout);
   fflush(stdout);
   } while (!mygeti(&temp)||(1>temp)||(temp>7) );
   
   if (temp==1){
      if (*Rflag==1){
      do {
      printf("A ruleset is already active. Reassign? (Y/N)_");
      scanf(" %c", &response);
      fflush(stdin);
      if (response=='y'||response=='Y'){
      count=1;
      *Rflag=1;
      *Rsubflag=1;      
      } else if (response=='n'||response=='N'){
      count=1;
      *Rflag=1;
      *Rsubflag=0;
      } else {
      count = 0;
      }
      } while (count <1);
      } else {
   *Rflag=1;
   *Rsubflag=1;
   }
   } else if (temp==2){
   *Rsubflag=2;
   } else if (temp==3){
   *Rsubflag=3;
   } else if (temp==4){
   *Rsubflag=4;
   } else if (temp==5){
      if (*Rflag==1){
      do {
      printf("A ruleset is already active. Reassign? (Y/N)_");
      scanf(" %c", &response);
      fflush(stdin);
      if (response=='y'||response=='Y'){
      count=1;
      *Rflag=1;
      *Rsubflag=5;      
      } else if (response=='n'||response=='N'){
      count=1;
      *Rflag=1;
      *Rsubflag=0;
      } else {
      count = 0;
      }
      } while (count <1);
      } else {
   *Rflag=1;
   *Rsubflag=5;
   }
   } else if (temp==6){
     if (*Rflag!=1){
     printf("No ruleset active! Please assign rules.");
     *Rsubflag=0;
     } else {  
   *Rflag=1;
   *Rsubflag=6;
   }
   }   
   }

void analysisMenu(char response, int *Aflag, int *Asubflag, int *Rflag) {
   int count=0, temp;
   printf("\nAnalysis menu:\n");
   printf("1. Calculate statespace\n");
   printf("2. Find attractors\n"); 
   printf("3. Find statespace coherence\n");
   printf("4. Save E-Cell model\n");
   printf("5. Quit analysis menu\n");              
   do {
   printf("\nSelect submenu (1-5)_");   
   fputs("", stdout);
   fflush(stdout);
   } while (!mygeti(&temp)||(1>temp)||(temp>5) );
   if (temp==1){
        if (*Rflag!=1){
        printf("No ruleset active! Please assign rules.");
        *Asubflag=0;
        } else { 
   *Aflag=1;
   *Asubflag=1;
   }
   } else if(temp==2){
        if (*Rflag!=1){
        printf("No ruleset active! Please assign rules.");
        *Asubflag=0;
        } else if (*Aflag!=1){
        printf("Please calculate statespace first.");
        *Asubflag=0;        
        } else {                
   *Aflag=1;
   *Asubflag=2;
   }
   } else if(temp==3){
        if (*Rflag!=1){
        printf("No ruleset active! Please assign rules.");
        *Asubflag=0;
        } else if (*Aflag!=1){
        printf("Please calculate statespace first.");
        *Asubflag=0;        
        } else {                
   *Aflag=1;
   *Asubflag=3;
   }
   } else if(temp==4){                
   *Aflag=1;
   *Asubflag=4;
   }   
   }

void targetingMenu(char response, int *Tflag, int *Tsubflag, int *Rflag) {
   int count=0, temp;
   printf("\nTargeting menu:\n");
   printf("1. Target nodes\n");
   printf("2. Restore nodes\n"); 
   printf("3. Quit targeting menu\n");           
   do {
   printf("\nSelect submenu (1-3)_");   
   fputs("", stdout);
   fflush(stdout);
   } while (!mygeti(&temp)||(1>temp)||(temp>3) );
   if (temp==1){
        if (*Rflag!=1){
        printf("No ruleset active! Please assign rules.");
        *Tsubflag=0;
        } else { 
   *Tflag=1;
   *Tsubflag=1;
   }
   }
   }

void mainMenu(char response, char discard, int *Attcount, int *pval, int *lines, int *Mflag, int *Nflag, int *Nsubflag, int *NVflag, int *Pflag, int *Psubflag, int *Rflag, int *Rsubflag, int *Aflag, int *Asubflag, int *Tflag, int *Tsubflag, int *Fflag, FILE *fp, char filename[200], int *verts, long *mrules, int *minA, int *maxA) {
   int count=0, temp;
   printf("\n\nMain menu:\n");
   printf("1. Network menu\n");
   printf("2. Partition menu\n"); 
   printf("3. Rules menu\n");
   printf("4. Analysis menu\n");
   printf("5. Targeting menu\n");
   printf("6. Quit StateSpace Miner\n");              
   do {
   printf("\nSelect submenu (1-6)_");   
   fputs("", stdout);
   fflush(stdout);
   } while (!mygeti(&temp)||(1>temp)||(temp>6) );
   if (temp==1){
   networkMenu(response, discard, filename, Attcount, pval, lines, fp, Nflag, Nsubflag, NVflag, Fflag, verts, mrules, minA, maxA, Mflag);
   } else if (temp==2){
        if (*Nflag!=1){
        printf("No network active! Please choose a network option.\n");
        mainMenu(response, discard, Attcount, pval, lines, Mflag, Nflag, Nsubflag, NVflag, Pflag, Psubflag, Rflag, Rsubflag, Aflag, Asubflag, Tflag, Tsubflag, Fflag, fp, filename, verts, mrules, minA, maxA);
        } else {
        partitionMenu(response, Pflag, Psubflag);
        }
   } else if (temp==3){
        if (*Nflag!=1){
        printf("No network active! Please choose a network option.\n");
        mainMenu(response, discard, Attcount, pval, lines, Mflag, Nflag, Nsubflag, NVflag, Pflag, Psubflag, Rflag, Rsubflag, Aflag, Asubflag, Tflag, Tsubflag, Fflag, fp, filename, verts, mrules, minA, maxA);
        } else {
        ruleMenu(response, Rflag, Rsubflag);
        }
   } else if (temp==4){
        if (*Nflag!=1){
        printf("No network active! Please choose a network option.\n");
        mainMenu(response, discard, Attcount, pval, lines, Mflag, Nflag, Nsubflag, NVflag, Pflag, Psubflag, Rflag, Rsubflag, Aflag, Asubflag, Tflag, Tsubflag, Fflag, fp, filename, verts, mrules, minA, maxA);
        } else if (*Rflag!=1){
        printf("No rules active! Please choose a rule option.\n");
        mainMenu(response, discard, Attcount, pval, lines, Mflag, Nflag, Nsubflag, NVflag, Pflag, Psubflag, Rflag, Rsubflag, Aflag, Asubflag, Tflag, Tsubflag, Fflag, fp, filename, verts, mrules, minA, maxA);   
        } else {
        analysisMenu(response, Aflag, Asubflag, Rflag);
        }
   }  else if (temp==5){
        if (*Nflag!=1){
        printf("No network active! Please choose a network option.\n");
        mainMenu(response, discard, Attcount, pval, lines, Mflag, Nflag, Nsubflag, NVflag, Pflag, Psubflag, Rflag, Rsubflag, Aflag, Asubflag, Tflag, Tsubflag, Fflag, fp, filename, verts, mrules, minA, maxA);
        } else if (*Rflag!=1){
        printf("No rules active! Please choose a rule option.\n");
        mainMenu(response, discard, Attcount, pval, lines, Mflag, Nflag, Nsubflag, NVflag, Pflag, Psubflag, Rflag, Rsubflag, Aflag, Asubflag, Tflag, Tsubflag, Fflag, fp, filename, verts, mrules, minA, maxA);    
        } else {
        targetingMenu(response, Tflag, Tsubflag, Rflag);
        }
   } else if (temp==6){
   *Mflag=1;
   }
   }

