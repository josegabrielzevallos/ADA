#include <windows.h>
#include <iostream>
#include <string>
#include <ctime> 


#define N 500

using namespace std;

unsigned t0, t1;
void* memsete(void* b, int c, size_t len) {
char* p = (char*)b;
for (size_t i = 0; i != len; ++i) {
p[i] = c;
}
return b;
}
class point
{
public:
	int x, y;
	point(){ x = y = 0; }
	void set( int a, int b ){ x = a; y = b; }
};

class nQueens
{
public:
	void solve( int c )
	{
		_count = c; int len = ( c + 1 ) * ( c + 1 ); 
		_queens = new bool[len]; 
		memsete( _queens, 0, len );
		_cl = new bool[c]; 
		memsete( _cl, 0, c ); 
		_ln = new bool[c]; 
		memsete( _ln, 0, c );
		point pt; 
		pt.set( rand() % c, rand() % c ); 
		putQueens( pt, c ); 
		displayBoard();
		delete [] _queens; 
		delete [] _ln; 
		delete [] _cl;
	}
	
private:
	void displayBoard()
	{
		system( "cls" ); 
		string t = "+---+", q = "| Q |", s = "|   |";
		COORD c = { 0, 0 }; 
		HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
		for( int y = _count-1, cy = 0; y >= 0; --y )
		{
			int yy = y * _count;
			for( int x = _count-1; x >= 0; --x )
			{
				SetConsoleCursorPosition( h, c ); 
				cout << t;
				c.Y++; 
				SetConsoleCursorPosition( h, c );
				if( _queens[x + yy] ) cout << q; 
				else cout << s;
				c.Y++; 
				SetConsoleCursorPosition( h, c );
				cout << t; 
				c.Y = cy; 
				c.X += 4;
			}
			cy += 2; 
			c.X = 0; 
			c.Y = cy;
		}
	}

	bool checkD( int x, int y, int a, int b )
	{
		if( x < 0 || y < 0 || x >= _count || y >= _count ) return true;
		if( _queens[x + y * _count] ) return false;
		if( checkD( x + a, y + b, a, b ) ) return true;
		return false;
	}
	
	bool check( int x, int y )
	{
		if( _ln[y] || _cl[x] )        return false;
		if( !checkD( x, y, -1, -1 ) ) return false;
		if( !checkD( x, y,  1, -1 ) ) return false;
		if( !checkD( x, y, -1,  1 ) ) return false;
		if( !checkD( x, y,  1,  1 ) ) return false;
		return true;
	}
	
	bool putQueens( point pt, int cnt )
	{
		int it = _count;
		while( it )
		{
			if( !cnt ) return true;
			if( check( pt.x, pt.y ) )
			{
				_queens[pt.x + pt.y * _count] = _cl[pt.x] = _ln[pt.y] = true;
				point tmp = pt; 
				if( ++tmp.x >= _count ) tmp.x = 0; 
				if( ++tmp.y >= _count ) tmp.y = 0;
				if( putQueens( tmp, cnt - 1 ) ) 
					return true;
				_queens[pt.x + pt.y * _count] = _cl[pt.x] = _ln[pt.y] = false;
			}
			if( ++pt.x >= _count ) pt.x = 0;
			it--;
		}
		return false;
	}
	
	int _count;
	bool* _queens, *_ln, *_cl;
};

int main()
{
	nQueens n; 
	//int nq;
	while( true )
	{
		system( "cls" ); 
		//cout << "Enter board size bigger than 3 (0 - 3 to QUIT): "; 
		//cin >> nq;
		//if( nq < 4 ) return 0; 
		
		t0=clock();
		//n.solve( nq );
		n.solve(N);
		t1 = clock();
		
		double time = (double(t1-t0)/CLOCKS_PER_SEC);
		cout << endl << "Execution Time: " << time << endl;
		system( "pause" );
	}
	return  0;
}
