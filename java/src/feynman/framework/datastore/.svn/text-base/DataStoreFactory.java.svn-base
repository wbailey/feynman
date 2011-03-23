/*
 * $Header: /cvsroot/feynman/src/feynman/framework/datastore/DataStoreFactory.java,v 1.1.1.1 2002/11/12 02:25:41 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:41 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.datastore;

/**
 * Factory class for the creation of particular <b>DataStore</b> implementation.
 * The frameworkd currently supports the <b>DataStoreFile</b> implementation only.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:41 $
 */
public class DataStoreFactory {
	
	// Create the instance of the class.
	private static final DataStoreFactory INSTANCE = new DataStoreFactory();
	
	private DataStoreFactory() {
		// singleton
	}
	
	/**
	 * Method to retrieve an instance of the class.
	 */
	public static DataStoreFactory getInstance() {
		return INSTANCE;
	}
	
	/**
	 * Method to create the <b>DataStore</b> object that has been specified
	 * in the <em>Simulation.properties</em> file in the following manner:
	 * <p>
	 * </pre>
	 * # Define the data storage mechanism to be used.
     * DataStore=file
     * #DataStore=dbms
     *
     * # Define the data source destination that the measurement data will be stored in.
     * DataStoreFile=data.csv
     * #DataStoreTable=table
	 * </pre>
	 * </p>
	 * <b>Note:</b> If an invalid data store is defined in the properties file
	 * the <b>Controller</b> class will throw and <em>InvalidDataStoreException</em>.
	 */
	
	public DataStore create(String type) throws InvalidDataStoreException {
		
		// Decision tree for the parametrized data store specification.
		if (type.equalsIgnoreCase("file")) {
			
			return new FileDataStore();
			
		} else if (type.equalsIgnoreCase("dbms")) {
			
			// no specific implementation for a dbms exists yet.
			//return new DbmsDataStore();
			throw new InvalidDataStoreException("DataStore dbms not implemented");
			
		} else {
			
			// The specified data store is not implemented.
			throw new InvalidDataStoreException("Invalid DataStore: " + type);
			
		}
		
	}
	
}
