package cassandra;

import com.datastax.driver.core.Cluster;
import com.datastax.driver.core.ResultSet;
import com.datastax.driver.core.Row;
import com.datastax.driver.core.Session;

public class SelectPersonne {

	public static void main(String[] args) {
		Cluster cluster;
		Session session;

		// Connect to the cluster and keyspace "replicate"
		cluster = Cluster.builder().addContactPoint("192.168.1.27").build();
		session = cluster.connect("replicate");

		// Use select to get the user we just entered
		ResultSet results = session.execute("SELECT * FROM personne");
		for (Row row : results) {
			System.out.format("%d %s %s\n", row.getInt("id"), row.getString("nom"), row.getString("ville"));
		}

		// Clean up the connection by closing it
		cluster.close();
	}
}
