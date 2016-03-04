//Focsaneanu Ciprian - 324 CB - Tema 1 AA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct transition // structura tranzitiilor citite
{
    int nextState;      // starea urmatoare
    char symbolWrite;   // simbolul ce trebuie scris
    char direction;     // directia in care trebuie sa mearga cursorul

};
int main(void)
{
    //citim inputul
    FILE *fp;
    fp = fopen ("date.in","r");
    if ( fp == NULL)
    {
        // eroare la deschiderea fisierului
        return -1;
    }
    char *tape = (char*)malloc(101*sizeof(char));     // banda de maxim 100 caractere
    //verificare fisier not empty
    char *token;
    if ( fgets(tape,100,fp) != NULL )
    {
        token=strtok(tape," \n");
    }
    int states, finalStates;
    fscanf(fp,"%d %d",&states,&finalStates);
    char *line = (char*)malloc(101*sizeof(char));
    fgets(line,100,fp);     // terminam linia cu numarul de stari si stari finale
    int i,j;
    int auxState;
    struct transition *t = (struct transition *)malloc( 3 * (states - finalStates) * sizeof(struct transition));
    for(i=0; i< 3 * (states - finalStates); i++)
    {
            fgets(line,100,fp);
            token = strtok(line," \n");
            auxState=0;
            if( token[0] != '-')
            {
                for(j=0; j< strlen(token); j++)
                {
                    auxState = auxState*10 + token[j] - '0';
                }
                t[i].nextState = auxState;
                // identificam char-ul care trebuie scris
                token = strtok(NULL," \n");
                t[i].symbolWrite = token[0];
                // indetificam char-ul pentru deplasare
                token = strtok(NULL," \n");
                t[i].direction = token[0];
                //printf("Pentru i: %d, next %d write %c go %c\n",i,t[i].nextState,t[i].symbolWrite,t[i].direction);
            }
            else
            {
                t[i].nextState = -1;
                // identificam doar char-ul care trebuie scris
                t[i].symbolWrite = '-';
                t[i].direction = '-';
            }
    }
    int currentState=0, cursor = 1;
    int ok=1;
    FILE * fout;
    fout = fopen("date.out","w");
    while ( currentState < states - finalStates )
    {
        if( tape[cursor] == '0' )
        {   if(t[currentState*3].symbolWrite == '-')
            {
                ok=0;
                fprintf(fout,"Eroare!");
                break;
            }
            if( currentState >= states - finalStates) break;
            tape[cursor] = t[currentState*3].symbolWrite;
            if( t[currentState*3].direction == 'L' )
                cursor--;
            if( t[currentState*3].direction == 'R' )
                cursor++;
            currentState = t[currentState*3].nextState;
        }
        if( tape[cursor] == '1' )
        {
            if(t[currentState*3 + 1].symbolWrite == '-')
            {
                ok=0;
                fprintf(fout,"Eroare!");
                break;
            }
            if( currentState >= states - finalStates) break;
            tape[cursor] = t[currentState*3 + 1].symbolWrite;
            if( t[currentState*3 + 1].direction == 'L' )
                cursor--;
            if( t[currentState*3 + 1].direction == 'R' )
                cursor++;
            currentState = t[currentState*3 + 1].nextState;
        }
        if( tape[cursor] == '#' )
        {   if(cursor == 0 && t[currentState*3 + 2].direction == 'L') break;
            if(t[currentState*3 + 2].symbolWrite == '-')
            {
                ok=0;
                fprintf(fout,"Eroare!");
                break;
            }
            if( currentState >= states - finalStates) break;
            tape[cursor] = t[currentState*3 + 2].symbolWrite;
            if( t[currentState*3 + 2].direction == 'L' )
                cursor--;
            if( t[currentState*3 + 2].direction == 'R' )
                cursor++;
            currentState = t[currentState*3 + 2].nextState;
        }
    }
    if (ok == 1 )
        fprintf(fout,"%s",tape);
    fclose(fout);
    fclose(fp);
    return 0;
}
