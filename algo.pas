PROGRAM Arbre;
///////////////////////////////////////////
TYPE voitures = record
	marque : string[30];
	modele : string[20];
	carb : char;
	annee : integer;
	prix : integer;
end;
///////////////////////////////////////////
TYPE
 liste = ^cellule;

 cellule = record
	contenu : voitures;
	suivant : liste;
 end;
///////////////////////////////////////////
VAR
	
///////////////////////////////////////////
BEGIN
	
	
END.
