#include<libTableauNoir.h>                                                                                                                                                                                        
#include<math.h>                                                                                                                                                                                                  
#include<stdlib.h>                                                                                                                                                                                                
#include<stdio.h>                                                                                                                                                                                                 
#define nb 55                                                                                                                                                                                         
# define nb1 8                                                                                                                                                                                                   
/***********************/                                                                                                                                                                                          
/* définition de TYPES */                                                                                                                                                                                         
/***********************/                                                                                                                                                                                          
                                                                                                                                                                                                                   
/* coordonnées dans le plan */                                                                                                                                                                                    
typedef struct {                                                                                                                                                                                                   
    double x;                                                                                                                                                                                                      
    double y;                                                                                                                                                                                                      
                                                                                                                                                                                                                   
} coord_t;                                                                                                                                                                                                         
 
/* structure score qui comporte le score et des images portants des chiffres*/ 
typedef struct {                                                                                                                                                                                                   
    Image image[10];                                                                                                                                                                                                      
    int nombre;                                                                                                                                                                                        
   int k;                                                                                                                                                                                                                
} 
score_t;         
                                                                                                                                                                                                                                                                                                                                                                                                                   
/* objet mobile dé??fini par une position p et une vitesse v*/                                                                                                                                                      
typedef struct {                                                                                                                                                                                                   
    coord_t p;                                                                                                                                                                                                     
    coord_t v;                                                                                                                                                                                                     
} mobile_t;                                                                                                                                                                                                        
                                                                                                                                                                                                                   
                                                                                                                                                                                                                   
/* ballon = objet mobile o avec une masse m */                                                                                                                                                                     
typedef struct {                                                                                                                                                                                                   
    mobile_t o;                                                                                                                                                                                                    
    double m;                                                                                                                                                                                                      
} ballon_t;

/* modèle conceptuel : une raquette, un ballon, des briques , et l'état de chaque brique  0 ou 1 */
typedef struct {
    mobile_t raquette;
    mobile_t briques[nb];
    int etat[nb];
    ballon_t ballon;
} modele_t;

/* stylos utilisés pour tracer les objets */
typedef struct {
    tStylo raquette;
    tStylo ballon;
    tStylo briques[nb];
} stylos_t;

/* état du programme :                                                                                                                                                                                            
   contient un modèle conceptuel et des stylos */
typedef struct {
    modele_t modele;
    stylos_t stylos;
    int fini;
} donnees_t;

/********************************/
/* déclaration des fonctions    */
/********************************/

/* initialisation */
	modele_t init_modele();
	stylos_t init_stylos(int,int,int,int );
	void effacer(donnees_t);
	void afficher(donnees_t,score_t);
	int mettre_a_jour(donnees_t *, int,int,score_t*,int);
	donnees_t initialiser_donnees(int,int,int,int);
	void effacerbrique(donnees_t donnees );
	donnees_t lignebrique(float ,donnees_t , int , int , int,int) ;
	int mode_jeu();
	void affichercoeur(int );
	int gagner(donnees_t );
	void menu1(EtatSourisClavier);
	int menu2(EtatSourisClavier );
	void afficher_score(score_t );

/*****************************************************/
/* fonction principale : point d'entré??e du programme */
/*****************************************************/
int main()
{
	/* quelques déclarations importantes*/
	int a,b,c,re,x,j,k,res;
	donnees_t donnees;
	
	score_t scores;
	scores.nombre=0;
	EtatSourisClavier esc = lireEtatSourisClavier();
	j=rand() % 55;
        int vies=3;	
	a=rand()%255;
	b=rand()%255;
	c=rand()%255;
       
       /* la création du tableau et la fixation de queleques paramètres*/
        creerTableau();
        fixerTaille(1920,1080);
        cacherSouris(1);
        choisirCouleurFond(255,255,255);
        Son musique;
	musique=chargerAudio("son.mp3");
	jouerSon(musique,3);
        /* L'appel des fonctions qui vont afficher des menus*/
        menu1(esc);
        effacerTableau();
        res=mode_jeu();   
        effacerTableau();
        k=menu2(esc);
        effacerTableau();
        choisirCouleurFond(255,255,255);
        Image im3=chargerImage("count 3.png" );
        afficherImage(im3,-400,500);
        attendreNms(1000);
        Image im2=chargerImage("count2.png" );
        afficherImage(im2,-350,500);
        attendreNms(1000);
        Image im1=chargerImage("count 1.png" );
        afficherImage(im1,-300,480);
        attendreNms(1000);
        changerTitre("Le casse-briques");
        fixerModeBufferisation(1);
       
    /* initialisation du modèle,des stylos, et quelques élements  */
    donnees = initialiser_donnees(k,a,b,c);
	affichercoeur(-1850/2);
	affichercoeur(-1700/2);
	affichercoeur(-1550/2);
	
	
    /* boucle d'animation */
    
	choisirTypeStylo(10,255,10,10);
	esc = lireEtatSourisClavier();

       while (! donnees.fini) 
       {
        	
       		 /* cré??er l'image sur le buffer */
             
        	afficher(donnees,scores);
	 
        	/* afficher le buffer à?? l'é??cran */
       		 tamponner();
       		 
 		/* effacer le buffer */
 		
		effacer(donnees);
			                                                                                                                                                                                      
     	 	/* mettre à?? jour le contenu de la variable donnees */
     	 	
		vies=mettre_a_jour(&donnees,res,vies,&scores,j);
	
		x=gagner(donnees);
       
	/* si le joueur a gagné */
	
		if (x==2)
		{
	
			while (!fermetureDemandee() && esc.touchesClavier[44] !=1){	
				
       		 	               	esc = lireEtatSourisClavier();
       		 	                Image image4=chargerImage("gagner.png" );	
	 				choisirCouleurFond(255,255,255);
                 		        afficherImage(image4,-1520/2,800/2);              		  
                 		        Image image99=chargerImage("ka7la.xcf" );
                 		        if(vies==1){
                 		       		afficherImage(image99,-650,0);
                 		        }
                 		        if(vies==2){
                 		        	afficherImage(image99,-650,0 );
                 		        	afficherImage(image99,-500,0);
                 		        }
                 		        if(vies==3){
                 		        	afficherImage(image99,-650,0);
                 		        	afficherImage(image99,-500,0);
                 		        	afficherImage(image99,-350,0);
                 		        }
                 		        tamponner();


	 	}
		break;
		}
		
	 }

	 	
		
    
    return EXIT_SUCCESS;
}



/* la fonction qui va afficher les coeurs*/

void affichercoeur(int x)
{
Image image=chargerImage("ka7la.xcf" );
	 afficherImage(image, x - tn_largeur(image)/2, 1000/2 + tn_hauteur(image)/2);
	 }




/* initialisation des données */

donnees_t initialiser_donnees(int k,int a,int b,int c)
{

    
        choisirCouleurFond(215,200,220);
       donnees_t donnees = { .fini=0 };
       donnees.modele = init_modele();
       donnees.stylos = init_stylos(k,a,b,c);
       int i;
       for (i=0;i<nb;i++)
       {
    		donnees.modele.etat[i]=1; /* initialisation des états des briques à 1 */
       }
	
	/*prévention d'un bug */
		
	donnees.modele.etat[47]=0;
	donnees.modele.etat[39]=0;
	donnees.modele.etat[31]=0;
	donnees.modele.etat[23]=0;
	donnees.modele.etat[15]=0;
	donnees.modele.etat[7]=0;
	
	/* traçage des briques */
	
	 donnees=lignebrique(350,donnees,0, 255, 0,0);
	 donnees=lignebrique(300,donnees,255, 0, 0,8);
	 donnees=lignebrique(250,donnees,0, 0, 255,16);
	 donnees=lignebrique(200,donnees,0, 255, 255,24);
	 donnees=lignebrique(150,donnees,255, 255,0, 32);
	 donnees=lignebrique(100,donnees,255, 255, 255,40);
	 donnees=lignebrique(50,donnees,25,55, 255,48);	
	 
    return donnees ;
}












/* initialisation du modèle */

modele_t init_modele()
{
modele_t m = {raquette: {p: {0, 0}, v: {0, 0}}, ballon: {o: {p: {0, -100}, v: {0, -5}}, m: 1}};
	return m;
	}


/* initialisation des stylos */

stylos_t init_stylos(int k,int a,int b,int c)
{
     
    stylos_t stylos;
    /* cré??ation d'un stylo pour la raquette en mé??moire */
    choisirTypeStylo(10,255,255,255);
    /* stockage du stylo */
    stylos.raquette = stockerStylo();
    /* idem pour le ballon */
    
    /* k est une valeur reçue par la fonction qui permet l'utilisateur de choisir la couleur de la balle */
    if (k==1){
    choisirTypeStylo(40,255,  0,  0);
    stylos.ballon  = stockerStylo();
    }
    if (k==2){
    choisirTypeStylo(40,0,0,255 );
    stylos.ballon  = stockerStylo();
   }
   if (k==3){
    choisirTypeStylo(40,255, 255,255);
    stylos.ballon  = stockerStylo();
   }
   if (k==4){
    choisirTypeStylo(40,a, b,c);
    stylos.ballon  = stockerStylo();
   }

    return stylos;
}


/* La fonction qui effacer les briques */

void effacerbrique(donnees_t donnees )
{
int j=0;
  while (j<nb)
  {	
        if (donnees.modele.etat[j]==0)
        {
                        effacerRectangle(donnees.modele.briques[j].p.x - 100,donnees.modele.briques[j].p.y,donnees.modele.briques[j].p.x + 100,donnees.modele.briques[j].p.y+30);
        }
                j++;
  }
}






/* La fonction qui affiche les élements de l'écran*/

void afficher(donnees_t donnees,score_t scores)
{
    selectionnerStylo(donnees.stylos.raquette);
    tracerRectangle(donnees.modele.raquette.p.x-80,-400,donnees.modele.raquette.p.x+80,-370);
    choisirTypeStylo(15,0,255,255);
    tracerSegment(donnees.modele.raquette.p.x-35,-398,donnees.modele.raquette.p.x-35,-373);
    tracerSegment(donnees.modele.raquette.p.x+35,-398,donnees.modele.raquette.p.x+35,-373);
    selectionnerStylo(donnees.stylos.ballon);
    tracerPoint(donnees.modele.ballon.o.p.x, donnees.modele.ballon.o.p.y);
}

/* La fonction qui efface les élement de l'écran*/

void effacer(donnees_t donnees)
{
                                                                                                                                                                         
    selectionnerStylo(donnees.stylos.raquette);
    effacerRectangle(donnees.modele.raquette.p.x-80,-400,donnees.modele.raquette.p.x+80,-370);
    effacerSegment(donnees.modele.raquette.p.x-35,-398,donnees.modele.raquette.p.x-35,-373);
    effacerSegment(donnees.modele.raquette.p.x+35,-398,donnees.modele.raquette.p.x+35,-373);
    effacerbrique(donnees);
    // effacer le ballon                                                                                                                                                                                               
    selectionnerStylo(donnees.stylos.ballon);
    effacerPoint(donnees.modele.ballon.o.p.x, donnees.modele.ballon.o.p.y);
}

/* La fonction qui va mettre à jour l'état du système */

int mettre_a_jour(donnees_t * donnees, int res, int vies, score_t*  score, int j)
{
	EtatSourisClavier esc = lireEtatSourisClavier();
        if (fermetureDemandee()) 
        {
        donnees->fini = 1;
        }
	if (res==1)
	{
     	// la raquette suit la souris                                                                                                                                                                                 
    	donnees->modele.raquette.p.x = esc.sourisX ;
        }
        
        /* Controle avec les flèches */
        
       if (res==2)
       {
   		if (esc.touchesClavier[79]==1)
   		{
        		 donnees->modele.raquette.p.x= donnees->modele.raquette.p.x+15;
       		}
    		if (esc.touchesClavier[80]==1)
    		{
        		 donnees->modele.raquette.p.x= donnees->modele.raquette.p.x-15;
        	}	
    	
       }
    
    
    /* vitesse + position */
    
    donnees->modele.ballon.o.p.x = donnees->modele.ballon.o.p.x + donnees->modele.ballon.o.v.x;
    donnees->modele.ballon.o.p.y = donnees->modele.ballon.o.p.y + donnees->modele.ballon.o.v.y;
    
    /* les conditions de rebondissement de la balle */
    
    if (-930 > donnees->modele.ballon.o.p.x -20){
      donnees->modele.ballon.o.p.x = -910;
      donnees->modele.ballon.o.v.x = -1.0 * donnees->modele.ballon.o.v.x;

    }
    if (930 < donnees->modele.ballon.o.p.x + 20){
      donnees->modele.ballon.o.p.x = 910;
      donnees->modele.ballon.o.v.x = -1.0* donnees->modele.ballon.o.v.x;

    }
    
    /* rebondissement sur la raquette et ses differentes parties */
    
    if ((donnees->modele.ballon.o.p.y -20 <  -320)  &&   (( donnees->modele.ballon.o.p.x  < donnees->modele.raquette. p.x + 100  )&& (donnees->modele.ballon.o.p.x > donnees->modele.raquette. p.x -100 ) ) && (donnees->modele.ballon.o.p.y  >  -320))  {
    
      if((donnees->modele.ballon.o.p.x + 20>donnees->modele.raquette. p.x -100)&&(donnees->modele.ballon.o.p.x + 20<donnees->modele.raquette. p.x - 10)){
      	     donnees->modele.ballon.o.v.x=-9;
             donnees->modele.ballon.o.v.y=9;
             donnees->modele.ballon.o.p.y=-295;
      
      
      
      }
      
      if((donnees->modele.ballon.o.p.x + 20>donnees->modele.raquette. p.x + 10 )&&(donnees->modele.ballon.o.p.x -20 <donnees->modele.raquette. p.x+100))
      {
      		donnees->modele.ballon.o.v.x=9;
                donnees->modele.ballon.o.v.y=9;
                donnees->modele.ballon.o.p.y=-295;
      
      }
           if((donnees->modele.ballon.o.p.x + 20>donnees->modele.raquette. p.x -10 )&&(donnees->modele.ballon.o.p.x - 20 <donnees->modele.raquette. p.x +10 ))
           {
           	donnees->modele.ballon.o.v.x=0;
          	donnees->modele.ballon.o.v.y=9;
                donnees->modele.ballon.o.p.y=-295;
           
           }
    }
   
       
  	
  	
  	
    
    
    if (450 < donnees->modele.ballon.o.p.y -20){
      //donnees->modele.ballon.o.p.y = 450;
      donnees->modele.ballon.o.v.y = -1.0 * donnees->modele.ballon.o.v.y;

    }
    
   /* si la balle tombe en dessous */
   
    if (donnees->modele.ballon.o.p.y -20  < -1080/2 && vies>0 ){
    		attendreNms(500);
    		donnees->modele.ballon.o.p.y  =-100;
		donnees->modele.ballon.o.p.x = 0;
		donnees->modele.ballon.o.v.y=-3;
		donnees->modele.ballon.o.v.x=0;
		vies=vies-1;
		Son musique1;
		
		musique1=chargerAudio("oof.mp3");
		jouerSon(musique1,0);
		if (vies==2)
		{	
			choisirTypeStylo(58,215,200,220);
			tracerPoint(-1555/2,510);
	 		
		}
		if (vies==1)
		{
			choisirTypeStylo(58,215,200,220);
			tracerPoint(-1705/2,510);
		}
		/* le joueur perd */
		
		if (vies==0)
		{
	 		choisirTypeStylo(58,215,200,220);
	 		tracerPoint(-1545/2,510);
	          	esc = lireEtatSourisClavier();
       		 	while (!fermetureDemandee() && esc.touchesClavier[44] !=1)  
       		 	{	
       		 	               	esc = lireEtatSourisClavier();
       		 	               Image image3=chargerImage("lostt.png" );
       		 	               choisirCouleurFond(255,255,255);
                 		        afficherImage(image3,-1520/2,800/2);
                 		        afficher_score(*score);
                 		        tamponner();
                 		       


	 	      }
        	
        	fermerTableau();

        }
	 	 
	}	




	

	/* La condition du rebondissment de la balle sur les briques */
	
	int i=0;
	while(i<nb)
	{
        	if  ((donnees->modele.ballon.o.p.x + 20  > donnees->modele.briques[i].p.x - 100 ) && (donnees->modele.ballon.o.p.x - 20 < donnees->modele.briques[i].p.x + 100 )  && (donnees->modele.etat[i]==1 ))
        	{
               		if (donnees->modele.ballon.o.p.y + 20  > donnees->modele.briques[i].p.y    && donnees->modele.ballon.o.p.y -+20  < donnees->modele.briques[i].p.y + 30 )
              		{                                           
		
                		donnees->modele.ballon.o.v.y = -1.04 * donnees->modele.ballon.o.v.y;
                		donnees->modele.etat[i]=0;
               		 	Son musique2;
				musique2=chargerAudio("item.mp3");
				jouerSon(musique2,0);
				score->nombre=score->nombre+1;
		
	

                	}
              }
              
                i++;
        }
       
    
      
	if ((((donnees->modele.ballon.o.p.x + 20 > donnees->modele.briques[i].p.x - 100) && (donnees->modele.ballon.o.p.y >  donnees->modele.briques[i].p.y) && ( donnees->modele.ballon.o.p.y <  donnees->modele.briques[i].p.y +30)) && (donnees->modele.etat[i]==1))  || (((donnees->modele.ballon.o.p.x - 15 < donnees->modele.briques[i].p.x + 100) && (donnees->modele.ballon.o.p.y >  donnees->modele.briques[i].p.y) && ( donnees->modele.ballon.o.p.y <  donnees->modele.briques[i].p.y +30) && (donnees->modele.etat[i]==1 ))))
	{
	 
      		donnees->modele.ballon.o.v.x = -1.0 * donnees->modele.ballon.o.v.x;
     		donnees->modele.etat[i]=0; 
		score->nombre=score->nombre+1;
       		  
	 }       
       
        
        
return vies;
}                                                                                                                                                                                                             




/* La fonction qui trace une ligne de briques */

donnees_t lignebrique(float y,donnees_t  donnees, int R, int G, int B,int j)
{

	 int a,c,x;
         a=-800;
         c=-600;
         x=0;
        while (x<7)
        {
                    	if (donnees.modele.etat[j]==1)
                    	{
				choisirTypeStylo(1,R,G,B);
				choisirCouleurPinceau(R,G,B);
				tracerRectangle(a,y,c,y+30);
				donnees.modele.briques[j].p.x=(a+c)/2;
				donnees.modele.briques[j].p.y=y;
			        x++;
                                j++;
			}
                a=a+225;
                c=c+225;
                }
	return donnees;
}


/* La fonction qui determine le mode de jeu (souris/clavier) */

int mode_jeu(EtatSourisClavier esc)
{
	
        int k=2;
        while (!fermetureDemandee())  
        {
        	esc = lireEtatSourisClavier();      
		Image image=chargerImage("mode.png" );
        	afficherImage(image, 0 - tn_largeur(image)/2, 0 + tn_hauteur(image)/2);
       
        	if (esc.sourisBoutonDroit==1||esc.sourisBoutonGauche==1)
        	{
        		k=1;	   
        		break;     		
        	}
        	if (esc.touchesClavier[79]==1||esc.touchesClavier[80]==1)
        	{
        		k=2;
        		break;
        	}
                 		
        }
	return k;
}

/* La fonction qui déroulera le menu 1*/

void menu1(EtatSourisClavier esc)
{
	   while (!fermetureDemandee())  
	   {
        	 esc = lireEtatSourisClavier();	          
	         Image image10=chargerImage("menu.png" );
                 afficherImage(image10, 0 - tn_largeur(image10)/2, 0 + tn_hauteur(image10)/2);
		if(esc.touchesClavier[44]==1)
		{
			break;
		}
		
	   }
	   
}

/* La fonction qui déroulera le menu 2*/


int menu2(EtatSourisClavier esc)
{
	   int k=0;
	   while (!fermetureDemandee())  
	   {
        	 esc = lireEtatSourisClavier();	          
	         Image image10=chargerImage("menu2.png" );
                 afficherImage(image10, 0 - tn_largeur(image10)/2, 0 + tn_hauteur(image10)/2);
		 if(esc.touchesClavier[89]==1)
		 {
			k= 1;
			break;
		}
		if(esc.touchesClavier[90]==1)
		{
			k= 2;
			break;
		}
		if(esc.touchesClavier[91]==1)
		{
			k= 3;
			break;
		}
		if(esc.touchesClavier[92]==1)
		{
			k= 4;
			break;
		}
	}
	return k;


}

/* La fonction qui la vérifie la condition de la victoire */

int gagner(donnees_t donnees)
{

int i=0;
while(i<nb)
{
	if (donnees.modele.etat[i]==1)
	{
		return 1;	
	}
	i++;
}

return 2;
}


/* La fonction qui afficher le score à la fin */

void afficher_score(score_t score)
{
	int d,u;
	if(score.nombre<9){
	d=0;
	}
	else{
	d=(score.nombre)/10;
	}
	u=(score.nombre)-d*10;
	Image im0,im1,im2,im3,im4,im5,im6,im7,im8,im9;
	im0=chargerImage("0.png");
	im1=chargerImage("1.png");
	im2=chargerImage("2.png");
	im3=chargerImage("3.png");
	im4=chargerImage("4.png");
	im5=chargerImage("5.png");
	im6=chargerImage("6.png");
	im7=chargerImage("7.png");
	im8=chargerImage("8.png");
	im9=chargerImage("9.png");
	
	score.image[0]=rotozoomImage(im0,0,0.3,0.3);
	score.image[1]=rotozoomImage(im1,0,0.3,0.3);
	score.image[2]=rotozoomImage(im2,0,0.3,0.3);
	score.image[3]=rotozoomImage(im3,0,0.3,0.3);
	score.image[4]=rotozoomImage(im4,0,0.3,0.3);
	score.image[5]=rotozoomImage(im5,0,0.3,0.3);
	score.image[6]=rotozoomImage(im6,0,0.3,0.3);
	score.image[7]=rotozoomImage(im7,0,0.3,0.3);
	score.image[8]=rotozoomImage(im8,0,0.3,0.3);
	score.image[9]=rotozoomImage(im9,0,0.3,0.3);
	
	
	for (int t=0; t<10;t++)
	{
		if(t==u) {afficherImage(score.image[t],10,90);}
	}
	for ( int w=0;w<10;w++)
	{
		if(w==d) {afficherImage(score.image[w],-80,90);}
	}
	
}

/* Fin du programme */

