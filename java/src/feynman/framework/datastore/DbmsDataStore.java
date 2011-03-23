package feynman.framework.datastore;

import feynman.framework.system.PhysicalMeasurement;
import java.io.*;
import java.sql.*;

public class DbmsDataStore implements DataStore {
	
	// Private instance variables.
	private Connection conn = null;
	private Statement stmt = null;
	private ResultSet rset = null;
	
	DbmsDataStore() {
		// Factory only instantiation.
	}
	
	public void open(String driver) throws ConnectionException {
		
		try {
			Class.forName(driver);
			
			conn = DriverManager.getConnection(
                       "jdbc:postgresql://127.0.0.1/feynman",
                       "feynman",
                       "feynman"
                   );

		}
		catch (ClassNotFoundException e) {
			throw new ConnectionException("Couldn't load database driver: " + e.toString());
		}
		catch (SQLException e) {
			throw new ConnectionException("Couldn't connect to database: " + e.toString());
		}
		
	}
	
	public void save(PhysicalMeasurement ps) {
		//null
	}
	
	public void close() throws ConnectionException {
		
		try {
			conn.close();
		}
		catch (SQLException e) {
			throw new ConnectionException(e.toString());
		}
		
	}
	
}
