/*
 * $Header: /cvsroot/feynman/src/feynman/framework/datastore/DataStore.java,v 1.1.1.1 2002/11/12 02:25:41 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:41 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.datastore;

import feynman.framework.system.PhysicalMeasurement;

/**
 * Interface for defining data store capabilities within the framework for
 * the <b>PhysicalMeasurement</b> bean.  The data store could be as simple
 * as a file or a database table.  To check for the current supported 
 * implementations, check the documentation in the <b>DataStoreFactory</b>
 * class.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:41 $
 */
public interface DataStore {
	
	/**
	 * Method to open a connection to the data store.  
	 */
	public void open(String source) throws ConnectionException;
	
	/**
	 * Method to save the PhysicalMeasurement bean to the data store.  At
	 * the present time, the framework will only support saving this bean 
	 * to the data store.
	 */
	public void save(PhysicalMeasurement pm);
	
	/**
	 * Method to close the connection to the data store.
	 */
	public void close() throws ConnectionException;
	
}
