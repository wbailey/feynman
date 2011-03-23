/*
 * $Header: /cvsroot/feynman/src/feynman/framework/datastore/FileDataStore.java,v 1.1.1.1 2002/11/12 02:25:41 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:41 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.datastore;

import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import feynman.framework.system.PhysicalMeasurement;

/**
 * File based implementation of the <b>DataStore</b> interface.  This
 * class makes use of the <em>toString()</em> method defined in the
 * <b>PhysicalMeasurement</b> interface.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:41 $
 */
public class FileDataStore implements DataStore {
	
	// Define the instance variables.
	private File file;
	private FileWriter fw;
	private PrintWriter pw;
	
	FileDataStore() {
		// Factory only instantiation.
	}
	
	/**
	 * Method to open a file for writing <b>PhysicalMeasurement</b> data to.
	 */
	public void open(String source) throws ConnectionException {
		
		// Create the file and open the writers.
		try {
			file = new File(source);
			fw = new FileWriter(file);
			pw = new PrintWriter(fw);
		}
		catch (Exception e) {
			throw new ConnectionException(e.toString());
		}
		
	}
	
	/**
	 * Method to write the <b>PhysicalMeasurement</b> data to the file.
	 */
	public void save(PhysicalMeasurement pm) {
		
		pw.println(pm.toString());
		
	}
	
	/**
	 * Method to close the <b>PhysicalMeasurement</b> data file for writing.
	 */
	public void close() throws ConnectionException {
		
		// Be a good citizen and close the streams.
		try {
			pw.close();
			fw.close();
		}
		catch (Exception e) {
			throw new ConnectionException(e.toString());
		}
		
	}
	
}
