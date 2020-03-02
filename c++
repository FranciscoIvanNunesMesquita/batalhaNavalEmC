#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define N_map 10 // map NxN
#define N_lenShip 4  // tamanho do navio
#define N_ships 3
#define N_turns 20000 // quantidade de rodadas
#define simbShip 254
#define simbShipFired 176
#define simSea 126
#define simFired 88
using namespace std;
/*lista de codigos para retorno de funcao int
200: simbolo nao encontrado no mapa
201: navio completo
202: ponta de navio ja conhecida
203: sem este simbolo nas imediacoes
*/

class Player
{
public:
    char mapaView[N_map][N_map];
    char mapaBackGround[N_map][N_map];
    char mapBackUpHits[N_map][N_map];

    void buildMap(char mapa[][N_map],char c) // gera o mapa com tamanho NxN e com elementos c
    {
        int i,j;

        for(i=0,j=0; i<N_map; i++)
        {
            mapa[i][j] = c;
            for(j=1; j<N_map; j++)
            {
                mapa[i][j] = c;
            }
            j=0;
        }
    }

    void insertShipHorinzontal(char map[][N_map],int i,int j)
    {

        int l;
        l = j+N_lenShip;
        for(; j<l; j++)
            map[i][j] = simbShip;

    }
    void insertShipVertical(char map[][N_map],int i,int j)
    {

        int l;
        l = i+N_lenShip;

        for(; i<l; i++)
            map[i][j] = simbShip;
    }
    void radomPositionShip(char map[][N_map])
    {
        int i,j,n,i2,s,ps;
        Sleep(1000);
        srand( (unsigned)time(NULL) );
        for(n=0; n<N_ships; n++)
        {


            i = rand()%N_map;

            j = rand()%N_map;

            s = rand()%2;


            if(i>=(N_map-N_lenShip))//verifica se x esta fora do intervalo
            {
                i=(N_map-N_lenShip);
            }
            if(i>=(N_map-N_lenShip))//verifica se y esta fora do intervalo
            {
                j=(N_map-N_lenShip);
            }

            if(s==1)
            {
                //printf("if horitontal\n");
                for(i2=0; i2<N_lenShip; i2++)
                {
                    if(map[i][j+i2] == (char)simbShip)
                    {
                        //printf("%c ",map[i][j+i2]);
                        // printf("horizontal L:%i C:%i\n",i,j);
                        i2=N_lenShip+1;
                        n=n-1;
                    }
                    else
                    {

                        if(i2==(N_lenShip-1))
                        {
                            //  printf("%c ",map[i][j]);
                            //printf("horizontal L:%i C:%i\n",i,j);
                            insertShipHorinzontal(map,i,j);

                            i2=N_lenShip+1;

                        }
                    }
                }


            }
            if(s==0)
            {
                for(i2=0; i2<N_lenShip; i2++)
                {
                    if(map[i+i2][j] == (char) simbShip)
                    {
                        //printf("%c ",map[i][j+i2]);
                        //printf("vertical L:%i C:%i\n",i,j);
                        i2 = N_lenShip+1;
                        n=n-1;
                    }
                    else

                    {
                        if(i2==(N_lenShip-1))
                        {
                            //printf("%c ",map[i][j]);
                            //  printf("vertical L:%i C:%i\n",i,j);
                            insertShipVertical(map,i,j);

                            i2 = N_lenShip+1;
                        }
                    }
                }
            }
        }



    }
    int searchSimbInMap(char mapS[][N_map],int simSearch,char coord)
    {
        int i,j,i2,j2;

        for(i=0; i<N_map; i++)
        {
            for(j=0; j<N_map; j++)
            {
                if(mapS[i][j] == (char)simSearch)
                {
                    i2=i;
                    j2=j;
                    i = N_map;
                    j = N_map;

                }
                else
                {
                    if((i==N_map-1)&&(j==N_map-1))
                        return 200; // nao encontrado
                }
            }
        }
        if(coord == 'i')
            return i2;
        if(coord == 'j')
            return j2;
    }
    int findRadomCoordinates(char mapR[][N_map],int simbSearch,char tCoord)
    {
        int i,j,i2;
        srand( (unsigned)time(NULL) );
        i = rand()%N_map;
        j = rand()%N_map;
        do
        {
            if(mapR[i][j]==simbSearch)
            {
                i2 = 0;
            }
            else
            {
                i = rand()%N_map;
                j = rand()%N_map;
                i2 = 1;

            }
        }
        while(i2==1);
        if(tCoord=='j')
            return j;
        if(tCoord=='i')
            return i;

    }
    int searchSimbInImediations(char m[][N_map],int i, int j,char coor,int simb)
    {
        if(m[i+1][j]==(char)simb)
        {
            if(simb != simbShipFired)
            {
                if(coor=='i')
                    return i+1;
                if(coor=='j')
                    return j;
            }
            else
            {
                if(coor=='i')
                    return i-1;
                if(coor=='j')
                    return j;
            }

        }
        else
        {
            if(m[i-1][j]==(char)simb)
            {

                if(simb != simbShipFired)
                {
                    if(coor=='i')
                        return i-1;
                    if(coor=='j')
                        return j;
                }
                else
                {
                    if(coor=='i')
                        return i+1;
                    if(coor=='j')
                        return j;
                }

            }
            else
            {
                if(m[i][j+1]==(char)simb)
                {
                    if(simb != simbShipFired)
                    {
                        if(coor=='i')
                            return i;
                        if(coor=='j')
                            return j+1;
                    }
                    else
                    {
                        if(coor=='i')
                            return i;
                        if(coor=='j')
                            return j-1;
                    }

                }
                else
                {
                    if(m[i][j-1]==(char)simb)
                    {

                        if(simb != simbShipFired)
                        {
                            if(coor=='i')
                                return i;
                            if(coor=='j')
                                return j-1;
                        }
                        else
                        {
                            if(coor=='i')
                                return i;
                            if(coor=='j')
                                return j+1;
                        }

                    }
                    else
                    {
                        return 203;
                    }
                }
            }
        }



    }
    int searchNextPositionToFire(char mapViewTarget[][N_map],char mapbackGroundTarget[][N_map],int i1,int j2,char coor)
    {
        int i_simbShipFired,j_simbShipFired;
        int  i_simSea,j_simSea;
        int i_simFired,j_simFired;

        i_simSea = searchSimbInImediations(mapViewTarget,i1,j2,'i',simSea);
        j_simSea = searchSimbInImediations(mapViewTarget,i1,j2,'j',simSea);

        i_simbShipFired = searchSimbInImediations(mapViewTarget,i1,j2,'i',simbShipFired);
        j_simbShipFired = searchSimbInImediations(mapViewTarget,i1,j2,'j',simbShipFired);


        //   i_simFired = searchSimbInImediations(mapViewTarget,i1,j2,'i',simFired);
        // j_simFired = searchSimbInImediations(mapViewTarget,i1,j2,'j',simFired);

        if(j_simbShipFired!=203&&(mapViewTarget[i_simbShipFired][j_simbShipFired]==(char)simSea))
        {
            if(coor=='i')
                return i_simbShipFired;
            if(coor=='j')
                return j_simbShipFired;
        }
        else
        {

            if(coor=='i')
                return i_simSea;
            if(coor=='j')
                return j_simSea;
        }
    }
    void fire(char mapViewTarget[][N_map],char mapbackGroudTarget[][N_map],int i_atual,int j_atual, int i2_proximo,int j2_proximo)
    {
        if(mapbackGroudTarget[i2_proximo][j2_proximo] == (char)simbShip)
        {


            mapViewTarget[i_atual][j_atual] = simbShipFired;
            mapViewTarget[i2_proximo][j2_proximo] = simbShip;
        }
        else
        {
            mapViewTarget[i2_proximo][j2_proximo] = simFired;
        }

    }
    void copyMap(char mapSource[][N_map],char mapDestiny[][N_map])
    {
        for(int i=0; i<N_map; i++)
        {
            for(int j=0; j<N_map; j++)
            {
                mapDestiny[i][j]=mapSource[i][j];
            }
        }
    }
    int verifyShipComplet(char mapViewTarget[][N_map],int i,int j,char coor)
    {

        if(mapViewTarget[i+1][j]==(char)simbShipFired)
        {
            if(mapViewTarget[i+N_lenShip][j]==(char)simSea)
            {
                if(coor=='i')
                    return i+N_lenShip;
                if(coor=='j')
                    return j;
            }
            else
            {
                return 204;
            }

        }
        else
        {

            if(mapViewTarget[i-1][j]==(char)simbShipFired)
            {
                if(mapViewTarget[i-N_lenShip][j]==(char)simSea)
                {
                    if(coor=='i')
                        return i-N_lenShip;
                    if(coor=='j')
                        return j;
                }
                else
                {
                    return 204;
                }

            }
            else
            {
                if(mapViewTarget[i][j+1]==(char)simbShipFired)
                {
                    if(mapViewTarget[i][j+N_lenShip]==(char)simSea)
                    {
                        if(coor=='i')
                            return i;
                        if(coor=='j')
                            return j+N_lenShip;
                    }
                    else
                    {
                        return 204;
                    }

                }
                else
                {
                    if(mapViewTarget[i][j-1]==(char)simbShipFired)
                    {
                        if(mapViewTarget[i][j-N_lenShip]==(char)simSea)
                        {
                            if(coor=='i')
                                return i;
                            if(coor=='j')
                                return j-N_lenShip;
                        }
                        else
                        {
                            return 204;
                        }

                    }
                    else
                    {
                        return 204;
                    }
                }
            }
        }
    }
    void AI_fire (char mapViewTarget[][N_map],char mapBackGroundTarget[][N_map])
    {
        int i,j,i2,j2,aux;
        // retorna a localizacao de navio se houver
        i = searchSimbInMap(mapViewTarget,simbShip,'i');
        j = searchSimbInMap(mapViewTarget,simbShip,'j');
        if(j==200) // não há navios ?
        {
            // gerar coordenadas ramdomicas
            i2 = findRadomCoordinates(mapViewTarget,simSea,'i');
            j2 = findRadomCoordinates(mapViewTarget,simSea,'j');
            fire(mapViewTarget,mapBackGroundTarget,i,j,i2,j2);

        }
        else // entap há navio
        {
            // verificar imediacoes
            i2 = searchNextPositionToFire(mapViewTarget,mapBackGroundTarget,i,j,'i');
            j2 = searchNextPositionToFire(mapViewTarget,mapBackGroundTarget,i,j,'j');
            if(j2==203)
            {
                i2 = verifyShipComplet(mapViewTarget,i,j,'i');
                j2 = verifyShipComplet(mapViewTarget,i,j,'j');
                if(j2==204) // navio completo?
                {
                    i2 = findRadomCoordinates(mapViewTarget,simSea,'i');
                    j2 = findRadomCoordinates(mapViewTarget,simSea,'j');
                }
                fire(mapViewTarget,mapBackGroundTarget,i,j,i2,j2);
                mapViewTarget[i][j] = simbShipFired;
            }
            else
            {
                fire(mapViewTarget,mapBackGroundTarget,i,j,i2,j2);
            }


        }


    }

};


class System
{
public:
    void screenSettings()
    {
        system("MODE con cols=100 lines=29"); //Redimensiona a tela
        system("color 3F");
    }
    void clearScreen() // limpa tela
    {

        system("cls");
    }

    void printOneMap(char mapa[][N_map]) // imprime um mapa NxN

    {

        int o = 0 ;
        int i,j,l=0;
        char alfaC[] = "ABCDEFGHIJKLMNOPQRST";
        cout << "  ";//A B C D E F G H I J K L M N O P Q R S T
        for(o=0; o<N_map; o++)
        {
            cout << " "<< alfaC[o];
        }
        cout << "\n";
        for(j=0,i=0; i<N_map; i++)
        {
            if(l<10)
                cout << " ";//comeco da linha
            cout << l <<" "<< mapa[i][j];
            for(j=1; j<N_map; j++)//j varia
            {
                cout<<" "<<mapa[i][j];
                if(j==(N_map-1))
                    cout << "\n";// fim da linha i varia

            }
            j=0;
            l++;
        }
    }

    void printTwoMaps(char map1[][N_map],char map2[][N_map]) // imprime dois mapas lado a lado com tamanhos NxN
    {

        int o = 0 ;
        int i,j,l=0;
        char alfaC[] = "ABCDEFGHIJKLMNOPQRST";
        cout<<"  ";//A B C D E F G H I J K L M N O P Q R S T    A B C D E F G H I J K L M N O P Q R S T\n");
        for(o=0; o<N_map; o++)
        {
            cout <<" "<<alfaC[o];
        }
        cout<<"   ";
        for(o=0; o<N_map; o++)

        {
            cout<<" "<<alfaC[o];
        }
        cout<<"\n";

        for(j=0,i=0; i<N_map; i++)
        {
            if(l<10)
                cout<<" ";//comeco da linha
            cout << l <<" "<< map1[i][j];
            for(j=1; j<N_map; j++)//j varia
            {
                cout<<" "<<map1[i][j];
                if(j==(N_map-1))

                    for(j=0; j<N_map;)
                    {
                        if(l<10)
                            cout<<" ";//comeco da linha
                        cout << " " << l << " " << map2[i][j];
                        for(j=1; j<N_map; j++)//j varia
                        {
                            cout<<" "<<map2[i][j];
                            if(j==(N_map-1))
                                cout<<"\n";// fim da linha i varia

                        }

                    }

            }
            j=0;
            l++;
        }
    }



};
int main()
{
    int i,j,i2,j2;
    //system settings
    System systemGame;
    systemGame.screenSettings();
    // bot1 settings
    Player bot1;
    bot1.buildMap(bot1.mapaView,'~');
    bot1.buildMap(bot1.mapaBackGround,'X');
    bot1.radomPositionShip(bot1.mapaBackGround);


    Player bot2;
    bot2.buildMap(bot2.mapaView,'~');
    bot2.buildMap(bot2.mapaBackGround,'X');
    bot2.radomPositionShip(bot2.mapaBackGround);

    //i = bot1.searchSimbInMap(bot1.mapaBackGround,simbShip,'i');
    //j = bot1.searchSimbInMap(bot1.mapaBackGround,simbShip,'j');

    //i2 = bot1.searchEndShipPosition(bot1.mapaBackGround,i,j,'i');
    //j2 = bot1.searchEndShipPosition(bot1.mapaBackGround,i,j,'j');
    //cout<<"i:"<<i<<" j:"<<j<<"\n";
    //cout<<"i:"<<i2<<" j:"<<j2<<"\n";
    Sleep(1000);
    for(i=0; i<100; i++)
    {
        bot1.AI_fire(bot2.mapaView,bot2.mapaBackGround);
        Sleep(100);
        bot2.AI_fire(bot1.mapaView,bot1.mapaBackGround);



        cout<<i<<"\n";
        systemGame.printTwoMaps(bot1.mapaView,bot2.mapaView);
        Sleep(1000);
        systemGame.clearScreen();


    }

    return 0;
}

