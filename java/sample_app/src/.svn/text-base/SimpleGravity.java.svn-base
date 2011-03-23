/*
 * Feynman Java Simulation Framework Sample Application
 *
 * $author: Wes Bailey$
 */
import java.util.Iterator;
import feynman.framework.system.PhysicalAlgorithm;
import feynman.framework.system.PhysicalSystem;
import feynman.framework.simulation.Simulation;

/**
 * This class is an implementation of the <b>PhysicalAlgorithm</b> class
 * using the Euler algorithm to update the equations of motion for the
 * <b>Ball</b> in our <b>PhysicalSystem</b>.
 */
public class SimpleGravity implements PhysicalAlgorithm {
	
	// ------------------------------------- instance variables.
	private Iterator i;
	private Ball b;
	
	/**
	 * This method is used by the <b>Controller</b> class to run the
	 * simulation step by step.  In addition to updating the equations
	 * of motion using the Euler algorithm, this method also calculates
	 * the maximum height and stops the simulation when the <b>Ball</b>'s
	 * height is less than zero indicating it has hit the ground.
	 *
	 *
	 * @param sim Simulation bean.
	 * @param ps The <b>PhysicalSystem<b> containing the <b>Ball</b>.
	 */
	public void calculate(Simulation sim, PhysicalSystem ps) {
		
		// Retrieve the reference to the particle from the physical system.
		i = ps.iterator();
		b = (Ball) i.next();
		
		// Store the previous velocity calculation.
		b.setVyold(b.getVy());
		
		// Euler algorithm.
		b.setAy(-9.8);
		b.setY(b.getY() + b.getVy() * sim.getInterval());
		b.setVy(b.getVy() + b.getAy() * sim.getInterval());
		
		// Look for a change in sign in the velocity to catch the max height.
		if ((b.getVy() * b.getVyold()) < 0) b.setMaxheight(b.getY());
		
		// Stop the simulation after the ball hits the ground.
		if(b.getY() < 0.0) sim.setRunning(false);
		
	}
	
}
