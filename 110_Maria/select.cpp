#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DATABASE_NAME  "electronique"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "trucmuche"
MYSQL *mysql1;

int main(int argc, char **argv)
{
	//initialisation MYSQL pour connection
	mysql1 = mysql_init(NULL);
    if(mysql1 == NULL) {
		fprintf(stderr, "Erreur : %s\n", mysql_error(mysql1));
        return -1;
    }
    //Connect to the database
    if(mysql_real_connect(mysql1, "127.0.0.1", DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0) == NULL) {
		fprintf(stderr, "%s\n", mysql_error(mysql1));
    } else {
        printf("Connection ok.\r\n");
    }
	if (mysql1 != NULL)
	{
        if (!mysql_query(mysql1, "SELECT nom, utilisation, nb_patte, alimentation FROM composants")) {
			MYSQL_RES *result = mysql_store_result(mysql1);
			if (result != NULL) {
				//Nombre de lignes
				int num_rows = mysql_num_rows(result);
				// Nombre de colonnes
				int num_fields = mysql_num_fields(result);

				MYSQL_ROW row;   //Tableau de String
				while( (row = mysql_fetch_row(result))) {
					if(num_fields >= 4) {
						char *nom = row[0];
						char *utilisation = row[1];
						char *nbPatte = row[2];
						char *alimentation = row[3];
						printf( "Nom: %s\n", nom);
						printf( "Utilisation: %s\n", utilisation);
						printf( "Nombre de pattes: %s\n", nbPatte);
						printf( "Alimentation: %s\n", alimentation);
					}
				}
                mysql_free_result(result);
			} else {
				printf("Récupération des données impossible\r\n");
			}
		} else {
			printf("Select impossible\r\n");
		}
    }
    mysql_close(mysql1);
    printf( "Déconnection.\r\n");
    return 0;
}