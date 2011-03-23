/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/PhysicalSystemFactoryException.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

/**
 * This excpetion is generally invoked when the user has either configured the
 * properties file incorrectly by specifying a sub-class of the <b>PhysicalObject</b>
 * that cannot be created by the Factory.  An example would be if the user created
 * a SphericalParticle that is a sub-class of <b>SphericalObject</b> which is a
 * a sub-class of <b>PhysicalObject</b>.  If the user tried to create the SphericalParticle
 * with a CartesianObjectFactory, then this exception would be thrown.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public class PhysicalSystemFactoryException extends Exception {
	
	// Only need package private contructors.
	public PhysicalSystemFactoryException() {
		super();
	}
	
	public PhysicalSystemFactoryException(String message) {
		super(message);
	}
	
}
