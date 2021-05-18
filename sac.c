# include <stdlib.h>
# include <stdio.h>

//LOUGANI FAOUZI M1 CHPS UVSQ

/*
Pour compiler : gcc -o sac.c
Pour l'exécuter : ./a.out 
*/


// cette fonction permet de maximiser la fonction objective et de mettre les objets dans le sac  
void selection(int capacite,int nb_objets,int *poid,int *valeur,int *dans_le_sac){
	
	double max; 
	int temp;
	for(int j=nb_objets-1;j>=-1;j--)
	{
	temp=-1; 
	max=0; 
		
        for (int i=0; i<nb_objets; i++)
        if(dans_le_sac[i]==0) //si l'objet n'est pas encore séléctionné 
        {
          if(poid[i]==capacite||poid[i]<capacite)//si le poid de l objet n'a pas dépassé la capacité du sac 
          {
             if( (*(valeur+i)/(*(poid+i)))==max || (*(valeur+i)/(*(poid+i)))>max )
             max=*(valeur+i)/(*(poid+i));   //on calcul valeur/poids
             temp=i;
          }
        }        
        // l’objet qui a le maximum de valeur/poids parmi les objet on le met dans le sac 			
	 if (temp!=-1){
	            *(dans_le_sac+temp)=1; 
	            capacite=capacite-*(poid+temp);
		   }
	}
}
		
int max(int a,int b){ 
    if (a<b) 
    return b; 
    else
    return a;
}


int valeurs_max(int *poid,int *valeur,int num_objet, int cont){  
	switch (num_objet)
	{
         case  0:  //si on a un seul objet on retourne sa valeur si le poid est inferieur a la capacite du sac
		 if (*(poid+num_objet)>cont)
		    return 0;
		 else 
		    return *(valeur+num_objet); 
         default : //si on a toujours des objets  

		 if (*(poid+num_objet)>cont)

		    return valeurs_max(poid,valeur,num_objet-1,cont); 
		 else 
		 //ici on applique le principe de séparation evaluation 
  return max(*(valeur+num_objet)+valeurs_max(poid,valeur,num_objet-1,cont-*(poid-num_objet)),valeurs_max(poid,valeur,num_objet-1,cont));
		      
        }

}



int main() {

        int capacite;						        //capacité du sac
	int *poid,*valeur;					        //Tableaux des poids et valeurs
	int nb_objets;							//nombre d'objets
	int *dans_le_sac;					        //tableau contenant les objets du sac 
	int s_val;                                                    //la somme des valeurs des objet dans le sac  


        printf("\n- Entrez la contenance du sac svp: "); 
        scanf("%d",&capacite);
        printf("\n- Entrez le nombre d objets svp : "); 
        scanf("%d",&nb_objets);
	printf("\n");
	
	poid=(int*)malloc(nb_objets*sizeof(int));
 	dans_le_sac=(int*)malloc(nb_objets*sizeof(int));				
 	valeur=(int*)malloc(nb_objets*sizeof(int));
	
	// on initialise le sac a vide 
	int i=0;
	while(i<nb_objets)
	{
		*(dans_le_sac+i)=0;
		i++;
	}
						
        //on entre les poids et valeurs des objets 
        int j=0;
        while(j<nb_objets)
        {
        printf("Objet n %d",j+1);
 	printf("\nLe poids= ");
        scanf("%d",&poid[j]);
 	printf("La valeur= ");
 	scanf("%d",&valeur[j]);
 	printf("\n");
        	j++;
        }
     

        //on calcule les valeurs maximales puis on cherche les objets a mettre dans le sac 
        s_val=valeurs_max(poid,valeur,nb_objets-1,capacite);
	selection(capacite,nb_objets,poid,valeur,dans_le_sac);
       
        printf("\n");
	printf("les objets a mettre dans le sac: \n");
	for(int i=0;i<nb_objets; i++) {
	if (*(dans_le_sac+i)==1) 
	printf("l'objet num :%d \n",i+1);
                              }
     
        return 0;
        
}
