/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/PhysicalMeasurement.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

import feynman.framework.simulation.Simulation;

/**
 * This interface defines the required method for the Measurement bean.  The user
 * will define the necessary get and set methods for the bean on the quantities
 * that are being measured as in the following example:
 * <p/>
 * <pre>
 * ...
 *     public void setTotalEnergy(double E) {
 *         this.E = E;
 *     }
 *
 *     public double getTotalEnergy() {
 *         return E;
 *     }
 * ...
 * </pre>
 * <p/>
 * The user of the framework will specify usage of this class in the 
 * <em>Simulation.properties</em> file in the following manner:
 * <p/>
 * <pre>
 * PhysicalMeasurementClass=EnergyMeasurement
 * </pre>
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public interface PhysicalMeasurement {
	
	/**
	 * Define this method for taking a measurement of the <b>PhysicalSystem</b>
	 * during the simulation.
	 */
	public void take(Simulation sim, PhysicalSystem ps);
	
	/**
	 * Define this method in order to use the <b>FileDataStore</b>.  Otherwise
	 * provide a null implementation.
	 */
	public String toString();
	
	/**
	 * Define this method in order to use the <b>DbmsDataStore</b>.  Otherwise
	 * provide a null implementation.
	 */
	public String toSql();
	
}
