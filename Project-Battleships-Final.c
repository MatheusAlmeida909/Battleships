#include <stdio.h> 
#include <stdlib.h>
#include <conio.h> //função rand
#include <windows.h> //beep e sleep
#include <locale.h>

#define LIN 12
#define COL 12

void mainMenu()
{
	char x = 92;
	
	printf("\n				 _           _   _   _           _     _ \n");
	printf("				| |         | | | | | |         | |   (_)\n");
	printf("				| |__   __ _| |_| |_| | ___  ___| |__  _ _ __   ___ \n");
	printf("				| '_ %c / _` | __| __| |/ _ %c/ __| '_ %c| | '_ %c / __| \n",x,x,x,x);
	printf("				| |_) | (_| | |_| |_| |  __/%c__ %c | | | | |_) |%c__ %c \n",x,x,x,x);
	printf("				|_.__/ %c__,_|%c__|%c__|_|%c___||___/_| |_|_| .__/ |___/ \n",x,x,x,x);
	printf("				                                        | | \n");
	printf("				                                        |_| \n");
	printf("\n\n\n\n\n\n					Pressione uma tecla para jogar");
	getch();
	
	system("cls");
}

void context()
{
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("				Sua base está sendo atacada por navios desconhecidos.");
	sleep(1);
	printf("\n		  Está uma noite escura, a iluminação da base foi danificada e seus radares também.");
	sleep(1);
	printf("\n			  Você terá de usar os canhões no escuro e rezar para acertar eles.");
	sleep(1);
	printf("\n		 Prepare-se, insira a latitude e longitude do ataque no console para acabar com eles!");
	
	getch();
	
	system("cls");
}

int main()
{
    setlocale(LC_ALL,"");
	mainMenu(); // menu de enfeite: linhas 10 - 26
	context();  // contextualizar o jogo: linhas 28 - 42 
	
	//geração do campo do jogoe campo de respostas: linhas 51 - 67
    int line, column;
    unsigned int playBoard[LIN][COL], answerBoard[LIN][COL]; 

    for(line = 0; line < LIN; line++)
	{
		printf("\n					");
		for(column = 0; column < COL; column++)
		{
			//	126 = til para representar agua
			playBoard[line][column] = 126;
			answerBoard[line][column] = 126;
			
			printf(" %c ", playBoard[line][column]);
			
			usleep(1100);
		}
	}
    
	// Posicionamento dos navios/respostas: linhas 68 - 74
    srand(time(NULL));
	int ship;

	for(ship = 0; ship < 4; ship++)
	{
	    answerBoard[rand() % LIN][rand() % COL] = 2;
	}
	
	// Extender cada navio para 4 casas na horizontal no campo: linhas 77 - 102
	int x ; // Váriavel 'x' é auxiliar para aumentar tamanho dos navios
	
	for(line = 0; line < LIN; line++)
	{
	    for(column = 0; column < COL; column++)
	    {	
	    	if(answerBoard[line][column] == 2)
            {
				if(column < 9)
		   	    {
				    for(x = 0;x < 4;x++,column++)
	    		    {
						answerBoard[line][column] = 2; 
					}
	    	    }	
	    		else
			    {
	          		for(x = 4;x > 0;x--,column--)
		       		{
			    		answerBoard[line][column] = 2;
	    		   	}
	    		}    
	        }
	    }
	}	
	
	// Reatribuindo o valor 0 para contar numero máximo de tiros: linhas 105 - 116
	ship = 0;
	
	for(line = 0; line < LIN; line++)
	{
    	for(column = 0; column < COL; column++)
    	{	
			if(answerBoard[line][column] == 2)
			{
				ship++;
			}
		}
	}

	int attempts = ship, hit = 0, shot = 0;
	
	printf("\n\n	Mantenha o foco e lembre que todos os inimigos estão no alcançe de 12km por 12km dos canhões\n");
	
    do // Área de processamento de respostas: linhas 122 - 196
    {
	     // Receber respostas e mostrar tentativas: linhas 126 - 130
	    printf("\n				Tiros restantes: %i \n", attempts);
		printf("\n				Latitude (linha): ");
	    scanf("%i", &line); line--;
	    printf("				Longitude (coluna): ");
	    scanf("%i", &column); column--;
	    
	    // Detecção de coordenadas fora do campo: linhas 131 - 148
	    while(line > 11 || line < 0 || column > 11 || column < 0)
	    {
			printf("			Vamos com calma, os inimigos não estão tão longe assim.");
		    printf("\n			Tente outras coordenadas.\n");

			printf("\n				Latitude: ");
		    scanf("%i", &line); line--;
		    printf("				Longitude: ");
		    scanf("%i", &column); column--;

		    if(line <= 11 && line >= 0 && column <= 11 && column >= 0)
		    {
		    	break;
			}
		}
	    
	    /*
			verificar resposta: linhas 153 - 197
	    	'if' é acerto, 'else' é errado
	    */
	    if(answerBoard[line][column] == 2)
	    {
	    	//64 = simbolo para acerto
	        playBoard[line][column] = 64;
	        answerBoard[line][column] = 64;
	        
			hit++; 
			attempts++;
	        shot++;
	        
			system("cls");
	        
	        for(line = 0; line < LIN; line++)
			{	
				printf("\n					");
				for(column = 0; column < COL; column++)
				{
					printf(" %c ", playBoard[line][column]);	
				}
			}
			
			printf("\n			Incrivel! Um acerto em cheio!! \n");
		}	
	    else
	    {
	    	// 88 = simbolo para erro
	        playBoard[line][column] = 88;
	        answerBoard[line][column] = 88;
	        
			attempts--;
			shot++;
			
			system("cls");
			
			for(line = 0; line < LIN; line++)
			{
				printf("\n					");
				for(column = 0; column < COL; column++)
				{
					printf(" %c ", playBoard[line][column]);	
				}
			}
	        
	        printf("\n			Droga! Não acertamos eles. Ná próxima você consegue \n");
	    }
	    
	    // 'if' para detectar quando achado todos os navios: 200 - 217
	    if(hit == ship)
	    {
	        system("cls");

			for(line = 0; line < LIN; line++)
		    {
				printf("\n					");
				for(column = 0; column < COL; column++)
				{
					printf(" %c ", answerBoard[line][column]);	
				}
			}
			
			printf("\n			Muito bem! Você destruiu todos os navios.");
			printf("\n			Numero de tiros: %i", shot);
			
			break;
		}
	}while(attempts > 0);
    
    // Tela de derrota: linha 221 - 235
    if(attempts == 0)
	{
        system("cls");
		
		for(line = 0; line < LIN; line++)
	    {	
			printf("\n					");
			for(column = 0; column < COL; column++)
			{
				printf(" %c ", answerBoard[line][column]);	
			}
		}
		printf("\n			Infelizmente você não destruiu todos os navios.");
		printf("\n			Numero de tiros: %i", shot);
	}	
	return 0;
}
