#include <PF.h>

int1 fimtempo = 0, ja_li_reset = 0, ja_li_mov = 0, ja_li_conf = 0;
int16 tempo = 0;
int8 i = 0, j = 0, x = 0, y = 0, filtro_reset = 100, filtro_mov = 100, filtro_conf = 100;
int8 pontuacaoJ1 = 0, pontuacaoJ2 = 0, ganhador = 0;
int8 tabuleiro[3][3];

void reinicia_tabuleiro();
void acende_tabuleiro();
int8 verifica_ganhador(int8 *);

#INT_TIMER0
void TIMER0_isr(void)
{
	tempo++;

	if (tempo == 50)
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

	//!   tabuleiro[0][0] = 1;
	//!   tabuleiro[0][1] = 2;
	//!   tabuleiro[0][2] = 0;
	//!   tabuleiro[1][0] = 1;
	//!   tabuleiro[1][1] = 2;
	//!   tabuleiro[1][2] = 0;
	//!   tabuleiro[2][0] = 1;
	//!   tabuleiro[2][1] = 2;
	//!   tabuleiro[2][2] = 0;

	while (TRUE)
	{
		if (input(B_RESET) == 0)
		{
			filtro_reset--;
			if(filtro_reset == 0 && ja_li_reset == 0){
				ja_li_reset = 1;
				reinicia_tabuleiro();
			}
		}else{
			ja_li_reset = 0;
			filtro_reset = 100;
		}

		if (input(B_MOVE) == 0)
		{
			filtro_mov--;
			if (filtro_mov == 0 && ja_li_mov == 0)
			{
				ja_li_mov = 1;
				// executar função move_cursor()
			}
		}
		else
		{
			ja_li_mov = 0;
			filtro_mov = 100;
		}

		if (input(B_CONFIRM) == 0)
		{
			filtro_conf--;
			if (filtro_conf == 0 && ja_li_conf == 0)
			{
				ja_li_conf = 1;
				// executar função confirma_acao()
			}
		}
		else
		{
			ja_li_conf = 0;
			filtro_conf = 100;
		}

		if (fimtempo)
		{
			acende_tabuleiro();

			y += 1;

			if (y == 3)
			{
				x += 1;
				y = 0;

				if (x == 3)
				{
					x = 0;
				}
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
	else
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
		return 0;
}