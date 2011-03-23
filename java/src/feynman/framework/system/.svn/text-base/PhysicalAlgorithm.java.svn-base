/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/PhysicalAlgorithm.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

import feynman.framework.simulation.Simulation;

/**
 * This interface defines the mechanism for implementing a numerical algorithm
 * for the simulation.  The user of the framework will define an implementation
 * and specify this in the <em>Simulation.properties</em> file in the following
 * manner:
 * <p/>
 * <pre>
 * PhysicalAlgorithmClass=SimpleGravity
 * </pre>
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public interface PhysicalAlgorithm {
	
	/**
	 * Implement this method to define the algorithm to be used in the <b>Simulation</b>.  The
	 * <b>Simulation</b> can be queuried to get the current time and the <b>PhysicalSystem</b>
	 * contains all of the <b>PhysicalObject</b>s in the <b>Simulation</b>.
	 */
	public void calculate(Simulation sim, PhysicalSystem ps);
	
}
