/* UVa Online Judge. Problemset Volumes :: Volume 1 :: 101. The blocks problem.
 * Time limit: 3.000 secs.
 */

#include <stdlib.h>
#include <stdio.h>


int main( void )
{
    const int max_blocks = 24;
    int world[max_blocks][max_blocks];
    char command1[5], command2[5];
    int n_blocks;
    int block1, block2;
    int block1_x = 0, block1_y = 0, block2_x = 0, block2_y = 0;
    int block_to_move;

    int i = 0, j = 0;

    /*************************************************************************/
    /* Initializations */
    /*************************************************************************/
    for ( i = 0; i < max_blocks; ++i )
    {
        for ( j = 1; j < max_blocks; ++j )
        {
            world[i][j] = -1;
        }
    }
    for ( i = 0; i < max_blocks; ++i )
    {
        world[i][0] = i;
    }

    /*************************************************************************/
    /* Input read */
    /*************************************************************************/
    scanf( "%d", &n_blocks );
    while ( 1 )
    {
        scanf( "%s", command1 );
        if ( command1[0] == 'q' )
            break;
        scanf( "%d%s%d", &block1, command2, &block2 );

        /*********************************************************************/
        /* Find position of blocks */
        /*********************************************************************/

        for ( i = 0; i < n_blocks; ++i )
        {
            for ( j = 0; j < n_blocks && world[i][j] != -1; ++j )
            {
                if ( world[i][j] == block1 )
                {
                    block1_x = i;
                    block1_y = j;
                }
                else if ( world[i][j] == block2 )
                {
                    block2_x = i;
                    block2_y = j;
                }
            }
        }
        /*********************************************************************/
        /* Make moves */
        /*********************************************************************/
        if ( command1[0] == 'm' )
        {
            if ( command2[1] == 'n' )
            {
                /* remove blocks above block2 */
                for ( i = block2_y + 1;
                        i < n_blocks && world[ block2_x ][i] != -1 ; ++i )
                {
                    block_to_move = world[block2_x][i];
                    world[ block_to_move ][0] = block_to_move;
                    world[ block2_x ][i] = -1;
                }
                if ( block1_x == block2_x )
                    for ( i = 0; i < n_blocks; ++i ) /* Get new positions */
                    {
                        for ( j = 0; j < n_blocks && world[i][j] != -1; ++j )
                        {
                            if ( world[i][j] == block1 )
                            {
                                block1_x = i;
                                block1_y = j;
                                break;
                            }
                        }
                    }
                /* remove blocks above block1 */
                for ( i = block1_y + 1;
                        i < n_blocks && world[ block1_x ][i] != -1 ; ++i )
                {
                    block_to_move = world[block1_x][i];
                    world[ block_to_move ][0] = block_to_move;
                    world[ block1_x ][i] = -1;
                }
                world[block1_x][block1_y] = -1;
                world[ block2_x ][ block2_y + 1 ] = block1;
            }
            else
            {
                /* remove blocks above block1 */
                for ( i = block1_y + 1;
                    i < n_blocks && world[ block1_x ][i] != -1 ; ++i )
                {
                    block_to_move = world[block1_x][i];
                    world[ block_to_move ][0] = block_to_move;
                    world[ block1_x ][i] = -1;
                }
                /* put block 1 on top of block2 pile */
                if ( block1_x != block2_x )
                {
                    for ( i = block2_y + 1;
                            i < n_blocks; ++i )
                    {
                        if ( world[block2_x][ i ] == -1 )
                        {
                            world[block2_x][i] = block1; /* Put block place */
                            break;
                        }
                    }
                    world[block1_x][block1_y] = -1;
                }
            }
        }
        else
        {
            if ( command2[1] == 'n' )
            {
                /* remove blocks above block2 */
                for ( i = block2_y + 1;
                        i < n_blocks && world[ block2_x ][i] != -1 ; ++i )
                {
                    block_to_move = world[block2_x][i];
                    world[ block_to_move ][0] = block_to_move;
                    world[ block2_x ][i] = -1;
                }
                /* move pile */
                for ( i = block1_y, j = block2_y + 1;
                        i < n_blocks && world[ block1_x ][i] != -1 ;
                        ++i, ++j )
                {
                    block_to_move = world[block1_x][i];
                    world[block2_x][j] = block_to_move;
                    world[block1_x][i] = -1;
                }
            }
            else /* Pile over */
            {
                if ( block1_x != block2_x ) {
                    /* get top of pile of block2 */
                    for ( j = block2_y + 1;
                            world[block2_x][j] != -1 && j < n_blocks; ++j )
                    {
                        ;
                    }
                    /* move pile */
                    for ( i = block1_y;
                            i < n_blocks && world[ block1_x ][i] != -1 ;
                            ++i, ++j )
                    {
                        block_to_move = world[block1_x][i];
                        world[block2_x][j] = block_to_move;
                        world[block1_x][i] = -1;
                    }
                }
            }
        }
    }

    /*************************************************************************/
    /* Print world */
    /*************************************************************************/
    for ( i = 0; i < n_blocks; ++i )
    {
        printf( "%d:", i );
        for ( j = 0; world[i][j] != -1 && j < n_blocks; ++j )
        {
            printf( " %d", world[i][j] );
        }
        putchar( '\n' );
    }

    return EXIT_SUCCESS;
}
