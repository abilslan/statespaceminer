#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <CytoParser1.h>
#include <windows.h>

#ifndef SSMINER1_H
#define SSMINER1_H
#include <ssminer1.h>
#endif

#ifndef SSMENUS_H
#define SSMENUS_H
#include <SSmenus.h>
#endif

#define maxv 25
#define minv 3
#define FILE2 "C:\\Documents and Settings\\EcellModel.em"
#define FILE3 "C:\\Documents and Settings\\Topology.net"
#define REP "C:\\Documents and Settings\\Report.txt"

         
/*Start application*/

int main(void) {
    
   /*StateSpace miner initial variables*/    
    int i, j, k, l, m, n, x, y, z, p, q;
    int USlineFlag, UScount, nodeAttributeLines, sourceFlag, targetingFlag, mainmenuFlag, targetingmenuFlag, targetingsubmenuFlag, netmenuFlag, netsubmenuFlag, netviewflag, rulemenuFlag, rulesubmenuFlag, partitionmenuFlag, partitionsubmenuFlag, analysismenuFlag, analysissubmenuFlag, fileFlag, searchFlag, partitionFlag, partitionTypeFlag, childflag, clusters, states, iterations, vertices, arcs, origin, destin, prob, count, remain, components, targetNode, constSetting;
    int min_arcs, max_arcs;
    long sum, sizeOfRules, max_rules, nextState;
    long index_i, index_j, *stateSpace=NULL, **attractorStates=NULL, **attractorStates2=NULL, *basins=NULL, *stateRepresentatives=NULL, *attractorStart=NULL, *attractorLength=NULL;
    int *randPartitionTest, targetnodenumber, **targets=NULL;
    char in, junk;
    short *visited=NULL, *visited2=NULL, **rulesSum=NULL;
    link *sslink;
    float *basinCoherence=NULL, *RandCoherence=NULL, *MaxCoherence=NULL, *StructCoherence=NULL, *cohNeighbours=NULL, *coherence=NULL;
    int *currentStateVector=NULL, *nextStateVector=NULL; 
      
    
    FILE *fp;
    FILE *fp1=NULL;   //Load file//
    FILE *fp2;    //E-Cell model//
    FILE *fp3;    //Net save//
    FILE *fp4;
    FILE *fp5;
    FILE *fp7;
    FILE *fp8;
    FILE *fp9;
    char SS1[] = "C:\\Documents and Settings\\statespace.net";
    char SS2[]="C:\\Documents and Settings\\statespace1.net";
    char saveFilePath[200];


    
   /*Cytoparser variables*/
    int edges;
    FILE *fp6;
    char loadfilepath[200];
    int readflag;
    
    /*Malloc flags for freeing*/
    short visitedFlag=0;
    short visited2Flag=0;
    short stateSpaceFlag=0;
    short coherenceFlag=0;
    short cohNeighboursFlag=0;
    short sslinkFlag=0;
    short basinsFlag=0;
    short stateRepresentativesFlag=0;
    short attractorStartFlag=0;
    short attractorLengthFlag=0;
    short basinCoherenceFlag=0;
    short RandCoherenceFlag=0;
    short StructCoherenceFlag=0;
    short MaxCoherenceFlag=0;   
    short attractorStatesFlag=0;
    short attractorStates2Flag=0;
    short targetsFlag=0;
    short rulesSumFlag=0;     
    short fp1flag=0;
        
    do {
    while ((netsubmenuFlag!=1)&&(netsubmenuFlag!=2)&&(netsubmenuFlag!=7)){
    /*First activate network*/ 
    networkMenu(in, junk, loadfilepath, &nodeAttributeLines, &prob, &arcs, fp1, &netmenuFlag, &netsubmenuFlag, &netviewflag, &fileFlag, &vertices, &max_rules, &min_arcs, &max_arcs, &mainmenuFlag);
    }
    

    
    
    if(netsubmenuFlag!=7){/*exit normally if no net active*/ 
   /*Declare topology arrays - must be before main to prevent reinititation when selecting network menu features*/    
    
    
    if(netsubmenuFlag==1){
    getFileType(in, &fileFlag);
    getFilename(loadfilepath, junk, fp1);
    if(fp1flag==0){
    fp1=fopen(loadfilepath, "r");
    } else {
    freopen(loadfilepath, "r", fp1);
    }
    fp1flag=1;
    if(fileFlag==1){
    getVerticesFromPajek(&vertices, fp1, loadfilepath);                       
    } else if (fileFlag==2){
    getVerticesFromCytoscape(&vertices, fp1, loadfilepath, &nodeAttributeLines);
    }                      
    }
    
        if (netsubmenuFlag==2){                          
        /*Initialise vertex structure array vertex_i and vertex_type fields*/
        /*Initialise topology matrix with 0 values*/
        printf("\nRepressor probability: %d\n", prob);
        printf("\nArcs: %d\n", arcs);
        }
      
    printf("\nVertices: %d\n", vertices);
    struct vert vertex[vertices];     
    short adj[vertices][vertices], topology[vertices][vertices];     
    initShortArray(vertices, vertices, adj);
    initShortArray(vertices, vertices, topology);
    max_rules=pow(2, vertices);        
                                
    

    /*----------------------------------------------------*/      
    /*--------------network menu option routines----------*/      
    /*---------------------------------------------------*/  

    /*load network*/     
    if ((netsubmenuFlag==1)&&(fileFlag==1)){   
                                            
     getTopologyFromPajek(vertices, fp1, loadfilepath, topology);
     
     initVertexName(vertex, vertices);
     for(i=0;i<vertices;i++){
     for(j=0;j<vertices;j++){
     if(topology[i][j]==0){
     adj[i][j]=0;
     }
     else {
     adj[i][j]=1;
     }                              
     }
     }
     netsubmenuFlag=0;
     }
     
    /*load from cytoscape*/    
     if ((netsubmenuFlag==1)&&(fileFlag==2)){     
     initVertexName(vertex, vertices);
       if (checkForMetaCore(fp1, loadfilepath, nodeAttributeLines)==1){
       dealWithUSLines(in, &USlineFlag, &prob);
       FillCytoscapeIDs(vertex, fp1, loadfilepath);
       FillCanonicalNames(vertex, fp1, loadfilepath); 
       getEdgeNumberFromCytoscape(&edges, fp1, loadfilepath);     
       for(i=0;i<vertices;i++){
       printf("\nvertex %2d,  canonicalName: %s", i+1, vertex[i].name);  
       }
       printf("\n");
       getAdjacencyFromMetaCore(vertex, vertices, adj, fp1, loadfilepath);    
       getTopologyFromMetaCore(vertex, vertices, topology, fp1, loadfilepath, &UScount, USlineFlag, prob);
       printf("\n\nedges: %d, unspecified: %d\n", edges, UScount);  
       }
       netsubmenuFlag=0;
       }
         
        if (netsubmenuFlag==2){                      
        rand_vertexType(vertex, vertices);     
        init_vertexType(vertex, vertices, prob);                                           
        do {
        /*Randomise arcs and populate adjacency (unsigned) matrix*/                        
        /*Calculate indegrees by summation of adjacency matrix columns*/
        /*Initialise indegree structure array field*/ 
        /*exclude source vertices by examination of assigned vertex k_in fields with counter*/
        initShortArray(vertices, vertices, adj);         
        initArcs(arcs, vertices, origin, destin, adj);           
        init_vertices(vertex, vertices, vertices, adj);
        initVertexName(vertex, vertices);
        checkForSources(vertex, &sourceFlag, vertices);  
        } while (sourceFlag < vertices);
        findTopology (vertex, vertices, adj, topology);
        netsubmenuFlag=0;
        }
        
         
   init_vertices(vertex, vertices, vertices, topology);
   checkForSources(vertex, &sourceFlag, vertices); 

    /*Declare statespace variables*/                
    /*adjacency matrices */
    int vertexCurrentInputs[vertices][vertices];       
    int bin[vertices];    

    if (currentStateVector==NULL){
    currentStateVector=malloc(vertices*sizeof(int));
    } else {
    realloc(currentStateVector, vertices*sizeof(int));
    }
    
    if (nextStateVector==NULL){
    nextStateVector=malloc(vertices*sizeof(int));
    } else {
    realloc(nextStateVector, vertices*sizeof(int));
    }
    
    if (visited==NULL){
    visited=malloc(max_rules*sizeof(short));
    } else {
    realloc(visited, max_rules*sizeof(short));
    }
    visitedFlag=1;

    if (visited2==NULL){
    visited2=malloc(max_rules*sizeof(short));
    } else {
    realloc(visited2, max_rules*sizeof(short));
    }
    visited2Flag=1;
        
    if (stateSpace==NULL){     
    stateSpace=malloc(max_rules*sizeof(long));
    } else {
    realloc(stateSpace, max_rules*sizeof(long));
    }
    stateSpaceFlag=1;          
    
    int vector_input[vertices][vertices];
    int input_vertices[vertices][vertices];  
    
    if (cohNeighbours==NULL){
    cohNeighbours=malloc(max_rules*sizeof(float));
    } else {
    realloc(cohNeighbours, max_rules*sizeof(float));
    }
    cohNeighboursFlag=1;

    if (coherence==NULL){
    coherence=malloc(max_rules*sizeof(float));
    } else {
    realloc(coherence, max_rules*sizeof(float));
    }
    coherenceFlag=1;
           
    sslink=malloc(max_rules*sizeof(link));
    sslinkFlag=1;           

   /*Initialise input vector and vertices arrrays*/    
   initArray_vertex(vertex, vertices, vertices, vector_input);
   initArray_vertex(vertex, vertices, vertices, input_vertices);    
             
   findNeighbours(vertices, topology, vector_input, input_vertices);     
 
      

    /*-------once networks initialised entry to main menu is OK-----------------------------*/      
    /*--------------main menu option routines-----------------------------------------------*/      
    /*---------------but, need to go back to top if new network declared--------------------*/  
  
                          
    while (mainmenuFlag!=1){

    mainMenu(in, junk, &nodeAttributeLines, &prob, &arcs, &mainmenuFlag, &netmenuFlag, &netsubmenuFlag, &netviewflag, &partitionmenuFlag, &partitionsubmenuFlag, &rulemenuFlag, &rulesubmenuFlag, &analysismenuFlag, &analysissubmenuFlag, &targetingmenuFlag, &targetingsubmenuFlag, &fileFlag, fp1, loadfilepath, &vertices, &max_rules, &min_arcs, &max_arcs); 

   if(netviewflag==1){
   printf("\nTopology Matrix:\n"); 
   printShortArray(vertices, vertices, topology);
   printf("\nSource vertices=%d", (vertices-sourceFlag)); 

   /*Check indegree and rule numer structure array fields*/    
   printf("\nVertex indegrees are :\n\n");    
   for(i=0;i<vertices;i++)  {
   printf("Vertex: %2d  k_in: %d  RuleNumber: %d\n", vertex[i].vertex_i, vertex[i].k_in, vertex[i].rulesNumber);    
   } 
    /*Check input vector and input vertices arrays*/    
    printf("\n\nVertex neighbours:");
    printArray_vertex(vertex, vertices, vertices, input_vertices);    
    netviewflag=0;
   }

    if ((netmenuFlag==1)&&(netsubmenuFlag==5)){
    nameVertices2 (junk, vertex, vertices);
    netsubmenuFlag=0;    
    }
    
    if ((netmenuFlag==1)&&(netsubmenuFlag==6)){
    saveArcsListtoPajekAsShort (saveFilePath, vertex, junk, fp3, vertices, topology, junk);
    netsubmenuFlag=0;    
    }
    /*----------------------------------------------*/      
    /*--------------partition menu routines---------*/      
    /*----------------------------------------------*/  
        
    if ((partitionmenuFlag==1)&&(partitionsubmenuFlag==2)){
    getPartitionType(in, &partitionTypeFlag);
    assignPartition(vertex, vertices, clusters, childflag, topology, partitionTypeFlag, randPartitionTest);
    partitionsubmenuFlag=0;                          
    }
    
    if ((partitionmenuFlag==1)&&(partitionsubmenuFlag==3)){
    savePartitiontoPajekAs (saveFilePath, junk, fp8, vertices, vertex, in);
    partitionsubmenuFlag=0;                          
    }    
    
    if ((partitionmenuFlag==1)&&(partitionsubmenuFlag==4)){
    showPartition (vertex, vertices);
    partitionsubmenuFlag=0;                          
    }       
    if ((partitionmenuFlag==1)&&(partitionsubmenuFlag==5)){
    dismissPartition (vertex, vertices);
    partitionmenuFlag=0;
    partitionsubmenuFlag=0;
    }
    
    /*----------------------------------------------*/      
    /*--------------rule menu routines---------*/      
    /*----------------------------------------------*/      
    
    if ((rulemenuFlag==1)&&(rulesubmenuFlag==1)){

    getRuleNumber(vertex, vertices, &sizeOfRules);
    if(rulesSum!=NULL){
    realloc(rulesSum, vertices*sizeof(short*));
    }else{
      rulesSum = malloc(vertices*sizeof(short*));
      } 
     for(i = 0; i < vertices; i++) {
     rulesSum[i] = malloc(sizeOfRules*sizeof(short));
     }
 
    zeroShortDynArray(vertices, sizeOfRules, rulesSum);
    rulesSumFlag=1;    
    growTruthTables(vertex, vertices, bin, vector_input,rulesSum, input_vertices); 
    assignRules(vertex, vertices, sizeOfRules, rulesSum);
    rulesubmenuFlag=0;   /*turn the flag off so the step doesn't repeat*/  
    }    

    if (rulesubmenuFlag==2){
    useThreshold(in, vertex, vertices);
    useWeighting(in, vertex, vertices);
    rulesubmenuFlag=0;   /*turn the flag off so the step doesn't repeat*/  
    } 
    
    if (rulesubmenuFlag==3){
    showThresholdsAndWeights(vertex, vertices);
    rulesubmenuFlag=0;   /*turn the flag off so the step doesn't repeat*/  
    }    

    if (rulesubmenuFlag==4){
    initThresholdsAndWeights(vertex, vertices);
    rulesubmenuFlag=0;   /*turn the flag off so the step doesn't repeat*/  
    }  
    
    if ((rulemenuFlag==1)&&(rulesubmenuFlag==5)){
    getRuleNumber(vertex, vertices, &sizeOfRules);
    

    rulesSum=initShortDynArray(vertices, sizeOfRules);
    zeroShortDynArray(vertices, sizeOfRules, rulesSum);
    rulesSumFlag=1;   
    randomiseRules(vertex, vertices, sizeOfRules, rulesSum);
    printf("\nActivated random ruleset");
    rulesubmenuFlag=0;   /*turn the flag off so the step doesn't repeat*/  
    }
      
    if ((rulemenuFlag==1)&&(rulesubmenuFlag==6)){
    printShortDynArray_j_i(vertices, sizeOfRules, rulesSum);
    rulesubmenuFlag=0;   /*turn the flag off so the step doesn't repeat*/  
    }     



    /*----------------------------------------------*/      
    /*--------------analysis menu routines---------*/      
    /*----------------------------------------------*/   

    if ((analysismenuFlag==1)&&(analysissubmenuFlag==1)){
    
    for (i=0; i<vertices; i++) {
    currentStateVector[i]=0;
    nextStateVector[i]=0;    
    }       
      
    initArray_vertex(vertex, vertices, vertices, vertexCurrentInputs);   /*zero vertexCurrentInputs array*/    
    printf("\n\nsizeofStateSpace: %d", max_rules); /*Check sizeofStateSpace variable*/
    printf("\nCalculating - please wait...");            
    
    for (i=0; i<max_rules; i++) {
    stateSpace[i]=0;
    }      

    /*Get statespace*/     
       for (i=0; i<max_rules; i++) {       
       m=0;  
       m=m+i;       
       nextState=0;         
       decToBin(m, vertices, currentStateVector);
                for (k=0; k<vertices; k++) {
                  x=0;
                  y=0;
                  sum=0;
                   do {
                       if ((x+1)==input_vertices[k][y]) {
                          vertexCurrentInputs[k][y]=currentStateVector[x];
                          x++;
                          y++;
                          } else {
                                 x++;
                                 } 
                                 } while (x<vertices);
                                 
                          for (n=1; n<=vertex[k].k_in; n++) {
                            l=(vertex[k].k_in-n);
                            z = vertexCurrentInputs[k][n-1]*pow(2, l);
                            sum = sum + z;    // sum it up
                              }
                              nextStateVector[k]=rulesSum[k][sum];
                              p=(vertices-(k+1));
                              q = nextStateVector[k]*pow(2, (p));
                              nextState=nextState+q;
                              }
                              stateSpace[i]=nextState; 
    
    
    analysissubmenuFlag=0;   /*turn the flag off so the step doesn't repeat*/  
    }
    saveArcsListtoPajekAs (saveFilePath, junk, fp4, max_rules, stateSpace, in);         
    } 
    
    if ((analysismenuFlag==1)&&(analysissubmenuFlag==2)){        
  
    
    initDFS(max_rules, sslink, visited);         
    initList(max_rules, sslink, stateSpace);      
    DFS(max_rules, visited, sslink, &components); 
    printf("\n\nNo. of basins of attraction: %4d", components);
    
    if(basins!=NULL){                 
    basins=realloc(basins, components*sizeof(long));
    } else {
    basins=malloc(components*sizeof(long));
    }
    basinsFlag=1;

    if(stateRepresentatives!=NULL){                 
    stateRepresentatives=realloc(stateRepresentatives, components*sizeof(long));
    } else {
    stateRepresentatives=malloc(components*sizeof(long));
    }
    stateRepresentativesFlag=1;  
      
    intInitLong1dAray(components, basins);
    intInitLong1dAray(components, stateRepresentatives); 
    
    count =1;
    for (i=0; i<max_rules; i++) {
    if (visited[i]==count) {
    stateRepresentatives[count-1]=i;
    count = count+1;  
    }
    }    
    getBasinSize(max_rules, components, visited, basins);     
    printf("\n\nBasin of attraction weights:");
    for (i=0; i<components; i++){
    printf("\nBasin %d: %d  Repesentative: %d", i+1, basins[i], stateRepresentatives[i]);
    } 
    
    printf("\n");
    
    if(attractorStart!=NULL){                 
    attractorStart=realloc(attractorStart, components*sizeof(long));
    } else {
    attractorStart=malloc(components*sizeof(long));
    }
    attractorStartFlag=1;
    
    if(attractorLength!=NULL){                 
    attractorLength=realloc(attractorLength, components*sizeof(long));
    } else {
    attractorLength=malloc(components*sizeof(long));
    }
    attractorLengthFlag=1;
            
    intInitLong1dAray(components, attractorStart);
    intInitLong1dAray(components, attractorLength);
    longInitInt1dAray(max_rules, visited2);
    setAttractorStart(components, max_rules, stateRepresentatives, stateSpace, visited2, attractorStart);
          
    longInitInt1dAray(max_rules, visited2);           
    findAttractorLength(components, max_rules, attractorStart, stateSpace, visited2, attractorLength);
   
    for (i=0; i<components; i++){
    printf("\nBasin %d: Attactor length:%d", i+1, attractorLength[i]);
    }
    printf("\n"); 
    
    if(attractorStates!=NULL){                 
    attractorStates=realloc(attractorStates, components*sizeof(long));
    } else {
    attractorStates=malloc(components*sizeof(long));
    }    
    for (i=0; i<components; i++){
    attractorStates[i]=malloc(attractorLength[i]*sizeof(long));
    }

    if(attractorStates2!=NULL){                 
    attractorStates2=realloc(attractorStates2, components*sizeof(long));
    } else {
    attractorStates2=malloc(components*sizeof(long));
    }    
    for (i=0; i<components; i++){
    attractorStates2[i]=malloc(attractorLength[i]*sizeof(long));
    }


    findAttractorStates(components, max_rules, attractorStart, stateSpace, attractorLength, attractorStates);
    
    printf("\n");     

    showAttractorVector(components, vertices, attractorLength, attractorStates, bin);
    makePartitionFromAttractorVector(saveFilePath, junk, fp9, in,components, vertices, attractorLength, attractorStates, bin);
    analysissubmenuFlag=0;
    }
    
    
    if ((analysismenuFlag==1)&&(analysissubmenuFlag==3)){                                                         
                                             
                                                               
    initFloat1dAray(max_rules, cohNeighbours);
    initFloat1dAray(max_rules, coherence);
          
    for (i=0; i<max_rules; i++){
    decToBin(i, vertices, bin);
    for (j=0; j<vertices; j++){
    findHammingNeighbour(j, vertices, bin);
    bin2dec(vertices, bin, &sum);
    compareBasins(i, sum, max_rules, visited, cohNeighbours);
    findHammingNeighbour(j, vertices, bin);
    }
    }  
     
    

    getStateCoherence(max_rules, vertices, cohNeighbours, coherence);
    if (basinCoherence!=NULL){
    realloc(basinCoherence, components*sizeof(long));
    } else {
    basinCoherence=malloc(components*sizeof(long));
    }
    basinCoherenceFlag=1;
    
    if (RandCoherence!=NULL){
    realloc(RandCoherence, components*sizeof(long));
    } else {
    RandCoherence=malloc(components*sizeof(long));
    }
    RandCoherenceFlag=1;
    
    if (MaxCoherence!=NULL){
    realloc(MaxCoherence, components*sizeof(long));
    } else {
    MaxCoherence=malloc(components*sizeof(long));
    }
    MaxCoherenceFlag=1;
    
    if (StructCoherence!=NULL){
    realloc(StructCoherence, components*sizeof(long));
    } else {
    StructCoherence=malloc(components*sizeof(long));
    }
    StructCoherenceFlag=1;
        
    intInitFloat1dAray(components, basinCoherence);
    intInitFloat1dAray(components, RandCoherence);    
    intInitFloat1dAray(components, MaxCoherence);
    intInitFloat1dAray(components, StructCoherence);  
                
    getBasinCoherence(max_rules, visited, coherence, components, basinCoherence, basins);
    getRandCoherence(components, vertices, basins, RandCoherence); 
    getMaxCoherence(components, vertices, basins, MaxCoherence);  
    getStructCoherence(components, basinCoherence, RandCoherence, MaxCoherence, StructCoherence); 
    
         
    for (i=0; i<components; i++){
    printf("Basin %d: Coherence: %f", i+1, basinCoherence[i]);        
    printf("\n");  
    } 
    for (i=0; i<components; i++){
    printf("Basin %d: Structural Coherence: %f", i+1, StructCoherence[i]);        
    printf("\n");  
    }     
    analysissubmenuFlag=0;    
    }
    
    if ((analysismenuFlag==1)&&(analysissubmenuFlag==4)){
    saveEcellModelAs(saveFilePath, junk, vertex, vertices, input_vertices, vector_input, fp2);
    analysissubmenuFlag=0;  
    }                                    
    
    /*----------------------------------------------*/      
    /*--------------Targeting menu routines---------*/      
    /*----------------------------------------------*/   
    
    if ((targetingmenuFlag==1)&&(targetingsubmenuFlag==1)){
    
                      
    getNodedegrees(in, vertices, vertex);                                                           
    getNumberTargetNodes(vertices, &targetnodenumber);                      
    
    if (targets!=NULL){
    realloc(targets, 2*sizeof(int));
    } else  {    
    targets=malloc(2*sizeof(int));
    }
    for(i=0;i<2;i++){
    targets[i]=malloc(targetnodenumber*sizeof(int));
    }    

       /*Take and validate target nodes*/     
    getTargetNodes(in, vertices, 0, targetnodenumber, targets);
   
    for (i=0;i<targetnodenumber;i++){
    printf("\nTarget vertex %d, Node %d, Setting %d", i+1, targets[0][i], targets[1][i]);
    }  
       /*Mutate rulesSum array*/
    targetVertex(vertex, vertices, sizeOfRules, rulesSum, targets, targetnodenumber);
    targetingsubmenuFlag=0;                                                        
    } 

    if (netsubmenuFlag==3){       /*If net dismissed*/


  fclose(fp1);
    
  /*Clear all menu flags*/
  netmenuFlag=0, targetingmenuFlag=0, rulemenuFlag=0, partitionmenuFlag=0, analysismenuFlag=0;
  netsubmenuFlag=0, targetingsubmenuFlag=0, rulesubmenuFlag=0, partitionsubmenuFlag=0, analysissubmenuFlag=0; 
  fileFlag=0, netviewflag=0; 
  }/*-------end netmenu dismiss option IF---------*/

}    /*-------end netmenu exit IF---------*/

     netsubmenuFlag=0;                                                            
}    /*-------end main menu while---------*/




printf("\nNetwork dismissed! Choose another load option or (7) to exit");   
} while (netmenuFlag!=1); /*-------Return to net menu if net dismissed---------*/

/*-------NORMAL EXIT---------*/
/*-------Free all assigned dynamic memory---------*/
  if (visited!=NULL){
  free(visited);
  visited=NULL;
  }
  
  if (visited2!=NULL){
  free(visited2);
  visited2=NULL;
  }
  
  if(stateSpace!=NULL){
  free(stateSpace);
  stateSpace=NULL;
  }
  
  if (coherence!=NULL){
  free(coherence);
  coherence=NULL;
  }
  
  if (cohNeighbours!=NULL){
  free(cohNeighbours);
  cohNeighbours=NULL;
  }
  
  if (sslink!=NULL){
  free(sslink);
  }
  
  if (basins!=NULL){
  free(basins);
  basins=NULL;
  }
  
  if (stateRepresentatives!=NULL){
  free(stateRepresentatives);
  stateRepresentatives=NULL;
  }
  
  if (attractorStart!=NULL){
  free(attractorStart);
  attractorStart=NULL;
  }
  
  if (attractorLength!=NULL){
  free(attractorLength);
  attractorLength=NULL;
  }
  
  if (basinCoherence!=NULL){
  free(basinCoherence);
  basinCoherence=NULL;
  }
  
  if (RandCoherence!=NULL){
  free(RandCoherence);
  RandCoherence=NULL;
  }
  
  if (StructCoherence!=NULL){
  free(StructCoherence);
  StructCoherence=NULL;
  }
  
  if (MaxCoherence!=NULL){
  free(MaxCoherence);
  MaxCoherence=NULL;
  }
  
  if (attractorStates!=NULL){
  for (i=0; i<components; i++){
  free(attractorStates[i]);
  }
  free(attractorStates);
  attractorStates=NULL;
  }
  
  if (attractorStates2!=NULL){
  for (i=0; i<components; i++){
  free(attractorStates2[i]);
  }
  free(attractorStates2);
  attractorStates2=NULL;
  }
  
  if (targets!=NULL){
  for(i=0;i<2;i++){
  free(targets[i]);
  }
  free(targets);
  targets=NULL;
  }

  if (rulesSum!=NULL){
  for(i=0;i<vertices;i++){
  free(rulesSum[i]);
  }
  free(rulesSum);
  rulesSum=NULL;
  }
return 0;
}         

