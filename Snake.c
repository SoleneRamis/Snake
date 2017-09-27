#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define CYCLE 100000L
#define SECONDE 1000000L

struct tete{
  int coordX;
  int coordY;
  int taille;
  int direction;
};
struct cellule{
  int coordX;
  int coordY;
};

int Menu(void);
int Regles(void);
int Jeu(void);
void Afficher(struct tete*,struct cellule*,struct cellule*,struct cellule*,struct cellule*);
void Deplacement(struct tete*,struct cellule*);
int GameOver(int);
int Pomme(int,struct cellule*);
int CreerEscargotCiseaux(struct cellule*,struct cellule*,int);
int TestPosS(struct tete*,struct cellule*,struct cellule*,struct cellule*,struct cellule*,long int*);

int Menu(void){
  int SposX,SposY,jeu=0;
  EffacerEcran(CouleurParNom("white"));
  ChargerImageFond("images/index.png");
  while (jeu==0){   
    if (SourisCliquee()){
      SposX = _X;
      SposY = _Y;
      if (SposX>422 && SposX<787 && SposY>275 && SposY<392){
	return(Jeu());
      }else if (SposX>422 && SposX<787 && SposY>425 && SposY<542){
	return(Regles());
      }else if (SposX>422 && SposX<787 && SposY>582 && SposY<699){
	jeu=1;
      }
    }
  }
  FermerGraphique();
  return EXIT_SUCCESS;
}

int Regles(void){
  int SposX,SposY;
  EffacerEcran(CouleurParNom("white"));
  ChargerImageFond("images/index2.png");
   while (1){   
    if (SourisCliquee()){
      SposX = _X;
      SposY = _Y;
      if (SposX>905 && SposX<952 && SposY>1 && SposY<54){
	return(Menu());
      }      
    }
  }
}

void Afficher(struct tete* teteS,struct cellule* tabS,struct cellule* tabP,struct cellule* escargot,struct cellule* ciseaux){
  int cmpt=0,pomme;
  EffacerEcran(CouleurParComposante(123,172,127));
  if(teteS->direction==0){
    ChargerImage("images/tete0.png",teteS->coordX,teteS->coordY,0,0,20,20);
  }else if(teteS->direction==1){
    ChargerImage("images/tete1.png",teteS->coordX,teteS->coordY,0,0,20,20);
  }else if(teteS->direction==2){
    ChargerImage("images/tete2.png",teteS->coordX,teteS->coordY,0,0,20,20);
  }else{
    ChargerImage("images/tete3.png",teteS->coordX,teteS->coordY,0,0,20,20);
  }
  while(cmpt<teteS->taille){
    ChargerImage("images/corps.png",tabS[cmpt].coordX,tabS[cmpt].coordY,0,0,20,20);
    cmpt++;
  }
  cmpt=0;
  ChoisirCouleurDessin(CouleurParNom("black"));
  while(cmpt<5){
    ChargerImage("images/pomme1.png",tabP[cmpt].coordX,tabP[cmpt].coordY,0,0,20,20);
    cmpt++;
  }
  ChargerImage("images/escargot.png",escargot->coordX,escargot->coordY,0,0,20,20);
  ChargerImage("images/ciseaux.png",ciseaux->coordX,ciseaux->coordY,0,0,20,20);
}

void Deplacement(struct tete* teteS,struct cellule* tabS){
  int Xtps=teteS->coordX,Ytps=teteS->coordY,cmpt=teteS->taille;
  if(teteS->direction==0){
    teteS->coordX=teteS->coordX-20;
  }else if(teteS->direction==1){
    teteS->coordY=teteS->coordY-20;
  }else if(teteS->direction==2){
    teteS->coordX=teteS->coordX+20;
  }else{
    teteS->coordY=teteS->coordY+20;
  }
  while(cmpt>0){
    tabS[cmpt].coordX=tabS[cmpt-1].coordX;
    tabS[cmpt].coordY=tabS[cmpt-1].coordY;
    cmpt--;
  }
  tabS[0].coordX=Xtps;
  tabS[0].coordY=Ytps;
}

int GameOver(int death){
  int SposX,SposY;
  couleur c;
  EffacerEcran(CouleurParNom("black"));
  ChargerImage("images/GameOver.png",0,0,0,0,1200,800);
  c=CouleurParNom("white");
  ChoisirCouleurDessin(c);
  /*EcrireTexte(80,80,"Game Over",2);
  DessinerRectangle(610,690,50,30);
  EcrireTexte(630,710,"Play Again",0);
  DessinerRectangle(610,730,50,30);
  EcrireTexte(630,750,"Back",0);*/
  while (1){   
    if (SourisCliquee()){
      SposX = _X;
      SposY = _Y;
      if (SposX>600 && SposX<723 && SposY>752 && SposY<789){
	return(Menu());
      }else if(SposX>500 && SposX<600 && SposY>752 && SposY<789){
	return(Jeu());
      }
    }
  }
}

int Pomme(int numP,struct cellule* tabP){
  int j;
  tabP[numP].coordX=round((rand()%1180)/20)*20;
  tabP[numP].coordY=round((rand()%780)/20)*20;
  for (j=0;j<5;j++){
    if (tabP[j].coordX==tabP[numP].coordX && tabP[j].coordY==tabP[numP].coordY){
      tabP[numP].coordX=round((rand()%1180)/20)*20;
      tabP[numP].coordY=round((rand()%780)/20)*20;
    }
  }
}

int CreerEscargotCiseaux(struct cellule* escargot,struct cellule* ciseaux,int choix){
  if(choix==0){
    escargot->coordX=round((rand()%1180)/20)*20;
    escargot->coordY=round((rand()%780)/20)*20;
  }else if(choix==1){
    ciseaux->coordX=round((rand()%1180)/20)*20;
    ciseaux->coordY=round((rand()%780)/20)*20;
  }
}

int TestPosS(struct tete* teteS,struct cellule* tabS,struct cellule* tabP,struct cellule* escargot, struct cellule* ciseaux,long int* delais){
  int death=0,cmpt=0,choix;
  if(teteS->coordX<0 || teteS->coordX>1180 || teteS->coordY<0 || teteS->coordY>780){
    death=1;
  }
  while(cmpt<5){
    if(teteS->coordX==tabP[cmpt].coordX && teteS->coordY==tabP[cmpt].coordY){
      teteS->taille=teteS->taille+2;
      Pomme(cmpt,tabP);
    }
    cmpt++;
  }
  cmpt=0;
  while(cmpt<teteS->taille){
    if(teteS->coordX==tabS[cmpt].coordX && teteS->coordY==tabS[cmpt].coordY){
      death=1;
    }
    cmpt++;
  }
  if(teteS->coordX==escargot->coordX && teteS->coordY==escargot->coordY){
    *delais=*delais/2;
    choix=0;
    CreerEscargotCiseaux(escargot,ciseaux,choix);
  }else if(teteS->coordX==ciseaux->coordX && teteS->coordY==ciseaux->coordY){
    teteS->taille=teteS->taille-4;
    choix=1;
    CreerEscargotCiseaux(escargot,ciseaux,choix);
    if(teteS->taille<1){
      death=1;
    }
  }
  if(death!=0){
    return(GameOver(death));
  }
  return(0);
}

int Jeu(void){
  EffacerEcran(CouleurParNom("white"));
  int fin=0,pause=0,T,cmpt=0,seconde=0,nbrTour=0,score,choix;
  long int suivant,suivant2,delais=0L;
  struct tete teteS={600,400,9,2};
  struct cellule tabS[2400];
  struct cellule tabP[5];
  struct cellule escargot;
  struct cellule ciseaux;
  char temps[100],scoreText[1000];
  unsigned int Timer = 0;
  suivant=Microsecondes()+CYCLE;
  suivant2=Microsecondes()+SECONDE;
  while(cmpt<10){
    tabS[cmpt].coordX=580-(cmpt*20);
    tabS[cmpt].coordY=400;
    cmpt++;
  }
  cmpt=0;
  while(cmpt<5){
    tabP[cmpt].coordX=0;
    tabP[cmpt].coordY=0;
    cmpt++;
  }
  cmpt=0;
  while(cmpt<5){
    Pomme(cmpt,tabP);
    cmpt++;
  }
  choix=0;
  CreerEscargotCiseaux(&escargot,&ciseaux,choix);
  choix=1;
  CreerEscargotCiseaux(&escargot,&ciseaux,choix);
  Afficher(&teteS,tabS,tabP,&escargot,&ciseaux);
  while(fin==0){
    if(Microsecondes()<suivant){
      if(ToucheEnAttente()){
	T=Touche();
	if(T==XK_Left && teteS.direction!=2){
	  if(teteS.direction==0){
	    delais=delais+2000L;
	  }
	  teteS.direction=0;
	}else if(T==XK_Up && teteS.direction!=3){
	  if(teteS.direction==1){
	    delais=delais+2000L;
	  }
	  teteS.direction=1;
	}else if(T==XK_Right && teteS.direction!=0){
	  if(teteS.direction==2){
	    delais=delais+2000L;
	  }
	  teteS.direction=2;
	}else if(T==XK_Down && teteS.direction!=1){
	  if(teteS.direction==3){
	    delais=delais+2000L;
	  }
	  teteS.direction=3;
	}else if(T==XK_Escape){
	  fin=1;
	}else if(T==XK_space){
	  pause=1;
	  while(pause!=0){
	    T=Touche();
	    if(T==XK_space){
	      pause=0;
	    }else if(T==XK_Escape){
	      pause=0;
	      fin=1;
	    } 
	  }   
	}
      }
      if(Microsecondes()>suivant2){
	Timer++;
	suivant2=Microsecondes()+SECONDE;
      }
    }else{
      Deplacement(&teteS,tabS);
      TestPosS(&teteS,tabS,tabP,&escargot,&ciseaux,&delais);
      Afficher(&teteS,tabS,tabP,&escargot,&ciseaux);
      CouleurParNom("black");
      bzero(temps, strlen(temps));
      suivant = Microsecondes()+CYCLE-delais;
      sprintf(temps,"temps : %d",Timer);
      EcrireTexte(450,80,temps,1);
      score=(teteS.taille-9)/2;
      if(score<0){
	score=0;
      }
      sprintf(scoreText,"score : %d",score);
      EcrireTexte(550,80,scoreText,1);
      if(nbrTour%20==0){
	if(delais<CYCLE-2001L){
	  delais=delais+2000L;
	}
      }
      nbrTour++;
    } 
  }
  return(Menu());
}

int main(void){
  srand((unsigned int) time(NULL));
  InitialiserGraphique();
  CreerFenetre(50,50,1200,800);
  Menu();
}
