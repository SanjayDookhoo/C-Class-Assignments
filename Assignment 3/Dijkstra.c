/*
Full Name: Sanjay Thistle Kashmir Dookhoo
Student ID: 814000842
E-mail: sanjaydookhoo@msn.com
Course Code: Comp2000
*/

//in vertex of graph, first vertex stored in 1
//default parents are set to -1 therefore the vertex names allowed for understanding sake should be any num >=0
/*
Format of input file:
    <number of vertices>
    <list of vertices seperated by white space>
    <vertex 1> <num of edges of vertex 1> (<id of vertex from edges> <weight of that vertext>)* <num of edges>
    .
    .
    .
    .
    <vertex n> ....

*/

//default parent is set to 0, will it work for a vertex of 0 existing ?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxVertices 20
#define Infinity 9999//let 9999 represent infinity
#define MaxFormat 50
#define UnchangedDigits 0//the digits did not change yet, used to indicate an initial value must be placed first before any comparison
#define DefaultParent -1

FILE *fp;


typedef struct gEdge{
    int child, weight;
    struct gEdge *nextEdge;
}GEdge,*GEdgePtr;

GEdgePtr newGEdge(int c,int w){
    GEdgePtr p=(GEdgePtr)malloc(sizeof(GEdge));
    p->child=c;
    p->weight=w;
    p->nextEdge=NULL;

    return p;
}

typedef struct{
    int id;
    GEdgePtr firstEdge;

    //needed for depth first trav
    char colour;
    int parent,cost,discover,finish,inDegree;
}GVertex;

GVertex newGVertex(int id){
    GVertex temp;
    temp.id=id;
    temp.firstEdge=NULL;

    return temp;
}

typedef struct graph{
    int numV;
    GVertex vertex[MaxVertices +1];

    //used for formatting in table output
    int digitsV;//amount of digits of greatest vertext stored in graph (done for maintaining a consistent and correct column size for weight and dist matrix)
    int digitsE;//amount of digits of greatest weight edge stored in graph (done for maintaining a consistent and correct column size for weight and dist matrix)
    int digitsC;//amount of digits of greatest cost of vertex stored in graph (done for maintaining a consistent and correct column size for weight and dist matrix)
}*Graph;

Graph newGraph(int n){
    if(n>MaxVertices){
        printf("\nToo big. Only %d vertices allowed.\n",MaxVertices);
        exit(1);
    }
    Graph p=(Graph)malloc(sizeof(struct graph));
    p->numV=n;

    //the digits did not change yet, used to indicate an initial value must be placed first before any comparison
    p->digitsV=UnchangedDigits;
    p->digitsE=UnchangedDigits;
    p->digitsC=UnchangedDigits;

    return p;
}

void addEdge(int X, int Y,int weight,Graph G){
    int j,k;

    for(j=1;j<=G->numV;j++) if(X==G->vertex[j].id)break;

    for(k=1;k<=G->numV;k++) if(Y==G->vertex[k].id)break;

    if(j>G->numV||k>G->numV){
        printf("No such edge: %d->%d",X,Y);
        exit(1);
    }

    GEdgePtr ep=newGEdge(k,weight);

    GEdgePtr prev,curr;
    prev=curr=G->vertex[j].firstEdge;

    while(curr!=NULL && Y>(G->vertex[curr->child].id)){
        prev=curr;
        curr=curr->nextEdge;
    }



    if(prev==curr){
        ep->nextEdge=G->vertex[j].firstEdge;
        G->vertex[j].firstEdge=ep;
    }else{
        ep->nextEdge=curr;
        prev->nextEdge=ep;
    }
}

int calcDigits(int x){
    int digits=0;
    while(x!=0){
        digits++;
        x/=10;
    }

    return digits;
}

void buildGraph(FILE *in,Graph G){
    int j,k,numEdges,weight;
    int nodeID,adjID;

    for(j=1;j<=G->numV;j++){
        G->vertex[j]=newGVertex(0);//create a vertex node
        fscanf(in,"%d", &G->vertex[j].id);

        //digitsV set
        if(G->digitsV==UnchangedDigits){
            G->digitsV=calcDigits(G->vertex[j].id);
        }else{
            if(calcDigits(G->vertex[j].id)>G->digitsV) G->digitsV=calcDigits(G->vertex[j].id);
        }
    }
    for(j=1;j<=G->numV;j++){
        fscanf(in,"%d %d",&nodeID,&numEdges);
        for(k=1;k<=numEdges;k++){
            fscanf(in,"%d %d",&adjID,&weight);

            //digitsE set
            if(G->digitsE==UnchangedDigits){
                G->digitsE=calcDigits(weight);
            }else{
                if (calcDigits(weight)>G->digitsE) G->digitsE=calcDigits(weight);
            }

            addEdge(nodeID,adjID,weight,G);
        }
    }

}

void initSingleSource(Graph G, int s){
    int j;
    for(j=1;j<=G->numV;j++){
        G->vertex[j].cost=Infinity;
        G->vertex[j].parent=DefaultParent;
    }
    G->vertex[s].cost=0;
}

void printGraph(Graph G){
    int j;
    int first =1;
    for(j=1;j<=G->numV;j++){
        printf("%d: ", G->vertex[j].id);
        GEdgePtr p=G->vertex[j].firstEdge;
        first=1;
        while(p!=NULL){
            if(first!=1){
                printf("-->");
            }else{
                first=0;
            }
            printf("%d-->%d ",G->vertex[p->child].id,p->weight);
            p=p->nextEdge;
        }
        printf("\n");
    }
}
//bellman ford

void relax(Graph G,int u, int v, int weight){
    if(G->vertex[u].cost+weight<G->vertex[v].cost){
        G->vertex[v].cost=G->vertex[u].cost+weight;
        G->vertex[v].parent=u;
    }
}

void followPath(Graph G,int c){
    //printf("\n\nthe parent is: %d\n\n",c);
    if(c!=-1){
        followPath(G,G->vertex[c].parent);
        if(G->vertex[c].parent!=0)printf("-->");
        printf("%d ",G->vertex[c].id);

    }
}

void printCostPath(Graph G,int s){
    int j;

    for(j=1;j<=G->numV;j++){
        if(j!=s){
            printf("Cost to %d: %d, Path: ",G->vertex[j].id,G->vertex[j].cost);
            followPath(G,j);
            printf("\n");
        }
    }
}


void calcDigitsC(Graph G){//set all digitsC in all vertex to Unchanged
    int j;
    for(j=1;j<=G->numV;j++){
        if(j==1){
            if(G->vertex[j].cost==Infinity) G->digitsC=calcDigits(1);//calc digit of 1 since its abotu the same size as the char 'I'
            else G->digitsC=calcDigits(G->vertex[j].cost);
        }else{
            if(G->vertex[j].cost==Infinity){
                if(calcDigits(1)>G->digitsC) G->digitsC=calcDigits(1);
            }else{
                if(calcDigits(G->vertex[j].cost)>G->digitsC) G->digitsC=calcDigits(G->vertex[j].cost);
            }
        }
    }
}

void dist(Graph G,int k){
    calcDigitsC(G);

    int i,j;
    int space=max(G->digitsV,G->digitsC)+2;//the max is found between the vertex and cost because the graph will include both of them
    char SDigits[MaxFormat];
    char SData[MaxFormat];
    char xHeadingFormat[MaxFormat]="";
    char yHeadingFormat[MaxFormat]="";
    char dataFormat[MaxFormat]="";
    GEdgePtr curr;

    strcat(xHeadingFormat,"%-");
    itoa(space,SDigits,10);
    strcat(xHeadingFormat,SDigits);
    strcat(xHeadingFormat,"d");

    strcat(yHeadingFormat,"%-10s");//the greatest of the y headers is "Distance: "

    strcat(dataFormat,"%-");
    itoa(space,SDigits,10);
    strcat(dataFormat,SDigits);
    strcat(dataFormat,"s");

    printf("Dist(%d) is",k);

    printf("\n");
    printf(yHeadingFormat,"ID: ");
    for(i=1;i<=G->numV;i++){
        printf(xHeadingFormat,G->vertex[i].id);
    }
    printf("\n");
    printf(yHeadingFormat,"Distance: ");
    for(i=1;i<=G->numV;i++){
        if(G->vertex[i].cost==Infinity) printf(dataFormat,"I");
        else {
            itoa(G->vertex[i].cost,SDigits,10);
            printf(dataFormat,SDigits);
        }
    }
    printf("\n");
    printf(yHeadingFormat,"Parent: ");
    for(i=1;i<=G->numV;i++){
        printf(xHeadingFormat,G->vertex[G->vertex[i].parent]);
    }
    printf("\n\n");
}

int BellmanFord(Graph G, int s){
    int j, u,v,pass;
    initSingleSource(G,s);
    for(pass=1; pass<G->numV;pass++){
        for(j=1; j<=G->numV;j++){
            if(G->vertex[j].cost!=Infinity){
                GEdgePtr p=G->vertex[j].firstEdge;
                while(p!=NULL){
                    relax(G,j,p->child,p->weight);
                    p=p->nextEdge;
                }
            }
        }
        dist(G,pass);
    }
    //make final pass to check for negative weight cycles
    for(j=1;j<=G->numV;j++){
        GEdgePtr p=G->vertex[j].firstEdge;
        while(p!=NULL){
            if(G->vertex[j].cost+p->weight<G->vertex[p->child].cost){
                printf("\nNo solution: graph has negative weight cycle\n");
                return 0;
            }
            p=p->nextEdge;
        }
    }
    printCostPath(G,s);

    //bellmanford needs to be completed because a cost can become less than it was before
    for(j=1;j<=G->numV;j++){
        if(G->digitsC==UnchangedDigits){
            G->digitsC=calcDigits(G->vertex[j].cost);
        }else{
            if(calcDigits(G->vertex[j].cost)>G->digitsC) G->digitsC=calcDigits(G->vertex[j].cost);
        }
    }

    return 1;
}

void adjustXPos(Graph G,int arr[],int QPosNext, int QPosMax){// using bubble sort delimited  by QPosNext and QPosMax
    int temp,x,y;

    for(x=QPosNext;x<QPosMax;x++){
        for(y=QPosNext;y<QPosMax;y++){
            if(G->vertex[arr[y]].cost > G->vertex[arr[y+1]].cost){//if to swap with the adjacent array
                temp=arr[y+1];
                arr[y+1]=arr[y];
                arr[y]=temp;
            }
        }
    }

}

void Dijkstra(Graph G,int s){
    int QMaxPos=G->numV;
    int QPos=1;
    int QPosTemp=2;
    int i,j,p,k;
    int Q[G->numV+1];//references the vertex as it is processed in the priority queue
    GEdgePtr curr;

    initSingleSource(G,s);

    //add all vertices of G to Q where the source index is at the head and everything else is in order
    Q[1]=s;
    for(i=1;i<=G->numV;i++){
        if(i!=s) Q[QPosTemp++]=i;
    }

    while(QPos<=QMaxPos){
        p=Q[QPos];
        //printf("\np: %d\n",p);
        if(G->vertex[p].cost==Infinity) break;

        curr=G->vertex[p].firstEdge;
        while(curr!=NULL){
            if(G->vertex[p].cost+curr->weight<G->vertex[curr->child].cost){//better path was found
                //if(QPos==7) printf("****************");

                G->vertex[curr->child].cost=G->vertex[p].cost+curr->weight;
                G->vertex[curr->child].parent=p;

                adjustXPos(G,Q,QPos+1,QMaxPos);
            }
            curr=curr->nextEdge;
        }
        dist(G,QPos-1);
        QPos++;
    }
    printCostPath(G,s);
}

int max(int a,int b){
    if(a>b) return a;
    else return b;
}

void weight(Graph G){//NB +1 is always used in case it was a negative number
    int i,j;
    int space=max(G->digitsV,G->digitsE)+2;//the max is found between the vertex and edges weight because the graph will include both of them, +2 is used because a negative number may exist therefore+1, +1 more for some space so the numbers dont seem to be too close to eachother
    char SDigits[MaxFormat];
    char SData[MaxFormat];
    char xyHeadingFormat[MaxFormat]="";
    char dataFormat[MaxFormat]="";
    GEdgePtr curr;

    strcat(xyHeadingFormat,"%-");
    itoa(space,SDigits,10);
    strcat(xyHeadingFormat,SDigits);
    strcat(xyHeadingFormat,"d");

    strcat(dataFormat,"%-");
    itoa(space,SDigits,10);
    strcat(dataFormat,SDigits);
    strcat(dataFormat,"s");


    for(i=1;i<=space;i++){
        printf(" ");
    }
    for(i=1;i<=G->numV;i++){
        printf(xyHeadingFormat,G->vertex[i].id);
    }
    printf("\n");

    for(i=1;i<=G->numV;i++){
        printf(xyHeadingFormat,G->vertex[i].id);
        curr=G->vertex[i].firstEdge;
        for(j=1;j<=G->numV;j++){
            if(curr!=NULL && curr->child==j){
                itoa(curr->weight,SData,10);
                printf(dataFormat,SData);
                curr=curr->nextEdge;
            } else if(i==j){
                printf(dataFormat,"0");
            }else{
                printf(dataFormat,"I");
            }

        }
        printf("\n");
    }
}


int main(){
    int numVertices;
    Graph G;

    fp=fopen("inputDijkstraAssign.txt","r");
    fscanf(fp,"%d",&numVertices);
    G=newGraph(numVertices);
    buildGraph(fp,G);

    //printGraph(G);
    printf("The weight matrix is\n");
    weight(G);
    printf("\n\n");
    Dijkstra(G,1);

    fclose(fp);

    return 0;
}
