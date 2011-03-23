/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/CartesianSystem.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

/**
 * Class that creates a system of <b>CartesianObjects</b>.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
class CartesianSystem extends PhysicalSystem {
	
	/**
	 * Overriden method to ensure the object being added is a CartesianObject.
	 *
	 * @param item <b>CartesianObject</b> that is being added to the system.
	 */
	public boolean add(Object item) {
		if (item instanceof CartesianObject) {
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
