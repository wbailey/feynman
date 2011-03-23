/*
 * $Header: /cvsroot/feynman/src/feynman/framework/controller/ControllerException.java,v 1.1.1.1 2002/11/12 02:25:41 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:41 $
 * $Copyright: Copyright (C) 2002 Path Integral Software $
 */
package feynman.framework.controller;

/**
 * This excpetion is generally invoked when the user has either configured the
 * properties file incorrectly or invoked the <b>feynman.jar</b> file with an
 * incorrect command line.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:41 $
 */
public class ControllerException extends Exception {
	
	// Only need package private contructors.
	ControllerException() {
		
		super("\nUsage: java -jar feynman.jar [propertiesFile]\n");
		
	}
	
	ControllerException(String message) {
		
		super("\nUsage: java -jar feynman.jar [propertiesFile]\n" + message);
		
	}
	
}
