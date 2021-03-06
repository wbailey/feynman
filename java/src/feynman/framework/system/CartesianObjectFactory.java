/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/CartesianObjectFactory.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

import feynman.framework.simulation.Simulation;

/**
 * Factory class that implements <b>PhysicalObjectFactory</b>.  Use
 * this class to create object that are used in the study of Cartesian
 * Coordinate Systems.  To do this first indicate in the 
 * <em>Simulation.properties</em> the usage of the Factory and a corresponding
 * <em>PhysicalObject</em> in the following manner:
 * <p/>
 * <pre>
 * # Use the cartesian coordinate system.
 * PhysicalObjectFactoryClass=feynman.framework.CartesianObjectFactory
 *
 * # User defined class of the PhysicalObject to use in the PhysicalSystem
 * PhysicalObjectClass=CartesianParticle 
 * </pre>
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public class CartesianObjectFactory implements PhysicalObjectFactory {
	
	// Create an instance of the class.
	private static final CartesianObjectFactory INSTANCE = new CartesianObjectFactory();
	
	// Implement a singleton.
	private CartesianObjectFactory() {
		// singleton
	}
	
	/**
	 * Use this method to retrieve an instance of the Factory.
	 * <br>
	 * <b>Note: </b> This method is used internally and should never be
	 * used for a user specific implementation.
	 */
	public static final CartesianObjectFactory getInstance() {
		return INSTANCE;
	}
	
	/** 
	 * Factory method for generating <b>PhysicalObject</b>s in the Cartesian
	 * Coordinate System.
	 */
	public PhysicalObject create(Simulation sim) throws PhysicalObjectFactoryException {
		
		try {
			// Get an instance of the user specified PhysicalObject.
			Class clazz = Class.forName(sim.getPhysicalObjectClass());
			PhysicalObject po = (PhysicalObject) clazz.newInstance();
			
			// Ensure the user has specified a CartesianObject.
			if (po instanceof CartesianObject) {
				return po;
			} else {
				throw new PhysicalObjectFactoryException(clazz.getName() + "is not a CartesianObject");
			}
		}
		catch (ClassNotFoundException e) {
			throw new PhysicalObjectFactoryException(e.toString());
		}
		catch (InstantiationException e) {
			throw new PhysicalObjectFactoryException(e.toString());
		}
		catch (IllegalAccessException e) {
			throw new PhysicalObjectFactoryException(e.toString());
		}
		
	}

}
