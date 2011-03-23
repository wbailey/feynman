/*
 * $Header: /cvsroot/feynman/src/feynman/framework/system/PhysicalConfiguration.java,v 1.1.1.1 2002/11/12 02:25:43 wesley_bailey Exp $
 * $Revision: 1.1.1.1 $
 * $Date: 2002/11/12 02:25:43 $
 * $Copyright: Copyright (C) 2002 Wes Bailey, Oakland, CA, USA $
 */
package feynman.framework.system;

/**
 * Interface for defining the configuration of a physical system before any
 * operations or measurements are performed on the physical system.
 * The class that will be used by the simulation should be defined in the
 * <em>Simulation.properties</em> file in the following manner:
 * <p/>
 * <pre>
 * # Define the class to use to configure the physical System.
 * PhysicalConfigurationClass=InitialSetup
 * </pre>
 *
 * @author Wes Bailey
 * @version $Revision: 1.1.1.1 $ $Date: 2002/11/12 02:25:43 $
 */
public interface PhysicalConfiguration {
	
	/**
	 * Implement this method to define how to configure the system.
	 */
	public void configure(PhysicalSystem system);
	
}
