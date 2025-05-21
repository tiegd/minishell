# Toutes les fonctions utilent pour **Minishell**

## Readline *#include <readline/readline.h>*

Prototype de la fonction :
```c
char *readline (const char *prompt);
```
Cette fonction est semblable à un GNL. Elle permet de lire la ligne saisie par un utilisateur dans un terminal.
*const char *prompt* permet d'afficher une string comme prompt dans le terminale.
Elle renvoie la string saisie par l'utilisateur, une string vide si rien n'est saisie et NULL si on arrive a la fin d'un ficher et que la ligne est vide.


## Add_history

Prototype de la fonction :
```c
void add_history(char *s);
```
Permet de sauvegarder la string passé en argument dans l'historique. Cela permet par exemple de retrouver ce qu'on a pu taper avant et qu'on a récuperé grâce à readline dans le terminal. (On va pouvoir retrouver nos saisis avec les flèches du haut ou bas par exemple)


## Readline_clear_history

Prototype de la fonction :
```c
void rl_clear_history(void);
```

Cette fonction permet de supprimer toute les entrées enregistré dans l'historique de readline().
Qui ont été ajouter grâce à add_history par exemple.


## Readline_on_new_line

Prototype de la fonction :
```c
int rl_on_new_line(void);
```
Cette fonction permet de dire à readline qu'on est desormais sur une nouvelle ligne. 
Si par exemple on a affiché quelque choses avec un printf et qu'on est pas passé par readline on doit lui indiquer explicitement pour evité des comportements inattendus.

Retourne 0 en cas de succés et autre chose si il y a une erreur.


## Readline_replace_line

Prototype de la fonction :
```c
int rl_replace_line(const char *text, int clear_undo);`
```
Le but de cette fonction est de remplacer le contenu actuel de la ligne que l'utilisateur est entrain de taper.
Cela va servir a afficher un texte pré-rempli ou une suggestion automatique. 


## Readline_redisplay

Prototype de la fonction :

```c
void rl_redisplay(void);
```

Elle est utilisé pour forcer l'affichage de la ligne d'entré de commande dans le terminal.
C'est utile par exemple si on a modifié la ligne avec replace_line ou si on veut afficher un message qui est en dehors de readline. Comment un message d'erreur par exemple.

## Getcwd *#include <unistd.h>*

Prototype de la fonction :

```c
char *getcwd(char *buf, size_t size);
```
Cette fonction permet de renvoyer le chemin du dossier dans lequel on se situe. Il est retourné via le resultat et aussi via l'argument buf.
Size étant la taille en octet du tableau buf.
On peut aussi allouer la mémoire automatiquement en mettant buf à NULL et size à 0. Cela induit le fait de devoir free la chaine que l'on aura récupéré.


## Chdir *#include <unistd.h>*

Prototype de la fonction :
```c
int chdir(const char *path);
```
Cette fonction permet de changer le répertoire courant du processus.
Pour ca il faut rentrer le nouveau path en argument.
Retourne 0 si il reussi ou -1 si il échoue.


## Stat, Lstat, Fstat *#include <sys/stat.h>*

Prototype des fonctions :

```c
int stat(const char *restrict pathname, struct stat *restrict statbuf);
int lstat(const char *restrict pathname, struct stat *restrict statbuf);
int fstat(int fd, struct stat *statbuf);
```

Ces fonctions récupère des informations sur le fichier passé en argument (pathname) dans le tampon pointé par stat.

```c
struct stat {
    dev_t     st_dev;         /* Périphérique                     */
    ino_t     st_ino;         /* Numéro d’inœud                   */
    mode_t    st_mode;        /* Protection                       */
    nlink_t   st_nlink;       /* Nombre de liens physiques        */
    uid_t     st_uid;         /* UID du propriétaire              */
    gid_t     st_gid;         /* GID du propriétaire              */
    dev_t     st_rdev;        /* Type de périphérique             */
    off_t     st_size;        /* Taille totale en octets          */
    blksize_t st_blksize;     /* Taille de bloc pour E/S          */
    blkcnt_t  st_blocks;      /* Nombre de blocs de 512 o alloués */
    /* Depuis Linux 2.6, le noyau permet une précision à la
       nanoseconde pour les champs temporels suivants. Pour
       plus de précisions avant Linux 2.6, consultez les NOTES.   */
    struct timespec st_atim;  /* Heure dernier accès              */
    struct timespec st_mtim;  /* Heure dernière modification      */
    struct timespec st_ctim;  /* Heure dernier changement état    */
#define st_atime st_atim.tv_sec      /* Rétrocompatibilité        */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
```

`stat()` récupère les informations de pathname et si c'est un lien symbolique il va quand même suivre ce lien pour afficher les informations du fichier pointé par ce lien. 
Contrairement à `lstat()` qui lui, va donner les informations du lien directement.

Quand à lui `fstat()` va récuperer les informations d'un fichier ouvert par `open()`.

## Opendir *#include <dirent.h>*

Prototype de la fonction : 

```c
DIR *opendir(const char *name);
```

`opendir()` va ouvrir un flux sur le chemin du dossier passé en argument et retourne un pointeur sur ce flux ou NULL en cas d'erreur.
En gros on va pouvoir ouvrir un répertoire et lire ce qu'il y a dedans.
C'est utilisé lorsqu'on va vouloir lister les fichiers présents dans un dossier (pour implémenter un ls par exemple) en utilisant `readdir()`.

## Readdir 

Prototype de la fonction :

```c
int readdir(DIR *dir, struct dirent *entry, struct dirent **result);
```

`readdir()` renvoie un pointeur sur une structure *dirent* représentant l'entré suivante du flux de répertoire pointé par *dir*. 
```c 
struct dirent *readdir(DIR *dir);
```
Elle renvoie NULL à la fin du répertoire, ou en cas d'erreur.

Les données renvoyées par readdir() sont écrasées lors de l'appel suivant à readdir() sur le même flux répertoire.

En gros à chaque appelle de readdir on passe au fichier suivant et on écrase les infos récupéré auparavant.

Structure de dirent :

```c
struct dirent {
    ino_t          d_ino;       /* numéro d'inœud */
    off_t          d_off;       /* décalage jusqu'à la dirent suivante */
    unsigned short d_reclen;    /* longueur de cet enregistrement */
    unsigned char  d_type;      /* type du fichier */
    char           d_name[256]; /* nom du fichier */
};
```

## Closedir

Prototype de la fonction :

```c
int closedir(DIR *dir);
```

La fonction `closedir()` ferme le flux de répertoire associé à *dir*. Après avoir appellé cette fonction, le descripteur *dir* du flux de répertoire n'est plus disponible.

Elle renvoie 0 si elle à reussi ou -1 si elle à échoué.

Lorsqu'on ouvre un répertoire avec opendir, le système alloue des ressources internes, cést donc pour cela qu'on va utilisé closedir et donc libéré les ressources.

## Isatty *#include <unistd.h>*

Prototype de la fonction :

```c
int isatty(int fd);
```

La fonction `isatty()` va vérifier si un descripteur de fichier se rapporte à un terminal.
Elle renvoie 1 si c'est le cas sinon elle renvoie 0.

## Ttyname

Prototype de la fonction :
```c
char **ttyname(int fd);
```

La fonction `ttyname()` renvoie un pointeur sur le chemin d'accès terminé par un octet nul du périphérique terminal ouvert associé au descripteur de fichier fd, ou NULL en cas d'erreur (par exemple si fd n'est pas connecté à un terminal).

