package mongoDB;

import org.bson.Document;

import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;

public class SelectPersonne {

	public static void main(String[] args) {
		MongoClientURI uri = new MongoClientURI("mongodb://user1:trucmuche@192.168.1.27:27017/replicateBase");
		MongoClient client = new MongoClient(uri);
		MongoDatabase dataBase = client.getDatabase(uri.getDatabase());
		MongoCollection<Document> collections = dataBase.getCollection("personne");
		
		FindIterable<Document> personnes = collections.find();
		
		for (Document personne : personnes) {
			System.out.println(personne.getString("nom") + ", " + personne.getString("ville"));
		}
		
		client.close();
	}

}
