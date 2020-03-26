#include <iostream>
#include "avl.h"
#include "AStar.h"
#include "Dijkstra.h"

void testAVL(){
    // Testing AVL Tree
    node *root = NULL;
    int i;
    for (i = 1; i <= 7; i++)
        root = insert(root, i);
    cout << "LevelOrder: ";
    levelOrder(root);
    root = deleteNode(root, 1); // Deleting key with value 1
    cout << "\nLevelOrder: ";
    levelOrder(root);
    root = deleteNode(root, 4); // Deletin key with value 4
    cout << "\nLevelOrder: ";
    levelOrder(root);
}


void testAStar(){
    Map m;
    Point s, e( 7, 7 );
    AStar as;

    if( as.search( s, e, m ) ) {
        std::list<Point> path;
        int c = as.path( path );
        for( int y = -1; y < 9; y++ ) {
            for( int x = -1; x < 9; x++ ) {
                if( x < 0 || y < 0 || x > 7 || y > 7 || m( x, y ) == 1 )
                    std::cout << "O";
                else {
                    if( std::find( path.begin(), path.end(), Point( x, y ) )!= path.end() )
                        std::cout << "x";
                    else std::cout << ".";
                }
            }
            std::cout << "\n";
        }

        std::cout << "\nPath cost " << c << ": ";
        for( std::list<Point>::iterator i = path.begin(); i != path.end(); i++ ) {
            std::cout<< "(" << ( *i ).x << ", " << ( *i ).y << ") ";
        }
    }
    std::cout << "\n\n";
}


void testDijkstra(){
    runDijkstra();
}


int main()
{
    //testAVL();
    //testAStar();
    testDijkstra();
    getchar();
    return 0;
}