/*
 * $Header: /cvsroot/feynman/src/feynman/framework/datastore/InvalidDataStoreException.java,v 1.1.1.1 2002/11/12 02:25:41 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:41 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.datastore;

/**
 * Exception for when the user specifies and invalid data store type.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:41 $
 */
public class InvalidDataStoreException extends Exception {
	
	public InvalidDataStoreException() {
		super();
	}
	
	public InvalidDataStoreException(String message) {
		super(message);
	}
	
}
