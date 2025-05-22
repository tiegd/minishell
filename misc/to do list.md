# Chose à savoir

## Commande ls :

`Ls` peut prendre en argument un dossier pour lister le contenu de ce dossier.

Elle peut aussi prendre en argument le dossier ou son path et en dernier argument l'option.
*Par exemple : ls home/jpiquet/download -la*
*Ou encore : ls -l 42cursus/MILSTONE_2 -a*

Parsing fonctionnel : 

ls -la
"ls" -la
'ls' -la
"ls" "-la"
'ls' 'la'
ls nomdudossier -la


"ls -la" => ls -la: command not found -> code erreur 127
'ls -la' => ls -la: command not found -> code erreur 127
ls dossier_non_existant => ls: cannot access 'oui': No such file or directory -> code erreur 1

Penser à env -i qui supprime la variable d'environnement.

nom_du_dossier => "42cursus: command not found" (code 127)
nom_du_dossier/ => "42cursus/: Is a directory" (code 126)

## Commande cat :

cat non_existing_file => "non_existing_file: No such file or directory" -> code erreur 1
cat pas_les_droits => "pas_les_droit: Permission denied" -> code erreur 1



