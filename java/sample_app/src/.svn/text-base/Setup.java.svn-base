/*
 * Feynman Java Simulation Framework Sample Application
 *
 * $author: Wes Bailey$
 */
import java.util.Iterator;
import feynman.framework.system.PhysicalConfiguration;
import feynman.framework.system.PhysicalSystem;

/**
 * This class implements the <b>PhysicalConfiguration</b> to setup
 * the initial conditions of the simulation.
 */
public class Setup implements PhysicalConfiguration {
	
	// ------------------------------------- instance variables.
	private Iterator i;
	private Ball b;
	
	/**
	 * Set the <b>Ball</b>'s initial height and velocity.  In a real
	 * application these properties could be set from a properties
	 * file so you would not need to recompile the application
	 * every time the initial conditions changed.
	 *
	 * @param ps The <b>PhysicalSystem<b> containing the <b>Ball</b>.
	 */
	public void configure(PhysicalSystem ps) {
		
		// Retrieve the reference to the particle from the physical system.
		i = ps.iterator();
		b = (Ball) i.next();
		
		// Setup its intial height and velocity.
		b.setY(0.0);
		b.setVy(10.0);
		
	}
	
}
