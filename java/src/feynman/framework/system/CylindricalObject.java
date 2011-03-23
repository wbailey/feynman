/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/CartesianObject.java,v 1.1.1.1 2002/11/12 02:25:42 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:42 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

/**
 * Sub-class to define a <b>PhysicalObject</b> for the <b>CylindricalSystem</b>.
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:42 $
 */
abstract public class CylindricalObject extends PhysicalObject {
	
	// Define the coordinate system that is the same for all Cartesian Objects.
	private double rho;
	private double phi;
	private double z;
	
	/**
	 * Method to define the Rho coordinate of the object.
	 * <br>
	 * <b>Note: </b>This method should <em>NOT</em> be overriden in the user implementation.
	 */
	public final void setRho(double rho) {
		this.rho = rho;
	}
	
	/**
	 * Use this method to retrieve the Rho coordinate value of the object.
	 * <br>
	 * <b>Note: </b>This method should <em>NOT</em> be overriden in the user implementation.
	 */
	public final double getRho() {
		return rho;
	}
	
	/**
	 * Method to define the Phi coordinate of the object.
	 * <br>
	 * <b>Note: </b>This method should <em>NOT</em> be overriden in the user implementation.
	 */
	public final void setPhi(double phi) {
		this.phi = phi;
	}
	
	/**
	 * Use this method to retrieve the Phi coordinate value of the object.
	 * <br>
	 * <b>Note: </b>This method should <em>NOT</em> be overriden in the user implementation.
	 */
	public final double getPhi() {
		return phi;
	}
	
	/**
	 * Method to define the Z coordinate of the object.
	 * <br>
	 * <b>Note: </b>This method should <em>NOT</em> be overriden in the user implementation.
	 */
	public final void setZ(double z) {
		this.z = z;
	}
	
	/**
	 * Use this method to retrieve the Z coordinate value of the object.
	 * <br>
	 * <b>Note: </b>This method should <em>NOT</em> be overriden in the user implementation.
	 */
	public final double getZ() {
		return z;
	}
	
}
