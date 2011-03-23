/*
 * Feynman Java Simulation Framework Sample Application
 *
 * $author: Wes Bailey$
 */
import feynman.framework.system.CartesianObject;

/**
 * Bean implementation of <b>CartesianObject</b> to define the physical
 * characteristics of a ball in the Cartesian coordinate system.
 */
public class Ball extends CartesianObject {
	
	// ---------------------------------------- instance variables.
	
	// Velocity components
	private double vx;
	private double vy;
	private double vz;
	
	// Used to calculate the max height.
	private double vyold;
	private double maxheight;
	
	// Acceleration components.
	private double ax;
	private double ay;
	private double az;
	
	/**
	 * Use this method to define the magnitude of the velocity of particle in the X direction.
	 *
	 * @param vx The magnitude of the x component of the velocity.
	 */
	public void setVx(double vx) {
		this.vx = vx;
	}

	/**
	 * Use this method to query the magnitude of the velocity of the particle in the X coordinate.
	 */
	public double getVx() {
		return vx;
	}

	/**
	 * Use this method to define the magnitude of the velocity of particle in the X direction.
	 *
	 * @param vx The magnitude of the x component of the velocity.
	 */
	public void setVy(double vy) {
		this.vy = vy;
	}
	
	/**
	 * Use this method to query the magnitude of the velocity of the particle in the Y coordinate.
	 */
	public double getVy() {
		return vy;
	}
	
	/**
	 * Use this method to calculate the max height by comparing a change in sign to signify
	 * the particle has reached its apogee.
	 */
	public void setVyold(double vyold) {
		this.vyold = vyold;
	}
	
	/**
	 * Use this method to get the previous value of the y component of the velocity.
	 */
	public double getVyold() {
		return vyold;
	}
	
	/**
	 * Use this method to define the magnitude of the velocity of particle in the X direction.
	 *
	 * @param vx The magnitude of the x component of the velocity.
	 */
	public void setVz(double vz) {
		this.vz = vz;
	}
	
	/**
	 * Use this method to query the magnitude of the velocity of the particle in the Z coordinate.
	 */
	public double getVz() {
		return vz;
	}

	/**
	 * Use this method to define the magnitude of the acceleration of particle in the X direction.
	 *
	 * @param ax The magnitude of the x component of the acceleration.
	 */
	public void setAx(double ax) {
		this.ax = ax;
	}

	/**
	 * Use this method to query the magnitude of the acceleration of the particle in the X coordinate.
	 */
	public double getAx() {
		return ax;
	}

	/**
	 * Use this method to define the magnitude of the acceleration of particle in the Y direction.
	 *
	 * @param ay The magnitude of the y component of the acceleration.
	 */
	public void setAy(double ay) {
		this.ay = ay;
	}

	/**
	 * Use this method to query the magnitude of the acceleration of the particle in the Y coordinate.
	 */
	public double getAy() {
		return ay;
	}

	/**
	 * Use this method to define the magnitude of the acceleration of particle in the Z direction.
	 *
	 * @param az The magnitude of the z component of the acceleration.
	 */
	public void setAz(double az) {
		this.az = az;
	}
	
	/**
	 * Use this method to query the magnitude of the acceleration of the particle in the Z coordinate.
	 */
	public double getAz() {
		return az;
	}
	
	/**
	 * Use this method to record the max height.
	 *
	 * @param maxheight
	 */
	public void setMaxheight(double maxheight) {
		this.maxheight = maxheight;
	}
	
	/**
	 * Use this method to query the maximum height the particle obtained.
	 */
	public double getMaxheight() {
		return maxheight;
	}
	
}
