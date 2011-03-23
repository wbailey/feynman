/*
 * Feynman Java Simulation Framework Sample Application
 *
 * $author: Wes Bailey$
 */
import java.text.DecimalFormat;
import java.util.Iterator;
import feynman.framework.system.FinalReport;
import feynman.framework.system.PhysicalSystem;
import feynman.framework.simulation.Simulation;

/**
 * Implementation of the <b>FinalReport</b> that is used by the
 * <b>Controller</b> after the simulation is complete to report
 * any statistics or information that needs to be known.
 */
public class Report implements FinalReport {
	
	// --------------------------------------------- instance variables.
	private Iterator i;
	private Ball b;
	private DecimalFormat df = new DecimalFormat("###.00000000");
	
	/**
	 * Method invoked by the <b>Controller</b> to provide the final report.
	 *
	 * @param sim Simulation bean
	 * @param ps The <b>PhysicalSystem</b> containing the <b>Ball</b>
	 */
	public void report(Simulation sim, PhysicalSystem ps) {
		
		// Retrieve the reference to the ball from the PhysicalSystem.
		i = ps.iterator();
		b = (Ball) i.next();
		
		// Print out some final statistics.
		System.out.println();
		System.out.println("---------- Simulation Report -----------");
		System.out.println("max height:         " + df.format(b.getMaxheight()) + " m");
		System.out.println("impact velocity:   " + df.format(b.getVy()) + " m/s");
		System.out.println("total flight time:  " + df.format(sim.getTime()) + " s");
		System.out.println("----------------------------------------");
		
	}
	
}
