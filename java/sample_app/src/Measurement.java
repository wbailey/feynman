/*
 * Feynman Java Simulation Framework Sample Application
 *
 * $author: Wes Bailey$
 */
import java.util.Iterator;
import java.text.DecimalFormat;
import feynman.framework.system.PhysicalSystem;
import feynman.framework.system.PhysicalMeasurement;
import feynman.framework.simulation.Simulation;

/**
 * Implementatin of the <b>PhysicalMeasurement</b> interface that the
 * <b>Controller</b> uses to record the data specified in this class.  The
 * <b>Controller</b> calls the <em>take</em> method to take a measurement
 * and record it to the <b>DataStore</b>.
 */
public class Measurement implements PhysicalMeasurement {
	
	// --------------------------------------- instance variables.
	private Iterator i;
	private Ball b;
	private StringBuffer sb;
	private double time = 0.0;
	private double kineticEnergy = 0.0;
	private double potentialEnergy = 0.0;
	private double totalEnergy = 0.0;
	private double y = 0.0;
	private DecimalFormat csv = new DecimalFormat("000000000.00000000");
	
	/**
	 * Use this method to set the time the measurement was taken.
	 */
	private void setTime(double time) {
		this.time = time;
	}
	
	/**
	 * Use this method to query the time the measurement was taken.
	 */
	private double getTime() {
		return this.time;
	}
	
	/**
	 * Use this method to set the kinetic energy at the time the 
	 * measurement is taken.
	 */
	private void setKineticEnergy(double kineticEnergy) {
		this.kineticEnergy = kineticEnergy;
	}
	
	/**
	 * Use this method to query the kinetic energy at the time the
	 * measurement is taken.
	 */
	private double getKineticEnergy() {
		return this.kineticEnergy;
	}

	/**
	 * Use this method to set the potential energy at the time the 
	 * measurement is taken.
	 */
	private void setPotentialEnergy(double potentialEnergy) {
		this.potentialEnergy = potentialEnergy;
	}
	
	/**
	 * Use this method to query the potential energy at the time the
	 * measurement is taken.
	 */
	private double getPotentialEnergy() {
		return this.potentialEnergy;
	}
	
	/**
	 * Use this method to set the total energy at the time the 
	 * measurement is taken.
	 */
	private void setTotalEnergy(double totalEnergy) {
		this.totalEnergy = totalEnergy;
	}
	
	/**
	 * Use this method to query the total energy at the time the
	 * measurement is taken.
	 */
	private double getTotalEnergy() {
		return this.totalEnergy;
	}
	
	/**
	 * Use this method to set the y value at the time the measurement
	 * is taken.
	 */
	private void setY(double y) {
		this.y = y;
	}
	
	/**
	 * Use this method to query the y value at the time the measurement
	 * is taken.
	 */
	private double getY() {
		return y;
	}
	
	/**
	 * This method use the private methods to calculate and store
	 * the values of the energy and position of the <b>Ball</b> at
	 * the time the measurement is taken.  These stored values are
	 * then used by the <b>DataStore</b> method to record the
	 * measurement.
	 *
	 * @param sim Simulation bean.
	 * @param ps The <b>PhysicalSystem<b> containing the <b>Ball</b>.
	 */
	public void take(Simulation sim, PhysicalSystem ps) {
		
		// Retrieve the particle.
		i = ps.iterator();
		b = (Ball) i.next();
		
		// Calculate and store the time, energy and position characterisics
		// of the simulation at the time the measurement is taken.
		setTime(sim.getTime());
		setPotentialEnergy(9.8 * b.getY());
		setKineticEnergy(0.5 * b.getVy() * b.getVy());
		setTotalEnergy(getKineticEnergy() + getPotentialEnergy());
		setY(b.getY());
		
	}
	
	/**
	 * Method used by the <b>FileDataStore</b> to store the measurements
	 * properties to a file in the supplied format in this method.
	 */
	public String toString() {
		
		sb = new StringBuffer();
		
		// Create a CSV file with the data.
		sb.append(csv.format(getTime()) + ", ");
		sb.append(csv.format(getY()) + ", ");
		sb.append(csv.format(getPotentialEnergy()) + ", ");
		sb.append(csv.format(getKineticEnergy()) + ", ");
		sb.append(csv.format(getTotalEnergy()));
		
		return sb.toString();
		
	}
	
	/**
	 * Method used by the <b>DbmsDataStore</b> to store the measurement's
	 * attributues to the specified database table.
	 */
	public String toSql() {
		
		return null;
		
	}
	
}

