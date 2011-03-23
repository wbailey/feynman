/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/PhysicalObject.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

/**
 * The class is really just a symbolic name that means more to physicists
 * than the default Java Object class name means.  It also helps to avoid
 * confusion with the System class by establishing the semantic pattern
 * in the framework of PhysicalObject and its counterpart PhysicalSystem.
 *
 * It does provide its sub-classes with an identifier mechanism and
 * and <em>equals</em> method based on the unique identifier.  This is
 * useful for systems that contain many objects.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
abstract public class PhysicalObject {
	
	// Used to identify the object.
	private int id;
	
	/**
	 * Use this method to assign a unique identifier.
	 *
	 * @param id An integer value for the unique identifier.
	 */
	public final void setId(int id) {
		this.id = id;
	}
	
	/**
	 * Use this method to get the unique identifier.
	 */
	public final int getId() {
		return id;
	}
	
	/**
	 * Use this method to test if the PhysicalObject you are working with
	 * is equal to another that you are using.
	 *
	 * @param po The physical object to compare to this.
	 */
	public final boolean equals(PhysicalObject po) {
		if (this.id == po.getId()) {
			return true;
		} else {
			return false;
		}
	}
	
}
