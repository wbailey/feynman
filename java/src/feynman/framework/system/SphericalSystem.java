/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/CartesianSystem.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

/**
 * Class that creates a system of <b>SphericalObjects</b>.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
class SphericalSystem extends PhysicalSystem {
	
	/**
	 * Overriden method to ensure the object being added is a SphericalObject.
	 *
	 * @param item <b>SphericalObject</b> that is being added to the system.
	 */
	public boolean add(Object item) {
		if (item instanceof SphericalObject) {
			if (system.add(item)) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	
}
