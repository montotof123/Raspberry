#include <iostream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   string sql;
   
   try{
      connection C("dbname=postgres user=postgres password=trucmuche \
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Base ouverte avec succès: " << C.dbname() << endl;
      } else {
         cout << "Ouverture de base impossible" << endl;
         return 1;
      }
      /* Requête SQL */
      sql = "SELECT nom, utilisation, nb_patte, alimentation FROM raspberry.composants";

      /* Création d'un objet non-transactionel. */
      nontransaction N(C);
      
      /* Execute requete SQL */
      result R( N.exec( sql ));
      
      /* Liste toutes les occurences */
      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
         cout << "Nom: " << c[0].as<string>() << endl;
         cout << "Utilisation: " << c[1].as<string>() << endl;
         cout << "Nombre de pattes: " << c[2].as<int>() << endl;
         cout << "Alimentation: " << c[3].as<float>() << endl;
      }
      cout << "Operation terminée avec succès" << endl;
      C.disconnect ();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}