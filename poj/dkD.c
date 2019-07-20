#define QSIZE 250000
#define HSIZE 250001
#define MSIZE 10

typedef struct mnode {
	unsigned long long pos;
	struct mnode *pred;
	struct mnode *hnext;
	char pmove;
} MNode;

MNode *hash[HSIZE];
MNode *q[QSIZE];
int qs, qe;
int nnode = 0;
char g[MSIZE][MSIZE];
int gs;

void printbmp( unsigned long long nbmp, char *name ) {
	int i, j;
	unsigned long long mask;

	printf( "%s:\n", name );
	mask = 0x8000000000000000LL;
	for( i = 0; i < gs-2; i++ ) {
		for( j = 0; j < gs-2; j++ ) {
			putchar( (nbmp&mask)?'1':'0' );
			mask = mask >> 1;
		}
		putchar( '\n' );
	}
	putchar( '\n' );
}

void PrintPath( MNode *tmp ) {
	if( tmp == 0 ) return;
	PrintPath( tmp->pred );
	switch( tmp->pmove ) {
	case 'n': printf( "north\n" ); break;
	case 'e': printf( "east\n" ); break;
	case 's': printf( "south\n" ); break;
	case 'w': printf( "west\n" ); break;
	}
}

int AddNode( MNode *tmp ) {
	int i, j, x;
	MNode *hsh;

	if( !tmp->pos ) {
		PrintPath( tmp );
		printf( "used %d nodes\n", nnode );
		exit(0);
	}

	x = tmp->pos % HSIZE;
	hsh = hash[x];
	while( hsh ) {
		if( tmp->pos == hsh->pos ) return 0;
		hsh = hsh->hnext;
	}

	tmp->hnext = hash[x];
	hash[x] = tmp;
	nnode++;
	q[qe++] = tmp;
	if( qe == QSIZE ) qe = 0;
	if( qe == qs ) {printf( "Queue overflow!!\n" ); exit(0);}
	return 1;
}

main() {
	int i, j, k, x, y, z, n;
	MNode *tmp, *tmp2;
	unsigned long long nbmp, ebmp, sbmp, wbmp, nwbmp, ewbmp, swbmp, wwbmp;
	unsigned long long mask;

	memset( hash, 0, sizeof(hash) );
	tmp = (MNode*)malloc(sizeof(MNode));
	tmp->pred = 0;
	scanf( " %d", &gs );
	for( i = 0; i < gs; i++ ) for( j = 0; j < gs; j++ )
		scanf( " %c", &g[j][i] );
	tmp->pos = nbmp = ebmp = sbmp = wbmp = nwbmp = ewbmp = swbmp = wwbmp = 0;
	mask = 0x8000000000000000LL;
	for( j = 1; j < gs-1; j++ ) for( i = 1; i < gs-1; i++ ) {
		if( g[i][j] != 'O' ) tmp->pos |= mask;
		if( g[i][j] != 'O' && j < gs-2 ) nbmp |= mask;
		if( g[i][j] != 'O' && i > 1 ) ebmp |= mask;
		if( g[i][j] != 'O' && j > 1 ) sbmp |= mask;
		if( g[i][j] != 'O' && i < gs-2 ) wbmp |= mask;
		if( g[i][j-1] == 'O' ) nwbmp |= mask;
		if( g[i+1][j] == 'O' ) ewbmp |= mask;
		if( g[i][j+1] == 'O' ) swbmp |= mask;
		if( g[i-1][j] == 'O' ) wwbmp |= mask;
		mask = mask >> 1;
	}
	qs = qe = 0;
	AddNode( tmp );

	tmp2 = (MNode*)malloc(sizeof(MNode));
	while( qs != qe ) {
		tmp = q[qs++];
		if( qs == QSIZE ) qs = 0;

		tmp2->pred = tmp;
		tmp2->pmove = 'n';
		tmp2->pos = ((tmp->pos << (gs-2)) & nbmp) | (tmp->pos & nwbmp);
		if( AddNode( tmp2 ) ) tmp2 = (MNode*)malloc(sizeof(MNode));
		if( !tmp2 ) {printf( "Out of memory at %d nodes\n", nnode ); exit(0);}

		tmp2->pred = tmp;
		tmp2->pmove = 'e';
		tmp2->pos = ((tmp->pos >> 1) & ebmp) | (tmp->pos & ewbmp);
		if( AddNode( tmp2 ) ) tmp2 = (MNode*)malloc(sizeof(MNode));
		if( !tmp2 ) {printf( "Out of memory at %d nodes\n", nnode ); exit(0);}

		tmp2->pred = tmp;
		tmp2->pmove = 's';
		tmp2->pos = ((tmp->pos >> (gs-2)) & sbmp) | (tmp->pos & swbmp);
		if( AddNode( tmp2 ) ) tmp2 = (MNode*)malloc(sizeof(MNode));
		if( !tmp2 ) {printf( "Out of memory at %d nodes\n", nnode ); exit(0);}

		tmp2->pred = tmp;
		tmp2->pmove = 'w';
		tmp2->pos = ((tmp->pos << 1) & wbmp) | (tmp->pos & wwbmp);
		if( AddNode( tmp2 ) ) tmp2 = (MNode*)malloc(sizeof(MNode));
		if( !tmp2 ) {printf( "Out of memory at %d nodes\n", nnode ); exit(0);}
	}
	printf( "Impossible\n" );
}
