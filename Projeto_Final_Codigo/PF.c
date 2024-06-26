#include <PF.h>

int1 fimtempo = 0, ja_li_reset = 0, ja_li_mov = 0, ja_li_conf = 0, isMovido = 0;
int16 tempo = 0;
int8 i = 0, j = 0, x = 0, y = 0, cursorx = 0, cursory = 0, filtro_reset = 100, filtro_mov = 100, filtro_conf = 100;
int8 pontuacaoJ1 = 0, pontuacaoJ2 = 0, ganhador = 0, contvelha = 0;
int8 tabuleiro[3][3];

void reinicia_tabuleiro();
void acende_tabuleiro();
void move_cursor();
int8 verifica_ganhador(int8 matriz[3][3]);
void zera_jogo();

#INT_TIMER0
void TIMER0_isr(VOID)
{
    tempo++;

    if (tempo == 35)
    {
        tempo = 0;
        fimtempo = 1;
    }
}

void main()
{
    setup_timer_0(RTCC_INTERNAL | RTCC_DIV_8 | RTCC_8_BIT); // 1, 0 ms overflow
    enable_interrupts(INT_TIMER0);
    enable_interrupts(GLOBAL);

    reinicia_tabuleiro();

    while (TRUE)
    {
        if (input(B_RESET) == 0)
        {
            filtro_reset--;
            if (filtro_reset == 0 && ja_li_reset == 0)
            {
                ja_li_reset = 1;
                reinicia_tabuleiro();
            }
        }
        else
        {
            ja_li_reset = 0;
            filtro_reset = 100;
        }

        if (input(B_MOVE) == 0)
        {
            filtro_mov--;
            if (filtro_mov == 0 && ja_li_mov == 0)
            {
                ja_li_mov = 1;
                move_cursor();
            }
        }
        else
        {
            ja_li_mov = 0;
            filtro_mov = 100;
        }

        // if (input(B_CONFIRM) == 0)
        // {
        //    filtro_conf--;
        //    if (filtro_conf == 0 && ja_li_conf == 0)
        //    {
        //       ja_li_conf = 1;
        //       // executar função confirma_acao()
        //    }
        // }
        // else
        // {
        //    ja_li_conf = 0;
        //    filtro_conf = 100;
        // }

        if (fimtempo)
        {
            acende_tabuleiro();
            y += 1;
            if (y > 2)
            {
                x += 1;
                y = 0;
                if (x > 2)
                {
                    x = 0;
                }
            }

            ganhador = verifica_ganhador(tabuleiro);

            if (ganhador != 0)
            {
                if (ganhador == 1)
                {

                    pontuacaoJ1++;
                    // DAR UM RETORNO VISUAL PARA O USUARIO
                }
                else if (ganhador == 2)
                {

                    pontuacaoJ2++;
                    // DAR UM RETORNO VISUAL PARA O USUARIO
                }
                else
                {
                    // DAR UM RETORNO VISUAL PARA O USUARIO QUE DEU VEIA
                }

                reinicia_tabuleiro();
            }

            fimtempo = 0;
        }
    }
}

void reinicia_tabuleiro()
{
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            tabuleiro[i][j] = -1;
        }
    }

    tabuleiro[0][0] = 0;
    cursorx = cursory = 0;
}

void acende_tabuleiro()
{
    output_high(LIN1);
    output_high(LIN2);
    output_high(LIN3);
    output_low(RED1);
    output_low(RED2);
    output_low(RED3);
    output_low(GREEN1);
    output_low(GREEN2);
    output_low(GREEN3);

    if (x == 0)
    {
        output_low(LIN1);
    }
    else if (x == 1)
    {
        output_low(LIN2);
    }
    else if (x == 2)
    {
        output_low(LIN3);
    }

    if (tabuleiro[x][y] == 1)
    {
        if (y == 0)
        {
            output_high(RED1);
        }
        else if (y == 1)
        {
            output_high(RED2);
        }
        else
        {
            output_high(RED3);
        }
    }
    else if (tabuleiro[x][y] == 2)
    {
        if (y == 0)
        {
            output_high(GREEN1);
        }
        else if (y == 1)
        {
            output_high(GREEN2);
        }
        else
        {
            output_high(GREEN3);
        }
    }
    else if (tabuleiro[x][y] == 0)
    {
        if (y == 0)
        {
            output_high(RED1);
            output_high(GREEN1);
        }
        else if (y == 1)
        {
            output_high(RED2);
            output_high(GREEN2);
        }
        else
        {
            output_high(RED3);
            output_high(GREEN3);
        }
    }
}

void move_cursor()
{
    tabuleiro[cursorx][cursory] = -1;
    isMovido = 0;
    while (isMovido == 0)
    {
        cursory++;
        if (cursory > 2)
        {
            cursory = 0;
            cursorx++;
            if (cursorx > 2)
            {
                cursorx = 0;
            }
        }

        if (tabuleiro[cursorx][cursory] == -1)
        {
            tabuleiro[cursorx][cursory] = 0;
            isMovido = 1;
        }
    }
}

int8 verifica_ganhador(int8 matriz[3][3])
{
    for (i = 0; i < 3; i++)
    {
        if (matriz[i][0] != -1 && matriz[i][0] == matriz[i][1] && matriz[i][0] == matriz[i][2])
            return matriz[i][0];

        if (matriz[0][i] != -1 && matriz[0][i] == matriz[1][i] && matriz[0][i] == matriz[2][i])
            return matriz[0][i];
    }

    if (matriz[0][0] != -1 && matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2])
        return matriz[0][0];

    else if (matriz[0][2] != -1 && matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0])
        return matriz[0][2];

    else
    {
        contvelha = 0;

        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (tabuleiro[i][j] != -1 && tabuleiro[i][j] != 0)
                {

                    contvelha++;
                }
            }
        }

        if (contvelha == 9)
            return 3;

        else
            return 0;
    }
}

void zera_jogo()
{
    reinicia_tabuleiro();

    fimtempo = 0;
    tempo = 0;
    i = j = x = y = cursorx = cursory = 0;
    pontuacaoJ1 = pontuacaoJ2 = ganhador = contvelha = 0;
}
