/******************************************************************************
 CS288 HW7 three search strategies: depth, breadth, and intelligent
 command example: command 16 numbers and search strategy

 fifteen 1 2 3 4 5 6 7 8 9 10 11 12 13 14 0 15 {dfs|bfs|astar}
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BF 4			/* Branching factor of the search tree */
#define N 4
#define NxN 16
#define DFS 1                   /* depth first search */
#define BFS 2                   /* breadth first search */
#define BEST 3                  /* best first search */
#define BB 4                    /* branch and bound */
#define ASTAR 5                 /* A* search */
#define UNKNOWN 9		/* unknown search strategy */

#define MAX_PATH 1000

#define DN 0			/* for finding path */
#define RT 1
#define UP 2
#define LT 3
#define UK 9

#define FVAL 0			/* f=g+h, keep it simple for now */
#define GVAL 1
#define HVAL 2
#define PATH 3			/* array index, how it got to this state */

#define TRUE 1
#define FALSE 0

int level, strategy;

int nodes_same(), str_compare(), count(), find_h();
void swap(), exit_proc(), print_a_node(), print_nodes();
int toggle_dir(), solvable();
void find_path(), print_path(), find_parent();
int path[MAX_PATH], path_buf[MAX_PATH];
void prep_dir_to_str(), dir_to_str();
char *dir_to_sdir[4], strategy_s[10]; /* four directions */

struct node {
  int board[N + 1][N];
  struct node *next;
};

struct node *start, *goal;
struct node *initialize(), *expand(), *merge(), *filter(), *move(), *prepend(), *append();
struct node *insert_node(), *check_list(), *goal_found();

int main(int argc, char **argv) {
  int iter, cnt = 0, total = 1, ocnt = 0, ccnt = 0;
  int perm;		/* perm = odd = no solution, perm = even = solvable */
  struct node *cp, *open, *closed, *succ, *tp;

  open = closed = succ = NULL;
  start = initialize(argc, argv);	/* init initial and goal states */
  perm = solvable(start);		/* check if solvable permutation */
  //if (perm & 1) { printf("nope:%d\n", perm); return 1; }

  open = start;
  iter = 0;

  while (open) {
	1 && printf("h = %d\n", open->board[N][0]);
    printf("%d: open = %d + clsd = %d = total = %d\n", iter, ocnt, ccnt, ocnt + ccnt);
    ocnt = count(open);
    ccnt = count(closed);
    cp = open; open = open->next; cp->next = NULL; /* get the first node from open */
    succ = expand(cp);			     /* Find new successors */
    succ = filter(succ, open);		     /* New succ list */
    succ = filter(succ, closed);		     /* New succ list */
    cnt = count(succ);
    total = total + cnt;
    if (succ) open = merge(succ, open, strategy); /* New open list */
    closed = append(cp, closed);		      /* New closed */
    if ((cp = goal_found(succ, goal))) break;
    iter++;
  }
  printf("%s strategy: %d iterations %d nodes\n", strategy_s, iter + 1, total);
  find_path(cp, open, closed);

  return 0;
} /* end of main */

int toggle_dir(int dir){
  int opp_dir;
  // return opp direction
  return opp_dir;
}

void print_path(int n, int *path){
  int i, p;
  //  for (i = 0; i < n; i++) path[i] = path_buf[path_cnt - i - 1];
  //  for (i = 0; i < path_cnt; i++) printf("%d ", path[i]); printf("\n");
  //  printf("entering print_path: n = %d\n", n);//1800-435-7764

  //  for (i = n - 1; i >= 0; i--) printf("%d ", *(path + i)); printf("\n");
  for (i = n - 1; i >= 0; i--) {
    p = *(path + i);
    if (i > 0) printf("%s -> ", dir_to_sdir[p]);
    else printf("%s", dir_to_sdir[p]);    
  }
  printf("\n");
  //  printf("exiting print_path\n");
}

//char **dir_to_sdir = {"DN", "RT", "UP", "LT"}; //[4];
void prep_dir_to_str(){
  //...
}

void find_path(struct node *cp, struct node *opnp, struct node *cldp){
  int i, j, dir, opp_dir;
  char *sdir, *opp_sdir;
  int path_cnt = 0, p;
  struct node *tp;
  //start from the very last node that matches the goal state because
  //that has the direction info
  //toggle the direction, get the parent
  //look for that parent in closed
  //repeat until you find the initial state
}

void find_parent(struct node *cp,int prev_dir){
  int i, j, k, cnt, row = 0, col = j;
}

// Expand: generate successors of the current node
struct node *expand(struct node *cp) {
  //int i, j, k, cnt, row = 0, col = j;
  int i, j;
  struct node *succ, *tp;
  /*struct node */succ = NULL;

  /* check where 0 is. find indices i,j */
  j = N;
  for (i = -1; j == N && ++i < N;) for (j = -1; ++j < N && cp->board[i][j];); /* found it */

  ((i + 1) < N) 	&& (succ = append(move(cp, i, j, i + 1, j, DN), succ));		/* DOWN */
  ((j + 1) < N) 	&& (succ = append(move(cp, i, j, i, j + 1, RT), succ));		/* RIGHT */
  ((i - 1) >= 0) 	&& (succ = append(move(cp, i, j, i - 1, j, UP), succ));		/* UP */
  ((j - 1) >= 0)	&& (succ = append(move(cp, i, j, i, j - 1, LT), succ));		/* LEFT */

  /*if ((i + 1) < N) {		/* DOWN 
    tp = move(cp, i, j, i + 1, j, DN);
    succ = append(tp, succ);
  }
  if ((j + 1) < N) {		/* RIGHT 
    tp = move(cp, i, j, i, j + 1, RT);
    succ = append(tp, succ);
  }
  if ((i - 1) >= 0) {		/* UP 
	//if ((i - 1) < N) {		/* UP 
    tp = move(cp, i, j, i - 1, j, UP);
    succ = append(tp, succ);
  }
  if ((j - 1) >= 0) {		/* LEFT 
	//if ((j - 1) < N) {		/* LEFT 
    tp = move(cp, i, j, i, j - 1, LT);
    succ = append(tp, succ);
  }*/
  return succ;
}

/* attach in the beginning */
struct node *prepend(struct node *tp, struct node *sp) {
  //.....
  return sp;
}

/* attach at the end */
struct node *append(struct node *tp, struct node *sp) {
  //struct node *cp;
  //.....
  if (!sp) return tp;
  struct node *cp;
  for (cp = sp; cp->next; cp = cp->next);
  cp->next = tp;
  return sp;
}

void swap(struct node *cp, int i, int j, int k, int l){
  int tmp;
  //.....
}

struct node *move(struct node *cp, int a, int b, int x, int y, int dir) {
  //struct node *newp;
  //int i, j, k, l, tmp;
  int i, j;
  // malloc
  struct node *newp = (struct node *) malloc(sizeof(struct node));
  newp->next = NULL;
  // copy from cp
  for (i = -1; ++i < N;) for (j = -1; ++j < N; newp->board[i][j] = cp->board[i][j]);
  // swap two vals
  newp->board[a][b] = newp->board[x][y];
  newp->board[x][y] = 0;
  // compute f,g,h
  //newp->board[N][1] = find_h(start->board, cp->board);
  newp->board[N][1] = cp->board[N][1] + 1;
  newp->board[N][2] = find_h(newp->board, goal->board);
  newp->board[N][0] = newp->board[N][1] + newp->board[N][2];
  // insert the direction that resulted in this node, used for printing path
  newp->board[N][3] = dir;

  if (0) {
	print_a_node(cp);
	printf("%d,%d->%d,%d\n", a, b, x, y);
	print_a_node(newp);
  }
  return newp;
}

struct node *goal_found(struct node *cp, struct node *gp){
  int flg = FALSE;
  // check if succ list has goal
  // if found, return that for finding path else return NULL
  for (; cp && !nodes_same(cp, gp); cp = cp->next);
  return cp;
}

int count(struct node *cp) {
  int cnt = 0;
  //return the number of nodes on the list
  for (; cp && ++cnt; cp = cp->next);
  return cnt;
}

struct node *merge(struct node *succ, struct node *open, int flg) {
  struct node *csucc, *copen;

  if (flg == DFS) 		open = append(open, succ);	/* attach in the front: succ -> ... -> open */
  else if (flg == BFS)	open = append(succ, open);	/* attach at the end: open -> ... -> succ */
  else if (flg == BEST) {	/* Best first: sort on h value */
    //...
	struct node *tp;
	for (csucc = succ; csucc; csucc = tp) {
	  tp = csucc->next;
	  if (!open) {
		open = csucc;
		open->next = NULL;
		continue;
	  }
	  if (csucc->board[N][2] < open->board[N][2]) {
		csucc->next = open;
		open = csucc;
		continue;
	  }
	  for (copen = open; copen->next && (csucc->board[N][2] >= copen->next->board[N][2]); copen = copen->next);// printf("oooo\n");
	  csucc->next = copen->next;
	  copen->next = csucc;
	}
  }
  else {			/* A* search: sort on f=g+h value */
    //...
	struct node *tp;
	for (csucc = succ; csucc; csucc = tp) {
	  tp = csucc->next;
	  if (!open) {
		open = csucc;
		open->next = NULL;
		continue;
	  }
	  if (csucc->board[N][0] < open->board[N][0]) {
		csucc->next = open;
		open = csucc;
		continue;
	  }
	  for (copen = open; copen->next && (csucc->board[N][0] >= copen->next->board[N][0]); copen = copen->next);// printf("oooo\n");
	  csucc->next = copen->next;
	  copen->next = csucc;
	}
  }
  return open;
}


/* insert succ into open in ascending order of x value, where x is an array 
   index: 0 = f, 1 = g, h = 2 of board[N][x]
 */
struct node *insert_node(struct node *succ, struct node *open, int x) {
  int cnt;
  struct node *copen, *topen;
  //...
  return open;
}

int find_h(int current[N + 1][N], int goalp[N + 1][N]) {
  int h = 0, i, j, k, l, done;
  // ...
  for (i = -1; ++i < N;) {
	for (j = -1; ++j < N;) {
	  if (!current[i][j]) continue;
	  l = N;
	  for (k = -1; l == N && ++k < N;) for (l = -1; ++l < N && current[i][j] != goalp[k][l];);
	  h += (abs(i - k) + abs(j - l));
	  //(current[i][j] != goalp[i][j]) && ++h;
	}
  }
  return h;
}

/* a = b = x[N][N] */
int nodes_same(struct node *xp, struct node *yp) {
  //int i, j, flg = FALSE;
  int i, j;
  //...
  for (i = -1; ++i < N;) for (j = -1; ++j < N;) if (xp->board[i][j] != yp->board[i][j]) return FALSE;
  //return flg;
  return TRUE;
}

/******************************************************************************
  Check succ against open and closed. Remove those succ nodes that are in open or closed.
******************************************************************************/
struct node *filter(struct node *succ, struct node *hp){ 
   struct node *lsp, *rsp;	/* lsp = left succ p, rsp = right succ p */
   struct node *tp;		/* temp ptr */
   //...
   lsp = rsp = succ;
   for (rsp = succ; rsp; rsp = rsp->next) {
	 for (tp = hp; tp && !nodes_same(tp, rsp); tp = tp->next);
	 if (tp) 	(nodes_same(lsp, rsp)) && (succ = lsp = rsp->next) || (lsp->next = rsp->next);
		 /*if (nodes_same(lsp, succ)) succ = lsp = rsp->next;
		   else lsp = rsp->next;*/
	 else 		lsp = rsp;
   }
   return succ;
}

void print_nodes(struct node *cp, char name[20]) {
  int i;
  printf("%s: \n", name);
  while (cp) { print_a_node(cp); cp = cp->next; }
}

void print_a_node(struct node *np) {
  int i, j;
  for (i = -1; ++i < N + 1; printf("\n")) for (j = -1; ++j < N; printf("%2d ", np->board[i][j]));
  printf("\n");
}

//cnt = odd -> no solution, cnt = even = solvable
int solvable(struct node *cp) {
  //int i, j, lst[NxN], cnt = 0, total = 0;
  int i, j, lst[NxN], cnt = 0, total = 0;
  //int k = 0;
  //flatten the board in to flat lst and work with that
  for (i = -1; ++i < N;) for (j = -1; ++j < N; lst[cnt++] = cp->board[i][j]);
  for (i = -1; ++i < NxN;) for (j = i - 1; ++j < NxN; (lst[j] && lst[j] < lst[i]) && total++);
  return total;	/* return the number we discussed in class today 3/31/2015*/
}

/* fif 0 1 2 4 5 6 3 8 9 10 7 12 13 14 11 15 astar */
struct node *initialize(int argc, char **argv){
  //int i, j, k, npe, n, idx, gidx, inv;
  int j, k, idx, gidx;
  struct node *tp = (struct node *) malloc(sizeof(struct node));
  tp->next = NULL;
  
  idx = 1;
  for (j = -1; ++j < N; tp->board[N][j] = 0) for (k = -1; ++k < N; tp->board[j][k] = atoi(argv[idx++])); /* set f,g,h of initial state to 0 */
  start = tp;

  printf("init state: \n");
  print_a_node(start);

  tp = (struct node *) malloc(sizeof(struct node));
  tp->next = NULL;
  gidx = 1;
  for (j = -1; ++j < N; tp->board[N][j] = 0) for (k = -1; ++k < N; tp->board[j][k] = gidx++);	/* set f,g,h of goal state to 0 */
  tp->board[N - 1][N - 1] = 0;		/* empty tile = 0 */
  goal = tp;

  printf("goal state: \n");
  print_a_node(goal);
  
  //71, 72, 73, 75, 76
  strcpy(strategy_s, argv[idx]);
  if (!strcmp(strategy_s, "dfs")) 			strategy = DFS;
  else if (!strcmp(strategy_s, "bfs")) 		strategy = BFS;
  else if (!strcmp(strategy_s, "best")) 	strategy = BEST;
  else if (!strcmp(strategy_s, "bb")) 		strategy = BB;
  else if (!strcmp(strategy_s, "astar")) 	strategy = ASTAR;
  else 										strategy = UNKNOWN;
  printf("strategy = %s\n", strategy_s);

  return start;
}

void exit_proc(char *msg) {
  printf("Error: %s\n", msg);
  exit(1);
}

/*****************************************************************************
 End of file: fif.c. Fifteen Puzzle, Sequential A* 1 processor version.
*****************************************************************************/
/*
 1  2  3  4
 5  6  7  8
13 10 12  0
11 14  9 15
5
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15  0
*/
