#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum player {
    U, // Undefined
    X,
    O,
} Player;

typedef struct plstt {
    bool isocc;
    Player player;
} Plstt;

char tochar(Player player)
{
    switch (player) {
    case X:
        return 'X';
    case O:
        return 'O';
    case U:
        return ' ';
    }
}

void draw(Plstt* poss)
{
    printf("       |       |       \n"
           "   %c   |   %c   |    %c  \n"
           "       |       |       \n"
           "-------+-------+-------\n"
           "       |       |       \n"
           "   %c   |   %c   |   %c   \n"
           "       |       |       \n"
           "-------+-------+-------\n"
           "       |       |       \n"
           "   %c   |   %c   |   %c   \n"
           "       |       |       \n",
        tochar(poss[0].player), tochar(poss[1].player), tochar(poss[2].player),
        tochar(poss[3].player), tochar(poss[4].player), tochar(poss[5].player),
        tochar(poss[6].player), tochar(poss[7].player), tochar(poss[8].player));
}

Player chkwin(Plstt* poss)
{
    bool cnd1 = poss[0].player == poss[1].player && poss[1].player == poss[2].player;
    bool cnd2 = poss[3].player == poss[4].player && poss[4].player == poss[5].player;
    bool cnd3 = poss[6].player == poss[7].player && poss[7].player == poss[8].player;
    bool cnd4 = poss[0].player == poss[3].player && poss[3].player == poss[6].player;
    bool cnd5 = poss[1].player == poss[4].player && poss[4].player == poss[7].player;
    bool cnd6 = poss[2].player == poss[5].player && poss[5].player == poss[8].player;
    bool cnd7 = poss[0].player == poss[4].player && poss[4].player == poss[8].player;
    bool cnd8 = poss[2].player == poss[4].player && poss[4].player == poss[6].player;

    if (cnd1 || cnd4 || cnd7) {
        switch (poss[0].player) {
        case X:
            return X;
        case O:
            return O;
        }
    } else if (cnd2 || cnd5 || cnd8) {
        switch (poss[4].player) {
        case X:
            return X;
        case O:
            return O;
        }
    } else if (cnd3 || cnd6) {
        switch (poss[8].player) {
        case X:
            return X;
        case O:
            return O;
        }
    }
    return U;
}

void play(int plturn, Plstt* poss, int c)
{
    int pos;

    while (true) {
        printf("Player %d turn\n", plturn);
        printf("Which square will you play in? (1-9)\n->");

        scanf("%d", &pos);
        if (!poss[pos - 1].isocc) {
            poss[pos - 1].player = plturn;
            poss[pos - 1].isocc = true;
        } else {
            printf("Already occupied!\n");
            play(plturn, poss, c);
        }

        draw(poss);

        if (chkwin(poss) == X) {
            printf("Player 1 wins!\n");
            exit(0);
        } else if (chkwin(poss) == O) {
            printf("Player 2 wins!\n");
            exit(0);
        }

        if (c++ == 9) {
            printf("Match draw!\n");
            exit(0);
        }

        plturn = plturn == 1 ? 2 : 1;
    }
}

int main(void)
{
    Plstt poss[9];
    int c = 1;

    for (size_t i = 0; i < 9; i++) {
        poss[i].player = U;
    }

    draw(poss);
    printf("The Player 1 is 'X' and Player 2 is 'O'\n");
    printf("Who will play the first turn (1 / 2)?\n->");

    int plturn;
    scanf("%d", &plturn);
    play(plturn, poss, c);

    return 0;
}
